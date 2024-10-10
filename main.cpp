#include "common.h"
float float_array[TOTAL_FLOATS];  // Array to hold the 32 floats
WINDOW *windows[num_windows];

int main() {
    
    WINDOW *mainwin, *statuswin;

    // Initialize ncurses
    initscr();
    clear();  // Clear the screen
    refresh(); // Refresh the screen to apply clearing
    start_color();  // Enable color functionality
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Define color pair (foreground, background)
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Create main display and status windows
    mainwin = newwin(ROWS, COLS, 0, 0);     // Main display window
    statuswin = newwin(1, COLS, ROWS + 2, 0);   // Status window for function key descriptions

    // Draw initial main view layout with 6 windows
    setup_main_view(windows);
    // Draw function keys at the bottom
    draw_function_keys(statuswin);
    setup_main_view(windows);
   
    int ch;
    while ((ch = getch()) != '0') {
      
            switch (ch) {
                case '1':
                    // Handle System View logic (e.g., refreshing with new data)
                    mvwprintw(statuswin, 0, 200, "System View");
                    wrefresh(statuswin);
                    display_all_voltage_data();
                    break;
                case '2':
                    // Handle Math View logic
                    mvwprintw(statuswin, 0, 200, "Memory Usage");
                    wrefresh(statuswin);
                    // todo
                    break;
                case '3':
                    // Handle Math View logic
                    mvwprintw(statuswin, 0, 200, "Future Usage");
                    wrefresh(statuswin);
                    //todo
                    break;
                default:
                    mvwprintw(statuswin, 0, 200, "Unknown Key Pressed");
                    wrefresh(statuswin);
                    break;
            }
    }
    // Cleanup
    for (int i = 0; i < num_windows; ++i) {
        delwin(windows[i]);
    }
    delwin(mainwin);
    delwin(statuswin);
    endwin();
    
    clear();  // Clear the screen
    refresh(); // Refresh the screen to apply clearing
    // Clear lingering screen remnants
    
}

