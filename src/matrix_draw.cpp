
#include "common.h"

// Calls matrix perform_matrix_operations, then prints the results.
void display_all_matrix_data(std::chrono::duration<double> addition_duration,
                             std::chrono::duration<double> subtraction_duration,
                             std::chrono::duration<double> multiplication_duration) {
    // Display packet matrices
    for(int i = 0; i < MATRIX_DIM; i++) {
        for(int j = 0; j < MATRIX_DIM; j++) {
            mvwprintw(windows[0], i + 1, j + 1, "%d", packet_matrix1[i][j]);
        }
    }
     wrefresh(windows[0]);
    
     for(int i = 0; i < MATRIX_DIM; i++) {
        for(int j = 0; j < MATRIX_DIM; j++) {
            mvwprintw(windows[0], i + 1, j + 50, "%d", packet_matrix2[i][j]);
        }
    }
    wrefresh(windows[0]);

    // Display addition result
    for(int i = 0; i < MATRIX_DIM; i++) {
        for(int j = 0; j < MATRIX_DIM; j++) {
            mvwprintw(windows[1], i + 1, j + 1, "%d", addition_result[i][j]);
        }
    }
    mvwprintw(windows[1], MATRIX_DIM + 1, 1, "Addition Time taken: %.2f seconds", addition_duration.count());
    wrefresh(windows[1]);

    // Display subtraction result
    for(int i = 0; i < MATRIX_DIM; i++) {
        for(int j = 0; j < MATRIX_DIM; j++) {
            mvwprintw(windows[2], i + 1, j + 1, "%d", subtraction_result[i][j]);
        }
    }
    mvwprintw(windows[2], MATRIX_DIM + 1, 1, "Subtraction Time taken: %.2f seconds", subtraction_duration.count());
    wrefresh(windows[2]);

    // Display multiplication result
    for(int i = 0; i < MATRIX_DIM; i++) {
        for(int j = 0; j < MATRIX_DIM; j++) {
            mvwprintw(windows[3], i + 1, j + 1, "%d", multiplication_result[i][j]);
        }
    }
    mvwprintw(windows[3], MATRIX_DIM + 1, 1, "Multiplication Time taken: %.2f seconds", multiplication_duration.count());
    wrefresh(windows[3]);
    
}

