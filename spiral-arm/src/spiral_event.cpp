# include <spiral_event.h>

# include <spiral_main.h>

void spiral::AddTrigger (spiral::Event e, void (*callback)(void*, spiral::Window*), spiral::Window* window) {
    window->event_triggers.insert({e, callback});
}