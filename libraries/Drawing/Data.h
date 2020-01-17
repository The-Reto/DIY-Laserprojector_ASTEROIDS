//
// Created by the-reto on 24.11.19.
//

#ifndef DRAWING_DATA_H
#define DRAWING_DATA_H

#include "Drawing.h"

extern const short DATA_HOUSE[] PROGMEM;
static drawingObject HOUSE =  {CLOSED_LINES, {0,0}, 0, 1, 10, RED_BIG+RED_SMALL, DATA_HOUSE};

extern const short DATA_SHIP[] PROGMEM;
static drawingObject SHIP =  {CLOSED_LINES, {0,0}, 0, 1, 8, RED_SMALL, DATA_SHIP};

extern const short DATA_ROCK[] PROGMEM;
static drawingObject ROCK =  {CLOSED_LINES, {0,0}, 0, 1, 14, RED_BIG, DATA_ROCK};

extern const short DATA_TREE[] PROGMEM;
static drawingObject TREE =  {CLOSED_LINES, {0,0}, 0, 1, 30, GREEN_BIG, DATA_TREE};

extern const short DATA_BOUNDARY[] PROGMEM;
static drawingObject BOUNDARY =  {CLOSED_LINES, {0,0}, 0, 1, 8, RED_BIG + BLUE_BIG + GREEN_BIG, DATA_BOUNDARY};

extern const short DATA_SHOT[] PROGMEM;
static drawingObject SHOT =  {CLOSED_LINES, {0,0}, 0, 1, 6, GREEN_BIG, DATA_SHOT};


#endif //DRAWING_DATA_H
