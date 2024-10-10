#include "common.h"

extern float float_array[];

void display_voltage_floats(WINDOW * win)
{
    mvwprintw(win, 1, 1, "STM32F7 Voltage Samples:");
    // Print the reconstructed float values for verification
    for (int i = 0; i < TOTAL_FLOATS; i++) {
        mvwprintw(win, i+2, 1, "%f\n", float_array[i]);
    }
    wrefresh(win);
}
