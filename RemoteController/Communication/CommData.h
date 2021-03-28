/**
 * @file CommData.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief All communication variables.
 * @date 2021-03-28
 * 
 */

#ifndef COMMDATA_H
#define COMMDATA_H

#include <ByteTypes.h>


struct CommData
{
    struct {
        int8Byte pitchAngle_deg;
        int8Byte rollAngle_deg;
        int16Byte heading_deg;
        int16Byte altitude_cm;
        int32Byte longitude; // TODO: add unit (same in drone code)
        int32Byte latitude; // TODO: add unit (same in drone code)
        uint8Byte connectionStability;
    } drone;

    struct {
        struct {
            uint16Byte throttle;
            int16Byte yaw;
            int16Byte pitch;
            int16Byte roll;
        } stick;

        // TODO: consider adding pilot coordinates (polar or rectangular)
    } pilot;

    struct {
        uint8Byte tunedController_ID;
        floatByte kP;
        floatByte kI;
        floatByte kD;
        floatByte iMax;
    } pidTuner;


    uint8Byte flightMode;
    //uint8Byte signalLostScenario; // read todo below (probably in a drone code)
};

extern CommData commData;


#endif
