# include "spiral_window.h"
# include <algorithm>

void SPIRAL::Window::create () {

    SDL_Init(SDL_INIT_VIDEO);
    buffer = new uint32_t[width * height];
    __window = SDL_CreateWindow(name, width * scale, height * scale, 0);
    __renderer = SDL_CreateRenderer(__window, "gpu");
    __texture = SDL_CreateTexture(__renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    // Set to nearest-neighbor scaling
    SDL_SetTextureScaleMode(__texture, SDL_ScaleMode::SDL_SCALEMODE_NEAREST);
    
}

bool SPIRAL::Window::update () {

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

void SPIRAL::Window::gracefulExit () {
    
    delete buffer;
    
    SDL_DestroyTexture(__texture);
    SDL_DestroyRenderer(__renderer);
    SDL_DestroyWindow(__window);
    SDL_Quit();

}

void SPIRAL::Window::clear (SPIRAL::Color color) {

    for (int p = 0; p < width * height; p++) {
        buffer[(uint32_t)p] = color;
    }

}

void SPIRAL::Window::drawPixel (int x, int y, SPIRAL::Color color) {

    buffer[(uint32_t)x + (uint32_t)y * width] = color;

}

void SPIRAL::Window::drawRectangle (int x, int y, int w, int e, SPIRAL::Color color) {

    int clamped_width = std::max(0, std::min(x + w, width) - x);
    int clamped_height = std::max(0, std::min(y + e, height) - y);

    for (int k = y; k < y + clamped_height; k++) {
        for (int h = x; h < x + clamped_width; h++) {
            buffer[(uint32_t)h + (uint32_t)k * width] = color;
        }
    }

}

void SPIRAL::Window::drawTextBox (SPIRAL::TextBox b) {

    drawRectangle(b.getX(), b.getY(), b.getWidth(), b.getHeight(), WHITE);
    drawRectangle(b.getX() + b.getLineWidth(), b.getY() + b.getLineWidth(), b.getWidth() - 2 * b.getLineWidth(), b.getHeight() - 2 * b.getLineWidth(), BLACK);

}