/**
 * @file PacketReceivedEvents.h
 * @author Jan Wielgus
 * @brief Implementation of all packet events.
 * @date 2021-01-07
 * 
 */

#ifndef PACKETRECEIVEDEVENTS_H
#define PACKETRECEIVEDEVENTS_H

#include <IExecutable.h>


namespace PacketReceivedEvents
{
    class DroneMeasurementsAndState : public IExecutable {
        void execute() override;
    };


    class PIDTuningAndroid : public IExecutable {
        void execute() override;
    };


    // events for other data packets...
}


#endif
