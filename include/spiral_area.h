# include <cstdint>
# ifndef SPIRAL_AREA_H

# define SPIRAL_AREA_H

namespace SPIRAL {

    struct Tile {
        uint8_t type;
        bool solid;
    };

    typedef SPIRAL::Image* Tileset[256];

    struct Area {
        uint8_t width;
        uint8_t height;
        Tile* tiles;
    };

}

# endif