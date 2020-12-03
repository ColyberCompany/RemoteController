/**
 * @file SendData.h
 * @author Jan Wielgus
 * @brief Structures with all variables that are sent.
 * @date 2020-12-03
 * 
 */

#ifndef SENDDATA_H
#define SENDDATA_H

#include <ByteTypes.h>


struct DataForDrone
{
    uint16Byte throttle;
    int16Byte yaw;
    int16Byte pitch;
    int16Byte roll;

    // TODO: check drone file (further development required)
};


#endif

