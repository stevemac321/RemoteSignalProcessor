#include "common.h"

// Function to draw the perimeter border of a given window
void draw_perimeter(WINDOW *win) {
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
}

// Function to draw the function key labels in the status window
void draw_function_keys(WINDOW *win) {
    wattron(win, COLOR_PAIR(1));  // Turn on color pair 1
    mvwprintw(win, 0, 2, "0: Quit");
    mvwprintw(win, 0, 12, "1: System View");
    mvwprintw(win, 0, 34, "2: Math View");
    wattroff(win, COLOR_PAIR(1)); // Turn off color pair 1
    wrefresh(win);
}
// Function to set up the main view with three windows
void setup_main_view(WINDOW *windows[]) {
    const char *titles[] = {
        "(1.) CPU Usage", "(2.) Memory Usage", "(3.) Network Activity"
    };

    int height = 57 - 2;  // Full height of the screen minus borders
    int width = 232 / 3;  // One-third of the screen width

    for (int i = 0; i < 3; ++i) {
        int starty = 0;                // Y position is fixed at top
        int startx = i * width;        // Calculate the starting x position for each column

        windows[i] = newwin(height, width, starty, startx);
        wattron(windows[i], COLOR_PAIR(1));  // Turn on color pair 1
        draw_perimeter(windows[i]);          // Draw border around each window
        mvwprintw(windows[i], 0, 1, "%s", titles[i]);  // Set window title
        wattroff(windows[i], COLOR_PAIR(1)); // Turn off color pair 1
        wrefresh(windows[i]);                // Refresh the window to display title
    }
}