/**
 * @file ReceiveData.h
 * @author Jan Wielgus
 * @brief Structures with all variables that are sent.
 * @date 2020-11-05
 * 
 */

#ifndef SENDDATA_H
#define SENDDATA_H

#include "../Enums/FlightModeTypes.h"
#include <ByteTypes.h>


struct DataForDrone
{
    uint16Byte throttle;
    int16Byte yaw;
    int16Byte pitch;
    int16Byte roll;

    uint16Byte pilotDistance_dm;
	uint16Byte pilotDirection;
    uint8Byte flightMode;
    //uint8Byte signalLostScenario; // read todo below (probably in a drone code)

    uint8Byte tunedPID_ID;
    floatByte pidP;
    floatByte pidI;
    floatByte pidD;
    floatByte pidIMax;
};


#endif
