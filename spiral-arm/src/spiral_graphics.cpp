# include <spiral_graphics.h>
# include <SDL3/SDL_log.h>
# include <algorithm>

spiral::Image* spiral::SolidImage (int width, int height, Color color) {
    Color* pixels = new Color[width * height];
    std::fill(pixels, pixels + (width * height), color);
    return new spiral::Image(width, height, pixels);
}