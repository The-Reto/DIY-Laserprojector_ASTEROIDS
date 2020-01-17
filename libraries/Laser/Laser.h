#ifndef LASER_LASER_H
#define LASER_LASER_H

//#define USE_SIMULATOR

/*
 * Encoding constants far the LaserCommands
 */
#define CMD_LASER_OFF 0x1u
#define CMD_COLOR_CHANGE 0x2u
#define CMD_RED_BIG 0x4u
#define CMD_RED_SMALL 0x8u
#define CMD_GREEN_BIG 0x10u
#define CMD_GREEN_SMALL 0x20u
#define CMD_BLUE_BIG 0x40u
#define CMD_BLUE_SMALL 0x80u
#define CMD_GET_DATA 0xFFFu

/*
 * Encoding constants for the Laser color which is stared in a unsigned char (8 bits)
 * Each chanel gets 2 bits (values can be 0, 75, 150, 255), the two msb are unused
 * EXAMPLE:
 * 00 11 00 11 (EMPTY EMPTY BLUE BLUE GREEN GREEN RED RED) <-> RGB: 255,0,255
 */
#define RED_SMALL   0x1u
#define RED_BIG     0x2u
#define GREEN_SMALL 0x4u
#define GREEN_BIG   0x8u
#define BLUE_SMALL  0x10u
#define BLUE_BIG    0x20u

#define COLOR_RED RED_BIG
#define COLOR_GREEN GREEN_BIG
#define COLOR_BLUE BLUE_BIG
#define COLOR_YELLOW RED_BIG+GREEN_BIG
#define COLOR_PURPLE RED_BIG+BLUE_BIG
#define COLOR_TEAL GREEN_BIG+BLUE_BIG
#define COLOR_WHITE RED_BIG+GREEN_BIG+BLUE_BIG
#define COLOR_BLACK 0

#define POINT_DELAY 150
#define COLOR_CHANGE_DELAY 250

typedef struct Laser LASER;             // use LASER instead of struct Laser
typedef unsigned long COMMAND;    // use COMMAND instead of struct LaserCommand
typedef unsigned char COLOR;            // use COLOR to indicate that the unsigned char is a color


#include <FixPoint.h>
#ifdef USE_SIMULATOR
    #include <Simulator.h>
    #define DAC_RESOLUTION 4096
    #define IMAGE_SIZE 512
    /*
     * Writes the picture drawn in the simulator to a .pdb file - the file will be located in the directory of execution
     * Only included in simulator version!
     * INPUTS
     * l: a pointer to the used Laser struct
     * OUTPUT
     * none
     */
    void writeFrame(LASER* l);
#else
    #include <DAC.h>

    #define SDI_PIN 51
    #define SCK_PIN 52
    #define CS_PIN 53
    #define LDAC_PIN 5

    #define RED_PIN 40
    #define GREEN_PIN 41
    #define BLUE_PIN 42
#endif //USE_SIMULATOR

/*
 * A struct holding representing the state of the Laser
 * contains the current x- and y-coordinate as well as the current color.
 * In Simulator mode this struct also includes the image as well as the image identifier (int frame) on which to be drawn.
 */
struct Laser {
    int x, y;
    COLOR color;
#ifdef USE_SIMULATOR
    int frame;
    IMAGE target;
#else
    DAC dac;
#endif //USE_SIMULATOR
};

/*
 * generates a Laser and initializes all neccesary values
 * INPUT
 * none
 * OUTPUT
 * a new Laser (it is allocated it has to be be freed using te deleteLaser function)
 */
LASER* generateLaser();

void setLaserColor(LASER *l, COLOR col);

/*
 * deletes a laser (frees the allocated space)
 * INPUT
 * l: a pointer to the Laser to be deleted
 * OUTPUT
 * none
 */
int deleteLaser(LASER* l);

/*
 * Moves the laser point to the new position specified in the Command cmd, during the move the laser will have the color encoded in the commnad
 * INPUT
 * l: a pointer to the Laser to move
 * cmd: the command for the laser, contains the coordinates and the color of the move
 */
void moveLaser(LASER* l, COMMAND cmd);

/*
 * extracts the color information from the command
 * INPUT
 * cmd: a command from which the color is to be extracted
 */
COLOR getColor(COMMAND cmd);


/*
 * creates a valid laser command (to be used in the moveLaser function)
 * using this method to generate commands (rather than doing it by hand) is highly recommended as the structure of a command may change
 * INPUT
 * xPos: the x-coordinate to move to (between 0 and 4095)
 * yPos: the y-coordinate to move to (between 0 and 4095)
 * col:  tho color of the laser during the move, see typedef Color
 * OUTPUTS
 * a valid command
 */
COMMAND getCommand(unsigned short xPos, unsigned short yPos, COLOR col);

COMMAND addCorrection(int x, int y, COMMAND c);

#endif //LASER_LASER_H