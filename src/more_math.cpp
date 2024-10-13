#include "common.h"
/*
# Fourier Series Formula:
The general form of a Fourier series is:

    f(x) = a_0 + Σ [n=1 to N] (a_n * cos(nx) + b_n * sin(nx))

Where:
- a_0 is the mean (DC component),
- a_n and b_n are Fourier coefficients for cosine and sine terms, respectively,
- N is the number of harmonic components you want to sum over,
- cos(nx) and sin(nx) represent the harmonic functions.

# Fourier Coefficients and FFT Data:
When using FFT data for the Fourier series approximation:
- The real part of the FFT data corresponds to the cosine coefficients (a_n).
- The imaginary part of the FFT data corresponds to the sine coefficients (b_n).

# Fourier Series Approximation:
The Fourier series reconstructs the signal using harmonic components by summing them as follows:

    f(x) ≈ a_0 + Σ [n=1 to N] (a_n * cos(nx) + b_n * sin(nx))

Where:
- a_0 is the average (DC component).
- a_n and b_n are the Fourier coefficients for the nth harmonic.

# Reconstructing the Signal:
To approximate the signal using the first N harmonic components, the Fourier series sums up these harmonic contributions:

    f(x) = a_0 + Σ [n=1 to N] (a_n * cos(n * t) + b_n * sin(n * t))

Where `t` is the time value (normalized over the range [0, 2π]).

*/
void more_math() {
   size_t harmonics_count = 10;  // Number of harmonics to include in the approximation
   size_t signal_length = 100;   // Number of points in the signal

   std::vector<float> approx_signal = fourier_series_approximation(save_fft, harmonics_count, signal_length);

   // Use windows[0] for Fourier series approximation display
   display_fourier_approximation(windows[0], approx_signal);
   polynomial_multiplication_using_save_fft();
}


// Fourier series approximation using FFT data
std::vector<float> fourier_series_approximation(const std::vector<std::complex<float>>& fft_data, 
                                                    size_t harmonics_count, size_t signal_length) 
{
    std::vector<float> reconstructed_signal(signal_length, 0.0f);
    float a0 = fft_data[0].real() / signal_length;  // DC component

    // Loop through harmonics and sum them
    for (size_t n = 1; n <= harmonics_count; ++n) {
        float an = fft_data[n].real() / signal_length;  // Cosine coefficient (real part)
        float bn = fft_data[n].imag() / signal_length;  // Sine coefficient (imaginary part)

        for (size_t i = 0; i < signal_length; ++i) {
            float t = static_cast<float>(i) / signal_length * 2.0f * M_PI;  // Normalized time value
            reconstructed_signal[i] += an * cos(n * t) + bn * sin(n * t);  // Add harmonic components
        }
    }

    // Add the DC component to the reconstructed signal
    for (size_t i = 0; i < signal_length; ++i) {
        reconstructed_signal[i] += a0;
    }

    return reconstructed_signal;
}


void display_fourier_approximation(WINDOW* win, const std::vector<float>& reconstructed_signal) 
{
    int win_height, win_width;
    getmaxyx(win, win_height, win_width);

    // Find the max and min values to scale the graph
    float max_value = *std::max_element(reconstructed_signal.begin(), reconstructed_signal.end());
    float min_value = *std::min_element(reconstructed_signal.begin(), reconstructed_signal.end());

    werase(win);
    box(win, 0, 0);

    for (size_t i = 0; i < reconstructed_signal.size() && i < win_width - 1; ++i) {
        // Normalize the reconstructed signal to fit window height
        int y_position = static_cast<int>((reconstructed_signal[i] - min_value) / (max_value - min_value) * (win_height - 2));
        mvwprintw(win, win_height - y_position - 1, i + 1, "*");
    }
    mvwprintw(win, 1, 100, "Fast Fourier Series Approximation");
    wrefresh(win);
}

// Function to multiply two sets of FFT results directly
std::vector<std::complex<float>> polynomial_multiply_fft(const std::vector<std::complex<float>>& fft1, const std::vector<std::complex<float>>& fft2)
{
    size_t n = std::min(fft1.size(), fft2.size());  // Ensure both FFTs have the same size
    std::vector<std::complex<float>> result(n);

    // Perform element-wise multiplication in the frequency domain
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = fft1[i] * fft2[i];  // Multiply corresponding FFT components
    }

    return result;  // The result is still in the frequency domain
}

 /*
Polynomial multiplication using FFT leverages the frequency domain to efficiently compute
the product of two polynomials. Here's the general idea:

1. **Polynomials Representation**:
   Two polynomials, A(x) and B(x), of degree n can be represented as:

   A(x) = a0 + a1 * x + a2 * x^2 + ... + an * x^n
   B(x) = b0 + b1 * x + b2 * x^2 + ... + bn * x^n

2. **Step-by-Step Process**:
   - **Convert Polynomials to Frequency Domain**: Use the FFT to transform the coefficient vectors
     of both polynomials into the frequency domain.
   - **Element-wise Multiplication**: Multiply the corresponding frequency components of the transformed polynomials.
   - **Inverse FFT**: Apply the inverse FFT to convert the result back to the time domain (coefficient space).
     This gives you the coefficients of the product polynomial.

3. **Mathematically**:
   Suppose we have two polynomials:
   A(x) = a0 + a1 * x + a2 * x^2
   B(x) = b0 + b1 * x + b2 * x^2

   Their product can be computed as:
   C(x) = A(x) * B(x) = (a0 + a1 * x + a2 * x^2) * (b0 + b1 * x + b2 * x^2)

   Using FFT, the process becomes:
   - Compute FFT(A) and FFT(B).
   - Multiply corresponding elements of FFT(A) and FFT(B).
   - Apply inverse FFT to obtain the coefficients of the product polynomial C(x).

4. **Efficiency**:
   Instead of multiplying each term directly (which would take O(n^2) time for n-degree polynomials),
   FFT allows polynomial multiplication in O(n log n) time, making it much faster for large polynomials.
*/

// Example usage with save_fft, displaying the result in windows[0]
void polynomial_multiplication_using_save_fft()
{
    std::vector<std::complex<float>> result = polynomial_multiply_fft(save_fft, save_fft);  // Multiply save_fft by itself

    // Display the result in windows[0]
    display_polynomial_multiplication_result(windows[1], result);
}
// Display the polynomial multiplication result in an ncurses window
void display_polynomial_multiplication_result(WINDOW* win, const std::vector<std::complex<float>>& result)
{
    werase(win);  // Clear the window

    mvwprintw(win, 1, 100, "Polynomial Multiplication Result:");
    size_t row = 2;  // Start printing from the second row

    for (size_t i = 0; i < result.size(); ++i)
    {
        mvwprintw(win, row, 1, "Result[%zu] = %.2f + %.2fi", i, result[i].real(), result[i].imag());
        row++;
    }

    wrefresh(win);  // Refresh the window to display the results
}
