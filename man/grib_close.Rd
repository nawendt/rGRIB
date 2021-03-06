% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/grib_close.R
\name{grib_close}
\alias{grib_close}
\title{Close GRIB files}
\usage{
grib_close(gribObj)
}
\arguments{
\item{gribObj}{\code{GRIB} class object.}
}
\description{
\code{grib_close} closes a GRIB file and frees it from memory.
}
\details{
\code{grib_close} checks to see if the GRIB object is open before closing it.
No formal return value is given with this function. Only feedback is a short
message inidicating success or failure.
}
\examples{
g <- grib_open(system.file("extdata", "lfpw.grib1", package = "gribr"))
# ...do some analysis...
grib_close(g)
g # check status
}
\seealso{
\code{\link{grib_open}}
}
