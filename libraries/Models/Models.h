#ifndef MODELS_MODELS_H
#define MODELS_MODELS_H

#include <stdio.h>
#include <stdlib.h>
#include <FixPoint.h>
#include <Drawing.h>
#include <Vector.h>
#include <Laser.h>


enum TYPE {
    player, asteroid, bullet, gameover
};
enum ASTRTYPE {NOAS, big, medium, small};

struct line {
    //NOTE: POSITION OF LINE IS RELATIVE TO CENTER OF OBJECT
    Vector pos;
    Vector magnitude;
    int color;
};

struct gameObject {
    struct drawingObject graphics;
    Vector velocity;
    enum TYPE type;
    enum ASTRTYPE astrtype;
    int mostsouth = 0;
    int mostnorth = 0;
    int mosteast = 0;
    int mostwest = 0;
    char reset = 0;
};

struct line* lineConstructor(int posx, int posy, int magx, int magy, int color);

struct gameObject emptyObject();

struct gameObject generateShot(int posx, int posy, int color, Vector velocity);

struct gameObject generateClosedFigure(int posx, int posy, int color, Vector velocity, enum TYPE typ, enum ASTRTYPE astr);

void rotateObject(struct gameObject *obj, int angle);



#endif //MODELS_MODELS_H