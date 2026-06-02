# ifndef SPIRAL_MAIN_H

# define SPIRAL_MAIN_H

# include <spiral_window.h>

namespace SPIRAL {

    extern Window* main_window;

    void Initialize (const char* window_name);

    int MainMenu (void (*main_menu_init)(), int (*main_menu_loop)());

    void RunChapter (void (*chapter_init)(), void (*chapter_frame)(), void (*chapter_tick)());

    void ExitChapter ();

}

# endif