/**
 * @file ScreenValues.h
 * @author Jan Wielgus
 * @brief Values that could be print on the screen.
 * @date 2020-12-02
 * 
 */

#ifndef SCREENVALUES_H
#define SCREENVALUES_H


struct ScreenValues
{
    uint8_t dronePitch;
    uint8_t droneRoll;

    uint16_t stickThrottle;
    int16_t stickYaw;
    int16_t stickPitch;
    int16_t stickRoll;

    bool leftSwitchState;
    bool rightSwitchState;
    // ...
};


#endif

