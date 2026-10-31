# ifndef SPIRAL_GRAPHICS_H

# define SPIRAL_GRAPHICS_H

# include <cstdint>

namespace spiral {

    typedef uint32_t Color;

    const Color COLOR_WHITE = 0xFFFFFFFF;
    const Color COLOR_BLACK = 0xFF000000;
    const Color COLOR_RED = 0xFFFF0000;
    const Color COLOR_YELLOW = 0xFFFFFF00;
    const Color COLOR_GREEN = 0xFF00FF00;
    const Color COLOR_CYAN = 0xFF00FFFF;
    const Color COLOR_BLUE = 0xFF0000FF;
    const Color COLOR_MAGENTA = 0xFFFF00FF;
    
    struct Image {

        int width;
        int height;
        Color* pixels;
         
        Image () : width(0), height(0), pixels(nullptr) {}
        Image (int w, int h, Color* p) : width(w), height(h), pixels(p) {}

        ~Image () {
            delete[] pixels;
        }

    };

    Image* SolidImage (int width, int height, Color color);

}

# endif