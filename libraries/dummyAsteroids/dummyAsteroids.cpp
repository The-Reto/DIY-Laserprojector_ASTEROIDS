#include "dummyAsteroids.h"

void playDummy() {
    scene* mainScene;

    mainScene = makeScene();
    mainScene->objects[1] = ROCK;
    mainScene->objects[1].color = COLOR_WHITE;
    mainScene->objects[1].scale = -4;

    mainScene->objects[2] = ROCK;
    mainScene->objects[2].color = COLOR_WHITE;
    mainScene->objects[2].scale = 6;

    mainScene->objects[0] = SHIP;
    mainScene->objects[0].color = COLOR_YELLOW;
    mainScene->objects[0].scale = 2;
    mainScene->noOfObjects = 3;


    short vX[3] = {0, 3, -5};
    short vY[3] = {0, 2, -6};
    short  x[3] = {2000, 2123, 3500};
    short  y[3] = {2000, 1234, 2340};

    while (!fp) {
        if(hp) {
            x[0] = y[0] = 2000;
            vX[0] = vY[0] = 0;
            lp = rp = tp = 0;
        }
        if (lp) {
            mainScene->objects[0].rot += 4;
        }
        if (rp) {
            mainScene->objects[0].rot -= 4;
        }
        mainScene->objects[0].rot = (360 + mainScene->objects[0].rot) % 360;
        if (tp) {
            vX[0] -= 4 * fpSin(mainScene->objects[0].rot) >> 16;
            vY[0] -= 4 * fpCos(mainScene->objects[0].rot) >> 16;
        }
        for (int i = 0; i < mainScene->noOfObjects; i++) {
            x[i] += vX[i];
            y[i] += vY[i];
            x[i] = (x[i] + 4095) % 4095;
            y[i] = (y[i] + 4095) % 4095;
            mainScene->objects[i].pos = {x[i],y[i]};
        }

        buildScene(mainScene);

        drawScene(*mainScene,*laser);
    }

    deleteScene(mainScene);
}
