/**
 * @file PacketReceivedCallbacks.h
 * @author Jan Wielgus
 * @brief Implementation of all packet events.
 * @date 2021-01-07
 * 
 */

#ifndef PACKETRECEIVEDCALLBACKS_H
#define PACKETRECEIVEDCALLBACKS_H


namespace PacketReceivedCallbacks
{
    void droneMeasurementAndStateCallback();
    void pidTuningAndroidCallback();

    // callbacks for other data packets...
}


#endif
