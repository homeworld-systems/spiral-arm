# include "spiral_scene.h"

# include <algorithm>
# include <iostream>

SPIRAL::Image* SPIRAL::Sprite::getTexture () {
    return &texture;
}

int SPIRAL::Sprite::getX () const {
    return x;
}

int SPIRAL::Sprite::getY () const {
    return y;
}

void SPIRAL::Sprite::setX (int h) {
    x = h;
}

void SPIRAL::Sprite::setY (int k) {
    y = k;
}

void SPIRAL::Sprite::setPosition (int h, int k) {
    x = h;
    y = k;
}

void SPIRAL::Sprite::changeX(int dx) {
    x += dx;
}

void SPIRAL::Sprite::changeY(int dy) {
    y += dy;
}

bool SPIRAL::Sprite::operator< (const Sprite& _sprite) const {
    return _sprite.getY() < y; // REVERSED IS NECESSARY. RENDER IN Y-AXIS ORDER
}

SPIRAL::Sprite* SPIRAL::Scene::createSprite (int x, int y, SPIRAL::Image* texture) {
    SPIRAL::Sprite* spr = new SPIRAL::Sprite(x, y, *texture);
    delete texture;
    addSprite(spr);
    return spr;
}

void SPIRAL::Scene::addSprite (SPIRAL::Sprite* s) {
    sprites.push_back(s);
    std::sort(sprites.begin(), sprites.end());
}

void SPIRAL::Scene::removeSprite (SPIRAL::Sprite* s) {
    for (int i = 0; i < sprites.size(); i++) {
        if (sprites[i] == s) {
            sprites.erase(sprites.begin() + i);
        }
    }
    std::sort(sprites.begin(), sprites.end());
}

SPIRAL::Area* SPIRAL::Scene::createArea (uint8_t width, uint8_t height, SPIRAL::Tile* tiles) {
    area = (SPIRAL::Area*)malloc(sizeof(SPIRAL::Area));
    area->tiles = (SPIRAL::Tile*)malloc(width * height * sizeof(SPIRAL::Tile));
    memcpy(area->tiles, tiles, width * height * sizeof(SPIRAL::Tile));
    return area;
}

std::vector<SPIRAL::Sprite*> SPIRAL::Scene::getSprites() {
    return sprites;
}