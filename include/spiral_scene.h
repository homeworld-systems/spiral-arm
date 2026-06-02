# ifndef SPIRAL_SCENE_H

# define SPIRAL_SCENE_H

# include <spiral_graphics.h>
# include <spiral_input.h>
# include <spiral_area.h>

# include <vector>

namespace SPIRAL {

    class Sprite {

        int x;
        int y;
        Image texture;
        
        public:
        Sprite (int h, int k, Image t) : x(h), y(k), texture(t) {}

        Image* getTexture();

        int getX() const;
        int getY() const;
        void setX(int h);
        void setY(int k);
        void setPosition(int h, int k);
        void changeX(int dx);
        void changeY(int dy);

        bool operator< (const Sprite& _sprite) const;

    };

    class Scene {

        Area* area;
        std::vector<Sprite*> sprites;

        public:
        Scene () {}

        Sprite* createSprite (int x, int y, Image* texture);
        Area* createArea (uint8_t width, uint8_t height, Tile* tiles);
        void removeSprite(Sprite* s);
        std::vector<Sprite*> getSprites();
        
        private:
        void addSprite(Sprite* s);

    };

    class Map {};

}

# endif