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

#define DATA_PACKET_SENDING_ID(id, name) \
    PacketComm::DataPacket name(id, payload(commData.name), payloadSize(commData.name))
#define DATA_PACKET_RECEIVING_ID(id, name, callback) \
    PacketComm::DataPacket name(id, payload(commData.name), payloadSize(commData.name), callback)


CommData commData;


namespace DataPackets
{
    using namespace PacketReceivedCallbacks;

    // drone <-> pilot
    DATA_PACKET_RECEIVING(droneMeasurements, droneMeasurementsCallback);
    DATA_PACKET_RECEIVING(droneState, droneStateCallback);
    DATA_PACKET_SENDING(steering);
    DATA_PACKET_SENDING(flightModeChange);
    DATA_PACKET_SENDING(pidTuning);

    // android:
    DATA_PACKET_RECEIVING_ID(70, androidPIDTuning, androidPidTuningCallback);
    DATA_PACKET_SENDING_ID(69, androidDroneData);
}
