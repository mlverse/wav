#' Read/write wav files
#'
#' Efficiently read and write [WAV files](https://en.wikipedia.org/wiki/WAV).
#'
#' @param path Path to file that will be read or written to.
#' @param x Numeric matrix with dimensions `[n_channels, n_samples]`. Values in
#'  the matrix should be `<double>` in the range `[-1, 1]` or integers in the range
#'  `[-.Machine$integer.max, .Machine$integer.max]` ie. 32 bits signed integers
#'  like R integers containing the amplitudes. Depending on the value of `normalize`
#'  and the `bit_depth` you can use different ranges.
#' @param sample_rate Sample rate in Hz of the associated samples.
#' @param bit_depth Bit depth of associated samples. This only affects the precision
#'   data is saved to the file.
#' @param normalize Boolean idicating wheter integers should be normalized before
#'   writing. Only used when [write_wav()] is called with a integer matrix.
#'   For example when you write a sample with a amplitude value of `2147483647`
#'   and `bit_depth = 8`, you would need to normalize this integer so it
#'   actually refers to the maximum unsigned int available (i.e. `255`).
#'   You can avoid normalizing when the amplitudes are already in the correct integer
#'   range for the `bit_depth` you are saving, in this case provide `normalize = FALSE`.
#' @param ... Currently unused.
#'
#'
#' @returns
#' - When reading: A numeric matrix with samples. It also contains the attributes `sample_rate`
#'   and `bit_depth`.
#' - When writing: A boolean which is `TRUE` if writing was sucessful and `FALSE`
#'   otherwise.
#'
#' @examples
#' x <- matrix(sin(440 * seq(0, 2*pi, length = 44100)), nrow=1)
#' tmp <- tempfile(fileext = ".wav")
#' write_wav(x, tmp)
#' y <- read_wav(tmp)
#' all.equal(as.numeric(x), as.numeric(y), tolerance = 1e-7)
#'
#' @export
read_wav <- function(path) {
  read_wav_dr(path.expand(path))
}

#' @describeIn read_wav Write a wav file.
#' @export
write_wav <- function(x, path, sample_rate = 44100, bit_depth = 32, ..., normalize = TRUE) {
  if (length(list(...)) > 0)
    stop("... shouldn't be used. Maybe you have a typo in the argument name?")

  if (nrow(x) > 65535) {
    stop("Number of channels exceeded. Maximum is ", 65535, " got ", nrow(x))
  }

  if (is.integer(x)) {
    write_wav_int(x, path, sample_rate = sample_rate, bit_depth, normalize)
  } else if (is.double(x)) {

    if (any(x < -1) || any(x > 1)) {
      stop("When inputs is numeric, amplitudes should be in the range [-1,1].")
    }

    write_wav_dbl(x, path, sample_rate = sample_rate, bit_depth)
  } else {
    stop("Only integers and double matrices are supported.")
  }
}
