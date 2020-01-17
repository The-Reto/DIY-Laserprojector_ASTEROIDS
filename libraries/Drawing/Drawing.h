#ifndef DRAWING_DRAWING_H
#define DRAWING_DRAWING_H

#include <Laser.h>
#include <Vector.h>

#define USE_HARDWARE

#define CLOSED_LINES 0
#define LINES  1
#define CLOSED_CURVE  2
#define CURVE  3



struct drawingObject {
    char type;
    Vector pos;
    short rot;
    short scale;
    int len;
    COLOR color;
    const short* data;
};

struct scene {
    int noOfObjects;
    int noOfPoints;
    drawingObject objects[16];
    COMMAND* cmds;
};

scene* makeScene();

void buildScene(scene* s);

void drawScene(scene toDraw, LASER l);

void deleteScene(scene* s);

void addObjectToScene(scene* scene, drawingObject object);

#endif //DRAWING_DRAWING_H