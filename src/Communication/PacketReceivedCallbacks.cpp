/**
 * @file PacketReceivedCallbacks.cpp
 * @author Jan Wielgus
 * @date 2021-01-07
 * 
 */

#include "Communication/PacketReceivedCallbacks.h"
#include "Instances.h"
#include "Communication/CommData.h"
#include "Communication/DataPackets.h"


void PacketReceivedCallbacks::droneMeasurementAndStateCallback()
{
    // TODO: do something when received new data
    // (LCD values update is in the lcd tasker task)
}


void PacketReceivedCallbacks::pidTuningAndroidCallback()
{
    commData.pidTuning.tunedController_ID = commData.pidTuningAndroid.tunedController_ID;
    commData.pidTuning.kP = float(commData.pidTuningAndroid.kP) / 100.f;
    commData.pidTuning.kI = float(commData.pidTuningAndroid.kI) / 100.f;
    commData.pidTuning.kD = float(commData.pidTuningAndroid.kD) / 100.f;
    commData.pidTuning.iMax = (float)commData.pidTuningAndroid.iMax;

    Instance::droneComm.send(&DataPackets::pidTuning);
}
