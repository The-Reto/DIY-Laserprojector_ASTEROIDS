#include "AsteroidsController.h"

void displayAsteroids(scene* s);

void setRotateLeft();
void setRotateRight();
void setAccelerate();
void hyperspace();
void shot();
gameObject gOArray[MAX_OBJECTS] = {emptyObject()};

int rotateLeft = 0, rotateRight = 0, accelerate = 0;

void playAsteroids() {
    Serial.println("getting ready for asterioids");
    long timesteps = millis();
    asteroidsInit(gOArray);
    int i = 1;
    setInterrupt(F_BUTTON, BUTTON_DOWN, shot);
    setInterrupt(H_BUTTON, BUTTON_DOWN, hyperspace);
    setInterrupt(L_BUTTON, BUTTON_CHANGE, setRotateLeft);
    setInterrupt(R_BUTTON, BUTTON_CHANGE, setRotateRight);
    setInterrupt(T_BUTTON, BUTTON_CHANGE, setAccelerate);
    Serial.println("Starting Asteroids");
    while (i > 0) {
        scene *mainScene = makeScene();
        timesteps = millis() - timesteps;
        if (! (getLifes() <= 0 || getScore() > WIN_POINTS))
        getUpdate(timesteps, gOArray);
        if (getLifes() <= 0) {
            renderString(mainScene, "GAME OVER", {1750, 1250}, COLOR_WHITE);
            if (accelerate) i = 0;
        } else if (getScore() > WIN_POINTS) {
            renderString(mainScene, "YOU WIN", {1750, 1250}, COLOR_WHITE);
            if (accelerate) i = 0;
        } else {
            if (rotateLeft) {
                playerRotation(12, gOArray);
            }
            if (rotateRight) {
                playerRotation(-12, gOArray);
            }
            if (accelerate) {
                playerAcceleration(16, gOArray);
            }
            for (int k = 0; k < MAX_OBJECTS; k++) {
                if (gOArray[k].reset == 0) addObjectToScene(mainScene, gOArray[k].graphics);
            }
        }
        displayAsteroids(mainScene);
        deleteScene(mainScene);
    }
}

void displayAsteroids(scene* s) {
    buildScene(s);
    drawScene(*s, *laser);
}

void setRotateLeft() {
    rotateLeft = (rotateLeft == 0) ? 1:0;
}

void setRotateRight() {
    rotateRight = (rotateRight == 0) ? 1:0;
}

void setAccelerate() {
    accelerate =  (accelerate == 0) ? 1:0;;
}

void shot() {
    shoot(gOArray);
}

void hyperspace() {
    accelerate = 0;
    rotateLeft = 0;
    rotateRight = 0;
    resetPlayer(gOArray, {(int) random(GAME_SIZE),(int) random(GAME_SIZE)});
}