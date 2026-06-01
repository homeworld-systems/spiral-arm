# ifndef SPIRAL_WINDOW_H

# define SPIRAL_WINDOW_H

# include <spiral_graphics.h>
# include <spiral_ui.h>
# include <spiral_scene.h>

# include <SDL3/SDL.h>
# include <SDL3/SDL_render.h>

namespace SPIRAL {

    class Window {

        SDL_Window* __window;
        SDL_Renderer* __renderer;
        SDL_Texture* __texture;

        int width;
        int height;
        int scale;
        const char* name;
        
        public:

        Color* buffer;

        Window (const char* n, int w, int h, int s) : name(n), width(w), height(h), scale(s) {}
        void create ();
        bool update ();
        void gracefulExit ();

        // Rendering
        void redrawScene ();

        // Scene things

        Scene* scene;

        void createScene ();
        Scene* getScene ();

        // Rendering Functions
        const void clear (Color color);
        const void blit (int x, int y, SPIRAL::Image* image, bool transparency = 0);

        // Primitives
        const void drawPixel (int x, int y, Color color);
        const void drawRectangle (int x, int y, int width, int height, Color color);

        // Drawing
        const void drawTextBox (TextBox b);
        const void drawSprite (Sprite* s);

        private:

        // PeepoScared (former hall of the ancient elven blit queens)

    };

}

# endif