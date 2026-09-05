# include <spiral_main.h>
# include <spiral_scene.h>
# include <spiral_graphics.h>
# include <spiral_event.h>

# include <cstdio>

namespace chapter2 {

    void scr_frame (spiral::Window* window) {

    }

    void scr_tick (spiral::Window* window) {

    }

    void scr_init (spiral::Window* window) {
        spiral::Clear(spiral::COLOR_CYAN, window);
    }

}

namespace chapter1 {

    namespace scene_test {

        void scr_init (spiral::Window* window) {
            
        }

        void scr_chapterswitch (void* data, spiral::Window* window) {
            
            spiral::SwitchChapter(chapter2::scr_init, chapter2::scr_frame, chapter2::scr_tick, window);

        }

    }

    void scr_init (spiral::Window* window) {

        spiral::Camera* camera;
        spiral::Scene* scene_test;
        spiral::Sprite* chara;

        // spiral::LoadScene(scene_test, "res/scenes/scene_test.star_rm");
        spiral::CreateScene(scene_test, 20, 16, chapter1::scene_test::scr_init);
        spiral::SetScene(scene_test, window);

        spiral::InitCamera(camera, 320, 240, window);
        spiral::CreateSprite(chara, 0, 0);
        spiral::AddPlayer(chara, window);

        spiral::Clear(spiral::COLOR_MAGENTA, window);

        spiral::AddTrigger(spiral::Event::EVENT_KEYDOWN, chapter1::scene_test::scr_chapterswitch, window);

    }

    void scr_frame (spiral::Window* window) {

    }

    void scr_tick (spiral::Window* window) {

    }

}

int main () {

    spiral::Window* window;
    spiral::InitWindow(window, 320, 240, 6, "SPIRAL ARM TEST");
    spiral::SwitchChapter(chapter1::scr_init, chapter1::scr_frame, chapter1::scr_tick, window);
    spiral::Start(window);

    return 0;

}