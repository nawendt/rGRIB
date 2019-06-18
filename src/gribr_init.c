#include <R_ext/Rdynload.h>
#include <Rconfig.h>
#include <Rinternals.h>

#include "gribr.h"

#define CALLDEF(name, n) {#name, (DL_FUNC) &name, n}

static const R_CallMethodDef callMethods[] = {
  CALLDEF(gribr_grib_open, 1),
  CALLDEF(gribr_grib_close, 1),
  CALLDEF(gribr_grib_list, 4),
  CALLDEF(gribr_grib_df, 4),
  CALLDEF(gribr_grib_length, 1),
  CALLDEF(gribr_is_null_ptr, 1),
  CALLDEF(gribr_is_multi_message, 1),
  CALLDEF(gribr_grib_get_message, 3),
  CALLDEF(gribr_select, 3),
  CALLDEF(gribr_api_version, 0),
  CALLDEF(gribr_redtoreg, 3),
  CALLDEF(gribr_grib_test, 1),
  CALLDEF(gribr_grib_nearest, 3),
  {NULL, NULL, 0}
};

void R_init_gribr(DllInfo *info)
{
  R_registerRoutines(info,
                     NULL,
                     callMethods,
                     NULL,
                     NULL);

  R_useDynamicSymbols(info, FALSE);
  R_forceSymbols(info, TRUE);

  /* Here is where we could export the C routines
   * so that other packages could call them from
   * their C routines.
   *
   * E.g,
   *
   * R_RegisterCCallable("gribr","grib_open",           (DL_FUNC) &gribr_grib_open);
   *
   */

}

