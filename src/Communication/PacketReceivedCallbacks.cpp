/**
 * @file PacketReceivedCallbacks.cpp
 * @author Jan Wielgus
 * @date 2021-01-07
 * 
 */

#include "Communication/PacketReceivedCallbacks.h"
#include "Instances.h"
#include "CommData.h"
#include "Communication/DataPackets.h"


void PacketReceivedCallbacks::droneMeasurementsCallback()
{
    // TODO: do something when received new data
    // (LCD values update is in the lcd tasker task)
}


void PacketReceivedCallbacks::droneStateCallback()
{
    
}


void PacketReceivedCallbacks::pidTuningAndroidCallback()
{
    const auto& input = commData.androidPIDTuning;
    auto& output = commData.pidTuning;

    output.tunedController_ID = input.tunedController_ID;
    output.kP = float(input.kP) / 100.f;
    output.kI = float(input.kI) / 100.f;
    output.kD = float(input.kD) / 100.f;
    output.iMax = (float)input.iMax;

    Instance::droneComm.send(&DataPackets::pidTuning);
}
