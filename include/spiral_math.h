# ifndef SPIRAL_MATH_H

# define SPIRAL_MATH_H

namespace SPIRAL {

    struct Rectangle {
        int x;
        int y;
        int width;
        int height;
    };

    bool AABBCollision (Rectangle A, Rectangle B);

}

# endif