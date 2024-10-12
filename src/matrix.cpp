
#include "common.h"

#include <iostream>
#include <fstream> // For file handling
#include <iomanip> // For formatting
#include <string>  // For std::string
#include <cstring> // For std::memcpy

int64_t expected_addition_result[MATRIX_DIM][MATRIX_DIM] = {
    {0, 192, 411, 136, 0, 352, 205, 196},
    {225, 224, 205, 68, 0, 224, 411, 136},
    {0, 384, 410, 136, 0, 384, 410, 136},
    {0, 384, 410, 136, 0, 224, 411, 136},
    {0, 224, 411, 136, 0, 448, 410, 136},
    {0, 384, 410, 136, 0, 224, 411, 136},
    {0, 192, 411, 136, 0, 448, 410, 136},
    {0, 224, 411, 136, 0, 352, 410, 136}
};

int64_t expected_subtraction_result[MATRIX_DIM][MATRIX_DIM] = {
    {0, 128, -1, 0, 0, 32, -205, 60},
    {225, -224, -205, -68, 0, -224, 1, 0},
    {0, 64, 0, 0, 0, 64, 0, 0},
    {0, 64, 0, 0, 0, -224, 1, 0},
    {0, 224, -1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, -160, 1, 0},
    {0, 192, -1, 0, 0, 0, 0, 0},
    {0, 224, -1, 0, 0, -32, 0, 0}
};

int64_t expected_multiplication_result[MATRIX_DIM][MATRIX_DIM] = {
    {0, 116384, 154493, 51204, 0, 145312, 154365, 51204},
    {0, 7200, 102794, 33932, 0, 95200, 102295, 33932},
    {0, 136864, 204043, 67592, 0, 200192, 203770, 67592},
    {0, 93856, 158329, 52428, 0, 157408, 158055, 52428},
    {0, 136864, 204043, 67592, 0, 200192, 203770, 67592},
    {0, 92832, 158329, 52428, 0, 156384, 158055, 52428},
    {0, 129696, 197483, 65416, 0, 193024, 197210, 65416},
    {0, 124576, 190923, 63240, 0, 187904, 190650, 63240}
};


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
    bool addition_valid = validate_matrix(addition_result, expected_addition_result, filename);

    // Subtraction
    auto subtraction_start = std::chrono::high_resolution_clock::now();
    matrix_subtraction(packet_matrix1, packet_matrix2, subtraction_result);
    auto subtraction_end = std::chrono::high_resolution_clock::now();
    auto subtraction_duration = std::chrono::duration_cast<std::chrono::microseconds>(subtraction_end - subtraction_start); // Microsecond timing

    // Validate subtraction result
    bool subtraction_valid = validate_matrix(subtraction_result, expected_subtraction_result, filename);

    // Multiplication
    auto multiplication_start = std::chrono::high_resolution_clock::now();
    matrix_multiplication();  
    auto multiplication_end = std::chrono::high_resolution_clock::now();
    auto multiplication_duration = std::chrono::duration_cast<std::chrono::microseconds>(multiplication_end - multiplication_start); // Microsecond timing

    // Validate multiplication result
    bool multiplication_valid = validate_matrix(multiplication_result, expected_multiplication_result, filename);

    // Display the results with the durations and validation status
    display_all_matrix_data(addition_duration, subtraction_duration, multiplication_duration, addition_valid, subtraction_valid, multiplication_valid);
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


bool validate_matrix(int64_t result[MATRIX_DIM][MATRIX_DIM], int64_t expected[MATRIX_DIM][MATRIX_DIM], 
                                                                        const std::string& filename) 
{
    // Open the file in append mode
    std::ofstream file(filename, std::ios::app);
    
    // Check if file is open
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    
    bool isValid = true; // To track if the matrix is valid
    int64_t diff[MATRIX_DIM][MATRIX_DIM] = {{0}}; // Store differences

    // Print headers for matrices
    file << "Result Matrix vs Expected Matrix\n";
    file << "--------------------------------------------\n";

    // Print both matrices side by side
    for (int i = 0; i < MATRIX_DIM; ++i) {
        for (int j = 0; j < MATRIX_DIM; ++j) {
            file << std::setw(10) << result[i][j]; // Format result
        }
        file << "   |   "; // Separator between result and expected
        for (int j = 0; j < MATRIX_DIM; ++j) {
            file << std::setw(10) << expected[i][j]; // Format expected
        }
        file << "\n";
    }

    // Perform comparison and print the difference matrix
    file << "\nDifference (Result - Expected):\n";
    file << "--------------------------------------------\n";
    
    for (int i = 0; i < MATRIX_DIM; ++i) {
        for (int j = 0; j < MATRIX_DIM; ++j) {
            diff[i][j] = result[i][j] - expected[i][j]; // Calculate difference
            if (diff[i][j] != 0) {
                isValid = false; // Mark as invalid if any difference is found
            }
            file << std::setw(10) << diff[i][j]; // Print difference matrix
        }
        file << "\n";
    }
    
    file << "\n"; // Add some spacing between different validation outputs

    // Close the file after writing
    file.close();

    return isValid; // Return true if matrices are equal, false otherwise
}

