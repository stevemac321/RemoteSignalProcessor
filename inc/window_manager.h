#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <ncurses.h>
#include <complex>
#include <vector>

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


#endif