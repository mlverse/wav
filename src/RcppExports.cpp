// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// read_wav_dr
NumericMatrix read_wav_dr(const std::string& path);
RcppExport SEXP _wav_read_wav_dr(SEXP pathSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type path(pathSEXP);
    rcpp_result_gen = Rcpp::wrap(read_wav_dr(path));
    return rcpp_result_gen;
END_RCPP
}
// write_wav_int
bool write_wav_int(const IntegerMatrix& x, const std::string& path, int sample_rate, int bit_depth);
RcppExport SEXP _wav_write_wav_int(SEXP xSEXP, SEXP pathSEXP, SEXP sample_rateSEXP, SEXP bit_depthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IntegerMatrix& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type path(pathSEXP);
    Rcpp::traits::input_parameter< int >::type sample_rate(sample_rateSEXP);
    Rcpp::traits::input_parameter< int >::type bit_depth(bit_depthSEXP);
    rcpp_result_gen = Rcpp::wrap(write_wav_int(x, path, sample_rate, bit_depth));
    return rcpp_result_gen;
END_RCPP
}
// write_wav_dbl
bool write_wav_dbl(const NumericMatrix& x, const std::string& path, int sample_rate, int bit_depth);
RcppExport SEXP _wav_write_wav_dbl(SEXP xSEXP, SEXP pathSEXP, SEXP sample_rateSEXP, SEXP bit_depthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const NumericMatrix& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type path(pathSEXP);
    Rcpp::traits::input_parameter< int >::type sample_rate(sample_rateSEXP);
    Rcpp::traits::input_parameter< int >::type bit_depth(bit_depthSEXP);
    rcpp_result_gen = Rcpp::wrap(write_wav_dbl(x, path, sample_rate, bit_depth));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_wav_read_wav_dr", (DL_FUNC) &_wav_read_wav_dr, 1},
    {"_wav_write_wav_int", (DL_FUNC) &_wav_write_wav_int, 4},
    {"_wav_write_wav_dbl", (DL_FUNC) &_wav_write_wav_dbl, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_wav(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
