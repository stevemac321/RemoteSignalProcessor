#ifndef VOLTAGE_H
#define VOLTAGE_H
#include "fft.h"
#include "packet.h"


extern float float_array[];
extern uint8_t packet_array[];
extern bool packet_captured;

// consolidation function for pressing '1'
void display_all_voltage_data();
void display_voltage_floats(WINDOW * win);
void display_voltage_packet(WINDOW * win);
void display_voltage_fft(WINDOW * win, std::vector<std::complex<float>> &v);
void display_voltage_graph(WINDOW* win, const std::vector<std::complex<float>>& complex_data,
    const std::vector<float> magnitudes);
void display_voltage_graph(WINDOW* win, const float voltage_data[], size_t data_size);

#endif