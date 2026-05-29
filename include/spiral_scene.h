# ifndef SPIRAL_SCENE_H

# define SPIRAL_SCENE_H

# include <spiral_graphics.h>

namespace SPIRAL {

    class Sprite {

        int x;
        int y;
        Image texture;

        public:
        Sprite (int h, int k, Image t) : x(h), y(k), texture(t) {}

        Image* getTexture();

        int getX();
        int getY();

    };

    class Scene {};

    class Map {};

}

# endif