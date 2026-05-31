# include <spiral_math.h>

bool SPIRAL::AABBCollision (SPIRAL::Rectangle A, SPIRAL::Rectangle B) {
    return (
        A.x <= B.x + B.width &&
        A.x + A.width >= B.x &&
        A.y <= B.y + B.height &&
        A.y + A.height >= B.y
    );
}