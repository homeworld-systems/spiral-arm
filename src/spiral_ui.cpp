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