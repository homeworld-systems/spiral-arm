# ifndef SPIRAL_SCENE_H

# define SPIRAL_SCENE_H

# include <spiral_graphics.h>
# include <spiral_input.h>

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

        bool operator< (const Sprite& _sprite) const;

    };

    struct Keybind {
        Scancode key;
        void* (*action)();
    };

    class Scene {

        std::vector<Sprite*> sprites;
        std::vector<Keybind> keybinds;

        public:
        Scene () {}
        void tick ();

        SPIRAL::Sprite* createSprite (int x, int y, SPIRAL::Image* texture);
        void removeSprite(Sprite* s);
        std::vector<Sprite*> getSprites();

        void addKeybind (Keybind keybind);

        private:
        void addSprite(Sprite* s);

    };

    class Map {};

}

# endif