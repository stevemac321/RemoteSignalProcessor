#ifndef COMMON_H
#define COMMON_H
#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_FLOATS 32
const int num_windows = 3;

extern float float_array[TOTAL_FLOATS];  // Declaration of the global float array
extern bool packet_captured;

extern WINDOW *windows[num_windows];  // Array to hold the six windows for the main view

// Function prototypes for window drawing
void draw_perimeter(WINDOW *win);
void draw_function_keys(WINDOW *win);
void setup_main_view(WINDOW *windows[]);

void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet);
void get_packet() ;
void packet_to_float(const u_char *packet);

void display_voltage_floats(WINDOW * win);
#endif // COMMON_H
