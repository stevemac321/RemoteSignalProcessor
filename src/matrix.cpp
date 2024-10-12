#include "common.h"

const size_t NUM_THREADS = std::thread::hardware_concurrency(); // Number of threads


float packet_matrix1[MATRIX_DIM][MATRIX_DIM];
float packet_matrix2[MATRIX_DIM][MATRIX_DIM];
float addition_result[MATRIX_DIM][MATRIX_DIM];
float subtraction_result[MATRIX_DIM][MATRIX_DIM];
float multiplication_result[MATRIX_DIM][MATRIX_DIM];

// controlling function
void perform_matrix_operations()
{
   create_src_matrices_from_packet();
   
   // Addition
   auto addition_start = std::chrono::high_resolution_clock::now();
   matrix_addition();
   auto addition_end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> addition_duration = addition_end - addition_start;

   // Subtraction
   auto subtraction_start = std::chrono::high_resolution_clock::now();
   matrix_subtraction();
   auto subtraction_end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> subtraction_duration = subtraction_end - subtraction_start;

   // Multiplication
   auto multiplication_start = std::chrono::high_resolution_clock::now();
   matrix_multiplication();  // Corrected from matrix_subtraction() to matrix_multiplication()
   auto multiplication_end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> multiplication_duration = multiplication_end - multiplication_start;

   // Display the results with the durations
   display_all_matrix_data(addition_duration, subtraction_duration, multiplication_duration);
}


void create_src_matrices_from_packet() {
    for (int i = 0; i < MATRIX_DIM; i++) {
        for (int j = 0; j < MATRIX_DIM; j++) {
            // Convert packet_array data to float and store in packet_matrix1 and packet_matrix2
            packet_matrix1[i][j] = static_cast<float>(packet_array[i * MATRIX_DIM + j]);
            packet_matrix2[i][j] = static_cast<float>(packet_array[MATRIX_DIM * MATRIX_DIM + i * MATRIX_DIM + j]);
        }
    }
}

void matrix_addition()
{
}
void matrix_subtraction()
{
}
void matrix_multiplication()
{
   threaded_matrix_multiplication(packet_matrix1, packet_matrix1, packet_matrix1);
}

// Multithreaded matrix multiplication using SIMD with raw arrays
// Function to multiply matrices using SIMD and multithreading
void multiply_matrices_simd(float A[MATRIX_DIM][MATRIX_DIM], float B[MATRIX_DIM][MATRIX_DIM], float C[MATRIX_DIM][MATRIX_DIM], 
                            size_t start_row, size_t end_row) 
{
    for (size_t i = start_row; i < end_row; ++i) {
        for (size_t j = 0; j < MATRIX_DIM; ++j) {
            __m256 sum = _mm256_setzero_ps();  // Initialize sum as zero
            for (size_t k = 0; k < MATRIX_DIM; k += 8) {
                // Load 8 elements from row i of A and column j of B
                __m256 a_vals = _mm256_loadu_ps(&A[i][k]);
                __m256 b_vals = _mm256_loadu_ps(&B[k][j]);
                // Multiply and add to sum
                sum = _mm256_add_ps(sum, _mm256_mul_ps(a_vals, b_vals));
            }
            // Sum all 8 floats in the SIMD register and store the result
            float temp[8];
            _mm256_storeu_ps(temp, sum);
            C[i][j] = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7];
        }
    }
}

// Multithreaded matrix multiplication using SIMD
void threaded_matrix_multiplication(float A[MATRIX_DIM][MATRIX_DIM], float B[MATRIX_DIM][MATRIX_DIM], 
                                                                     float C[MATRIX_DIM][MATRIX_DIM]) 
{
    std::vector<std::thread> threads;
    size_t rows_per_thread = MATRIX_DIM / NUM_THREADS;

    for (size_t t = 0; t < NUM_THREADS; ++t) {
        size_t start_row = t * rows_per_thread;
        size_t end_row = (t == NUM_THREADS - 1) ? MATRIX_DIM : start_row + rows_per_thread;
        threads.push_back(std::thread(multiply_matrices_simd, A, B, C, start_row, end_row));
    }

    for (auto& thread : threads) {
        thread.join();  // Wait for all threads to finish
    }
}


