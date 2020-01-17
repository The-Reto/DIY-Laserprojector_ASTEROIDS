#include "TextRenderer.h"

#ifdef USE_HARDWARE
const short DATA_A[12] PROGMEM = {10,10,0,-20,0,-20,-10,10,-5,0,5,0};
const short DATA_B[24] PROGMEM = {-10,-20,-10,10,-10,10,10,0,10,0,0,-5,0,-5,10,-10,10,-10,-10,-20,-10,-5,0,-5};
const short DATA_C[20] PROGMEM = {10,-20,0,-20,0,-20,-10,-10,-10,-10,-10,0,-10,0,0,10,0,10,10,10};
const short DATA_D[16] PROGMEM = {-10,-20,-10,10,-10,10,10,0,10,0,10,-10,10,-10,-10,-20};
const short DATA_E[16] PROGMEM = {10,-20,-10,-20,-10,-20,-10,10,-10,10,10,10,-10,-5,0,-5};
const short DATA_F[12] PROGMEM = {10,-20,-10,-20,-10,-20,-10,10,-10,-5,0,-5};
const short DATA_G[24] PROGMEM = {0,-5,10,0,10,0,0,10,0,10,-10,0,-10,0,-10,-10,-10,-10,0,-20,0,-20,10,-20};
const short DATA_H[12] PROGMEM = {-10,-20,-10,10,-10,-5,10,-5,10,-20,10,10};
const short DATA_I[4]  PROGMEM = {0,-20,0,10};
const short DATA_J[12] PROGMEM = {10,-20,10,0,10,0,0,10,0,10,-10,0};
const short DATA_K[12] PROGMEM = {10,10,-10,-5,-10,-5,10,-20,-10,-20,-10,10};
const short DATA_L[8]  PROGMEM = {10,10,-10,10,-10,10,-10,-20};
const short DATA_M[16] PROGMEM = {-10,10,-10,-20,-10,-20,0,0,0,0,10,-20,10,-20,10,10};
const short DATA_N[12] PROGMEM = {-10,10,-10,-20,-10,-20,10,10,10,10,10,-20};
const short DATA_O[24] PROGMEM = {-10,0,-10,-10,-10,-10,0,-20,0,-20,10,-10,10,-10,10,0,10,0,0,10,0,10,-10,0};
const short DATA_P[20] PROGMEM = {-10,10,-10,-20,-10,-20,0,-20,0,-20,10,-10,10,-10,0,0,0,0,-10,0};
const short DATA_Q[28] PROGMEM = {-10,0,-10,-10,-10,-10,0,-20,0,-20,10,-10,10,-10,10,0,10,0,0,10,0,10,-10,0,0,0,10,10};
const short DATA_R[24] PROGMEM = {-10,10,-10,-20,-10,-20,0,-20,0,-20,10,-10,10,-10,0,0,0,0,-10,0,0,0,10,10};
const short DATA_S[20] PROGMEM = {-10,10,0,10,0,10,10,0,10,0,-10,-10,-10,-10,0,-20,0,-20,10,-20};
const short DATA_T[8]  PROGMEM = {0,10,0,-20,-10,-20,10,-20};
const short DATA_U[12] PROGMEM = {-10,-20,-10,10,-10,10,10,10,10,0,10,-20};
const short DATA_V[8]  PROGMEM = {-10,-20,0,10,0,10,10,-20};
const short DATA_W[16] PROGMEM = {-10,-20,-10,10,-10,10,0,-10,0,-10,10,10,10,10,10,-20};
const short DATA_X[8]  PROGMEM = {-10,10,10,-20,-10,-20,10,10};
const short DATA_Y[12] PROGMEM = {0,10,0,-5,-10,-20,0,-5,0,-5,10,-20};
const short DATA_Z[12] PROGMEM = {10,10,-10,10,-10,10,10,-20,10,-20,-10,-20};

const drawingObject alphabet[] = {
        {LINES, {0,0}, 0, 1, 12, 0, DATA_A},
        {LINES, {0,0}, 0, 1, 24, 0, DATA_B},
        {LINES, {0,0}, 0, 1, 20, 0, DATA_C},
        {LINES, {0,0}, 0, 1, 16, 0, DATA_D},
        {LINES, {0,0}, 0, 1, 16, 0, DATA_E},
        {LINES, {0,0}, 0, 1, 12, 0, DATA_F},
        {LINES, {0,0}, 0, 1, 24, 0, DATA_G},
        {LINES, {0,0}, 0, 1, 12, 0, DATA_H},
        {LINES, {0,0}, 0, 1, 4,  0, DATA_I},
        {LINES, {0,0}, 0, 1, 12, 0, DATA_J},
        {LINES, {0,0}, 0, 1, 12, 0, DATA_K},
        {LINES, {0,0}, 0, 1, 8,  0, DATA_L},
        {LINES, {0,0}, 0, 1, 16, 0, DATA_M},
        {LINES, {0,0}, 0, 1, 12, 0, DATA_N},
        {LINES, {0,0}, 0, 1, 24, 0, DATA_O},
        {LINES, {0,0}, 0, 1, 20, 0, DATA_P},
        {LINES, {0,0}, 0, 1, 28, 0, DATA_Q},
        {LINES, {0,0}, 0, 1, 24, 0, DATA_R},
        {LINES, {0,0}, 0, 1, 20, 0, DATA_S},
        {LINES, {0,0}, 0, 1, 8,  0, DATA_T},
        {LINES, {0,0}, 0, 1, 12, 0, DATA_U},
        {LINES, {0,0}, 0, 1, 8,  0, DATA_V},
        {LINES, {0,0}, 0, 1, 16, 0, DATA_W},
        {LINES, {0,0}, 0, 1, 8,  0, DATA_X},
        {LINES, {0,0}, 0, 1, 12, 0, DATA_Y},
        {LINES, {0,0}, 0, 1, 12, 0, DATA_Z},
};

#else
const short DATA_A[12] = {10,10,0,-20,0,-20,-10,10,-5,0,5,0};
const short DATA_B[24] = {-10,-20,-10,10,-10,10,10,0,10,0,0,-5,0,-5,10,-10,10,-10,-10,-20,-10,-5,0,-5};
const short DATA_C[20] = {10,-20,0,-20,0,-20,-10,-10,-10,-10,-10,0,-10,0,0,10,0,10,10,10};
const short DATA_D[16] = {-10,-20,-10,10,-10,10,10,0,10,0,10,-10,10,-10,-10,-20};
const short DATA_E[16] = {10,-20,-10,-20,-10,-20,-10,10,-10,10,10,10,-10,-5,0,-5};
const short DATA_F[12] = {10,-20,-10,-20,-10,-20,-10,10,-10,-5,0,-5};
const short DATA_G[24] = {0,-5,10,0,10,0,0,10,0,10,-10,0,-10,0,-10,-10,-10,-10,0,-20,0,-20,10,-20};
const short DATA_H[12] = {-10,-20,-10,10,-10,-5,10,-5,10,-20,10,10};
const short DATA_I[4] = {0,-20,0,10};
const short DATA_J[12] = {10,-20,10,0,10,0,0,10,0,10,-10,0};
const short DATA_K[12] = {10,10,-10,-5,-10,-5,10,-20,-10,-20,-10,10};
const short DATA_L[8] = {10,10,-10,10,-10,10,-10,-20};
const short DATA_M[16] = {-10,10,-10,-20,-10,-20,0,0,0,0,10,-20,10,-20,10,10};
const short DATA_N[12] = {-10,10,-10,-20,-10,-20,10,10,10,10,10,-20};
const short DATA_O[24] = {-10,0,-10,-10,-10,-10,0,-20,0,-20,10,-10,10,-10,10,0,10,0,0,10,0,10,-10,0};
const short DATA_P[20] = {-10,10,-10,-20,-10,-20,0,-20,0,-20,10,-10,10,-10,0,0,0,0,-10,0};
const short DATA_Q[28] = {-10,0,-10,-10,-10,-10,0,-20,0,-20,10,-10,10,-10,10,0,10,0,0,10,0,10,-10,0,0,0,10,10};
const short DATA_R[24] = {-10,10,-10,-20,-10,-20,0,-20,0,-20,10,-10,10,-10,0,0,0,0,-10,0,0,0,10,10};
const short DATA_S[20] = {-10,10,0,10,0,10,10,0,10,0,-10,-10,-10,-10,0,-20,0,-20,10,-20};
const short DATA_T[8] = {0,10,0,-20,-10,-20,10,-20};
const short DATA_U[16] = {-10,-20,-10,0,-10,0,0,10,0,10,10,0,10,0,10,-20};
const short DATA_V[8] = {-10,-20,0,10,0,10,10,-20};
const short DATA_W[16] = {-10,-20,-10,10,-10,10,0,-10,0,-10,10,10,10,10,10,-20};
const short DATA_X[8] = {-10,10,10,-20,-10,-20,10,10};
const short DATA_Y[12] = {0,10,0,-5,-10,-20,0,-5,0,-5,10,-20};
const short DATA_Z[12] = {10,10,-10,10,-10,10,10,-20,10,-20,-10,-20};
#endif

drawingObject getLetter(char c);

#ifdef USE_HARDWARE
void renderString(scene* s, String str, Vector pos, COLOR col){
#else
drawingObject renderString(std::string s){
#endif
    int i = 0;
    while (str[i] != 0) {
        if (str[i] != 32) {
            s->objects[s->noOfObjects++] = getLetter(str[i]);
            s->objects[s->noOfObjects - 1].pos = pos;
            s->objects[s->noOfObjects - 1].pos.x += i * 30 * 5;
            s->objects[s->noOfObjects - 1].color = col;
            s->objects[s->noOfObjects - 1].scale = 5;
        }
        i++;
    }
}

drawingObject getLetter(char c) {
    static drawingObject myArraySRAM;
    memcpy(&myArraySRAM, &alphabet[c - 65], sizeof(drawingObject));
    return myArraySRAM;
}