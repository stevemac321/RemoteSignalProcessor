#include "common.h"
#include <inttypes.h> // For PRIi64

int spacing = 4;
const int column_spacing = 50;

// Calls matrix perform_matrix_operations, then prints the results.
void display_all_matrix_data(std::chrono::microseconds addition_duration, 
                             std::chrono::microseconds subtraction_duration,
                             std::chrono::microseconds multiplication_duration, 
                             bool addition_valid, bool subtraction_valid, bool multiplication_valid)
{
    // Display packet matrices
    for(int i = 0; i < MATRIX_DIM; i++) {
        for(int j = 0; j < MATRIX_DIM; j++) {
            mvwprintw(windows[0], i + 1, j * spacing + 1, "%" PRIi64, packet_matrix1[i][j]); 
        }
    }
    wrefresh(windows[0]);

    for(int i = 0; i < MATRIX_DIM; i++) {
        for(int j = 0; j < MATRIX_DIM; j++) {
            mvwprintw(windows[0], i + 1, (j * spacing) + column_spacing + 1, "%" PRIi64, packet_matrix2[i][j]); 
        }
    }
    wrefresh(windows[0]);

    spacing = 10;

    // Display addition result
    for (int i = 0; i < MATRIX_DIM; i++) {
        for (int j = 0; j < MATRIX_DIM; j++) {
            mvwprintw(windows[1], i + 1, j * spacing + 1, "%" PRIi64, addition_result[i][j]); 
        }
    }
    mvwprintw(windows[1], MATRIX_DIM + 1, 1, "Addition Time taken: %ld microseconds", addition_duration.count());
    mvwprintw(windows[1], MATRIX_DIM + 2, 1, "Addition Validation: %s", addition_valid ? "Passed" : "Failed");
    wrefresh(windows[1]);

    // Display subtraction result
    for (int i = 0; i < MATRIX_DIM; i++) {
        for (int j = 0; j < MATRIX_DIM; j++) {
            mvwprintw(windows[2], i + 1, j * spacing + 1, "%" PRIi64, subtraction_result[i][j]); 
        }
    }
    mvwprintw(windows[2], MATRIX_DIM + 1, 1, "Subtraction Time taken: %ld microseconds", subtraction_duration.count());
    mvwprintw(windows[2], MATRIX_DIM + 2, 1, "Subtraction Validation: %s", subtraction_valid ? "Passed" : "Failed");
    wrefresh(windows[2]);

    // Display multiplication result
    for (int i = 0; i < MATRIX_DIM; i++) {
        for (int j = 0; j < MATRIX_DIM; j++) {
            mvwprintw(windows[3], i + 1, j * spacing + 1, "%" PRIi64, multiplication_result[i][j]); 
        }
    }
    mvwprintw(windows[3], MATRIX_DIM + 1, 1, "Multiplication Time taken: %ld microseconds", multiplication_duration.count());
    mvwprintw(windows[3], MATRIX_DIM + 2, 1, "Multiplication Validation: %s", multiplication_valid ? "Passed" : "Failed");
    wrefresh(windows[3]);
}
