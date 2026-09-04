# include <spiral_scene.h>

void spiral::CreateScene (spiral::Scene* &scene, int width, int height, void (*init)(spiral::Window*)) {
    scene = new Scene(width, height, init);
}

void spiral::SetScene (spiral::Scene* scene, spiral::Window* window) {
    window->scene = scene;
}

void spiral::CreateSprite (spiral::Sprite* &sprite, int h, int k) {
    sprite = new Sprite(h, k);
}
void spiral::AddSprite (spiral::Sprite* sprite, spiral::Scene* scene) {
    scene->sprites.push_back(sprite);
}

void spiral::AddPlayer (spiral::Sprite* sprite, spiral::Window* window) {
    window->players.push_back(sprite);
}