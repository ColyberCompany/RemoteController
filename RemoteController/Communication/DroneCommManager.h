/**
 * @file DroneCommManager.h
 * @author Jan Wielgus
 * @brief This class set up drone communication data packets
 * and contain all variables used in communication with drone.
 * @date 2021-01-07
 * 
 */

#ifndef DRONECOMMMANAGER_H
#define DRONECOMMMANAGER_H

#include <PacketCommunication.h>
#include <DataPacket.h>
#include "ReceiveData.h"
#include "SendData.h"
#include "PacketReceivedEvents.h"


class DroneCommManager
{
public:
    struct Sending
    {
        DataForDrone data;

        DataPacket steering;
        // add other here...

        Sending()
            : steering(0)
        {}
    } sending;


    struct Receiving
    {
        DataFromDrone data;
        
        DataPacket measurementsAndState;
        // add other here...

        Receiving()
            : measurementsAndState(10)
        {}
    } receiving;


private:
    PacketReceivedEvents::MeasurementsAndState measurementsAndStatePacketEvent;


public:
    DroneCommManager(PacketCommunication& packetComm)
    {
        // - add all data that this packet consists of
        // - set packet received events for received packets
        // - add receive data packets to the packetComm

    // receive:

        // measurements and state
        // TODO: think about structure of this packet and if to split it (same on the drone side)
        receiving.measurementsAndState.addByteType(receiving.data.pitchAngle_deg);
        receiving.measurementsAndState.addByteType(receiving.data.rollAngle_deg);
        receiving.measurementsAndState.addByteType(receiving.data.heading_deg);
        receiving.measurementsAndState.addByteType(receiving.data.altitude_cm);
        receiving.measurementsAndState.addByteType(receiving.data.longitude);
        receiving.measurementsAndState.addByteType(receiving.data.latitude);
        receiving.measurementsAndState.addByteType(receiving.data.droneConnectionStability);
        receiving.measurementsAndState.setPacketReceivedEvent(measurementsAndStatePacketEvent);

        packetComm.addReceiveDataPacketPointer(&receiving.measurementsAndState);


    // send:

        // steering
        sending.steering.addByteType(sending.data.throttle);
        sending.steering.addByteType(sending.data.yaw);
        sending.steering.addByteType(sending.data.pitch);
        sending.steering.addByteType(sending.data.roll);
    }


    DroneCommManager(const DroneCommManager&) = delete;
    DroneCommManager& operator=(const DroneCommManager&) = delete;
};


#endif
