#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <FixPoint.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct vector Vector;

struct vector {
    int x, y;
};

Vector add(Vector v1, Vector v2);

Vector multiply(Vector v, int scale);

Vector rotate(Vector v, int angle);

int eq(Vector v1, Vector v2);

#ifdef __cplusplus
}
#endif

#endif //VECTOR_VECTOR_H