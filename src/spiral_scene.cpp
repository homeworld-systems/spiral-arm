# include "spiral_scene.h"

SPIRAL::Image* SPIRAL::Sprite::getTexture () {
    return &texture;
}

int SPIRAL::Sprite::getX () {
    return x;
}

int SPIRAL::Sprite::getY () {
    return y;
}