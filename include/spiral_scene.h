# ifndef SPIRAL_SCENE_H

# define SPIRAL_SCENE_H

# include <spiral_graphics.h>

# include <vector>

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

    class Scene {

        std::vector<Sprite*> sprites;

        public:
        Scene () {}

        void addSprite(Sprite* s);
        void removeSprite(Sprite* s);

    };

    class Map {};

}

# endif