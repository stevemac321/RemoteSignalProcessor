#include "voltage.h"
#include "graph.h"

std::vector<std::complex<float>> save_fft(TOTAL_FLOATS);

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

    int row = 1;  // Start at the 1st row
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
void display_voltage_graph(WINDOW* win, const std::vector<std::complex<float>>& complex_data,
                                                        const std::vector<float> magnitudes)
{
    auto graph = analyze_results<TOTAL_FLOATS>(complex_data);
    graph.printGraph(win, magnitudes);
}

void display_all_voltage_data()
{
    std::vector<std::complex<float>> v(TOTAL_FLOATS);
    std::priority_queue<float> pq;
    std::vector<float> magnitudes;

    packet_captured = false;
    get_packet();
    display_voltage_floats(windows[1]);
    display_voltage_packet(windows[0]);
    v = prepare_complex_fft(float_array, TOTAL_FLOATS);
    save_fft = v;
    normalize_signal(v);
    FFT(v, TOTAL_FLOATS);
    display_voltage_fft(windows[2], v);
    magnitudes = convert_to_magnitudes(v);
    pq = pqueue_from_magnitudes(magnitudes, magnitudes.size());
    display_voltage_graph(windows[3], save_fft, magnitudes);
}
