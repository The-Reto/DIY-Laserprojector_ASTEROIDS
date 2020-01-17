#include <Utils.h>
#include <TextRenderer.h>
#include <Drawing.h>
#include <Data.h>
#include <FixPoint.h>
#include <DAC.h>
#include <Laser.h>
#include <CAOSButtons.h>
#include <dummyAsteroids.h>
#include <AsteroidsController.h>
#include <Asteroids.h>
#include <Models.h>
#include <Sound.h>


void setup() {

  boot();
  Serial.println("boot finished");
}

void loop() {
  //display_pressH();
  playAsteroids();
}
