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

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_OBJECTS 30

void asteroidsInit(gameObject gOArray[MAX_OBJECTS]);

void getUpdate(FIXPOINT deltaT, gameObject gOArray[MAX_OBJECTS]);

void shoot(gameObject gOArray[MAX_OBJECTS]);

void playerRotation(int angle, gameObject gOArray[MAX_OBJECTS]);

void playerAcceleration(int acceleration, gameObject gOArray[MAX_OBJECTS]);

void addObject(gameObject obj, gameObject gOArray[MAX_OBJECTS]);

void resetPlayer(gameObject gOArray[MAX_OBJECTS]);

int getLifes();
int getScore();

#ifdef __cplusplus
}
#endif

#endif //ASTEROIDSMAIN_ASTEROIDS_H
