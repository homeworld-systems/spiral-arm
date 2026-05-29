# ifndef SPIRAL_WINDOW_H

# define SPIRAL_WINDOW_H

# include <spiral_graphics.h>
# include <spiral_ui.h>

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

        // stuff
        void redrawScene ();

        // Drawing Functions
        void clear (Color color);

        // Primitives
        void drawPixel (int x, int y, Color color);
        void drawRectangle (int x, int y, int width, int height, Color color);

        // UI
        void drawTextBox (TextBox b);

        // Textures
        const void blitFast (int x, int y, SPIRAL::Image* image);

    };

}

# endif