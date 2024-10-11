#include "common.h"

const float PI = 3.14159265358979323846f;

std::complex<float> complex_multiply(std::complex<float> a, std::complex<float> b) {
    std::complex<float> result;
    result = std::complex<float>((a.real() * b.real()) - (a.imag() * b.imag()), 
                                 (a.real() * b.imag()) + (a.imag() * b.real()));
    return result;
}

std::complex<float> complex_add(std::complex<float> a, std::complex<float> b) {
    std::complex<float> result;
    result = std::complex<float>(a.real() + b.real(), a.imag() + b.imag());
    return result;
}

std::complex<float> complex_subtract(std::complex<float> a, std::complex<float> b) {
    std::complex<float> result;
    result = std::complex<float>(a.real() - b.real(), a.imag() - b.imag());
    return result;
}

// Recursive FFT function
// Recursive FFT function
void FFT(std::vector<std::complex<float>> &x, const size_t size) {
    if (size <= 1) return;

    // Divide the array into two halves
    std::vector<std::complex<float>> even(size / 2);
    std::vector<std::complex<float>> odd(size / 2);

    for (size_t i = 0; i < size / 2; i++) {
        even[i] = x[i * 2];
        odd[i] = x[i * 2 + 1];
    }

    // Recursive FFT on both halves
    FFT(even, size / 2);
    FFT(odd, size / 2);

    // Combine
    for (size_t k = 0; k < size / 2; k++) {
        // Create twiddle factor using std::polar
        std::complex<float> twiddle = std::polar(1.0f, -2 * PI * k / size) * odd[k];
        x[k] = even[k] + twiddle;
        x[k + size / 2] = even[k] - twiddle;
    }
}
// Normalize the signal before FFT
void normalize_signal(std::vector<std::complex<float>> &signal) {
    // Calculate the mean value of the real part of the signal
    float mean = std::accumulate(signal.begin(), signal.end(), 0.0f, 
                                 [](float sum, std::complex<float> val) { return sum + val.real(); }) / signal.size();
    
    // Subtract the mean from each sample to center the signal around zero
    for (auto &sample : signal) {
        sample.real(sample.real() - mean);
    }
}
std::vector<std::complex<float>> prepare_complex_fft(const float float_array[], const size_t size)
{
   std::vector<std::complex<float>> result(size);
   for(size_t i=0; i < size; i++) {
      result[i] = std::complex<float>(float_array[i], 0.0f);
   }
   return result;
}
/*
 The magnitude of a complex number 𝑧 = 𝑎 +𝑏𝑖
   z=a+bi is calculated as:

Magnitude = (radical sign over)a^2 + b^2
 */
// Function to convert complex FFT results to magnitudes and return a float vector
std::vector<float> convert_to_magnitudes(const std::vector<std::complex<float>> &fft_results) {
    std::vector<float> magnitude_array;

    for (const auto& result : fft_results) {
        // Calculate magnitude and store it in the float array
        magnitude_array.push_back(std::abs(result));
    }

    return magnitude_array;  // RVO or move semantics will optimize this return
}
std::priority_queue<float> pqueue_from_magnitudes(const std::vector<float> &magnitude_array, const size_t size) {
    // Define a priority queue with greater comparator to maintain a min-heap
    std::priority_queue<float> pq;

    // Add all elements up to the specified size into the priority queue
    for (size_t i = 0; i < size; i++) {
        pq.push(magnitude_array[i]);
    }

    return pq;  // Return the populated priority queue
}
