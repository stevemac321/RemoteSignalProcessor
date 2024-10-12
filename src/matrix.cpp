
#include "common.h"

#include <iostream>
#include <fstream> // For file handling
#include <iomanip> // For formatting
#include <string>  // For std::string
#include <cstring> // For std::memcpy

const size_t NUM_THREADS = std::thread::hardware_concurrency(); // Number of threads

int64_t packet_matrix1[MATRIX_DIM][MATRIX_DIM];
int64_t packet_matrix2[MATRIX_DIM][MATRIX_DIM];
int64_t addition_result[MATRIX_DIM][MATRIX_DIM];
int64_t subtraction_result[MATRIX_DIM][MATRIX_DIM];
int64_t multiplication_result[MATRIX_DIM][MATRIX_DIM];

#include <chrono>

void perform_matrix_operations()
{
    // Open the file for appending results of each operation
    const std::string filename = "matrix_validation.txt";

    // Create the source matrices from the packet data
    create_src_matrices_from_packet();
   
    // Addition
    auto addition_start = std::chrono::high_resolution_clock::now();
    matrix_addition(packet_matrix1, packet_matrix2, addition_result);
    auto addition_end = std::chrono::high_resolution_clock::now();
    auto addition_duration = std::chrono::duration_cast<std::chrono::microseconds>(addition_end - addition_start); // Microsecond timing

    // Validate addition result
    log_matrix(addition_result, filename, "Addition:");

    // Subtraction
    auto subtraction_start = std::chrono::high_resolution_clock::now();
    matrix_subtraction(packet_matrix1, packet_matrix2, subtraction_result);
    auto subtraction_end = std::chrono::high_resolution_clock::now();
    auto subtraction_duration = 
                            std::chrono::duration_cast<std::chrono::microseconds>(subtraction_end - subtraction_start); 

    // Validate subtraction result
    log_matrix(subtraction_result, filename, "Subtraction:");

    // Multiplication
    auto multiplication_start = std::chrono::high_resolution_clock::now();
    matrix_multiplication();  
    auto multiplication_end = std::chrono::high_resolution_clock::now();
    auto multiplication_duration = 
                    std::chrono::duration_cast<std::chrono::microseconds>(multiplication_end - multiplication_start); 

    // Validate multiplication result
    log_matrix(multiplication_result, filename, "Multiplication:");

    // Display the results with the durations and validation status
    display_all_matrix_data(addition_duration, subtraction_duration, multiplication_duration);
}


// controlling function
void create_src_matrices_from_packet() {
    int index = 0;

    for (int i = 0; i < MATRIX_DIM; i++) {
        for (int j = 0; j < MATRIX_DIM; j++) {
            packet_matrix1[i][j] = packet_array[index];
            index++;
        }
    }

    for (int i = 0; i < MATRIX_DIM; i++) {
        for (int j = 0; j < MATRIX_DIM; j++) {
            packet_matrix2[i][j] = packet_array[index];
            index++;
        }
    }
}

void matrix_addition(int64_t A[MATRIX_DIM][MATRIX_DIM], int64_t B[MATRIX_DIM][MATRIX_DIM], 
                     int64_t C[MATRIX_DIM][MATRIX_DIM])
{
    for (size_t i = 0; i < MATRIX_DIM; ++i) {
        for (size_t j = 0; j < MATRIX_DIM; ++j) {
            int sum = A[i][j] + B[i][j];
            C[i][j] = sum;
        }
    }
}

void matrix_subtraction(int64_t A[MATRIX_DIM][MATRIX_DIM], int64_t B[MATRIX_DIM][MATRIX_DIM], 
                        int64_t C[MATRIX_DIM][MATRIX_DIM])
{
    for (size_t i = 0; i < MATRIX_DIM; ++i) {
        for (size_t j = 0; j < MATRIX_DIM; ++j) {
            int diff = A[i][j] - B[i][j];
            C[i][j] = diff;
        }
    }
}


void matrix_multiplication()
{
  threaded_matrix_multiplication(packet_matrix1, packet_matrix2, multiplication_result);
}
void multiply_matrices_single(int64_t A[MATRIX_DIM][MATRIX_DIM], int64_t B[MATRIX_DIM][MATRIX_DIM], 
                              int64_t C[MATRIX_DIM][MATRIX_DIM])
{
    for (size_t i = 0; i < MATRIX_DIM; ++i) {
        for (size_t j = 0; j < MATRIX_DIM; ++j) {
            int sum = 0;
            for (size_t k = 0; k < MATRIX_DIM; ++k) {
                sum += A[i][k] * B[k][j]; // Perform the dot product
            }
            C[i][j] = sum;
        }
    }
}

void multiply_matrices(int64_t A[MATRIX_DIM][MATRIX_DIM], int64_t B[MATRIX_DIM][MATRIX_DIM], 
                       int64_t C[MATRIX_DIM][MATRIX_DIM], size_t start_row, size_t end_row) {
    for (size_t i = start_row; i < end_row; ++i) {
        for (size_t j = 0; j < MATRIX_DIM; ++j) {
            int64_t sum = 0; // Use 'uint64_t' to handle larger sums
            for (size_t k = 0; k < MATRIX_DIM; ++k) {
                sum += A[i][k] * B[k][j]; // Accumulate the dot product
            }
            C[i][j] = sum; 
        }
    }
}

void threaded_matrix_multiplication(int64_t A[MATRIX_DIM][MATRIX_DIM], int64_t B[MATRIX_DIM][MATRIX_DIM], 
                                    int64_t C[MATRIX_DIM][MATRIX_DIM]) {
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

void log_matrix(int64_t result[MATRIX_DIM][MATRIX_DIM], const std::string& filename, const std::string& mesg) 
{
    // Open the file in append mode
    std::ofstream file(filename, std::ios::app);
    
    // Check if file is open
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Log the provided message
    file << mesg << "\n";
    
    // Print header for matrices
    file << "Matrix 1 vs Matrix 2 vs Result Matrix\n";
    file << "--------------------------------------------\n";

    // Log packet_matrix1, packet_matrix2, and the result matrix side by side
    for (int i = 0; i < MATRIX_DIM; ++i) {
        // Log packet_matrix1
        for (int j = 0; j < MATRIX_DIM; ++j) {
            file << std::setw(10) << packet_matrix1[i][j]; // Format packet_matrix1 values
        }

        file << "   |   "; // Separator between matrices

        // Log packet_matrix2
        for (int j = 0; j < MATRIX_DIM; ++j) {
            file << std::setw(10) << packet_matrix2[i][j]; // Format packet_matrix2 values
        }

        file << "   |   "; // Separator for the result

        // Log result matrix
        for (int j = 0; j < MATRIX_DIM; ++j) {
            file << std::setw(10) << result[i][j]; // Format result values
        }

        file << "\n"; // Newline for the next row
    }

    file << "\n"; // Add some spacing between different log outputs

    // Close the file after writing
    file.close();
}
