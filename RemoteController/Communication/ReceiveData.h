/**
 * @file ReceiveData.h
 * @author Jan Wielgus
 * @brief Structures for all received data.
 * @date 2020-11-05
 * 
 */

#ifndef RECEIVEDATA_H
#define RECEIVEDATA_H

#include <ByteTypes.h>


struct DataFromDrone
{
    int8Byte pitchAngle_deg;
    int8Byte rollAngle_deg;
    int16Byte heading_deg;
    int16Byte altitude_cm;
    int32Byte longitude; // TODO: add unit (same in drone code)
    int32Byte latitude; // TODO: add unit (same in drone code)

    uint8Byte droneConnectionStability;
};


#endif