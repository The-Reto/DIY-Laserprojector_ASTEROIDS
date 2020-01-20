//
// Created by Livio on 09.11.2019.
//

#ifndef ASTEROIDSMAIN_ASTEROIDS_H
#define ASTEROIDSMAIN_ASTEROIDS_H

#include <stdbool.h>
#include <Models.h>
#include <Vector.h>
#include <Laser.h>
#include <Sound.h>
#include <Utils.h>


#define MAX_OBJECTS 20
#define START_LIVES 3
#define WIN_POINTS 20000
#define GAME_SIZE 4096
#define POINTS_FOR_NEW_LIFE 10000


void asteroidsInit(gameObject gOArray[MAX_OBJECTS]);

void getUpdate(FIXPOINT deltaT, gameObject gOArray[MAX_OBJECTS]);

void shoot(gameObject gOArray[MAX_OBJECTS]);

void playerRotation(int angle, gameObject gOArray[MAX_OBJECTS]);

void playerAcceleration(int acceleration, gameObject gOArray[MAX_OBJECTS]);

void addObject(gameObject obj, gameObject gOArray[MAX_OBJECTS]);

void resetPlayer(gameObject gOArray[MAX_OBJECTS], Vector position);

int getLifes();
int getScore();


#endif //ASTEROIDSMAIN_ASTEROIDS_H
