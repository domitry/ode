#include "odepack.h"
#include <stdlib.h>
#include <ruby.h>

VALUE Oderb = Qnil;

int ode_jacobian_function(int *n, double *t, double *y, int *ml, int *mu, double *pd, int *nrowpd){
  return -1;
}

void ode_function(int *n, double *t, double *y, double *ydot){
  ydot[0] = -0.04*y[0] + 1e4*y[1]*y[2];
  ydot[2] = 3e7*y[1]*y[1];
  ydot[1] = -ydot[0] - ydot[2];
}

VALUE method_excute_lsoda(VALUE self){
  int neq=3;
  double y[3] = {1, 0, 0};
  double t = 0;
  double tout = 0.4;
  int itol = 2;
  double rtol = 1e-4;
  double atol[3] = {1e-6, 1e-10, 1e-6};
  int itask = 1;
  int istate = 1;
  int iopt = 0;
  int lrw = 70;
  int liw = 23;
  int jt = 2;
  int *iwork = (int*)malloc(sizeof(int)*23);
  double *rwork = (double*)malloc(sizeof(double)*70);
  VALUE result = rb_ary_new();

  lsoda_(ode_function, &neq, y, &t, &tout, &itol, &rtol, atol, &itask, &istate, &iopt, rwork, &lrw, iwork, &liw, ode_jacobian_function, &jt);

  return result;
}

void Init_oderb(){
  Oderb = rb_define_module("Oderb");
  rb_define_method(Oderb, "excute_lsoda", method_excute_lsoda, 0);
}
