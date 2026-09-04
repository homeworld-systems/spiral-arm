# ifndef SPIRAL_MAIN_H

# define SPIRAL_MAIN_H

# include <vector>

# include <SDL3/SDL.h>
# include <SDL3/SDL_render.h>

namespace spiral {

    // Forward declarations because SPIRAL_MAIN_H should never reference other Spiral Arm files

    class Window;
    class Camera;
    class Scene;
    class Sprite;

    typedef uint32_t Color;

    void InitWindow (spiral::Window* &window, int width, int height, int scale, const char* name);

    class Window {

        private:
        int width;
        int height;
        int scale;
        const char* name;

        spiral::Color* buffer;
        SDL_Window* __window;
        SDL_Renderer* __renderer;
        SDL_Texture* __texture;

        public:
        spiral::Scene* scene;
        spiral::Camera* camera;
        std::vector<spiral::Sprite*> players;

        bool update ();
        void gracefulExit ();
        const void clear (spiral::Color color);
        const void drawPixel (int x, int y, spiral::Color color);
        const void drawRectangle (int x, int y, int w, int e, spiral::Color color);

        private:
        Window (int w, int h, int s, const char* n) : width(w), height(h), scale(s), name(n) {}

        friend void InitWindow (spiral::Window* &window, int width, int height, int scale, const char* name);

    };

    void InitCamera (spiral::Camera* &camera, int w, int h, spiral::Window* window);

    class Camera {

        private:
        int scene_x;
        int scene_y;
        int view_width;
        int view_height;

        private:
        spiral::Scene* scene;

        friend void spiral::InitCamera (spiral::Camera* &camera, int w, int h, spiral::Window* window);

    };

    void StartChapter (void (*chapter_init)(spiral::Window*), void (*chapter_frame)(spiral::Window*), void (*chapter_tick)(spiral::Window*), spiral::Window* window);

}

# endif