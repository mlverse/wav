path <- test_path("resources/test-audio.wav")

bench::mark(
  audio::load.wave(path),
  tuneR::readWave(path),
  wav::read_wav(path),
  check = FALSE,
  min_time = 2
)

v_for_wav <- wav::read_wav(path)
v_for_audio <- audio::audioSample(v_for_wav, bits = 32)
v_for_tuneR <- tuneR::Wave(t(v_for_wav), samp.rate = 44100, pcm = FALSE, bit = 32)

bench::mark(
  audio::save.wave(v_for_audio, tempfile()),
  tuneR::writeWave(v_for_tuneR, tempfile()),
  wav::write_wav(v_for_wav, tempfile(), ),
  check = FALSE,
  min_time = 2
)

