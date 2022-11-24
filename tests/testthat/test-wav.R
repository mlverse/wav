test_that("Can read a file", {
  x <- read_wav(test_path("resources/test-audio.wav"))

  temp <- tempfile()
  y <- write_wav(x, temp, bit_depth = 32)

  expect_true(y)

  x2 <- read_wav(temp)

  expect_equal(as.numeric(x), as.numeric(x2))
})

patrick::with_parameters_test_that("Can write from double with multiple bit_depth's:", {
    x <- read_wav(test_path("resources/test-audio.wav"))
    temp <- tempfile()
    y <- write_wav(x, temp, bit_depth = bit_depth)
    expect_true(y)
    x2 <- read_wav(temp)
    expect_equal(as.numeric(x), as.numeric(x2))
  },
  bit_depth = c(32, 64)
)

patrick::with_parameters_test_that("Can write from ints with multiple depths:", {
    x <- read_wav(test_path("resources/test-audio.wav"))
    int_x <- matrix(as.integer(x*.Machine$integer.max), nrow = 2)

    temp <- tempfile()
    y <- write_wav(int_x, temp, bit_depth = bit_depth)
    expect_true(y)
    x2 <- read_wav(temp)

    # this is a way of computing machine precision given the number of bits.
    # it's inspited by https://en.wikipedia.org/wiki/Machine_epsilon#cite_note-2
    expect_true(max(as.numeric(x) - as.numeric(x2)) <= 10^(-log10(2^bit_depth) + 1))
  },
  bit_depth = c(8, 16, 32)
)

test_that("can use normalize for uint8", {
  x <- read_wav(test_path("resources/test-audio.wav"))
  int_x <- matrix(as.integer(trunc((x+1)/2*255)), nrow = 2)

  temp <- tempfile()
  y <- write_wav(int_x, temp, bit_depth = 8, normalize = FALSE)

  expect_true(y)
  x2 <- read_wav(temp)

  expect_true(max(as.numeric(x) - as.numeric(x2)) <= 10^(-log10(2^8) + 1))
})

test_that("can use normalize for int16", {
  x <- read_wav(test_path("resources/test-audio.wav"))
  int_x <- matrix(as.integer(trunc((x * (2^16/2-1)))), nrow = 2)

  temp <- tempfile()
  y <- write_wav(int_x, temp, bit_depth = 16, normalize = FALSE)

  expect_true(y)
  x2 <- read_wav(temp)

  expect_true(max(as.numeric(x) - as.numeric(x2)) <= 10^(-log10(2^16) + 1))
})

test_that("errors on writing", {
  temp <- tempfile()

  expect_error(
    write_wav(matrix("a", nrow = 2, ncol = 1000), path = temp),
    regexp = "Only integers"
  )

  expect_error(
    write_wav(matrix(0, nrow = 6555555, ncol = 2), path = temp),
    regexp = "Number of channels"
  )

  expect_error(
    write_wav(matrix(0, nrow = 2, ncol = 1000), path = temp, bit_depth = 24),
    regexp = "Can't write file with"
  )

  expect_error(
    write_wav(matrix(0, nrow = 2, ncol = 1000), path = temp, bit_depth = 24),
    regexp = "Can't write file with"
  )

  expect_error(
    write_wav(matrix(0L, nrow = 2, ncol = 1000), path = temp, bit_depth = 24),
    regexp = "Can't write file with"
  )

  expect_error(
    write_wav(array(0L, dim = c(1, 2, 100)), path = temp, bit_depth = 24),
    regexp = "Not a matrix"
  )

  expect_error(
    write_wav(matrix(2, nrow = 2, ncol = 1000), path = temp, bit_depth = 32),
    regexp = "range"
  )

})
