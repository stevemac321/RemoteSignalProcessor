#include "main.h"

WINDOW *windows[NUM_WINDOWS];

const char* matrix_titles[] = {
    "Packet Matrices",
    "Matrix Addition",
    "Matrix Subtraction",
    "Matrix Multiplication"
};

const char* math_titles[] = {
    "FFT Series",
    "Polynomial Multiplication",
    "TBD",
    "TBD"
};

int main() {
    
    WINDOW* mainwin = nullptr;
    WINDOW *statuswin = nullptr;
 
    initialize_screen();
    // Create main display and status windows
    mainwin = newwin(ROWS, COLUMNS, 0, 0);     // Main display window
    statuswin = newwin(1, COLUMNS, ROWS + 2, 0);   // Status window for function key descriptions

    // Draw initial main view layout with 6 windows
    setup_main_view(windows);
    // Draw function keys at the bottom
    draw_function_keys(statuswin);

    int ch;
    while ((ch = getch()) != '0') {
      
            switch (ch) {
                case '1':
                    // Handle System View logic (e.g., refreshing with new data)
                    wclear(statuswin);
                    mvwprintw(statuswin, 0, 200, "Voltage View");
                    wrefresh(statuswin);
                    setup_main_view(windows);
                    display_all_voltage_data();
                    break;
                case '2':
                    // Handle Math View logic
                    wclear(statuswin);
                    mvwprintw(statuswin, 0, 200, "Matrix View");
                    wrefresh(statuswin);
                    setup_math_view(windows, matrix_titles);
                    perform_matrix_operations();
                    break;
                case '3':
                    // Handle Math View logic
                    wclear(statuswin);
                    mvwprintw(statuswin, 0, 200, "More Math");
                    wrefresh(statuswin);
                    setup_math_view(windows, math_titles);
                    draw_function_keys(statuswin);
                    more_math();
                    break;
                default:
                    mvwprintw(statuswin, 0, 200, "Unknown Key Pressed");
                    wrefresh(statuswin);
                    break;
            }
    }
    // Cleanup
    for (int i = 0; i < NUM_WINDOWS; ++i) {
        delwin(windows[i]);
    }
    delwin(mainwin);
    delwin(statuswin);
    endwin();
    
    clear();  // Clear the screen
    refresh(); // Refresh the screen to apply clearing
    // Clear lingering screen remnants
    
}

