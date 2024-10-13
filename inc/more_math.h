#ifndef MORE_MATH_H
#define MORE_MATH_H
#include <ncurses.h>
#include <vector>
#include <complex>
#include <algorithm>

extern WINDOW *windows[];
extern std::vector<std::complex<float>> save_fft;

void more_math();
std::vector<float> fourier_series_approximation(const std::vector<std::complex<float>>& fft_data, 
                                                    size_t harmonics_count, size_t signal_length);
void display_fourier_approximation(WINDOW* win, const std::vector<float>& reconstructed_signal);
// Function to multiply two sets of FFT results directly
std::vector<std::complex<float>> polynomial_multiply_fft(const std::vector<std::complex<float>>& fft1, 
                                                         const std::vector<std::complex<float>>& fft2);

// Display the polynomial multiplication result in an ncurses window
void display_polynomial_multiplication_result(WINDOW* win, const std::vector<std::complex<float>>& result);
void polynomial_multiplication_using_save_fft();

#endif