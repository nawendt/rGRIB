.onLoad <- function(libname, pkgname) {
  # Windows will be binary distributions most of the time
  # Need to set ECCODES_DEFINITION_PATH to avoid crash if it
  # is not already set
	if (.Platform$OS.type == "windows") {
		if (Sys.getenv("ECCODES_DEFINITION_PATH") == "") {
			normPath <- normalizePath(system.file("extdata", "definitions",
			                                      package = "gribr"), mustWork = FALSE)
			if (normPath == "") {
			  warning("R was unable to set ECCODES_DEFINITION_PATH. Please set manually.")
			} else {
			  Sys.setenv(ECCODES_DEFINITION_PATH = normPath)
			  Sys.setenv(GRIBR_MOD = 1)
			}
		}
	}
}

.onUnload <- function(libpath) {
	# Clean up if .onLoad made mods to env
	if (.Platform$OS.type == "windows") {
		if (Sys.getenv("GRIBR_MOD") == 1) {
			Sys.unsetenv("ECCODES_DEFINITION_PATH")
			Sys.unsetenv("GRIBR_MOD")
		}
	}

	library.dynam.unload("gribr", libpath)
}
