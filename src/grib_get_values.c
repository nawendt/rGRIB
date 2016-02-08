#include <grib_api.h>

#include <R.h>
#include <Rinternals.h>

#include "rGRIB.h"

SEXP R_grib_get_values(SEXP R_fileHandle) {
  int err;
  long nx,ny;
  R_len_t i;
  size_t values_length;
  SEXP R_values, R_output,R_names;
  double *values, *p_R_values;
  FILE *file = NULL;
  grib_handle *h = NULL;

  file = R_ExternalPtrAddr(R_fileHandle);

  h = grib_handle_new_from_file(DEFAULT_CONTEXT, file, &err);
  err = grib_get_long(h, "Ni", &nx);
  if (err) {
    gerror("unable to get x dim", err);
  }
  err = grib_get_long(h, "Nj", &ny);
  if (err) {
    gerror("unable to get y dim", err);
  }

  /* It will be easier to just deal with a vector instead
   * of trying to coerce to a "matrix" in c */
  values_length = nx*ny;
  R_values = PROTECT(allocVector(REALSXP, values_length));
  values = malloc((values_length)*sizeof(double));
  err = grib_get_double_array(h,"values",values,&values_length);
  if (err) {
    gerror("unable to get values", err);
  }

  /* Copy over the values to the R object;
     Use pointers for speed */
  p_R_values = REAL(R_values);
  for (i = 0; i < values_length; i++) {
    p_R_values[i] =  values[i];
  }
  free(values);

  /* Need to pass out nx, ny to be able to
   * create matrix in R wrapper */
  R_output = PROTECT(allocVector(VECSXP,3));
  SET_VECTOR_ELT(R_output, 0, R_values);
  SET_VECTOR_ELT(R_output, 1, ScalarInteger(nx));
  SET_VECTOR_ELT(R_output, 2, ScalarInteger(ny));

  /* Set names of output list for ease of handling
   * in the R wrapper function */
  R_names = PROTECT(allocVector(STRSXP,3));
  SET_STRING_ELT(R_names, 0, mkChar("values"));
  SET_STRING_ELT(R_names, 1, mkChar("nx"));
  SET_STRING_ELT(R_names, 2, mkChar("ny"));
  namesgets(R_output, R_names);

  UNPROTECT(3);
  return R_output;
}
