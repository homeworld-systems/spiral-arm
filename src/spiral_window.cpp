# include "spiral_window.h"

# include <algorithm>
# include <cmath>
# include <iostream>

# include <spiral_scene.h>
# include <constants.h>
# include <spiral_math.h>

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
    for (Sprite* s : getScene()->getSprites()) {
        if (SPIRAL::AABBCollision(
            {s->getX(), s->getY(), s->getTexture()->width, s->getTexture()->height},
            {0, 0, FRAME_WIDTH, FRAME_HEIGHT})) { // CHANGE THESE TO BE CAMERA BASED LATER
            drawSprite(s);
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
    /* consider an initial buffer of data k and a buffer size p. to begin with, check if SUM of [first p of k]
     XOR [transparency bitmask] is expected value for uniform transparency. if yes, check for fully transparent
     / fully opaque, then if neccesary perform blitDirty approach. if no, then split buffer [jth p of k] where
     j is the current depth into halves, before then repeating SUM of [jth p of k] XOR [transparency bitmask] and
     checking for expected value. follow same condition check as earlier, repeating this process until either all
     checks success or the max depth (value) of j is hit. if this max value of j, being h, is it (j == h) then
     transparency is sufficiently dense and traditional blitSlow approach is used as benefits of optimisations now
     are outweighed by overhead */
    
    #define transparency_bitmask_unscaled       0x00FFFFFF  // unscaled bitmask to be repeated (ARGB8888)

    #define initial_buffer_size                 32;         // n, in bytes, must be less than 32
    #define max_depth                           8;          // h, must be less than 256
    
    uint8_t buffer_size = initial_buffer_size;
    uint8_t current_depth = max_depth;
    
    uint32_t position = 0;

    for (int i = 0; i < (image->width * image->height); i += buffer_size) {
        // (((image->pixels[(uint32_t)0] & 0xff000000) >> 6) << 6)
    }

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