/**
 * @file DataPackets.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief This class contains instances of all data packets.
 * @date 2021-03-28
 * 
 */


#ifndef DATAPACKETS_H
#define DATAPACKETS_H

#include "CommData.h"
#include "PacketReceivedCallbacks.h"
#include <DataPacket.h>
#include <EventPacket.h>

// -------
// Remember that each data packet should have different ID!
// -------


namespace DataPacketClasses
{
    class Steering : public PacketComm::DataPacket
    {
    public:
        Steering()
            : DataPacket(0)
        {
            addVar(commData.pilot.stick.throttle);
            addVar(commData.pilot.stick.yaw);
            addVar(commData.pilot.stick.pitch);
            addVar(commData.pilot.stick.roll);
        }
    };


    class FlightModeChange : public PacketComm::DataPacket
    {
    public:
        FlightModeChange()
            : DataPacket(10)
        {
            addVar(commData.flightMode);
        }
    };


    class DroneMeasurementsAndState : public PacketComm::DataPacket
    {
    public:
        DroneMeasurementsAndState()
            : DataPacket(50)
        {
            addVar(commData.drone.pitchAngle_deg);
            addVar(commData.drone.rollAngle_deg);
            addVar(commData.drone.heading_deg);
            addVar(commData.drone.altitude_cm);
            addVar(commData.drone.longitude);
            addVar(commData.drone.latitude);
            addVar(commData.drone.connectionStability);

            addVar(commData.drone.pitch);
            addVar(commData.drone.roll);
            addVar(commData.drone.accX);
            addVar(commData.drone.accY);
            addVar(commData.drone.accZ);
            addVar(commData.drone.gyroX);
            addVar(commData.drone.gyroY);
            addVar(commData.drone.gyroZ);
            addVar(commData.drone.magnX);
            addVar(commData.drone.magnY);
            addVar(commData.drone.magnZ);

            setOnReceiveCallback(PacketReceivedCallbacks::droneMeasurementAndStateCallback);
        }
    };


    class AndroidAppData : public PacketComm::DataPacket
    {
    public:
        AndroidAppData()
            : DataPacket(69)
        {
            addVar(commData.androidApp.pitch);
            addVar(commData.androidApp.roll);
            addVar(commData.androidApp.heading);
            addVar(commData.androidApp.altitude);
            addVar(commData.androidApp.latitude);
            addVar(commData.androidApp.longitude);
            addVar(commData.androidApp.accX);
            addVar(commData.androidApp.accY);
            addVar(commData.androidApp.accZ);
            addVar(commData.androidApp.gyroX);
            addVar(commData.androidApp.gyroY);
            addVar(commData.androidApp.gyroZ);
            addVar(commData.androidApp.magnX);
            addVar(commData.androidApp.magnY);
            addVar(commData.androidApp.magnZ);
        }
    };


    class PIDTuning : public PacketComm::DataPacket
    {
    public:
        PIDTuning() : DataPacket(51) {
            addVar(commData.pidTuning.tunedController_ID);
            addVar(commData.pidTuning.kP);
            addVar(commData.pidTuning.kI);
            addVar(commData.pidTuning.kD);
            addVar(commData.pidTuning.iMax);
        }
    };


    class PIDTuningAndroid : public PacketComm::DataPacket
    {
    public:
        PIDTuningAndroid() : DataPacket(100) {
            addVar(commData.pidTuningAndroid.tunedController_ID);
            addVar(commData.pidTuningAndroid.kP);
            addVar(commData.pidTuningAndroid.kI);
            addVar(commData.pidTuningAndroid.kD);
            addVar(commData.pidTuningAndroid.iMax);

            setOnReceiveCallback(PacketReceivedCallbacks::pidTuningAndroidCallback);
        }
    };
}


namespace DataPackets
{
    // Instances created in src/CommunicationGlobals.cpp
    extern DataPacketClasses::Steering steering;
    extern DataPacketClasses::FlightModeChange flightModeChange;
    extern DataPacketClasses::DroneMeasurementsAndState droneMeasurementsAndState;
    extern DataPacketClasses::PIDTuning pidTuning;
    extern DataPacketClasses::PIDTuningAndroid pidTuningAndroid;

    extern DataPacketClasses::AndroidAppData androidAppData;
}


#endif
