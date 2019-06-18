#include <R.h>
#include <Rinternals.h>

#include "gribr.h"

SEXP gribr_grib_nearest(SEXP gribr_fileHandle, SEXP lat, SEXP lon) {
  FILE *file = NULL;
  codes_handle *h = NULL;

  file = R_ExternalPtrAddr(gribr_fileHandle);
  if (file == NULL) {
    error("gribr: grib file not opened");
  }

  /* Make sure it is rewound */
  grewind(file);

  if (is_multi) {
    codes_grib_multi_support_on(DEFAULT_CONTEXT);
  }

  return 0;
};
