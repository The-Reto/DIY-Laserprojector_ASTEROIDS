#ifndef TEXTRENDERER_TEXTRENDERER_H
#define TEXTRENDERER_TEXTRENDERER_H

#include <Drawing.h>

#define USE_HARDWARE

#ifdef USE_HARDWARE
void renderString(scene* s, String str, Vector pos, COLOR col);
#else
#include <string>
drawingObject renderString(std::string s);
#endif

extern const short DATA_A[] PROGMEM;
extern const short DATA_B[] PROGMEM;
extern const short DATA_C[] PROGMEM;
extern const short DATA_D[] PROGMEM;
extern const short DATA_E[] PROGMEM;
extern const short DATA_F[] PROGMEM;
extern const short DATA_G[] PROGMEM;
extern const short DATA_H[] PROGMEM;
extern const short DATA_I[] PROGMEM;
extern const short DATA_J[] PROGMEM;
extern const short DATA_K[] PROGMEM;
extern const short DATA_L[] PROGMEM;
extern const short DATA_M[] PROGMEM;
extern const short DATA_N[] PROGMEM;
extern const short DATA_O[] PROGMEM;
extern const short DATA_P[] PROGMEM;
extern const short DATA_Q[] PROGMEM;
extern const short DATA_R[] PROGMEM;
extern const short DATA_S[] PROGMEM;
extern const short DATA_T[] PROGMEM;
extern const short DATA_U[] PROGMEM;
extern const short DATA_V[] PROGMEM;
extern const short DATA_W[] PROGMEM;
extern const short DATA_X[] PROGMEM;
extern const short DATA_Y[] PROGMEM;
extern const short DATA_Z[] PROGMEM;
extern const drawingObject alphabet[];

#endif //TEXTRENDERER_TEXTRENDERER_H