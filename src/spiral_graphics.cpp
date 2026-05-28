# include "spiral_graphics.h"

# include <iostream>

# include <SDL3/SDL_surface.h>
# include <SDL3_image/SDL_image.h>

SPIRAL::Image* SPIRAL::Image::LoadFromSource (const char* src) {

    int width = 0;
    int height = 0;
    SPIRAL::Color* pixels = {};

    SDL_Surface* __surface_unformatted = IMG_Load(src);

    if (__surface_unformatted != nullptr) {

        SDL_Surface* __surface = SDL_ConvertSurface(__surface_unformatted, SDL_PIXELFORMAT_ARGB8888);
        
        width = __surface->w;
        height = __surface->h;
        pixels = new SPIRAL::Color[width * height];

        size_t size = __surface->pitch * __surface->h;

        memcpy(pixels, __surface->pixels, size);

        SDL_DestroySurface(__surface);

    }

    else {
        
        std::cout << SDL_GetError() << "\n";

    }

    SDL_DestroySurface(__surface_unformatted);

    return new SPIRAL::Image(width, height, pixels);

}