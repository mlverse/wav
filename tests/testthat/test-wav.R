test_that("Can read a file", {
  x <- read_wav(test_path("resources/test-audio.wav"))

  temp <- tempfile()
  y <- write_wav(x, temp, bit_depth = 32)

  expect_true(y)

  x2 <- read_wav(temp)

  expect_equal(as.numeric(x), as.numeric(x2))
})
