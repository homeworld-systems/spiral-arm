# include <spiral_main.h>

# include <constants.h>
# include <spiral_window.h>

# include <cstdio>
# include <chrono>

SPIRAL_Window* SPIRAL_main_window;

void SPIRAL_Initialize (const char* window_name) {

    printf("STARSHIFT.\n");

    SPIRAL_main_window = new SPIRAL_Window(window_name, FRAME_WIDTH, FRAME_HEIGHT, SCALE_FACTOR);
    SPIRAL_main_window->create();
    SPIRAL_main_window->clear(WHITE);

}

void SPIRAL_MainMenu (void (*main_menu_init)(), void (*main_menu_loop)()) {

    main_menu_init();
    
    do {
        
        main_menu_loop();
        
    } while (SPIRAL_main_window->update());

}

void SPIRAL_RunChapter (void (*chapter_init)(), void (*chapter_loop)()) {

    // Initialization things

    std::chrono::steady_clock delta_clock;
    std::chrono::steady_clock::time_point prev_tick_time = delta_clock.now(); 
    std::chrono::steady_clock::time_point curr_tick_time;
    const long long tick_length = 50;

    chapter_init();
    
    do {
        chapter_loop();
        
        curr_tick_time = delta_clock.now();

        std::chrono::milliseconds delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(curr_tick_time - prev_tick_time);

        if (delta_time.count() >= tick_length) {
            // tick();
            prev_tick_time = curr_tick_time;
        }
        
    } while (SPIRAL_main_window->update());

}

void SPIRAL_ExitChapter () {

    SPIRAL_main_window->gracefulExit();

}