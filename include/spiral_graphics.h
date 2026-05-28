# include <cstdint>

# ifndef SPIRAL_GRAPHICS_H

# define SPIRAL_GRAPHICS_H

namespace SPIRAL {

    typedef uint32_t Color;

    class Image {};
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