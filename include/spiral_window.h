# ifndef SPIRAL_WINDOW_H

# define SPIRAL_WINDOW_H

# include <spiral_graphics.h>

# include <SDL3/SDL_main.h>
# include <SDL3/SDL_render.h>

class SPIRAL_Window {

    SDL_Window* __window;
    SDL_Renderer* __renderer;
    SDL_Texture* __texture;

    int width;
    int height;
    int scale;
    const char* name;
    
    public:

    SPIRAL_Color* buffer;

    SPIRAL_Window (const char* n, int w, int h, int s) : name(n), width(w), height(h), scale(s) {}
    void create ();
    bool update ();
    void gracefulExit ();

    // stuff
    void redrawScene ();

    // Drawing Functions
    void clear ();
    void drawPixel (int x, int y, SPIRAL_Color color);

};

# endif