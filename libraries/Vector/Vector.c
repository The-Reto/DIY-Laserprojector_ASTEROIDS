#include "Vector.h"

#ifdef __cplusplus
extern "C"{
#endif

Vector add(Vector v1, Vector v2) {
    return (Vector) {.x = v1.x + v2.x, .y = v1.y + v2.y};
}

Vector multiply(Vector v, int scale) {
    return (Vector) {.x = v.x * scale, .y = v.y * scale};
}

Vector rotate(Vector v, int angle) {
    return (Vector) { .x = fixedToInt(fpCos(angle) * v.x) + fixedToInt(fpSin(angle) * v.y), .y = fixedToInt(fpCos(angle) * v.y) - fixedToInt(fpSin(angle) * v.x) };
}

int eq(Vector v1, Vector v2) {
    return (v1.x == v2.x) && (v1.y == v2.y);
}
#ifdef __cplusplus
}
#endif