#include "CAN_Mock.hpp"

bool CAN_Mock::mayInitialise = true;
bool CAN_Mock::message_available = true;
bool CAN_Mock::may_send_message = true;

CAN_Frame CAN_Mock::rx_frame = Echo_Request_Packet::serialise(32);
CAN_Frame CAN_Mock::latest_tx_frame;

void CAN_Mock::set_packet_rx(CAN_Frame frame)
{
    rx_frame = frame;
}
