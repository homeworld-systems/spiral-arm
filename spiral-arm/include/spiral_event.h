# include <spiral_main.h>

# ifndef SPIRAL_EVENT_H

# define SPIRAL_EVENT_H

namespace spiral {

    enum class Event {
        EVENT_KEYDOWN
    };

    struct EventTrigger {
        spiral::Event event;
        void (*callback)(void*, spiral::Window*);
    };

    void AddTrigger (spiral::Event e, void (*callback)(void*, spiral::Window*), spiral::Window* window);

}

# endif