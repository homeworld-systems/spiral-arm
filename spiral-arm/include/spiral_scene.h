# include <spiral_main.h>

# ifndef SPIRAL_SCENE_H

# define SPIRAL_SCENE_H

namespace spiral {

    struct Map {

        int width;
        int height;

        uint16_t* tiles;
        uint8_t* terrain;

        Map(int w, int h, uint16_t* tl, uint8_t* tr) : width(w), height(h), tiles(tl), terrain(tr) {}

    };

    void CreateScene (spiral::Scene* &scene, int width, int height, spiral::Map* map, void (*init)(spiral::Window*));
    void SetScene (spiral::Scene* scene, spiral::Window* window);

    void CreateSprite (spiral::Sprite* &sprite, int h, int k);
    void AddSprite (spiral::Sprite* sprite, spiral::Scene* scene);
    void SetMap (spiral::Map* map, spiral::Scene* scene);
    void AddPlayer (spiral::Sprite* sprite, spiral::Window* window);

    class Scene {

        private:

        int state;
        int width;
        int height;

        void (*scene_init)(spiral::Window*);

        Map* map;
        std::vector<Sprite*> sprites;

        Scene (int w, int h, Map* m, void (*init)(spiral::Window*)) : width(w), height(h), map(m), scene_init(init) {}

        friend bool spiral::Window::update ();
        friend void spiral::CreateScene (spiral::Scene* &scene, int width, int height, spiral::Map* map, void (*init)(spiral::Window*));
        friend void spiral::SetScene (spiral::Scene* scene, spiral::Window* window);
        friend void spiral::AddSprite (spiral::Sprite* sprite, spiral::Scene* scene);

    };

    class Sprite {

        int x;
        int y;

        Sprite (int h, int k) : x(h), y(k) {}

        friend void spiral::CreateSprite(spiral::Sprite* &sprite, int h, int k);

    };

}

# endif