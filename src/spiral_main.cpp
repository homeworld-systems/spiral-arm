# include <spiral_main.h>

# include <constants.h>
# include <spiral_window.h>

# include <cstdio>
# include <chrono>

SPIRAL::Window* SPIRAL::main_window;

void SPIRAL::Initialize (const char* window_name) {

    printf("STARSHIFT.\n");

    SPIRAL::main_window = new SPIRAL::Window(window_name, FRAME_WIDTH, FRAME_HEIGHT, SCALE_FACTOR);
    SPIRAL::main_window->create();
    SPIRAL::main_window->clear(WHITE);

}

int SPIRAL::MainMenu (void (*main_menu_init)(), int (*main_menu_loop)()) {

    main_menu_init();

    int exit = 0;
    
    do {
        
        exit = main_menu_loop();
        if (exit != 0) {
            break;
        }
        
    } while (SPIRAL::main_window->update());

    return exit;

}

void SPIRAL::RunChapter (void (*chapter_init)(), void (*chapter_frame)(), void (*chapter_tick)()) {

    // Initialization things

    std::chrono::steady_clock delta_clock;
    std::chrono::steady_clock::time_point prev_tick_time = delta_clock.now(); 
    std::chrono::steady_clock::time_point curr_tick_time;
    const long long tick_length = 32;

    SPIRAL::main_window->createScene();
    chapter_init();
    
    do {
        
        curr_tick_time = delta_clock.now();

        std::chrono::milliseconds delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(curr_tick_time - prev_tick_time);

        chapter_frame();

        if (delta_time.count() >= tick_length) {
            chapter_tick();
            prev_tick_time = curr_tick_time;
        }
        
    } while (SPIRAL::main_window->update());

}

void SPIRAL::Exit () {

    SPIRAL::main_window->gracefulExit();

}