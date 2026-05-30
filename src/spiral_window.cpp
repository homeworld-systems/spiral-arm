# include "spiral_window.h"

# include <algorithm>
# include <cmath>

# include <spiral_scene.h>

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
    return scene;
}

void SPIRAL::Window::redrawScene () {
    for (Sprite* s : getScene()->getSprites()) {
        drawSprite(s);
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
    
    blitFast(s->getX(), s->getY(), s->getTexture());

}

const void SPIRAL::Window::blit (int x, int y, SPIRAL::Image* image) { // interface for all blit modes

    return blitSlow(x, y, image); // FIXME: this is just a bandaid fix i just dont wanna implement this rn

}

const void SPIRAL::Window::blitDirty (int x, int y, SPIRAL::Image* image) { // blit entire image at transparency of first value

    uint32_t offset = 0;
    uint32_t transparency = (image->pixels[(uint32_t)0] & 0xff000000) >> 6;

    for (int i = 0; i < image->width * image->height; i++) {

        offset = std::clamp((
            (uint32_t)y + 
            (uint32_t)std::round((i + 1) / image->width)
        ) * width + (uint32_t)x, (uint32_t)0, (uint32_t)(width * height));

        buffer[offset] = (uint32_t)((
            (uint64_t)image->pixels[(uint32_t)i] + (uint64_t)buffer[offset]
        ) / 2); // take average of existing pixel and new pixel

    }

}

const void SPIRAL::Window::blitOptimised (int x, int y, SPIRAL::Image* image) { // blitSlow w/ buffer skipping optimisations

    const uint32_t initial_buffer_size = 64; // n
    const uint32_t max_depth = 8; // how many times n can be split
    
    int buffer_size = initial_buffer_size;
    int current_depth = max_depth;
    
    uint32_t position = 0;

    // TODO: FINISH THIS
    
}

const void SPIRAL::Window::blitSlow (int x, int y, SPIRAL::Image* image) { // supports transparency, slow
    /* this is still left in the codebase as while normally slower than blitOptimised w/ an 
    identical result, in some cases (i.e. lots of transparency of different values) it may be faster */

    uint32_t offset = 0;

    for (int i = 0; i < image->width * image->height; i++) {

        uint32_t transparency = (image->pixels[(uint32_t)i] & 0xff000000) >> 6;

        switch (transparency) {

            case 0: // for code clarity
                break;
            
            case 255: // skip taking average since pixel is opaque
                offset = std::clamp((
                    (uint32_t)y + 
                    (uint32_t)std::round((i + 1) / image->width)
                ) * width + (uint32_t)x, (uint32_t)0, (uint32_t)(width * height));

                buffer[offset] = image->pixels[(uint32_t)i];

            default: // everything else
                offset = std::clamp((

                    (uint32_t)y + 
                    (uint32_t)std::round((i + 1) / image->width)

                ) * width + (uint32_t)x, (uint32_t)0, (uint32_t)(width * height));

                buffer[offset] = (uint32_t)((
                    (uint64_t)image->pixels[(uint32_t)i] + (uint64_t)buffer[offset]
                ) / 2); // take average of existing pixel and new pixel

        }

    }

}

const void SPIRAL::Window::blitFast (int x, int y, SPIRAL::Image* image) { // direct memory copy, fast

    for (int r = 0; r < std::clamp(image->height, 0, height - y); r++) {
    
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

}