#ifndef COMMON_H
#define COMMON_H

#include <ncurses.h>
#include <immintrin.h>  // For AVX intrinsics
#include <thread>
#include <chrono>
#include "window_manager.h"
#include "packet.h"
#include "fft.h"

constexpr  int COLUMNS = 251; // adjust to how many columns you set your terminal to.
constexpr  int ROWS = 65;  // ditto for rows

constexpr  int TOTAL_FLOATS = 32;
constexpr int PACKET_LENGTH = 128;
constexpr  int NUM_WINDOWS = 4;
constexpr  int NUM_MATRICES = 2;
constexpr  int MATRIX_DIM = (PACKET_LENGTH / sizeof(uint8_t)) / NUM_MATRICES;

// voltage and packet buffers
extern float float_array[];  
extern uint8_t packet_array[];
extern bool packet_captured;

extern float packet_matrix1[MATRIX_DIM][MATRIX_DIM];
extern float packet_matrix2[MATRIX_DIM][MATRIX_DIM];
extern float addition_result[MATRIX_DIM][MATRIX_DIM];
extern float subtraction_result[MATRIX_DIM][MATRIX_DIM];
extern float multiplication_result[MATRIX_DIM][MATRIX_DIM];

extern WINDOW *windows[];  // Array to hold the six windows for the main view
// controlling function
void perform_matrix_operations();
// step one prep function
void create_src_matrices_from_packet();

// thread procs
void matrix_addition();
void matrix_subtraction();
void matrix_multiplication();
void multiply_matrices_simd(float A[MATRIX_DIM][MATRIX_DIM], float B[MATRIX_DIM][MATRIX_DIM], 
                           float C[MATRIX_DIM][MATRIX_DIM], size_t start_row, size_t end_row);

void threaded_matrix_multiplication(float A[MATRIX_DIM][MATRIX_DIM], float B[MATRIX_DIM][MATRIX_DIM], 
                                                                     float C[MATRIX_DIM][MATRIX_DIM]);

#endif // COMMON_H
