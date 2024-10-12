#include "common.h"

WINDOW *windows[NUM_WINDOWS];

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
                    mvwprintw(statuswin, 0, 200, "Voltage View");
                    wrefresh(statuswin);
                    display_all_voltage_data();
                    break;
                case '2':
                    // Handle Math View logic
                    mvwprintw(statuswin, 0, 200, "Math Usage");
                    wrefresh(statuswin);
<<<<<<< HEAD
                    setup_main_view(windows);
                    perform_matrix_operations();
=======
                    //setup_main_view(windows);
                    //perform_matrix_operations();
                    // todo
>>>>>>> b8f0303d376b91db7b77cc4e69f0ca52b5c82c88
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

