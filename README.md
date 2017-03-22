# gribr
GRIB interface for R using the [ECMWF ecCodes package](https://software.ecmwf.int/wiki/display/ECC).

[![Travis-CI Build Status](https://travis-ci.org/nawendt/gribr.svg?branch=master)](https://travis-ci.org/nawendt/gribr)  
[![License](https://img.shields.io/badge/License-BSD%202--Clause-blue.svg)](https://opensource.org/licenses/BSD-2-Clause)  
[![codecov](https://codecov.io/gh/nawendt/gribr/branch/master/graph/badge.svg)](https://codecov.io/gh/nawendt/gribr)

### Purpose
This project was started to address a need to easily read GRIB data into R as has been done in other languages (e.g., Python). Working on this also presents a great opportunity to learn more about R, C, and the interface between the two.

### Status
gribr is functional at this point in time. Several functions exist for reading GRIB messages and extracting them. Functions are also available to help with projecting the data. All of the documentation has been written and some basic examples exist to get you started. I have yet to develop good plotting examples. gribr now works exclusively with ecCodes as all future GRIB API development will occur within that library.

### Installation
**NOTE:** This is not _natively_ available for Windows at this time due to difficulties compiling ecCodes on that platform. See below for details.

1. Prerequisites
  * gribr depends on the ECMWF ecCodes package (>=2.0.0), and the proj4 R package
  * ecCodes can be easily installed via a package manager on Linux (`apt-get`, `yum`, etc.) or MacOS (`port`, `fink`, `brew`). As this library is newer, it may not be widely available yet. However, this would be the recommened option. Since some repositories carry versions that are too old, you may have to install from source.
    * To install from source, download ecCodes [here](https://software.ecmwf.int/wiki/display/ECC/Releases)
2. Set up environment (if necessary)
  * _ecCodes installed in a system location_: The the libraries/headers should be found by the linker/compiler without any additional environmental settings.
  * _ecCodes installed in a non-system/user location_: When ecCodes is installed in a non-system location (i.e., a path that is not in the `ld` search paths), there are some extra steps that need to be taken depending on your use case:
    * _R_: Prior to running `R CMD INSTALL`, set the `ECCODES_LIBS` and `ECCODES_CPPFLAGS` environment variables to the GRIB API library and header directories, respectively. The configure script should pick up on these variables and build the `PKG_LIBS` and `PKG_CPPFLAGS` for gribr appropriately.

    * _RStudio_: RStudio does not grab the envionment variables that you set on the terminal or in your shell login scripts. Instead, use .Renviron. If you do not have this file, create it in your home directory (this is where R searches for it by default). Setting `ECCODES_LIBS` and `ECCODES_CPPFLAGS` will cause RStudio to load them into the session and allow the configure script to use them.
  * __NOTE__: When linking to ecCodes from a non-system location, be sure to include the `ECCODES_LIBS` variable in your `LD_LIBRARY_PATH` (or `DYLD_LIBRARY_PATH` on OSX) environment variable. R will not otherwise be able to load the gribr shared object as it will need to know where the linked GRIB API functions are. I have found that RStudio is quite picky that the `LD_LIBRARY_PATH` is set in a login script. If you have trouble with this with RStudio, make sure it is set at login. One option to avoid setting/altering `LD_LIBRARY_PATH` is to use `-Wl,-rpath=$ECCODES_LIBS` in the compiler flags. I have had some luck with this using `gcc`.
3. Install gribr
  * _From the command line_:
   ```shell
   R CMD INSTALL /path/to/gribr --configure-vars="ECCODES_CPPFLAGS=-I/path/to/eccodes/include ECCODES_LIBS=-L/path/to/eccodes/lib"
   ```
  * _From within R or RStudio_:
   ```R
   install.packages("path/to/cloned/gribr/repo", repos = NULL, configure.vars = c("ECCODES_LIBS=-L/path/to/eccodes/lib", "ECCODES_CPPFLAGS=-I/path/to/eccodes/include"))
   ```
   ```R
   devtools::install_github("nawendt/gribr", args = "--configure-args='ECCODES_LIBS=-L/path/to/eccodes/lib ECCODES_CPPFLAGS=-I/path/to/eccodes/include'")
   ```

### Windows Install Options
While a native Windows ecCodes library that will work with R is not available, there are ways to run gribr on Windows. The first option is to use the [Windows 10 Linux Subsystem](https://msdn.microsoft.com/en-us/commandline/wsl/install_guide). Simply follow the [instructions](https://cran.r-project.org/bin/linux/ubuntu/) to install the latest R as you would on any other Linux system. Any other necessary libraries should be available on the package manager. Build gribr as usual and enjoy using it on Windows.

The second option is to use gribr via [Cygwin](https://cygwin.org/). A Cygwin build of R is available through their package manager. Simply make sure to also install the dev versions of the libraries that you will need. This will likely include libraries that the R package proj4 depends on. You will have to install ecCodes from source for this. From there, install gribr from R CMD INSTALL taking care to include all the correct configure-vars. If you build ecCodes with PNG or JPEG support, you'll need to add the appropriate linker flags.

### Contributing
You are welcome to contribute to this project. At some point in the future I will put together some more formal guidelines so as to keep this project as uniform as possible. For now, simply take advantage of the features of git and github and sumbit pull requests for anything you would like to contribute.

__Current Needs__: While all improvements are welcome, here are a few specific needs:
  * Build GRIB API on Windows to get gribr ported to that platform
  * Plotting wrapper functions to give some quick/easy plotting functionality to the package

#### Contact
[Nathan Wendt](mailto:nathan.wendt@noaa.gov)

