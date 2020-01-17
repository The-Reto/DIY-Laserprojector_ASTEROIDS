#include "Utils.h"

LASER* laser = nullptr;
char lp = 0, tp = 0, rp = 0, fp= 0,hp = 0;
COLOR c[8] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW, COLOR_PURPLE, COLOR_TEAL, COLOR_WHITE, COLOR_BLACK};

void boot() {
    Serial.begin(9600);
    Serial.print("BOOT\n");

    laser = generateLaser();

    setUpButtons();

    randomSeed(analogRead(0));

    setInterrupt(F_BUTTON, BUTTON_CHANGE, toggle_fp);
    setInterrupt(H_BUTTON, BUTTON_CHANGE, toggle_hp);
    setInterrupt(L_BUTTON, BUTTON_CHANGE, toggle_lp);
    setInterrupt(R_BUTTON, BUTTON_CHANGE, toggle_rp);
    setInterrupt(T_BUTTON, BUTTON_CHANGE, toggle_tp);

    //showBootAnimation();

    Serial.println("BOOT COMPLETE!");
}

void showBootAnimation() {
    static int tones[14] = {2000, 4000, 2000, 4000, 3000, 4000, 2500, 6000, 2000, 4500, 5000, 6000, 2000, 3000};

    for (int a = 0; a < 14; a++) {
        playTone(tones[a], 500);
        setLaserColor(laser, c[a % 7]);
        int mil = millis();
        int phi = 0;
        while (millis() - mil < 550) {
            Set(&(laser->dac), (1000 * fpCos(phi) >> 16) + 2000, ((1000 * fpSin((a % 3 + 1) * phi)) >> 16) + 2000);
            phi = (++phi) % 360;
        }
    }
   setLaserColor(laser, 0);
}


void showCountDown() {
    static char countdown[5][5] = { {ON,ON,ON,OFF,OFF}, {SAME,SAME,OFF,SAME,SAME}, {SAME,OFF,SAME,SAME,SAME}, {ON,ON,ON,OFF,OFF}, {OFF,OFF,OFF,OFF,OFF}};
    static int tones[5] = {1000, 1000, 1000, 2000, 0};

    for (int i = 0; i < 5; i++) {
        setLightPattern(countdown[i]);
        playTone(tones[i], 850);
        delay(1000);
    }
}

void toggle_lp() {
    lp = lp == 1 ? 0:1;
    playTone(2500, 50);
}

void toggle_tp() {
    tp = tp == 1 ? 0:1;
    playTone(2500, 50);
}

void toggle_rp() {
    rp = rp == 1 ? 0:1;
    playTone(2500, 50);
}

void toggle_fp() {
    fp = fp == 1 ? 0:1;
    playTone(2500, 50);
}

void toggle_hp() {
    hp = hp == 1 ? 0:1;
    playTone(2500, 50);
}

void set_hp() {
    hp = 1;
    playTone(2500, 50);
}

void set_lp() {
    lp = 1;
    playTone(2500, 50);
}

void set_rp() {
    rp = 1;
    playTone(2500, 50);
}

void set_fp() {
    fp = 1;
    playTone(2500, 50);
}

void set_tp() {
    tp = 1;
    tone(SPEAKER_PIN, 2500, 50);
}

void display_pressH() {
    scene* s = makeScene();
    renderString(s, "PUSH", {1750, 1250}, COLOR_WHITE);
    renderString(s, "H", {2000, 1500}, COLOR_WHITE);
    renderString(s, "TO START", {1500, 1750}, COLOR_WHITE);

    setLight(H_BUTTON, ON);
    static char pat[5] = {RANDOM, RANDOM, RANDOM, RANDOM, SAME};
    long milliSec = millis();
    int i = 0;
    setLaserColor(laser, COLOR_WHITE);
    while( !hp ) {
        if ((millis() - milliSec) > 500) {
            setLightPattern(pat);
            for (int j = 0; j < s->noOfObjects; j++) {
                (*s).objects[j].color = c[i];
                playTone(1000, 50);
            }
            i = ++i % 7;
            buildScene(s);
            milliSec = millis();
        }
        drawScene(*s,*laser);
    }
    showCountDown();
    hp = 0;
    setInterrupt(H_BUTTON, BUTTON_CHANGE, toggle_hp);
    deleteScene(s);
}
