//
// Created by Livio on 06.11.2019.
//

#ifndef DIY_LASERPROJEKTOR_FIXEDPOINTARITHMETIC_H
#define DIY_LASERPROJEKTOR_FIXEDPOINTARITHMETIC_H

#ifdef __cplusplus
extern "C"{
#endif

#define FIXEDPOINT_SCALE 16u

//UNCOMMENT NEXT LINE FOR USE ON ARDUINO
//#define USE_HARDWARE

typedef long FIXPOINT;
typedef unsigned long U_FIXPOINT;

/*
 * Transforms an integer to a fixedpoint value.
 * casts the integer into a long and bitshifts it by FIXEDPOINT_SCALE to the left
 */
FIXPOINT intToFixed(int x);

/*
 * Transforms a fixedpoint to an int
 * bitshifts the fixedpoint by FIXEDPOINT_SCALE to the right and casts it to an int
 */
int fixedToInt(FIXPOINT x);


/*
 * Transforms a double to an FIXPOINt
 * Avoid using on arduino!!
 */
#define doubleToFixed(x) ((FIXPOINT) ((x) * ((U_FIXPOINT) 1u << FIXEDPOINT_SCALE)))

/*
 * Transforms a FIXPOINT to a double
 * Avoid using on arduino!!
 */
#define fixedToDouble(x) (((double) (x) / ((double) ((FIXPOINT) 1u << FIXEDPOINT_SCALE))))

/*
 * multiplies two Fixedpoints together
 * To be used only if absolutely needed because a cast to a long long is required (expensive)
 * Avoid using on arduino!!
 * Only use if the expected result of the multiplication >= 2^16!!! Otherwise use normal multiplication
 */
FIXPOINT fpMultiplication(FIXPOINT x, FIXPOINT y);

/*
 * divides two Fixedpoint x by fixedpoint y
 * To be used only if absolutely needed because a cast to a long long is required (expensive)
 * Avoid using on arduino!!
 * Only use this in case that y > x, otherwise use normal division!
 */
FIXPOINT fpDivision(FIXPOINT x, FIXPOINT y);

/*
 * Returns the sin of the angle as a FIXPOINT
 * the angle is to be passed in degrees (0 to 360)
 * for angles larger than 360 the remainder x%360 will be used
 */
FIXPOINT fpSin(int angle);

/*
 * Returns the cos of the angle as a FIXPOINT
 * the angle is to be passed in degrees (0 to 360)
 * for angles larger than 360 the remainder x%360 will be used
 */
FIXPOINT fpCos(int angle);


/*
 * Returns the result of the following function as a FIXPOINT:
 * ( 1 + erf( 6.1645 * ( x / 256 - 0.5 ) ) ) / 2
 * Explanation:
 * Returns values between 0 and 1 in a pleasant S curve
 */
FIXPOINT fpErf(int x);

#ifdef __cplusplus
}
#endif

#endif //DIY_LASERPROJEKTOR_FIXEDPOINTARITHMETIC_H
