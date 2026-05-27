# include "spiral_window.h"

void SPIRAL_Window::create () {

    SDL_Init(SDL_INIT_VIDEO);
    buffer = new uint32_t[width * height];
    __window = SDL_CreateWindow(name, width * scale, height * scale, 0);
    __renderer = SDL_CreateRenderer(__window, "gpu");
    __texture = SDL_CreateTexture(__renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    // Set to nearest-neighbor scaling
    SDL_SetTextureScaleMode(__texture, SDL_ScaleMode::SDL_SCALEMODE_NEAREST);
    
}

bool SPIRAL_Window::update () {

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

void SPIRAL_Window::gracefulExit () {
    
    delete buffer;
    
    SDL_DestroyTexture(__texture);
    SDL_DestroyRenderer(__renderer);
    SDL_DestroyWindow(__window);
    SDL_Quit();

}

void SPIRAL_Window::clear () {

    for (int p = 0; p < width * height; p++) {
        buffer[(uint32_t)p] = WHITE;
    }

}

void SPIRAL_Window::drawPixel (int x, int y, SPIRAL_Color color) {

    buffer[(uint32_t)x + (uint32_t)y * width] = color;

}