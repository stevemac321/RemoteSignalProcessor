#ifndef MAIN_H
#define MAIN_H

#include <ncurses.h>
#include "more_math.h"
#include "matrix.h"
#include "voltage.h"

extern WINDOW *windows[];  // Array to hold the six windows for the main view

// main window, subwindow layout
void initialize_screen();
void draw_perimeter(WINDOW* win);
void draw_function_keys(WINDOW* win);
void setup_main_view(WINDOW* windows[]);
void setup_math_view(WINDOW* windows[], const char* titles[]);

#endif // COMMON_H
