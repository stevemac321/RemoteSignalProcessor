#ifndef MATRIX_H
#define MATRIX_H
#include <ncurses.h>
#include <iostream>
#include <fstream> // For file handling
#include <iomanip> // For formatting
#include <string>  // For std::string
#include <cstring> // For std::memcpy
#include <chrono>
#include <thread>
#include <inttypes.h> // For PRIi64

extern WINDOW *windows[];

extern int64_t packet_matrix1[MATRIX_DIM][MATRIX_DIM];
extern int64_t packet_matrix2[MATRIX_DIM][MATRIX_DIM];
extern int64_t addition_result[MATRIX_DIM][MATRIX_DIM];
extern int64_t subtraction_result[MATRIX_DIM][MATRIX_DIM];
extern int64_t multiplication_result[MATRIX_DIM][MATRIX_DIM];

// controlling function
void perform_matrix_operations();
// step one prep function
void create_src_matrices_from_packet();

// thread procs
void matrix_addition(int64_t A[MATRIX_DIM][MATRIX_DIM], int64_t B[MATRIX_DIM][MATRIX_DIM], 
                     int64_t C[MATRIX_DIM][MATRIX_DIM]);

void matrix_subtraction(int64_t A[MATRIX_DIM][MATRIX_DIM], int64_t B[MATRIX_DIM][MATRIX_DIM], 
                        int64_t C[MATRIX_DIM][MATRIX_DIM]);

// multiplication, this one calls the others 
void matrix_multiplication();

void multiply_matrices_single(int64_t A[MATRIX_DIM][MATRIX_DIM], int64_t B[MATRIX_DIM][MATRIX_DIM], 
                              int64_t C[MATRIX_DIM][MATRIX_DIM]);

void multiply_matrices(int64_t A[MATRIX_DIM][MATRIX_DIM], int64_t B[MATRIX_DIM][MATRIX_DIM], 
                       int64_t C[MATRIX_DIM][MATRIX_DIM], size_t start_row, size_t end_row);

void threaded_matrix_multiplication(int64_t A[MATRIX_DIM][MATRIX_DIM], int64_t B[MATRIX_DIM][MATRIX_DIM], 
                                    int64_t C[MATRIX_DIM][MATRIX_DIM]);

void log_matrix(int64_t result[MATRIX_DIM][MATRIX_DIM], const std::string& filename, const std::string& mesg);

// for matrix
// calls matrix perform_matrix_operations, then prints the results.
void display_all_matrix_data(std::chrono::microseconds addition_duration, 
                             std::chrono::microseconds subtraction_duration,
                             std::chrono::microseconds multiplication_duration);

#endif