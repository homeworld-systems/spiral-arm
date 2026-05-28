# ifndef SPIRAL_GUI_H

# define SPIRAL_GUI_H

# include <vector>

namespace SPIRAL {

    class TextBox {

        int x;
        int y;
        int width;
        int height;
        bool selected;
        const char* text;

        public:
        TextBox () : x(0), y(0), width(0), height(0), selected(false), text("") {}
        TextBox (int h, int k, int w, int e, const char* t) : x(h), y(k), width(w), height(e), text(t) {}

        int getX ();
        int getY ();
        int getWidth ();
        int getHeight ();

    };

    class Select {

        std::vector<TextBox> options;
        std::vector<TextBox>::size_type selected_index;

        public:
        Select () : options(std::vector<TextBox>()), selected_index(0) {}
        Select (std::vector<TextBox> o) : options(o), selected_index(0) {}
        void next ();
        void previous ();
        void set (int i);
        int result ();

    };

    class Dialogue;

}

# endif