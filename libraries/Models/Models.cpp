#include <Data.h>
#include "Models.h"
#include "../Drawing/Data.h"
#include "../Vector/Vector.h"



void calculateBoundingBox(struct gameObject *obj);

//NOTE: ALL INTEGERS GIVEN INTO FUNCTIONS (except for color) MUST BE FIXPOINT-ADJUSTED

struct line *lineConstructor(int posx, int posy, int magx, int magy, int color) {
    struct line *line = (struct line*) malloc(sizeof(struct line));
    Vector position = {posx, posy};
    line->pos = position;
    line->color = color;
    Vector magnitude = {magx, magy};
    line->magnitude = magnitude;
    return line;
}

//generates a shot if shoot() is called in library: Asteroids
struct gameObject generateShot(int posx, int posy, int color, Vector velocity) {
    struct gameObject shot;

    shot.graphics = SHOT;

    Vector centerpos = {posx , posy};
    shot.graphics.pos = centerpos;
    shot.velocity = velocity;
    shot.type = bullet;
    shot.reset = 0;
    calculateBoundingBox(&shot);
    return shot;
}

struct gameObject
generateClosedFigure(int posx, int posy, int color, Vector velocity,
                     enum TYPE typ, enum ASTRTYPE astr) {
    struct gameObject obj;
    switch (typ) {
        case player:
            obj.graphics = SHIP;
            obj.graphics.scale = 2;
            break;
        case asteroid:
            obj.graphics = ROCK;
            break;
        case bullet:
        case gameover:
        default:
            //should never happen
            break;
    }
    obj.graphics.color = color;
    obj.graphics.pos = {posx, posy};
    obj.velocity = velocity;
    obj.type = typ;
    obj.reset = 0;
    if(typ == asteroid){
        obj.astrtype = astr;
    }
    else{
        obj.astrtype = NOAS;
    }
    switch (astr) {
        case big:
            obj.graphics.scale = 6;
            break;
        case medium:
            obj.graphics.scale = -4;
            break;
        case small:
            obj.graphics.scale = 2;
            break;
        case NOAS:
            obj.graphics.scale = 1;
            break;
        default:
            //should never happen
            break;
    }

    calculateBoundingBox(&obj);
    return obj;
}

void rotateObject(struct gameObject* obj, int angle){
    obj->graphics.rot += angle;
    if (obj->graphics.rot < 0) obj->graphics.rot += 360;
    obj->graphics.rot = obj->graphics.rot % 360;

    calculateBoundingBox(obj);
}

gameObject emptyObject() {
    gameObject o;
    o.reset = 1;
    return o;
}

void calculateBoundingBox(struct gameObject *obj) {
    obj->mosteast = 0;
    obj->mostwest = 0;
    obj->mostnorth = 0;
    obj->mostsouth = 0;
    for (int i = 0; i < obj->graphics.len; i=i+2) {
        Vector pos = {((short) pgm_read_word(&obj->graphics.data[i])), ((short) pgm_read_word(&obj->graphics.data[(i + 1)]))};
        pos = rotate(pos, obj->graphics.rot);
        int temposx = (obj->graphics.scale * pos.x);
        int temposy = (obj->graphics.scale * pos.y);


        if (temposx >=  obj->mosteast)  (*obj).mosteast = temposx;
        if (temposx <= obj->mostwest) (*obj).mostwest = temposx;
        if (temposy >= obj->mostsouth) (*obj).mostsouth = temposy;
        if (temposy <= obj->mostnorth) (*obj).mostnorth = temposy;
    }
}
