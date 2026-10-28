# include <spiral_main.h>
# include <spiral_graphics.h>

# ifndef SPIRAL_SCENE_H

# define SPIRAL_SCENE_H

namespace spiral {

    struct Tileset {

        const uint16_t* indices;
        const Image* textures;

        Tileset(const uint16_t i[], const Image t[]) : indices(i), textures(t) {}

    };

    struct Map {

        const int width;
        const int height;

        uint16_t* tiles;
        uint8_t* terrain;

        Tileset tileset;

        Map(const int w, const int h, uint16_t tls[], uint8_t trn[], Tileset tst) : width(w), height(h), tiles(tls), terrain(trn), tileset(tst) {}

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