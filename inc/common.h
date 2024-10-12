#ifndef COMMON_H
#define COMMON_H

#include <ncurses.h>
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

const int COLUMNS = 251; // adjust to how many columns you set your terminal to.
const int ROWS = 65;  // ditto for rows

const int TOTAL_FLOATS = 32;
const int PACKET_LENGTH = 128;
const int NUM_WINDOWS = 4;
const int NUM_MATRICES = 2;
const int MATRIX_DIM = 8;

// voltage and packet buffers
extern float float_array[];  
extern uint8_t packet_array[];
extern bool packet_captured;

extern int64_t packet_matrix1[MATRIX_DIM][MATRIX_DIM];
extern int64_t packet_matrix2[MATRIX_DIM][MATRIX_DIM];
extern int64_t addition_result[MATRIX_DIM][MATRIX_DIM];
extern int64_t subtraction_result[MATRIX_DIM][MATRIX_DIM];
extern int64_t multiplication_result[MATRIX_DIM][MATRIX_DIM];

extern WINDOW *windows[];  // Array to hold the six windows for the main view
// main window, subwindow layout
void initialize_screen();
void draw_perimeter(WINDOW* win);
void draw_function_keys(WINDOW* win);
void setup_main_view(WINDOW* windows[]);
void setup_math_view(WINDOW* windows[]);

void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet);
void get_packet() ;
void packet_to_float(const u_char *packet);
void save_packet(const u_char *packet);

// consolidation function for pressing '1'
void display_all_voltage_data();
void display_voltage_floats(WINDOW * win);
void display_voltage_packet(WINDOW * win);
void display_voltage_fft(WINDOW * win, std::vector<std::complex<float>> &v);
void display_voltage_graph(WINDOW* win, const std::vector<std::complex<float>>& complex_data,
    const std::vector<float> magnitudes);

    // FFT
std::complex<float> complex_multiply(std::complex<float> a, std::complex<float> b);
std::complex<float> complex_add(std::complex<float> a, std::complex<float> b);
std::complex<float> complex_subtract(std::complex<float> a, std::complex<float> b);
void FFT(std::vector<std::complex<float>> &x, const size_t size);
std::vector<std::complex<float>> prepare_complex_fft(const float float_array[], const size_t size);
void normalize_signal(std::vector<std::complex<float>> &signal);

// FFT to magnitudes
std::vector<float> convert_to_magnitudes(const std::vector<std::complex<float>> &fft_results);
// Magnitudes to pqueue
std::priority_queue<float> pqueue_from_magnitudes(const std::vector<float> &magnitude_array, const size_t size);

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

bool validate_matrix(int64_t result[MATRIX_DIM][MATRIX_DIM], int64_t expected[MATRIX_DIM][MATRIX_DIM], 
                                                                        const std::string& filename);

// for matrix
// calls matrix perform_matrix_operations, then prints the results.
void display_all_matrix_data(std::chrono::microseconds addition_duration, 
                             std::chrono::microseconds subtraction_duration,
                             std::chrono::microseconds multiplication_duration, 
                             bool addition_valid, bool subtraction_valid, bool multiplication_valid);
#endif // COMMON_H
