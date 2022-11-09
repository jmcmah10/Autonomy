#include <stdint.h>
#include "pigpio.h"
#include "tank.h"


int16_t Initialize_Tank()
{
    int16_t ret;
    if((ret = gpioinitialise()) < 0) return ret;
    return SUCCESS;
}

int16_t Set_Left_Velocity(float velocity)
{
    if(velocity < VEL_MAX_NEG || velocity > VEL_MAX_POS) return VELOCITY_OUT_OF_RANGE;

    int16_t ret;
    
    uint16_t PWM;
    if(velocity == 0)
        if((ret = gpioHardwarePWM(LEFT_MOTOR_PIN, PWM_FREQUENCY, PWM_ZERO)) < 0) return ret;
    else if(velocity > 0)
    {
        velocity = velocity < VEL_MIN_POS ? VEL_MIN_POS : velocity;
        uint16_t PWM = (uint16_t)(PWM_ZERO + velocity * (PWM_MAX_POS - PWM_MIN_POS) / (VEL_MAX_POS - VEL_MIN_POS));
        PWM = PWM < PWM_MIN_POS ? PWM_MIN_POS : PWM;
        if((ret = gpioHardwarePWM(LEFT_MOTOR_PIN, PWM_FREQUENCY, PWM)) < 0) return ret;
    }
    else
    {
        velocity = velocity > VEL_MIN_NEG ? VEL_MIN_NEG : velocity;
        uint16_t PWM = (uint16_t)(PWM_ZERO + velocity * (PWM_MAX_NEG - PWM_MIN_NEG) / (VEL_MAX_NEG - VEL_MIN_NEG));
        PWM = PWM > PWM_MIN_NEG ? PWM_MIN_NEG : PWM;
        if((ret = gpioHardwarePWM(LEFT_MOTOR_PIN, PWM_FREQUENCY, PWM)) < 0) return ret;
    }

    return SUCCESS;
}

int16_t Set_Right_Velocity(float velocity)
{
    if(velocity < VEL_MAX_NEG || velocity > VEL_MAX_POS) return VELOCITY_OUT_OF_RANGE;

    int16_t ret;
    
    uint16_t PWM;
    if(velocity == VEL_ZERO)
        if((ret = gpioHardwarePWM(RIGHT_MOTOR_PIN, PWM_FREQUENCY, PWM_ZERO)) < 0) return ret;
    else if(velocity > 0)
    {
        velocity = velocity < VEL_MIN_POS ? VEL_MIN_POS : velocity;
        uint16_t PWM = (uint16_t)(PWM_ZERO + velocity * (PWM_MAX_POS - PWM_MIN_POS) / (VEL_MAX_POS - VEL_MIN_POS));
        PWM = PWM < PWM_MIN_POS ? PWM_MIN_POS : PWM;
        if((ret = gpioHardwarePWM(RIGHT_MOTOR_PIN, PWM_FREQUENCY, PWM)) < 0) return ret;
    }
    else
    {
        velocity = velocity > VEL_MIN_NEG ? VEL_MIN_NEG : velocity;
        uint16_t PWM = (uint16_t)(PWM_ZERO + velocity * (PWM_MAX_NEG - PWM_MIN_NEG) / (VEL_MAX_NEG - VEL_MIN_NEG));
        PWM = PWM > PWM_MIN_NEG ? PWM_MIN_NEG : PWM;
        if((ret = gpioHardwarePWM(RIGHT_MOTOR_PIN, PWM_FREQUENCY, PWM)) < 0) return ret;
    }
    
    return SUCCESS;
}

int16_t Move_Forward(float velocity)
{
    int16_t ret;

    if((ret = Set_Left_Velocity(velocity)) < 0) return ret;
    if((ret = Set_Right_Velocity(velocity)) < 0) return ret;

    return SUCCESS;
}

int16_t Move_Backward(float velocity)
{
    int16_t ret;

    if((ret = Set_Left_Velocity(-velocity)) < 0) return ret;
    if((ret = Set_Right_Velocity(-velocity)) < 0) return ret;

    return SUCCESS;
}

int16_t Swivel_Left()
{
    int16_t ret;

    if((ret = Set_Left_Velocity(VEL_MED_NEG)) < 0) return ret;
    if((ret = Set_Right_Velocity(VEL_MED_POS)) < 0) return ret;

    return SUCCESS;
}

int16_t Swivel_Right()
{
    int ret;

    if((ret = Set_Left_Velocity(VEL_MED_POS)) < 0) return ret;
    if((ret = Set_Right_Velocity(VEL_MED_NEG)) < 0) return ret;

    return SUCCESS;
}

int16_t Stop_Left()
{
    int16_t ret;

    if((ret = Set_Left_Velocity(VEL_ZERO)) < 0) return ret;

    return SUCCESS;
}

int16_t Stop_Right()
{
    int16_t ret;

    if((ret = Set_Right_Velocity(VEL_ZERO)) < 0) return ret;

    return SUCCESS;
}

int16_t Stop()
{
    int16_t ret;
    
    if((ret = Stop_Left()) < 0) return ret;
    if((ret = Stop_Right()) < 0) return ret;

    return SUCCESS;
}