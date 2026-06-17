# include "spiral_window.h"
#include "spiral_graphics.h"

# include <algorithm>
# include <iostream>

# include <spiral_scene.h>
# include <spiral_math.h>
# include <constants.h>

void SPIRAL::Window::create () {

    SDL_Init(SDL_INIT_VIDEO);
    buffer = new uint32_t[width * height];
    __window = SDL_CreateWindow(name, width * scale, height * scale, 0);
    __renderer = SDL_CreateRenderer(__window, "gpu");
    __texture = SDL_CreateTexture(__renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    // Set to nearest-neighbor scaling
    SDL_SetTextureScaleMode(__texture, SDL_ScaleMode::SDL_SCALEMODE_NEAREST);
    
}

bool SPIRAL::Window::update () {

    SDL_Event e;

    if (SDL_PollEvent(&e)) {

        if (e.type == SDL_EVENT_QUIT)
            return false;

        if (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE) 
            return false;

    }

    unsigned char* pixels;
    int pitch;
  
    SDL_LockTexture(__texture, NULL, (void**)&pixels, &pitch);
    
    uint8_t* dest_row;
    uint32_t* source_row;

    for (int y = 0; y < height; y++) {

        dest_row = pixels + y * pitch;
        source_row = buffer + y * width;

        memcpy(dest_row, source_row, width * sizeof(uint32_t));

    }
    

    SDL_UnlockTexture(__texture);  
    SDL_RenderTexture(__renderer, __texture, NULL, NULL);
    SDL_RenderPresent(__renderer);
    
    return true;

}

void SPIRAL::Window::gracefulExit () {
    
    delete buffer;
    
    SDL_DestroyTexture(__texture);
    SDL_DestroyRenderer(__renderer);
    SDL_DestroyWindow(__window);
    SDL_Quit();

}

void SPIRAL::Window::createScene () {
    scene = new Scene();
}

SPIRAL::Scene* SPIRAL::Window::getScene () {
    if (scene != nullptr) {
        return scene;
    }
    else {
        std::cerr << "[SPIRAL ARM] Scene has not been created.\n";
        std::exit(EXIT_FAILURE);
    }
}

void SPIRAL::Window::redrawScene () {

    std::vector<Sprite*> sprites = scene->getSprites();

    for (Sprite* s : sprites) {

        int x = s->getX();
        int y = s->getY();
        int width = s->getTexture()->width;
        int height = s->getTexture()->height;

        if (SPIRAL::AABBCollision(
            {x, y, width, height},
            {0, 0, FRAME_WIDTH, FRAME_HEIGHT})) { // CHANGE THESE TO BE CAMERA BASED LATER
            drawSprite(s);
        }

    }

    Area* area = scene->getArea();
    Tileset* tileset = scene->getTileset();
    uint8_t height = area->height;
    uint8_t width = area->width;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint8_t tile_type = area->tiles[y * width + x].type;
            blit(x * 20, y * 20, (*tileset)[256], false);
        }
    }


}

const void SPIRAL::Window::clear (SPIRAL::Color color) {

    for (int p = 0; p < width * height; p++) {
        buffer[(uint32_t)p] = color;
    }

}

const void SPIRAL::Window::drawPixel (int x, int y, SPIRAL::Color color) {

    buffer[(uint32_t)x + (uint32_t)y * width] = color;

}

const void SPIRAL::Window::drawRectangle (int x, int y, int w, int e, SPIRAL::Color color) {

    int clamped_width = std::max(0, std::min(x + w, width) - x);
    int clamped_height = std::max(0, std::min(y + e, height) - y);

    for (int k = y; k < y + clamped_height; k++) {
        for (int h = x; h < x + clamped_width; h++) {
            buffer[(uint32_t)h + (uint32_t)k * width] = color;
        }
    }

}

const void SPIRAL::Window::drawTextBox (SPIRAL::TextBox b) {

    drawRectangle(b.getX(), b.getY(), b.getWidth(), b.getHeight(), WHITE);
    drawRectangle(b.getX() + b.getLineWidth(), b.getY() + b.getLineWidth(), b.getWidth() - 2 * b.getLineWidth(), b.getHeight() - 2 * b.getLineWidth(), BLACK);

}

const void SPIRAL::Window::drawSprite (SPIRAL::Sprite* s) {
    
    blit(s->getX(), s->getY(), s->getTexture());

}

const void SPIRAL::Window::blit (int x, int y, SPIRAL::Image* image, bool transparency) { // interface for all blit modes

    if ((height - y) < 0) { return; }

    if (transparency) { // PARTIAL TRANSPARENCY (REQUIRES TRANSPARENCY VALUES)

        for (int r = 0; r < std::clamp(image->height, 0, height - y); r++) {

            uint32_t* from = image->pixels + (uint32_t)r * image->width;
            uint32_t* to = buffer + ((uint32_t)y + r) * width + (uint32_t)x;

            if ((uint32_t)((width - x) * sizeof(Color)) <= 0) {

                continue;

            }

            uint32_t length = std::clamp(

                (uint32_t)(sizeof(Color) * image->width),
                (uint32_t)0, (uint32_t)((width - x) * sizeof(Color))

            );

            uint32_t offset = 0;

            while (offset < length) {

                if ((from[offset] & 0xFF000000) == 0xFF000000) {

                    to[offset] = from[offset];

                }
                
                offset += sizeof(Color);

            }

            offset = 1;

        }

    } else { // NO TRANSPARENCY (TRANSPARENT VALUES WILL BE IGNORED) (FASTER)

        for (int r = 0; r < std::clamp(image->height, 0, height - y); r++) {

            if ((uint32_t)((width - x) * sizeof(Color)) <= 0) {

                continue;

            }
            
            memcpy(

                buffer + ((uint32_t)y + r) * width + (uint32_t)x,
                image->pixels + (uint32_t)r * image->width,
                std::clamp(

                    (uint32_t)(sizeof(Color) * image->width),
                    (uint32_t)0,
                    (uint32_t)((width - x) * sizeof(Color))
                    
                ) // all the casts to uint32_t are to ensure parity across architectures

            );

        }

        return;

    }

}