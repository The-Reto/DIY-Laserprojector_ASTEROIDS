#include "Utils.h"

LASER* laser = nullptr;
char lp = 0, tp = 0, rp = 0, fp= 0,hp = 0;
COLOR c[8] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW, COLOR_PURPLE, COLOR_TEAL, COLOR_WHITE, COLOR_BLACK};

void displayLissajous(int a, int b, long duration, COLOR col, int phase);

void displayLissajous(int a, int b, long duration, COLOR col, int phase) {
    int phi = 0;
    setLaserColor(laser, col);
    for (int i = 0; i < 360; i++) {
        Set(&(laser->dac), (1000 * fpCos((a + 1) * phi) >> 16) + 2000,
            ((1000 * fpSin((b + 1) * phi + phase)) >> 16) + 2000);
        phi = (++phi) % 360;
    }
    setLaserColor(laser, 0);
}

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

    Serial.println("BOOT COMPLETE!");
}

void showBootAnimation() {
    static int tones[14] = {2000, 4000, 2000, 4000, 3000, 4000, 2500, 6000, 2000, 4500, 5000, 6000, 2000, 3000};

    int a = 0;
    do {
        long t = 0;
        for (int i = 0; (i < 360) && (a < 14); ++i) {
            if (millis() - t > 550) {
                playTone(tones[a], 500);
                t = millis();
                a++;
            }
            displayLissajous(2,3, 550, c[a % 7], i);
        }
    } while (a < 14);
    setLaserColor(laser, COLOR_BLACK);
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

    setInterrupt(H_BUTTON, BUTTON_CHANGE, toggle_hp);

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

void lissajousDemonstration() {
    int a = 0, b = 0;
    setInterrupt(H_BUTTON, BUTTON_DOWN, set_hp);
    setInterrupt(R_BUTTON, BUTTON_DOWN, set_rp);
    setInterrupt(L_BUTTON, BUTTON_DOWN, set_lp);
    setInterrupt(T_BUTTON, BUTTON_DOWN, set_tp);
    setInterrupt(F_BUTTON, BUTTON_DOWN, set_fp);
    hp = 0;
    int phase = 0;
    while (!hp) {
        Serial.println("fyi");
        displayLissajous(a,b,250,COLOR_RED, phase);
        if(tp) {
            a++;
            tp = 0;
        }
        if(fp) {
            a--;
            fp = 0;
        }
        if(lp) {
            b++;
            lp = 0;
        }if(rp) {
            b--;
            rp = 0;
        }
        phase = ++phase % 360;
    }
    hp = 0;
    rp = 0;
    lp = 0;
    tp = 0;
    fp = 0;
}

void figuresDemonstration() {
    scene *mainScene = makeScene();
    drawingObject obj = HOUSE;
    obj.pos = {2800, 1000};
    obj.scale = 5;
    addObjectToScene(mainScene, obj);

    obj = ROCK;
    obj.pos = {1000, 1000};
    obj.scale = 5;
    obj.color = COLOR_WHITE;
    addObjectToScene(mainScene, obj);

    obj = TREE;
    obj.pos = {2800, 2800};
    obj.scale = 20;
    addObjectToScene(mainScene, obj);

    obj = SHIP;
    obj.pos = {1000, 2800};
    obj.scale = 5;
    obj.color = COLOR_YELLOW;
    addObjectToScene(mainScene, obj);
    buildScene(mainScene);
    long mil = millis();
    while (millis() - mil < 10000) {
        drawScene(*mainScene, *laser);
    }
    deleteScene(mainScene);
}
