#include "MCP2515_Mock.hpp"

bool MCP2515::mayInitialise = true;
bool MCP2515::message_available = true;
bool MCP2515::may_send_message = true;

can_frame MCP2515::rx_frame = Echo_Request_Packet::serialise(32);
can_frame MCP2515::latest_tx_frame;

MCP2515::MCP2515(uint8_t _CS_Pin)
    : CS_Pin(_CS_Pin)
{
}

MCP2515::ERROR MCP2515::reset()
{
    if (!mayInitialise)
        return ERROR_FAILINIT;

    return ERROR_OK;
}

MCP2515::ERROR MCP2515::setNormalMode()
{
    return ERROR_OK;
}

MCP2515::ERROR MCP2515::setBitrate(const CAN_SPEED canSpeed, CAN_CLOCK canClock)
{
    return ERROR_OK;
}

MCP2515::ERROR MCP2515::readMessage(can_frame *dst_frame)
{
    if (!message_available)
        return ERROR_NOMSG;

    copy_frame(dst_frame, &rx_frame);

    // No more messages pls :)
    message_available = false;
    return ERROR_OK;
}

MCP2515::ERROR MCP2515::sendMessage(can_frame *frame)
{
    copy_frame(&latest_tx_frame, frame);

    if (!may_send_message)
        return ERROR_FAILTX;

    return ERROR_OK;
}

void MCP2515::set_packet_rx(can_frame frame)
{
    rx_frame = frame;
}
