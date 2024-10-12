#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <ncurses.h>
#include <complex>
#include <vector>
#include <thread>
#include <chrono>

// main window, subwindow layout
void initialize_screen();
void draw_perimeter(WINDOW* win);
void draw_function_keys(WINDOW* win);
void setup_main_view(WINDOW* windows[]);

// consolidation function for pressing '1'
void display_all_voltage_data();
void display_voltage_floats(WINDOW * win);
void display_voltage_packet(WINDOW * win);
void display_voltage_fft(WINDOW * win, std::vector<std::complex<float>> &v);
void display_voltage_graph(WINDOW* win, const std::vector<std::complex<float>>& complex_data,
    const std::vector<float> magnitudes);

// for matrix
// calls matrix perform_matrix_operations, then prints the results.
void display_all_matrix_data(std::chrono::duration<double> addition_duration, 
                             std::chrono::duration<double> subtraction_duration,
                                std::chrono::duration<double> multiplication_duration);

#endif