/**
 * @file PacketReceivedCallbacks.cpp
 * @author Jan Wielgus
 * @date 2021-01-07
 * 
 */

#include "../Communication/PacketReceivedCallbacks.h"
#include "../Instances.h"
#include "../Communication/CommData.h"
#include "../Communication/DataPackets.h"

#include "../tempChangeIPFunc.h"


void PacketReceivedCallbacks::droneMeasurementAndStateCallback()
{
    // TODO: do something when received new data
    // (LCD values update is in the lcd tasker task)

    //Serial.println("dziala1");


    commData.androidApp.pitch = float(commData.drone.pitch) / 100.f;
    commData.androidApp.roll = float(commData.drone.roll) / 100.f;
    commData.androidApp.heading = float(commData.drone.heading_deg);
    commData.androidApp.altitude = float(commData.drone.altitude_cm);
    commData.androidApp.latitude = float(commData.drone.latitude);
    commData.androidApp.longitude = float(commData.drone.longitude);
    commData.androidApp.accX = float(commData.drone.accX) / 100.f;
    commData.androidApp.accY = float(commData.drone.accY) / 100.f;
    commData.androidApp.accZ = float(commData.drone.accZ) / 100.f;
    commData.androidApp.gyroX = float(commData.drone.gyroX) / 100.f;
    commData.androidApp.gyroY = float(commData.drone.gyroY) / 100.f;
    commData.androidApp.gyroZ = float(commData.drone.gyroZ) / 100.f;
    commData.androidApp.magnX = float(commData.drone.magnX) / 100.f;
    commData.androidApp.magnY = float(commData.drone.magnY) / 100.f;
    commData.androidApp.magnZ = float(commData.drone.magnZ) / 100.f;

    tempSetIPToAndroidApp();

    Instance::droneComm.send(&DataPackets::androidAppData);

    tempSetIPToDrone();
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
