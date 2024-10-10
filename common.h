#ifndef COMMON_H
#define COMMON_H
#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex>
#include <vector>
#include <numeric> // For std::accumulate
#include <queue>
#include <pcap.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include "graph.h"

#define COLS 251 // adjust to how many columns you set your terminal to.
#define ROWS 65  // ditto for rows

#define TOTAL_FLOATS 32
#define PACKET_LENGTH 128
const int num_windows = 4;

extern float float_array[];  // Declaration of the global float array
extern uint8_t packet_array[];
extern bool packet_captured;

extern WINDOW *windows[];  // Array to hold the six windows for the main view

// Function prototypes for window drawing
void draw_perimeter(WINDOW *win);
void draw_function_keys(WINDOW *win);
void setup_main_view(WINDOW *windows[]);

void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet);
void get_packet() ;
void packet_to_float(const u_char *packet);
void save_packet(const u_char *packet);

// consolidation function for pressing '1'
void display_all_voltage_data();

void display_voltage_floats(WINDOW * win);
void display_voltage_packet(WINDOW * win);
void display_voltage_fft(WINDOW * win, std::vector<std::complex<float>> &v);
void display_voltage_magnitude_pqueue(WINDOW *win,
             std::priority_queue<float, std::vector<float>, std::less<float>> &pq);

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
std::priority_queue<float, std::vector<float>, std::less<float>> 
pqueue_from_magnitudes(const std::vector<float> &magnitude_array, const size_t size);
#endif // COMMON_H
