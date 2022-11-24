#include <Rcpp.h>
#define DR_WAV_IMPLEMENTATION
#include "dr_libs/dr_wav.h"
using namespace Rcpp;

// [[Rcpp::export]]
NumericMatrix read_wav_dr (const std::string& path) {
  drwav wav;
  if (!drwav_init_file(&wav, path.c_str(), NULL)) {
    stop("Error reading file with path '%s'", path);
  }

  auto n_samples = wav.totalPCMFrameCount;
  auto n_channels = wav.channels;

  auto buffer = std::vector<float>(n_channels*n_samples);
  size_t actually_decoded = drwav_read_pcm_frames_f32(&wav, n_samples, &buffer[0]);
  drwav_uninit(&wav);

  if (actually_decoded != n_samples) {
    stop("Malformed file. Reported size is %i but could only read %i", n_samples, actually_decoded);
  }

  auto res = NumericMatrix(n_channels, n_samples, buffer.begin());

  res.attr("sample_rate") = wav.sampleRate;
  res.attr("bit_depth") = wav.bitsPerSample;
  return res;
}

template<typename T>
T int_to (int v, bool normalize) {
  if (normalize) {
    return ((double)v/std::numeric_limits<int>::max())*std::numeric_limits<T>::max();
  }

  return v;
}

template<>
uint8_t int_to (int v, bool normalize) {
  // 8 bit audio are actually unsigned ints thus we need to specialize here so
  // we correctly create values in (0, 255) range.
  if (normalize) {
    return (((double)v/std::numeric_limits<int>::max())+1)/2*255;
  }

  return v;
}

template<typename T>
std::vector<T> make_buffer (IntegerMatrix x, bool normalize) {
  auto buffer = std::vector<T>(x.size());
  std::transform(x.begin(), x.end(), buffer.begin(), [&normalize](int v) {
    return int_to<T>(v, normalize);
  });
  return buffer;
}

// [[Rcpp::export]]
bool write_wav_int (const IntegerMatrix& x, const std::string& path, int sample_rate = 44100,
                   int bit_depth = 16, bool normalize = true) {

  drwav_data_format format;

  format.container = drwav_container_riff;
  format.format = DR_WAVE_FORMAT_PCM;
  format.channels = x.nrow();
  format.sampleRate = sample_rate;
  format.bitsPerSample = bit_depth;

  drwav wav;
  drwav_init_file_write(&wav, path.c_str(), &format, NULL);

  if (bit_depth == 8) {
    // bit_depth 8 should actually be a unsigned int.
    drwav_write_pcm_frames(&wav, x.ncol(), &make_buffer<uint8_t>(x, normalize)[0]);
  }
  else if (bit_depth == 16) {
    drwav_write_pcm_frames(&wav, x.ncol(), &make_buffer<int16_t>(x, normalize)[0]);
  }
  else if (bit_depth == 32) {
    drwav_write_pcm_frames(&wav, x.ncol(), x.begin());
  }
  else {
    drwav_uninit(&wav);
    Rcpp::stop("Can't write file with bit_depth %i", bit_depth);
  }

  drwav_uninit(&wav);
  return true;
}

// [[Rcpp::export]]
bool write_wav_dbl (const NumericMatrix& x, const std::string& path, int sample_rate = 44100,
                    int bit_depth = 32) {
  drwav_data_format format;

  format.container = drwav_container_riff;
  format.format = DR_WAVE_FORMAT_IEEE_FLOAT;
  format.channels = x.nrow();
  format.sampleRate = sample_rate;
  format.bitsPerSample = bit_depth;

  drwav wav;
  drwav_init_file_write(&wav, path.c_str(), &format, NULL);

  if (bit_depth == 32) {
    auto buffer = std::vector<float>(x.begin(), x.end());
    drwav_write_pcm_frames(&wav, x.ncol(), &buffer[0]);
  }
  else if (bit_depth == 64) {
    drwav_write_pcm_frames(&wav, x.ncol(), x.begin());
  }
  else {
    drwav_uninit(&wav);
    Rcpp::stop("Can't write file with bit_depth %i", bit_depth);
  }

  drwav_uninit(&wav);
  return true;
}
