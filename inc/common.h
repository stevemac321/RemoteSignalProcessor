#ifndef COMMON_H
#define COMMON_H

#include <ncurses.h>
#include "window_manager.h"
#include "packet.h"
#include "matrix.h"
#include "fft.h"

const int COLUMNS = 251; // adjust to how many columns you set your terminal to.
const int ROWS = 65;  // ditto for rows

const int TOTAL_FLOATS = 32;
const int PACKET_LENGTH = 128;
const int NUM_WINDOWS = 4;

extern float float_array[];  // Declaration of the global float array
extern uint8_t packet_array[];
extern bool packet_captured;

extern WINDOW *windows[];  // Array to hold the six windows for the main view

#endif // COMMON_H
