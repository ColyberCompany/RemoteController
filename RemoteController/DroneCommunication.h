/**
 * @file DroneCommunication.h
 * @author Jan Wielgus
 * @brief This class is used to put in one place data and
 * data packets needed to communicate with drone.
 * @date 2020-12-03
 * 
 */

#ifndef DRONECOMMUNICATION_H
#define DRONECOMMUNICATION_H

#include <PacketCommunication.h>
#include <DataPacket.h>
#include "SendData.h"
// TODO: ReceiveData.h


class DroneCommunication
{
public:
    DroneCommunication()
        : steering(0)
    {
    // send:
        steering.addByteType(sendData.throttle);
        steering.addByteType(sendData.yaw);
        steering.addByteType(sendData.pitch);
        steering.addByteType(sendData.roll);


    // receive:
        //...
    }

    DroneCommunication(const DroneCommunication&) = delete;
    DroneCommunication& operator=(const DroneCommunication&) = delete;


    DataForDrone sendData;
    // receive data


    // send data packets:
    DataPacket steering; // ID 0


    // receive data packets:
    // TODO: to implement
    // ...
};


#endif

