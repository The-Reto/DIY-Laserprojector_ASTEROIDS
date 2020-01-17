//
// Created by the-reto on 22.12.19.
//

#ifndef UTILITIES_UTILS_H
#define UTILITIES_UTILS_H

#include <Arduino.h>
#include <Laser.h>
#include <CAOSButtons.h>
#include <Sound.h>
#include <FixPoint.h>
#include <Drawing.h>
#include <TextRenderer.h>



extern LASER* laser;

extern char lp,tp,rp,fp,hp;

extern COLOR c[8];

void boot();

void showBootAnimation();

void display_pressH();

void showCountDown();

void toggle_lp();
void toggle_tp();
void toggle_rp();
void toggle_fp();
void toggle_hp();

void set_hp();
void set_lp();
void set_rp();
void set_fp();
void set_tp();


#endif //UTILITIES_UTILS_H
