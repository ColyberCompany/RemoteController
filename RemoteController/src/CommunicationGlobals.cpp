/**
 * @file CommunicationGlobals.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Instantiation of communication global variables.
 * @date 2021-03-28
 * 
 */

#include "../Communication/CommData.h"
#include "../Communication/DataPackets.h"


CommData commData;


namespace DataPackets
{
    using namespace DataPacketClasses;

    Steering steering;
    FlightModeChange flightModeChange;
    DroneMeasurementsAndState droneMeasurementsAndState;
    // all other data packets...
}
