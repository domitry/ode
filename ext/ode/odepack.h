void lsoda_(void (*f)(int*, double*, double*, double*), int *neq, double *y, double *t, double *tout, int *itol, double *rtol, double *atol, int *itask, int *istate, int *iopt, double *rwork, int *lrw, int *iwork, int *liw, int (*jac)(int*, double*, double*, int*, int*,  double*, int*), int *jt);

  /*int itol = 2; // indicator for error control
  double rtol = 1e-4; // relative error tolerance parameter (scalar or array)
  double atol[3] = {1e-6, 1e-10, 1e-6}; // absolute error tolerance parameter  (scalar or array)
  */
