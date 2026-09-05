# ifndef SPIRAL_MAIN_H

# define SPIRAL_MAIN_H

# include <vector>
# include <unordered_map>

# include <SDL3/SDL.h>
# include <SDL3/SDL_render.h>

namespace spiral {

    // Forward declarations because SPIRAL_MAIN_H should never reference other Spiral Arm files

    class Window;
    class Camera;
    class Scene;
    class Sprite;
    enum class Event;
    void AddTrigger (spiral::Event e, void (*callback)(void*, spiral::Window*), spiral::Window* window);

    // End forward declarations

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

        std::unordered_multimap<spiral::Event, void(*)(void*, spiral::Window*)> event_triggers;

        public:
        spiral::Scene* scene;
        spiral::Camera* camera;
        std::vector<spiral::Sprite*> players;

        bool update ();
        void gracefulExit ();

        void (*chapter_init)(spiral::Window*);
        void (*chapter_frame)(spiral::Window*);
        void (*chapter_tick)(spiral::Window*);

        private:
        Window (int w, int h, int s, const char* n) : width(w), height(h), scale(s), name(n) {}

        friend void spiral::AddTrigger (spiral::Event e, void (*callback)(void*, spiral::Window*), spiral::Window* window);

        friend void InitWindow (spiral::Window* &window, int width, int height, int scale, const char* name);
        friend void Clear (spiral::Color color, spiral::Window* window);
        friend void DrawPixel (int x, int y, spiral::Color color, spiral::Window* window);
        friend void DrawRectangle (int x, int y, int w, int h, spiral::Color color, spiral::Window* window);

    };

    void Clear (spiral::Color color, spiral::Window* window);
    void DrawPixel (int x, int y, spiral::Color color, spiral::Window* window);
    void DrawRectangle (int x, int y, int w, int h, spiral::Color color, spiral::Window* window);

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

    void Start (spiral::Window* window);
    void SwitchChapter (void (*chapter_init)(spiral::Window*), void (*chapter_frame)(spiral::Window*), void (*chapter_tick)(spiral::Window*), spiral::Window* window);

}

# endif