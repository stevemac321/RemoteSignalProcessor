#include "common.h"

void initialize_screen()
{
    initscr();
    clear();  // Clear the screen
    refresh(); // Refresh the screen to apply clearing
    start_color();  // Enable color functionality
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Define color pair (foreground, background)
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}
void draw_perimeter(WINDOW *win) {
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
}

// Function to draw the function key labels in the status window
void draw_function_keys(WINDOW *win) {
    wattron(win, COLOR_PAIR(1));  // Turn on color pair 1
    mvwprintw(win, 0, 2, "0: Quit");
    mvwprintw(win, 0, 12, "1: Capture Voltage");
    mvwprintw(win, 0, 34, "2: Matrix View");
    wattroff(win, COLOR_PAIR(1)); // Turn off color pair 1
    wrefresh(win);
}
// Function to set up the windows based on the given layout.
void setup_main_view(WINDOW* windows[]) {
    int first_window_height = ROWS / 4;  // First window takes 25% of the total height
    int bottom_height = ROWS - first_window_height;  // Remaining height for the other three windows

    // Dimensions for the three bottom windows
    int window_1_width = COLUMNS / 4;   // 25% of the width
    int window_2_width = COLUMNS / 4;   // 25% of the width
    int window_3_width = COLUMNS / 2;   // 50% of the width

    // Window 0: Top window spanning the full width
    windows[0] = newwin(first_window_height, COLS, 0, 0);
    box(windows[0], 0, 0);  // Draw box border
    mvwprintw(windows[0], 0, 1, "(0) Packet Display and Sine Wave");
    wrefresh(windows[0]);

    // Window 1: Bottom-left window spanning 75% of the height and 25% of the width
    windows[1] = newwin(bottom_height, window_1_width, first_window_height, 0);
    box(windows[1], 0, 0);  // Draw box border
    mvwprintw(windows[1], 0, 1, "(1) Voltage Data");
    wrefresh(windows[1]);

    // Window 2: Bottom-middle window spanning 75% of the height and 25% of the width
    windows[2] = newwin(bottom_height, window_2_width, first_window_height, window_1_width);
    box(windows[2], 0, 0);  // Draw box border
    mvwprintw(windows[2], 0, 1, "(2) Fast Fourier Transfer Results");
    wrefresh(windows[2]);

    // Window 3: Bottom-right window spanning 75% of the height and 50% of the width
    windows[3] = newwin(bottom_height, window_3_width, first_window_height, window_1_width + window_2_width);
    box(windows[3], 0, 0);  // Draw box border
    mvwprintw(windows[3], 0, 1, "(3) Priority Queue and Graph");
    wrefresh(windows[3]);
}
void setup_math_view(WINDOW* windows[], const char* titles[]) 
{
    int window_height = ROWS / 4;  // Each window takes 25% of the total height
    int window_width = COLS;       // Each window spans the full width

    // Loop through each window and apply titles
    for (int i = 0; i < 4; ++i) {
        // Create the window
        windows[i] = newwin(window_height, window_width, i * window_height, 0);
        box(windows[i], 0, 0);  // Draw box border

        // Add the appropriate title from the titles array
        mvwprintw(windows[i], 0, 1, "(%d) %s", i, titles[i]);
        wrefresh(windows[i]);
    }
}







