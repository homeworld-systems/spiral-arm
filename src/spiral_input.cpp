# include <spiral_input.h>

# include <SDL3/SDL.h>

bool SPIRAL::IsKeyDown(SPIRAL::Scancode c) {

    int keycount;
    const bool* keyboard_state = SDL_GetKeyboardState(&keycount);

    return keyboard_state[c];

}

std::vector<SPIRAL::Scancode> SPIRAL::GetKeysDown() {

    std::vector<SPIRAL::Scancode> codes;

    int keycount;
    const bool* keyboard_state = SDL_GetKeyboardState(&keycount);

    for (int c = 0; c < keycount; c++) { // C++ !!! [YIPPEEEEEEE!!!!]
        if (keyboard_state[c]) {
            codes.push_back((SPIRAL::Scancode)c);
        }
    }

    return codes;

}