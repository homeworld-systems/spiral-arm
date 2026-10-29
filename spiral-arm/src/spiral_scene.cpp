# include <spiral_scene.h>

void spiral::CreateMap (spiral::Map* &map, const int width, const int height) {
    map = new Map(width, height);
}

void spiral::CreateScene (spiral::Scene* &scene, int width, int height, spiral::Map* map, void (*init)(spiral::Window*)) {
    scene = new Scene(width, height, map, init);
}

void spiral::DestroyScene (spiral::Scene* &scene) {
    delete scene;
    scene = nullptr;
}

void spiral::SetScene (spiral::Scene* scene, spiral::Window* window) {
    window->scene = scene;
    scene->scene_init(window);
}

// uses ref to pointer since it's creating/destroying
void spiral::CreateSprite (spiral::Sprite* &sprite, int h, int k) {
    sprite = new Sprite(h, k);
}

void spiral::DestroySprite (spiral::Sprite* &sprite) {
    delete sprite;
    sprite = nullptr;
}

void spiral::AddSprite (spiral::Sprite* sprite, spiral::Scene* scene) {
    scene->sprites.push_back(sprite);
}

void spiral::AddPlayer (spiral::Sprite* sprite, spiral::Window* window) {
    window->players.push_back(sprite);
}