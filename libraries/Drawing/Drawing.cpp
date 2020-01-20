#include "Drawing.h"

int makeLine(COMMAND *arr, int start, short xStart, short yStart, short xEnd, short yEnd, COLOR col);

void addObjectToSceneCommands(scene* scene, drawingObject object);

void addClosedLinesToScene(scene* scene, drawingObject object);

void addLinesToScene(scene* scene, drawingObject object);

void addCurveToScene(scene* scene, drawingObject object);

void addClosedCurveToScene(scene* scene, drawingObject object);

int getLineResFromDxDy(unsigned int dx, unsigned int dy);

int getMoveResFromDxDy(unsigned int dx, unsigned int dy);

Vector translation(Vector orig, Vector translation);

Vector scale(Vector point, short scale);

void setColerChangeFlag(scene *s);

void drawScene(scene toDraw, LASER l) {
    for (int i = 0; i < toDraw.noOfPoints; ++i) {
        moveLaser(&l, toDraw.cmds[i]);
    }
}

void buildScene(scene* s) {
    s->noOfPoints = 0;
    for (int i = 0; i < s->noOfObjects; ++i) {
        addObjectToSceneCommands(s, s->objects[i]);
        s->noOfPoints += makeLine(s->cmds, s->noOfPoints,  s->objects[i].pos.x,  s->objects[i].pos.y,  s->objects[(i + 1) %  s->noOfObjects].pos.x, s->objects[(i + 1) %  s->noOfObjects].pos.y,0);
    }
    setColerChangeFlag(s);
}

void setColerChangeFlag(scene *s) {
    COMMAND curr = s->cmds[0];
    s->cmds[0] += CMD_COLOR_CHANGE;
    for (int i = 1; i < s->noOfPoints; ++i) {
        if (getColor(curr) != getColor(s->cmds[i])) s->cmds[i] += CMD_COLOR_CHANGE;
        curr = s->cmds[i];
    }
}

void addObjectToSceneCommands(scene* scene, drawingObject object) {
    switch (object.type) {
        case CLOSED_LINES:
            addClosedLinesToScene(scene, object);
            break;
        case LINES:
            addLinesToScene(scene, object);
            break;
        case CURVE:
            addCurveToScene(scene, object);
            break;
        case CLOSED_CURVE:
            addClosedCurveToScene(scene, object);
            break;
    }
}

void addClosedCurveToScene(scene* scene, drawingObject object) {
    for (int i = 0; i <= object.len; i += 2) {
        Vector newPos{(short) pgm_read_word(&object.data[i % object.len]), (short) pgm_read_word(&object.data[(i + 1) % object.len])};
        newPos = rotate(newPos, object.rot);
        newPos = scale(newPos, object.scale);
        newPos = translation(newPos, object.pos);
        scene->cmds[scene->noOfPoints + i/2] = getCommand(newPos.x,newPos.y,object.color);
    }
    scene->noOfPoints += object.len / 2 + 1;
}

Vector scale(Vector p, short scale) {
    return multiply(p, scale);
}

Vector translation(Vector orig, Vector translation) {
    return add(orig, translation);
}

void addCurveToScene(scene* scene, drawingObject object) {
    for (int i = 0; i < object.len - 1; i += 2) {
        Vector newPos{(short) pgm_read_word(&object.data[i]), (short) pgm_read_word(&object.data[i + 1])};
        newPos = rotate(newPos, object.rot);
        newPos = scale(newPos, object.scale);
        newPos = translation(newPos, object.pos);
        scene->cmds[scene->noOfPoints + i/2] = getCommand(newPos.x,newPos.y,object.color);
    }
    scene->noOfPoints += object.len / 2;
}

void addLinesToScene(scene* scene, drawingObject object) {
    Vector sPos, ePos;
    ePos = object.pos;


    for (int i = 0; i < object.len - 3;i += 4) {
        sPos = (Vector) {.x = (short) pgm_read_word(&object.data[i]), .y = (short) pgm_read_word(&object.data[i + 1])};

        sPos = rotate(sPos, object.rot);
        sPos = scale(sPos, object.scale);
        sPos = translation(sPos, object.pos);

        if (!eq(sPos, ePos)) {
            scene->noOfPoints += makeLine(scene->cmds, scene->noOfPoints, ePos.x, ePos.y, sPos.x, sPos.y, 0);
        }

        ePos = (Vector) {.x = (short) pgm_read_word(&object.data[i + 2]), .y = (short) pgm_read_word(&object.data[i + 3])};

        ePos = rotate(ePos, object.rot);
        ePos = scale(ePos, object.scale);
        ePos = translation(ePos, object.pos);

        scene->noOfPoints += makeLine(scene->cmds,scene->noOfPoints, sPos.x, sPos.y, ePos.x, ePos.y, object.color);
    }
}

void addClosedLinesToScene(scene* scene, drawingObject object) {
    int n = 0;
    Vector sPos = (Vector) {.x = (short) pgm_read_word(&object.data[0]), .y = (short) pgm_read_word(&object.data[1])};
    sPos = scale(sPos, object.scale);
    sPos = rotate(sPos, object.rot);
    sPos = translation(sPos, object.pos);
    n += makeLine(scene->cmds,scene->noOfPoints + n, object.pos.x, object.pos.y, sPos.x, sPos.y, 0);

    for (int i = 0; i <= object.len + 4; i += 2) {
        Vector ePos = (Vector) { .x = (short) pgm_read_word(&object.data[i % object.len]), .y = (short) pgm_read_word(&object.data[(i + 1) % object.len])};
        ePos = scale(ePos, object.scale);
        ePos = rotate(ePos, object.rot);
        ePos = translation(ePos, object.pos);
        if ((i < 2) || (i > object.len + 2)) n += makeLine(scene->cmds,scene->noOfPoints + n, sPos.x, sPos.y, ePos.x, ePos.y, 0);
        else  n += makeLine(scene->cmds,scene->noOfPoints + n, sPos.x, sPos.y, ePos.x, ePos.y, object.color);
        sPos = ePos;
    }
    n += makeLine(scene->cmds,scene->noOfPoints + n, sPos.x, sPos.y, object.pos.x, object.pos.y, 0);
    scene->noOfPoints += n;
}

int
makeLine(COMMAND *arr,int start, short xStart, short yStart, short xEnd, short yEnd,
         COLOR col) {
    unsigned int dx =  abs(xEnd - xStart);
    unsigned int dy =  abs(yEnd - yStart);


    int n = getLineResFromDxDy(dx, dy);
    if (col == 0) n = getMoveResFromDxDy(dx, dy);

    unsigned int x, y;


    for (int k = 0; k < n; k++) {
        unsigned int kx = ((unsigned long) dx * fpErf((256 / n) * k)) >> 16u;
        unsigned int ky = ((unsigned long) dy * fpErf( (256 / n) * k)) >> 16u;
        if (xEnd > xStart) x = xStart + kx;
        else x = xStart - kx;

        if (yEnd > yStart) y =  yStart + ky;
        else y = yStart - ky;

        arr[start + k] = getCommand((unsigned short) x, (unsigned short)  y,col);
    }
    return n;
}

int getLineResFromDxDy(unsigned int dx, unsigned int dy) {
    if (dx + dy == 0) return 0;
    if(dx*dx + dy*dy > 4000000) return 256;
    if(dx*dx + dy*dy >  1000000) return 128;
    if(dx*dx + dy*dy >  250000) return 64;
    if(dx*dx + dy*dy >  62500) return 32;
    if(dx*dx + dy*dy >  15625) return 16;
    if(dx*dx + dy*dy >  3906) return 8;
    return 4;
}

int getMoveResFromDxDy(unsigned int dx, unsigned int dy) {
    if (dx + dy == 0) return 0;
    if(dx*dx + dy*dy > 4000000) return 128;
    if(dx*dx + dy*dy >  1000000) return 64;
    if(dx*dx + dy*dy >  250000) return 32;
    if(dx*dx + dy*dy >  3906) return 8;
    return 4;
}

void deleteScene(scene* s) {
    free(s->cmds);
    free(s);
}

scene* makeScene() {
    scene* toRet = (scene*) malloc(sizeof(scene));
    toRet->noOfObjects = 0;
    toRet->noOfPoints = 0;
    toRet->cmds = (COMMAND*) malloc(1024 * sizeof(COMMAND));
    return toRet;
}

void addObjectToScene(scene *scene, drawingObject object) {
    scene->objects[scene->noOfObjects++] = object;
}
