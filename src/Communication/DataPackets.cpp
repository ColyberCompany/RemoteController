/**
 * @file DataPackets.cpp
 * @author Jan Wielgus
 * @brief Instantiation of communication data packets.
 * @date 2022-07-04
 */

#include "DataPackets.h"
#include "DataPacketIDs.h"
#include "PacketReceivedCallbacks.h"

#define payload(x) ((uint8_t*)&(x))
#define payloadSize(x) (sizeof(x))

// Better looking way to create a DataPacket instance
#define DATA_PACKET_SENDING(name) \
    PacketComm::DataPacket name(DataPacketIDs::name, payload(commData.name), payloadSize(commData.name))
#define DATA_PACKET_RECEIVING(name, callback) \
    PacketComm::DataPacket name(DataPacketIDs::name, payload(commData.name), payloadSize(commData.name), callback)


CommData commData;


namespace DataPackets
{
    using namespace PacketReceivedCallbacks;

    // -------
    // Remember that each data packet should have different ID!
    // -------

    // received:
    DATA_PACKET_RECEIVING(droneMeasurements, droneMeasurementsCallback);
    DATA_PACKET_RECEIVING(droneState, droneStateCallback);
    // sent:
    DATA_PACKET_SENDING(steering);
    DATA_PACKET_SENDING(flightModeChange);
    DATA_PACKET_SENDING(pidTuning);
}
