# include <spiral_main.h>
# include <spiral_scene.h>

void chapter1_scene_test_init (spiral::Window* window) {

}

void chapter1_init (spiral::Window* window) {

    spiral::Camera* camera;
    spiral::Scene* scene_test;
    spiral::Sprite* chara;

    // spiral::LoadScene(scene_test, "res/scenes/scene_test.star_rm");
    spiral::CreateScene(scene_test, 20, 16, chapter1_scene_test_init);
    spiral::SetScene(scene_test, window);

    spiral::InitCamera(camera, 320, 240, window);
    spiral::CreateSprite(chara, 0, 0);
    spiral::AddPlayer(chara, window);

}

void chapter1_frame (spiral::Window* window) {

}

void chapter1_tick (spiral::Window* window) {

}

int main () {

    spiral::Window* window;
    spiral::InitWindow(window, 320, 240, 6, "SPIRAL ARM TEST");
    spiral::StartChapter(chapter1_init, chapter1_frame, chapter1_tick, window);

    return 0;

}