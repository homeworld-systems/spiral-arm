# include <spiral_main.h>

# ifndef SPIRAL_SCENE_H

# define SPIRAL_SCENE_H

namespace spiral {

    void CreateScene (spiral::Scene* &scene, int width, int height, void (*init)(spiral::Window*));
    void SetScene (spiral::Scene* scene, spiral::Window* window);

    void CreateSprite (spiral::Sprite* &sprite, int h, int k);
    void AddSprite (spiral::Sprite* sprite, spiral::Scene* scene);
    void AddPlayer (spiral::Sprite* sprite, spiral::Window* window);

    class Scene {

        private:

        const int STATE_UNINITIALIZED = 0;
        const int STATE_INITIALIZED = 1;

        int state;
        int width;
        int height;

        void (*scene_init)(spiral::Window*);

        std::vector<Sprite*> sprites;

        Scene (int w, int h, void (*init)(spiral::Window*)) : state(STATE_UNINITIALIZED), width(w), height(h) {}

        friend void spiral::CreateScene (spiral::Scene* &scene, int width, int height, void (*init)(spiral::Window*));
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