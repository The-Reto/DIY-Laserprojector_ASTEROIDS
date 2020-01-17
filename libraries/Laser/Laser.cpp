#include "Laser.h"

void moveLaser(LASER *l, COMMAND cmd) {
    if (cmd & CMD_COLOR_CHANGE) {
        setLaserColor(l, getColor(cmd));
    }

    unsigned short x = (cmd >> 8u) & CMD_GET_DATA;
    unsigned short y = (cmd >> ( 8u + 12u))  & CMD_GET_DATA;


#ifdef USE_SIMULATOR //Running on simulator
    fillRect(&(l->target), l->x/(DAC_RESOLUTION / IMAGE_SIZE), l->y/(DAC_RESOLUTION / IMAGE_SIZE), 2, 2, fromLaserColor(l->color));
    drawLine(&(l->target), l->x/(DAC_RESOLUTION / IMAGE_SIZE), l->y / (DAC_RESOLUTION / IMAGE_SIZE), x / (DAC_RESOLUTION / IMAGE_SIZE), y / (DAC_RESOLUTION / IMAGE_SIZE), fromLaserColor(l->color));
    l->x = x;
    l->y = y;
    fillRect(&(l->target), l->x/(DAC_RESOLUTION / IMAGE_SIZE), l->y/(DAC_RESOLUTION / IMAGE_SIZE), 2, 2, fromLaserColor(l->color));
#else //not running on simulator
    Set(&(l->dac), 4095 - y, 4095 - x);
    delayMicroseconds(POINT_DELAY);
#endif //USE_SIMULATOR
    l->x = x;
    l->y = y;
}

COMMAND addCorrection(int x, int y, COMMAND c) {
    short cx = (c >> 8u) & CMD_GET_DATA;
    short cy = (c >> ( 8u + 12u))  & CMD_GET_DATA;
    short nx = (x + cx);
    short ny = (y + cy);
    if (nx >= DAC_RESOLUTION) nx = nx % DAC_RESOLUTION;
    if (ny >= DAC_RESOLUTION) nx = ny % DAC_RESOLUTION;

    if (nx < 0) nx = DAC_RESOLUTION + nx;
    if (ny < 0) ny = ny + DAC_RESOLUTION;
    return getCommand(nx, ny, getColor(c));
}

COLOR getColor(COMMAND cmd) {
    COLOR col = 0;
    if (!(cmd & CMD_LASER_OFF)) {
        if (cmd & CMD_RED_BIG) {
            col += RED_BIG;
        }
        if (cmd & CMD_RED_SMALL) {
            col += RED_SMALL;
        }
        if (cmd & CMD_GREEN_BIG) {
            col += GREEN_BIG;
        }
        if (cmd & CMD_GREEN_SMALL) {
            col += GREEN_SMALL;
        }
        if (cmd & CMD_BLUE_BIG) {
            col += BLUE_BIG;
        }
        if (cmd & CMD_BLUE_SMALL) {
            col += BLUE_SMALL;
        }
    }
    return col;
}

LASER* generateLaser() {
#ifndef USE_SIMULATOR
    Serial.println("Starting Laser setup!");
#endif
    LASER* result = (LASER*) malloc(sizeof(LASER));
    result->x = result->y = 2000;
    result->color = 0;
#ifdef USE_SIMULATOR
    result.frame = 0;
    result.target = createImage(IMAGE_SIZE, COLOR_BLACK);
#else
    result->dac = *generateDAC(SDI_PIN,SCK_PIN,CS_PIN,LDAC_PIN);
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    setLaserColor(result, 0);
    moveLaser(result, getCommand(result->x,result->y,result->color));
    Serial.println("Laser setup complete!");
#endif //USE_SIMULATOR

    return result;
}

int deleteLaser(LASER *l) {
#ifdef USE_SIMULATOR
    deleteImage(&(l->target));
#endif //USE_SIMULATOR
    return 0;
}

COMMAND getCommand(unsigned short xPos, unsigned short yPos, COLOR col) {
    COMMAND result;
    if (xPos >= 4096) xPos = xPos % 4096;
    if (yPos >= 4096) yPos = yPos % 4096;
    result = ((unsigned long) yPos);
    result = (result << 12u) + xPos;
    result = result << 8;
    if (col & RED_BIG) result += CMD_RED_BIG;
    if (col & RED_SMALL) result += CMD_RED_SMALL;
    if (col & GREEN_BIG) result += CMD_GREEN_BIG;
    if (col & GREEN_SMALL) result += CMD_GREEN_SMALL;
    if (col & BLUE_BIG) result += CMD_BLUE_BIG;
    if (col & BLUE_SMALL) result += CMD_BLUE_SMALL;
    return result;
}

void setLaserColor(LASER *l, COLOR col) {
    l->color = col;
#ifndef USE_SIMULATOR
    delayMicroseconds(COLOR_CHANGE_DELAY);
    if (col & RED_BIG || col & RED_SMALL) digitalWrite(RED_PIN, HIGH);
    else digitalWrite(RED_PIN, LOW);
    if (col & GREEN_BIG || col & GREEN_SMALL) digitalWrite(GREEN_PIN, HIGH);
    else digitalWrite(GREEN_PIN, LOW);
    if (col & BLUE_BIG || col & BLUE_SMALL) digitalWrite(BLUE_PIN, HIGH);
    else digitalWrite(BLUE_PIN, LOW);
    //if (!(col & GREEN_BIG || col & GREEN_SMALL) && !(col & BLUE_BIG || col & BLUE_SMALL) && !(col & RED_BIG || col & RED_SMALL)) digitalWrite(RED_PIN, HIGH);
#endif
}


#ifdef USE_SIMULATOR
inline int abs(int a) {
    return a<0 ? -a:a;
}
#endif

#ifdef USE_SIMULATOR
void writeFrame(LASER* l) {
        char *path = (char*) malloc(13 * sizeof(char));
        sprintf(path, "%d.pbm", l->frame++);
        writeImage(&(l->target), path);
        deleteImage(&(l->target));
        l->target = createImage(IMAGE_SIZE, COLOR_BLACK);
    }
#endif //USE_SIMULATOR
