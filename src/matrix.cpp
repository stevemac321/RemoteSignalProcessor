
#include "common.h"

const size_t NUM_THREADS = std::thread::hardware_concurrency(); // Number of threads

uint8_t packet_matrix1[MATRIX_DIM][MATRIX_DIM];
uint8_t packet_matrix2[MATRIX_DIM][MATRIX_DIM];
uint8_t addition_result[MATRIX_DIM][MATRIX_DIM];
uint8_t subtraction_result[MATRIX_DIM][MATRIX_DIM];
uint8_t multiplication_result[MATRIX_DIM][MATRIX_DIM];


// controlling function
void perform_matrix_operations()
{
   create_src_matrices_from_packet();
   
   // Addition
   auto addition_start = std::chrono::high_resolution_clock::now();
   matrix_addition(packet_matrix1, packet_matrix2, addition_result);
   auto addition_end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> addition_duration = addition_end - addition_start;

   // Subtraction
   auto subtraction_start = std::chrono::high_resolution_clock::now();
   matrix_subtraction(packet_matrix1, packet_matrix2, subtraction_result);
   auto subtraction_end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> subtraction_duration = subtraction_end - subtraction_start;

   // Multiplication
   auto multiplication_start = std::chrono::high_resolution_clock::now();
   matrix_multiplication();  
   auto multiplication_end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> multiplication_duration = multiplication_end - multiplication_start;

   // Display the results with the durations
   display_all_matrix_data(addition_duration, subtraction_duration, multiplication_duration);
}

void create_src_matrices_from_packet() {
    int index = 0;

    // First 8x8 matrix
    for (int i = 0; i < MATRIX_DIM; i++) {
        for (int j = 0; j < MATRIX_DIM; j++) {
            packet_matrix1[i][j] = packet_array[index];
            index++;
        }
    }

    // Second 8x8 matrix
    for (int i = 0; i < MATRIX_DIM; i++) {
        for (int j = 0; j < MATRIX_DIM; j++) {
            packet_matrix2[i][j] = packet_array[index];
            index++;
        }
    }
}

void matrix_addition(uint8_t A[MATRIX_DIM][MATRIX_DIM], uint8_t B[MATRIX_DIM][MATRIX_DIM], 
                                                        uint8_t C[MATRIX_DIM][MATRIX_DIM]) 
{
    for (size_t i = 0; i < MATRIX_DIM; ++i) {
        for (size_t j = 0; j < MATRIX_DIM; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void matrix_subtraction(uint8_t A[MATRIX_DIM][MATRIX_DIM], uint8_t B[MATRIX_DIM][MATRIX_DIM], 
                                                            uint8_t C[MATRIX_DIM][MATRIX_DIM]) 
{
    for (size_t i = 0; i < MATRIX_DIM; ++i) {
        for (size_t j = 0; j < MATRIX_DIM; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void matrix_multiplication()
{
   threaded_matrix_multiplication(packet_matrix1, packet_matrix2, multiplication_result);
}

// Multithreaded matrix multiplication using SIMD with raw arrays
// Function to multiply matrices using SIMD and multithreading
void multiply_matrices(uint8_t A[MATRIX_DIM][MATRIX_DIM], uint8_t B[MATRIX_DIM][MATRIX_DIM], 
                       uint8_t C[MATRIX_DIM][MATRIX_DIM], size_t start_row, size_t end_row) {
    for (size_t i = start_row; i < end_row; ++i) {
        for (size_t j = 0; j < MATRIX_DIM; ++j) {
            uint8_t sum = 0; // Initialize sum as zero
            for (size_t k = 0; k < MATRIX_DIM; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

void threaded_matrix_multiplication(uint8_t A[MATRIX_DIM][MATRIX_DIM], uint8_t B[MATRIX_DIM][MATRIX_DIM], 
                                    uint8_t C[MATRIX_DIM][MATRIX_DIM]) {
    std::vector<std::thread> threads;
    size_t rows_per_thread = MATRIX_DIM / NUM_THREADS;

    for (size_t t = 0; t < NUM_THREADS; ++t) {
        size_t start_row = t * rows_per_thread;
        size_t end_row = (t == NUM_THREADS - 1) ? MATRIX_DIM : start_row + rows_per_thread;
        threads.push_back(std::thread(multiply_matrices, A, B, C, start_row, end_row));
    }

    for (auto& thread : threads) {
        thread.join();  // Wait for all threads to finish
    }
}
