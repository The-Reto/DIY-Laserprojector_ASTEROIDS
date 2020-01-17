//
// Created by Livio on 09.11.2019.
//
#include "Asteroids.h"
#include "../Models/Models.h"
#include "../Vector/Vector.h"
#include "../CAOSButtons/CAOSButtons.h"

#ifdef __cplusplus
extern "C"{
#endif


//Contains all Objects in the game, first object is always the player
int sizeAO;
//Quadratic size of the game NxN
int sizeOfGame;
//needed for spacefriction(), counts to 0.25 seconds
int quartersecond = 0;
int lifes = 3;
int score = 0;
int pointsForNewLife = 10000;
int playerResetCounter = 0;
static char lifeDisplay[6][5] = { {OFF,OFF,OFF,OFF,OFF}, {ON,OFF,OFF,OFF,OFF}, {ON,ON,OFF,OFF,OFF}, {ON,ON,ON,OFF,OFF}, {ON,ON,ON,ON,OFF}, {ON,ON,ON,ON,ON}};



//Initializes Asteroids game
void asteroidsInit(gameObject gOArray[MAX_OBJECTS]) {
    sizeOfGame = 4096;
    sizeAO = 1;
    Vector vel = {0, 0};
    gOArray[0] = generateClosedFigure(2000, 2000, COLOR_YELLOW, vel, player, NOAS);

    for (int i = 1; i < MAX_OBJECTS; ++i) {
        (gOArray)[i] = emptyObject();
        (gOArray)[i].reset = 1;
    }

    //for testing purposes
    Vector vel2 = {17,23};
    addObject(generateClosedFigure(600, 800, COLOR_WHITE, vel2, asteroid,big), gOArray);
    vel2 = {-14,5};
    addObject(generateClosedFigure(3250, 3250, COLOR_WHITE, vel2, asteroid,medium), gOArray);
    sizeAO = 3;
    quartersecond = 0;
    setLightPattern(lifeDisplay[lifes]);
}

//Players shoots
void shoot(gameObject gOArray[MAX_OBJECTS]) {
    Vector velocity = {0,-45};
    velocity = rotate(velocity, gOArray[0].graphics.rot);

    addObject( generateShot(gOArray[0].graphics.pos.x + velocity.x, gOArray[0].graphics.pos.y + velocity.y, COLOR_RED, velocity), gOArray );
    playTone(NOTE_C7, 100);
}

//Player rotates, int=2 => 2 Grad Rotation
void playerRotation(int angle, gameObject gOArray[MAX_OBJECTS]) {
    rotateObject(&gOArray[0], angle);
}

//player enters hyperspace
void resetPlayer(gameObject gOArray[MAX_OBJECTS]){
    gOArray[0].graphics.pos.x = sizeOfGame/2;
    gOArray[0].graphics.pos.y = sizeOfGame/2;
    gOArray[0].velocity.x = 0;
    gOArray[0].velocity.y = 0;
    gOArray[0].reset = 1;
    playerResetCounter = 0;
}

//adds new Asteroids into the game when there is only one asteroid left in order to keep it fresh
void endlessMode(gameObject gOArray[MAX_OBJECTS]){
    int x;
    int y;
    int xvelocity;
    int yvelocity;
    int randomNegate = random(1);
    if(randomNegate == 1){
        randomNegate = -1;
    }else{
        randomNegate = 1;
    }
    switch(random(4)){
        case 0:
            x = 0;
            y = random(sizeOfGame);
            xvelocity = random(1,21);
            yvelocity = randomNegate*random(1,21);
            break;
        case 1:
            x = sizeOfGame-1;
            y = random(sizeOfGame);
            xvelocity = -1*random(1,21);
            yvelocity = randomNegate*random(1,21);
            break;
        case 2:
            x = random(sizeOfGame);
            y = 0;
            xvelocity = randomNegate*random(1,21);
            yvelocity = random(1,21);
            break;
        case 3:
            x = random(sizeOfGame);
            y = sizeOfGame-1;
            xvelocity = randomNegate*random(1,21);
            yvelocity = -1*random(1,21);
            break;
    }
    Vector tmpvec = {xvelocity,yvelocity};
    addObject(generateClosedFigure(x,y,COLOR_WHITE,tmpvec,asteroid,big), gOArray);
}

//playerAccelerates in a direction
void playerAcceleration(int acceleration, gameObject gOArray[MAX_OBJECTS]) {
    playTone(NOTE_C3, 100);
    Vector accel = {0, -acceleration};
    gOArray[0].velocity = add(gOArray[0].velocity, rotate(accel, gOArray[0].graphics.rot));
}

void removeObject(int id, gameObject gOArray[MAX_OBJECTS]) {
    gOArray[id] = emptyObject();
}

void gameOver(gameObject gOArray[]) {
    playTone(NOTE_C6, 5000);
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        (gOArray)[i] = emptyObject();
        (gOArray)[i].reset = 1;
    }
}

//if object is out of bounds reposition it
void objectOutOfBounds(gameObject gOArray[MAX_OBJECTS]){
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if(gOArray[i].reset == 0) {
            if(gOArray[i].type == bullet & ((gOArray[i].graphics.pos.x) < 0 || (gOArray[i].graphics.pos.x > sizeOfGame) || (gOArray[i].graphics.pos.y < 0) || (gOArray[i].graphics.pos.y > sizeOfGame))){
                removeObject(i, gOArray);
            }else {
                if (gOArray[i].graphics.pos.x < 0) {
                    gOArray[i].graphics.pos.x = sizeOfGame + gOArray[i].graphics.pos.x;
                }
                if (gOArray[i].graphics.pos.x >= sizeOfGame) {
                    gOArray[i].graphics.pos.x = gOArray[i].graphics.pos.x - sizeOfGame;
                }
                if (gOArray[i].graphics.pos.y < 0) {
                    gOArray[i].graphics.pos.y = sizeOfGame + gOArray[i].graphics.pos.y;
                }
                if (gOArray[i].graphics.pos.y >= sizeOfGame) {
                    gOArray[i].graphics.pos.y = gOArray[i].graphics.pos.y - sizeOfGame;
                }
            }
        }
    }
}

void awardPoints(int points) {
    score += points;
    if (score % 10000 >= 1 + pointsForNewLife) {
        lifes++;
        pointsForNewLife++;
    }
    if(lifes > 5) {
        setLightPattern(lifeDisplay[5]);
    } else {
        setLightPattern(lifeDisplay[lifes]);
    }
}

//creates 3 new Asteroids if size of size of destroyed asteroid has not reached minimum yet
void splitterAsteroid(struct gameObject ptr, gameObject gOArray[MAX_OBJECTS]) {
    playTone(NOTE_C4, 200);
    if((ptr).astrtype == small){
        awardPoints(100); //do something, lol
        int countastr = 0;
        for(int i = 1; i< MAX_OBJECTS;i++){
            if( (gOArray[i].type == asteroid) && (gOArray[i].reset == 0) )countastr++;
        }
        if(countastr <= 1)endlessMode(gOArray);
    }
    else if((ptr).astrtype == medium){
        awardPoints(50);
        addObject( generateClosedFigure( (ptr).graphics.pos.x - 500,  (ptr).graphics.pos.y - 150, COLOR_WHITE, {-28, 12}, asteroid, small), gOArray);
        addObject( generateClosedFigure( (ptr).graphics.pos.x + 150,  (ptr).graphics.pos.y - 500, COLOR_WHITE, {17, -5}, asteroid, small), gOArray);
    }else{//fuck, it's so big
        awardPoints(20);
        addObject( generateClosedFigure( (ptr).graphics.pos.x + 500,  (ptr).graphics.pos.y - 250, COLOR_WHITE,  {28, -12}, asteroid, medium), gOArray);
        addObject( generateClosedFigure( (ptr).graphics.pos.x + 700,  (ptr).graphics.pos.y + 220, COLOR_WHITE,  {17, -17}, asteroid, small), gOArray);
    }
}



bool collide(gameObject pObject, gameObject pObject1);

void playerCollision(gameObject gOArray[MAX_OBJECTS]);

//checks if player is in hyperspace
void checkPlayerReset(long deltaT, gameObject gOArray[MAX_OBJECTS]){
    if(gOArray[0].reset == 1) {
        if (playerResetCounter > 2000) {
            gOArray[0].reset = 0;
            playerResetCounter = 0;
        }else{
            playerResetCounter += deltaT;
        }
    }
}

void checkCollision(gameObject gOArray[MAX_OBJECTS]) {
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if(gOArray[i].reset == 0 && gOArray[i].type == asteroid) {
            for (int j = 0; j < MAX_OBJECTS; ++j) {
                if( gOArray[j].reset == 0 &&  !(i == j || gOArray[j].type == asteroid)) {
                    if(collide(gOArray[i], gOArray[j])) {
                        if (gOArray[j].type == player) playerCollision(gOArray);
                        else {
                            gOArray[j].reset = 1;
                        }
                        gOArray[i].reset = 1;
                        splitterAsteroid(gOArray[i], gOArray);
                    }
                }
            }
        }
    }
}

void playerCollision(gameObject gOArray[MAX_OBJECTS]) {
    lifes--;
    if(lifes > 5) {
        setLightPattern(lifeDisplay[5]);
    } else {
        setLightPattern(lifeDisplay[lifes]);
    }
    gOArray[0].graphics.pos = {2000,2000};
    if (lifes <= 0) {
        gameOver(gOArray);
    }
}

bool collide(gameObject pObject, gameObject pObject1) {
    static int aX, aY, aW, aH;
    static int bX, bY, bW, bH;

    aX = pObject.graphics.pos.x + pObject.mostwest;
    aY = pObject.graphics.pos.y + pObject.mostnorth;
    aW = pObject.mosteast - pObject.mostwest;
    aH = pObject.mostsouth - pObject.mostnorth;

    bX = pObject1.graphics.pos.x + pObject1.mostwest;
    bY = pObject1.graphics.pos.y + pObject1.mostnorth;
    bW = pObject1.mosteast - pObject1.mostwest;
    bH = pObject1.mostsouth - pObject1.mostnorth;

    return (aX < bX + bW) &&
            (aX + aW > bX) &&
            (aY < bY + bH) &&
            (aY + aH > bY);
}

void moveObjects(long deltaT, gameObject gOArray[MAX_OBJECTS]) {
    static int timeDivision = 8192;
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (gOArray[i].reset == 0) {
            int dx = ((gOArray[i]).velocity.x * deltaT) / timeDivision;
            int dy = ((gOArray[i]).velocity.y * deltaT) / timeDivision;
            (gOArray[i]).graphics.pos.x += dx;
            (gOArray[i]).graphics.pos.y += dy;
        }
    }
}

//because apparently there is friction in space
void spaceFriction(long dt, gameObject gOArray[MAX_OBJECTS]){
    if(quartersecond >= 8000) {
        if (gOArray[0].velocity.x > 0) {
            if (gOArray[0].velocity.x > 16) {
                gOArray[0].velocity.x -= 8;
            } else {
                gOArray[0].velocity.x -= 1;
            }
        } else if (gOArray[0].velocity.x < 0) {
            if (gOArray[0].velocity.x < -16) {
                gOArray[0].velocity.x += 8;
            } else {
                gOArray[0].velocity.x += 1;
            }
        }

        if (gOArray[0].velocity.y > 0) {
            if (gOArray[0].velocity.y > 16) {
                gOArray[0].velocity.y -= 8;
            } else {
                gOArray[0].velocity.y -= 1;
            }
        } else if (gOArray[0].velocity.y < 0) {
            if (gOArray[0].velocity.y < -16) {
                gOArray[0].velocity.y += 8;
            } else {
                gOArray[0].velocity.y += 1;
            }
        }
        quartersecond = 0;
    }else{
        quartersecond += dt;
    }
}

int getLifes() {
    return lifes;
}

int getScore() {
    return score;
}

//returns objects in the game in updated position depending on deltaT
//deltaT must be entered in fixpoint and should be in seconds ,example: 0.1 seconds => deltaT = floatToFixpoint(0.1);
void getUpdate(long deltaT, gameObject gOArray[MAX_OBJECTS]) {
    moveObjects(deltaT, gOArray);
    objectOutOfBounds(gOArray);
    spaceFriction(deltaT, gOArray);
    checkCollision(gOArray);
    checkPlayerReset(deltaT, gOArray);
}

void addObject(gameObject obj, gameObject gOArray[MAX_OBJECTS]) {
    for (int i = 1; i < MAX_OBJECTS; ++i) {
        if(gOArray[i].reset == 1) {
            gOArray[i] = obj;
            break;
        }
    }
}

#ifdef __cplusplus
}
#endif