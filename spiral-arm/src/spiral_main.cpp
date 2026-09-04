# include <spiral_main.h>

# include <chrono>
# include <algorithm>
# include <iostream>

# include <SDL3/SDL.h>
# include <SDL3/SDL_render.h>

# include <spiral_graphics.h>

void spiral::InitWindow (spiral::Window* &window, int width, int height, int scale, const char* name) {

    window = new spiral::Window(width, height, scale, name);

    SDL_Init(SDL_INIT_VIDEO);
    window->buffer = new uint32_t[window->width * window->height];
    window->__window = SDL_CreateWindow(name, window->width * scale, window->height * window->scale, 0);
    window->__renderer = SDL_CreateRenderer(window->__window, "gpu");
    window->__texture = SDL_CreateTexture(window->__renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    // Set to nearest-neighbor scaling
    SDL_SetTextureScaleMode(window->__texture, SDL_ScaleMode::SDL_SCALEMODE_NEAREST);

    spiral::Clear(spiral::COLOR_WHITE, window);

}

bool spiral::Window::update () {

    SDL_Event e;

    if (SDL_PollEvent(&e)) {

        if (e.type == SDL_EVENT_QUIT)
            return false;

        if (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE) 
            return false;

    }

    unsigned char* pixels;
    int pitch;
  
    SDL_LockTexture(__texture, NULL, (void**)&pixels, &pitch);
    
    uint8_t* dest_row;
    uint32_t* source_row;

    for (int y = 0; y < height; y++) {

        dest_row = pixels + y * pitch;
        source_row = buffer + y * width;

        memcpy(dest_row, source_row, width * sizeof(uint32_t));

    }
    

    SDL_UnlockTexture(__texture);  
    SDL_RenderTexture(__renderer, __texture, NULL, NULL);
    SDL_RenderPresent(__renderer);
    
    return true;

}

void spiral::Window::gracefulExit () {
    
    delete buffer;
    
    SDL_DestroyTexture(__texture);
    SDL_DestroyRenderer(__renderer);
    SDL_DestroyWindow(__window);
    SDL_Quit();

}

void spiral::Clear (spiral::Color color, spiral::Window* window) {

    for (int p = 0; p < window->width * window->height; p++) {
        window->buffer[(uint32_t)p] = color;
    }

}

void spiral::DrawPixel (int x, int y, spiral::Color color, spiral::Window* window) {

    window->buffer[(uint32_t)x + (uint32_t)y * window->width] = color;

}

void spiral::DrawRectangle (int x, int y, int w, int e, spiral::Color color, spiral::Window* window) {

    int clamped_width = std::max(0, std::min(x + w, window->width) - x);
    int clamped_height = std::max(0, std::min(y + e, window->height) - y);

    for (int k = y; k < y + clamped_height; k++) {
        for (int h = x; h < x + clamped_width; h++) {
            window->buffer[(uint32_t)h + (uint32_t)k * window->width] = color;
        }
    }

}

// const void spiral::Window::blit (int x, int y, spiral::Image* image, bool transparency) { // interface for all blit modes

//     if ((height - y) < 0) { return; }

//     if (transparency) { // PARTIAL TRANSPARENCY (REQUIRES TRANSPARENCY VALUES)

//         for (int r = 0; r < std::clamp(image->height, 0, height - y); r++) {

//             uint32_t* from = image->pixels + (uint32_t)r * image->width;
//             uint32_t* to = buffer + ((uint32_t)y + r) * width + (uint32_t)x;

//             if ((uint32_t)((width - x) * sizeof(Color)) <= 0) {

//                 continue;

//             }

//             uint32_t length = std::clamp(

//                 (uint32_t)(sizeof(Color) * image->width),
//                 (uint32_t)0, (uint32_t)((width - x) * sizeof(Color))

//             );

//             uint32_t offset = 0;

//             while (offset < length) {

//                 if ((from[offset] & 0xFF000000) == 0xFF000000) {

//                     to[offset] = from[offset];

//                 }
                
//                 offset += sizeof(Color);

//             }

//             offset = 1;

//         }

//     } else { // NO TRANSPARENCY (TRANSPARENT VALUES WILL BE IGNORED) (FASTER)

//         for (int r = 0; r < std::clamp(image->height, 0, height - y); r++) {

//             if ((uint32_t)((width - x) * sizeof(Color)) <= 0) {

//                 continue;

//             }
            
//             memcpy(

//                 buffer + ((uint32_t)y + r) * width + (uint32_t)x,
//                 image->pixels + (uint32_t)r * image->width,
//                 std::clamp(

//                     (uint32_t)(sizeof(Color) * image->width),
//                     (uint32_t)0,
//                     (uint32_t)((width - x) * sizeof(Color))
                    
//                 ) // all the casts to uint32_t are to ensure parity across architectures

//             );

//         }

//         return;

//     }

// }

void spiral::InitCamera (spiral::Camera* &camera, int w, int h, spiral::Window* window) {

}

void spiral::Start (spiral::Window* window) {
    
    // Initialization things

    std::chrono::steady_clock delta_clock;
    std::chrono::steady_clock::time_point prev_tick_time = delta_clock.now(); 
    std::chrono::steady_clock::time_point curr_tick_time;
    const long long tick_length = 32;

    do {
        
        curr_tick_time = delta_clock.now();

        std::chrono::milliseconds delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(curr_tick_time - prev_tick_time);

        window->chapter_frame(window);

        if (delta_time.count() >= tick_length) {
            window->chapter_tick(window);
            prev_tick_time = curr_tick_time;
        }
        
    } while (window->update());
    
}

void spiral::SwitchChapter (void (*chapter_init)(spiral::Window*), void (*chapter_frame)(spiral::Window*), void (*chapter_tick)(spiral::Window*), spiral::Window* window) {

    spiral::Clear(spiral::COLOR_WHITE, window);

    window->chapter_init = chapter_init;
    window->chapter_frame = chapter_frame;
    window->chapter_tick = chapter_tick;

    window->chapter_init(window);

}