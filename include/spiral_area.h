# include <cstdint>
# ifndef SPIRAL_AREA_H

# define SPIRAL_AREA_H

namespace SPIRAL {

    struct Tile {
        uint8_t type;
        bool solid;
    };

    struct Tileset {
        uint8_t tile_types[256];
        SPIRAL::Image* tile_textures[256];
    };

    struct Area {
        uint8_t width;
        uint8_t height;
        Tile* tiles;
    };

}

# endif