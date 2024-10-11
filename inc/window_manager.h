#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include "common.h"

class window_manager {
public:
	void initialize_screen();
	void draw_perimeter(WINDOW *win);
	void draw_function_keys(WINDOW *win);
	void setup_main_view(WINDOW* windows[]);
};

#endif // WINDOW_MANAGER_H