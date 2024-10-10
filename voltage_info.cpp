#include "common.h"

//extern float float_array[];

void display_voltage_floats(WINDOW * win)
{
    // Print the reconstructed float values for verification
    for (int i = 0; i < TOTAL_FLOATS; i++) {
        mvwprintw(win, i+2, 1, "%f\n", float_array[i]);
    }
    wrefresh(win);
}
void display_voltage_packet(WINDOW *win) {
    // Get the dimensions of the window
    int height, width;
    getmaxyx(win, height, width);

    int row = 2;  // Start at the 2nd row
    int col = 1;  // Start at the 1st column

    // Iterate over packet_array and display each element
    for(int i = 0; i < PACKET_LENGTH; i++) {
        // Print the packet data at the current position
        mvwprintw(win, row, col, "%02x", packet_array[i]);

        // Move the column position right by 3 (each hex character is 2, plus 1 space)
        col += 3;

        // Check if the text exceeds the window's width
        if (col + 3 > width) {
            col = 1;  // Reset to the first column
            row++;    // Move to the next row
        }

        // Break if row exceeds window height (prevent overflow)
        if (row >= height - 1) {
            break;
        }
    }

    wrefresh(win);  // Refresh the window to display changes
}
void display_voltage_fft(WINDOW * win, std::vector<std::complex<float>> &v)
{
       // Print the reconstructed float values for verification
    for (int i = 0; i < TOTAL_FLOATS; i++) {
        mvwprintw(win, i+2, 1, "Real: %f : Imag: %f\n", v[i].real(), v[i].imag());
    }
    wrefresh(win);
}
void display_voltage_magnitude_pqueue(WINDOW *win,
             std::priority_queue<float, std::vector<float>, std::less<float>> &pq)
{
    int row = 1;
    int col = 1;
    while (!pq.empty()) {
        mvwprintw(win, row++, col, "%f", pq.top());
        pq.pop();
    }
     wrefresh(win);
}
