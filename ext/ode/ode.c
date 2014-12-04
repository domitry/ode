#include "odepack.h"
#include <stdlib.h>
#include <ruby.h>
#include <stdio.h>

static int number_of_params;
static VALUE func_proc, jac_proc, f_args;

#define RESTORE_NEQ(neq) number_of_params=neq;
#define RESTORE_FUNC(func) func_proc=func;
#define RESTORE_JAC(func) jac_proc=func;
#define RESTORE_FARGS(args) f_args=args;
#define max(v1, v2) (v1 < v2 ? v2 : v1)
#define min(v1, v2) (v1 < v2 ? v1 : v2)

int ode_jacobian_function(int *n, double *t, double *y, int *ml, int *mu, double *pd, int *nrowpd){
  return -1;
}

void ode_function(int *n, double *t, double *y, double *ydot){
  VALUE y_arr = rb_ary_new2(number_of_params), ret;
  int i;

  for(i=0; i<number_of_params; i++)
    rb_ary_store(y_arr, i, y[i]);
  
  ret = rb_funcall(func_proc, rb_intern("call"), 3, DBL2NUM(*t), y_arr, f_args);

  for(i=0; i<number_of_params; i++){
    VALUE num = rb_ary_entry(ret, i);
    ydot[i] = NUM2DBL(num);
  }
}

VALUE excute_lsoda(VALUE t_out, VALUE func, VALUE jac, VALUE init_t, VALUE init_y, VALUE fargs, VALUE opts){
  int itol; double rtol, atol;
  int *iwork; double *rwork;
  int lrw, liw;
  int neq = RARRAY_LEN(init_y);

  double *y = (double *)ALLOC_N(double, neq);
  double t = NUM2DBL(init_t);
  double tout = NUM2DBL(t_out);

  int itask = 1;  // run solver untill t == tout
  int istate = 1; // this is the first call of the problem
  int iopt = 0;   // no optional inputs

  int jt = 2;     // jacobian type indicator. 1: user provides full jacobian. 2: interanally generated jacobian.
  VALUE ret_arr = rb_ary_new2(neq);
  int i;

  RESTORE_NEQ(neq)
  RESTORE_FUNC(func)
  RESTORE_FARGS(fargs)

  for(i=0; i<neq; i++){
    y[i] = NUM2DBL(rb_ary_entry(init_y, i));
  }

  // parse options (TODO: accept array)
  itol = NUM2INT(rb_hash_aref(opts, rb_intern("itol")));
  rtol = NUM2DBL(rb_hash_aref(opts, rb_intern("rtol")));
  atol = NUM2DBL(rb_hash_aref(opts, rb_intern("atol")));

  // decide lrw, liw
  liw = 20;
  iwork = (int *)ALLOC_N(int, liw);

  if(jac != Qnil){
    jt = 1;
    RESTORE_JAC(jac);
    lrw = max(20+16*neq, 22+9*neq+neq*neq);
  }
  else{
    int ml=0, mu=0; VALUE val;
    if(val = rb_hash_aref(opts, rb_intern("ml")) == Qnil)ml = NUM2INT(val);
    if(val = rb_hash_aref(opts, rb_intern("mu")) == Qnil)mu = NUM2INT(val);

    iwork[0] = mu;
    iwork[1] = ml;
    lrw = max(20+16*neq, 22+10*neq+(2*ml+mu)*neq);
  }

  rwork = (double *)ALLOC_N(double, lrw);
  

  // run lsoda
  lsoda_(ode_function, &neq, y, &t, &tout, &itol, &rtol, &atol, &itask, &istate, &iopt, rwork, &lrw, iwork, &liw, ode_jacobian_function, &jt);

  // check error
  if(istate<0){
    rb_raise(rb_eTypeError, "Something went wrong.");
  }

  for(i=0; i<neq; i++){
    VALUE num = DBL2NUM(y[i]);
    rb_ary_store(ret_arr, i, num);
  }

  xfree(y);
  xfree(iwork);
  xfree(rwork);
  return ret_arr;
}


void Init_ode(){
  VALUE ode = rb_define_module("Ode");
  VALUE methods = rb_define_module_under(ode, "Methods");

  rb_define_singleton_method(methods, "lsoda", excute_lsoda, 7);
}
