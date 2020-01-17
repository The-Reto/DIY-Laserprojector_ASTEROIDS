//
// Created by the-reto on 24.11.19.
//

#include "Data.h"

#ifdef USE_HARDWARE
const short DATA_HOUSE[10] PROGMEM = {50,50,50,-25,0,-75,-50,-25,-50,50};
const short DATA_SHIP[8]   PROGMEM = {0,0,50,50,0,-75,-50,50};
const short DATA_ROCK[14]  PROGMEM = {-75,0,0,-100,50,-50,25,0,50,25,0,75,-50,50};
const short DATA_TREE[30]  PROGMEM = {0,-20,15,-10,5,-10,20,0,10,0,30,20,10,20,10,40,-10,40,-10,20,-30,20,-10,0,-20,0,-5,-10,-15,-10};
const short DATA_BOUNDARY[8] PROGMEM = {100,100,100,4000,4000,4000,4000,100};
const short DATA_SHOT[6] PROGMEM = {5,0,0,10,-5,0};
#else
const short DATA_HOUSE[10] = {50,50,50,-25,0,-75,-50,-25,-50,50};

const short DATA_SHIP[8] = {0,0,50,50,0,-75,-50,50};

const short DATA_ROCK[14] = {-75,0,0,-100,50,-50,25,0,50,25,0,75,-50,50};
#endif