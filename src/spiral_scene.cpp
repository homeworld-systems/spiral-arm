# include "spiral_scene.h"

# include <algorithm>

SPIRAL::Image* SPIRAL::Sprite::getTexture () {
    return &texture;
}

int SPIRAL::Sprite::getX () const {
    return x;
}

int SPIRAL::Sprite::getY () const {
    return y;
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

std::vector<SPIRAL::Sprite*> SPIRAL::Scene::getSprites() {
    return sprites;
}