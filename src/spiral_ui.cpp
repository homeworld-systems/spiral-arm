# include "spiral_ui.h"

void SPIRAL::Select::next () {
    selected_index = (selected_index + 1) % options.size();
}

void SPIRAL::Select::previous () {
    selected_index = (selected_index - 1) % options.size();
}

void SPIRAL::Select::set (int i) {
    selected_index = i % options.size();
}

int SPIRAL::Select::result () {
    return selected_index;
}

int SPIRAL::TextBox::getX () {
    return x;
}

int SPIRAL::TextBox::getY () {
    return y;
}

int SPIRAL::TextBox::getWidth () {
    return width;
}

int SPIRAL::TextBox::getHeight () {
    return height;
}