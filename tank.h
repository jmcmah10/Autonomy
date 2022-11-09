#ifndef TANK_H
#define TANK_H

#include <stdint.h>

#define SUCCESS 0
#define VELOCITY_OUT_OF_RANGE -1

#define LEFT_MOTOR_PIN 13
#define RIGHT_MOTOR_PIN 19

#define PWM_FREQUENCY 50
#define PWM_MAX_POS 85000
#define PWM_MIN_POS 78000
#define PWM_ZERO 75000
#define PWM_MIN_NEG 72000
#define PWM_MAX_NEG 65000
#define PWM_RANGE (PWM_MAX_POS - PWM_MAX_NEG)

#define VEL_MAX_NEG -10.0
#define VEL_MED_NEG -5.0
#define VEL_MIN_NEG -0.01
#define VEL_ZERO 0.0
#define VEL_MAX_POS 10.0
#define VEL_MED_POS 5.0
#define VEL_MIN_POS 0.01

/* All functions return an error code. */
/* SUCCESS == 0 */
/* VELOCITY_OUT_OF_RANGE == -1 */
/* The rest can be found here: https://abyz.me.uk/rpi/pigpio/cif.html */

/* These three functions are all you need to mimic the odrive control */

int16_t Initialize_Tank();

int16_t Set_Left_Velocity(float velocity); /* VEL_MAX_NEG <= velocity <= VEL_MAX_POS */

int16_t Set_Right_Velocity(float velocity); /* VEL_MAX_NEG <= velocity <= VEL_MAX_POS */


/* These functions are extra functionality you may or may not use */

int16_t Move_Forward(float velocity); /* VEL_MAX_NEG <= velocity <= VEL_MAX_POS */

int16_t Move_Backward(float velocity); /* VEL_MAX_NEG <= velocity <= VEL_MAX_POS */

int16_t Swivel_Left();

int16_t Swivel_Right();

int16_t Stop_Left();

int16_t Stop_Right();

int16_t Stop();

#endif