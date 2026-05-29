#include "spiral_window.h"
# include <cstdint>

# ifndef SPIRAL_GRAPHICS_H

# define SPIRAL_GRAPHICS_H

namespace SPIRAL {

    typedef uint32_t Color;

    class Image {

        int width;
        int height;
        Color* pixels;
        
        public:

        Image (int w, int h, Color* p) : width(w), height(h), pixels(p) {}
        static Image* LoadFromSource (const char* src);

        const int getWidth();
        const int getHeight();
        
        Image* crop (int x, int y, int w, int h);

        friend class Window; // freind is my favourite cpp keyword :3

    };

    class Animation {};

}

static const SPIRAL::Color RED = 0xFFFF0000;
static const SPIRAL::Color YELLOW = 0xFFFFFF00;
static const SPIRAL::Color GREEN = 0xFF00FF00;
static const SPIRAL::Color CYAN = 0xFF00FFFF;
static const SPIRAL::Color BLUE = 0xFF0000FF;
static const SPIRAL::Color MAGENTA = 0xFFFF00FF;
static const SPIRAL::Color WHITE = 0xFFFFFFFF;
static const SPIRAL::Color BLACK = 0xFF000000;

# endif