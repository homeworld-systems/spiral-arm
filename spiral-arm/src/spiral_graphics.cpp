# include <spiral_graphics.h>
# include <algorithm>
# include <SDL3/SDL.h>
# include <SDL3_image/SDL_image.h>
# include <iostream>

spiral::Image* spiral::SolidImage (int width, int height, Color color) {
    Color* pixels = new Color[width * height];
    std::fill(pixels, pixels + (width * height), color);
    return new spiral::Image(width, height, pixels);
}

spiral::Image* spiral::LoadFromSource (const char* src) {

    int width;
    int height;
    Color* pixels = new Color[width * height];

    SDL_Surface* __surface_unformatted = IMG_Load(src);

    if (__surface_unformatted != nullptr) {

        SDL_Surface* __surface = SDL_ConvertSurface(__surface_unformatted, SDL_PIXELFORMAT_ARGB8888);
        
        width = __surface->w;
        height = __surface->h;
        pixels = new spiral::Color[width * height];

        size_t size = __surface->pitch * __surface->h;

        memcpy(pixels, __surface->pixels, size);

        SDL_DestroySurface(__surface);

    }

    else {
        
        std::cout << SDL_GetError() << "\n";

    }

    SDL_DestroySurface(__surface_unformatted);

    return new spiral::Image(width, height, pixels);

}