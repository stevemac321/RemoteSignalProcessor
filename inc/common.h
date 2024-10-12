#ifndef COMMON_H
#define COMMON_H

#include <ncurses.h>
#include <immintrin.h>  // For AVX intrinsics
#include <thread>
#include <chrono>
#include <pcap.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <cstring>
#include <complex>
#include <vector>
#include <numeric>  
#include <queue>
#include <array>
#include "window_manager.h"
#include "packet.h"
#include "fft.h"

const int COLUMNS = 251; // adjust to how many columns you set your terminal to.
const  int ROWS = 65;  // ditto for rows

const int TOTAL_FLOATS = 32;
const int PACKET_LENGTH = 128;
const int NUM_WINDOWS = 4;
const int NUM_MATRICES = 2;
const int MATRIX_DIM = 8;

// voltage and packet buffers
extern float float_array[];  
extern uint8_t packet_array[];
extern bool packet_captured;

extern uint8_t packet_matrix1[MATRIX_DIM][MATRIX_DIM];
extern uint8_t packet_matrix2[MATRIX_DIM][MATRIX_DIM];
extern uint8_t addition_result[MATRIX_DIM][MATRIX_DIM];
extern uint8_t subtraction_result[MATRIX_DIM][MATRIX_DIM];
extern uint8_t multiplication_result[MATRIX_DIM][MATRIX_DIM];


extern WINDOW *windows[];  // Array to hold the six windows for the main view

// controlling function
void perform_matrix_operations();
// step one prep function
void create_src_matrices_from_packet();

// thread procs
void matrix_addition(uint8_t A[MATRIX_DIM][MATRIX_DIM], uint8_t B[MATRIX_DIM][MATRIX_DIM], 
                                                        uint8_t C[MATRIX_DIM][MATRIX_DIM]);
void matrix_subtraction(uint8_t A[MATRIX_DIM][MATRIX_DIM], uint8_t B[MATRIX_DIM][MATRIX_DIM], 
                                                            uint8_t C[MATRIX_DIM][MATRIX_DIM]);
void matrix_multiplication();
void multiply_matrices(uint8_t A[MATRIX_DIM][MATRIX_DIM], uint8_t B[MATRIX_DIM][MATRIX_DIM], 
                       uint8_t C[MATRIX_DIM][MATRIX_DIM], size_t start_row, size_t end_row);

void threaded_matrix_multiplication(uint8_t A[MATRIX_DIM][MATRIX_DIM], uint8_t B[MATRIX_DIM][MATRIX_DIM], 
                                    uint8_t C[MATRIX_DIM][MATRIX_DIM]);


// for matrix
// calls matrix perform_matrix_operations, then prints the results.
void display_all_matrix_data(std::chrono::duration<double> addition_duration, 
                             std::chrono::duration<double> subtraction_duration,
                                std::chrono::duration<double> multiplication_duration);

#endif // COMMON_H
