# ifndef SPIRAL_MAIN_H

# define SPIRAL_MAIN_H

# include <spiral_window.h>

extern SPIRAL_Window* SPIRAL_main_window;

void SPIRAL_Initialize (const char* window_name);

void SPIRAL_MainMenu (void (*main_menu_init)(), void (*main_menu_loop)());

void SPIRAL_RunChapter (void (*chapter_init)(), void (*chapter_loop)());

void SPIRAL_ExitChapter ();

# endif