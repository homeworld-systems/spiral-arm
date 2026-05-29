# ifndef SPIRAL_INPUT_H

# define SPIRAL_INPUT_H

# include <cstdint>
# include <vector>

namespace SPIRAL {

    typedef uint32_t Scancode;

    bool IsKeyDown(SPIRAL::Scancode c);
    std::vector<Scancode> GetKeysDown();

}

# endif