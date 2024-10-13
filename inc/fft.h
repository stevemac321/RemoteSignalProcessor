#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex>
#include <queue>
#include <numeric> 
    // FFT
std::complex<float> complex_multiply(std::complex<float> a, std::complex<float> b);
std::complex<float> complex_add(std::complex<float> a, std::complex<float> b);
std::complex<float> complex_subtract(std::complex<float> a, std::complex<float> b);
void FFT(std::vector<std::complex<float>> &x, const size_t size);
std::vector<std::complex<float>> prepare_complex_fft(const float float_array[], const size_t size);
void normalize_signal(std::vector<std::complex<float>> &signal);

// FFT to magnitudes
std::vector<float> convert_to_magnitudes(const std::vector<std::complex<float>> &fft_results);
// Magnitudes to pqueue
std::priority_queue<float> pqueue_from_magnitudes(const std::vector<float> &magnitude_array, const size_t size);

#endif