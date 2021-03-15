//
//  CAN_Mock.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 10/03/2021.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef mocks_CAN_Mock_CAN_Mock_hpp
#define mocks_CAN_Mock_CAN_Mock_hpp

#include <stdint.h>
#include "../../lib/CAN_Interface/include/Packets.hpp"

#define CAN_OK (0)
#define CAN_FAILINIT (1)
#define CAN_FAILTX (2)
#define CAN_MSGAVAIL (3)
#define CAN_NOMSG (4)
#define CAN_CTRLERROR (5)
#define CAN_GETTXBFTIMEOUT (6)
#define CAN_SENDMSGTIMEOUT (7)
#define CAN_FAIL (0xff)

typedef enum
{
    CAN_NOBPS,
    CAN_5KBPS,
    CAN_10KBPS,
    CAN_20KBPS,
    CAN_25KBPS,
    CAN_31K25BPS,
    CAN_33KBPS,
    CAN_40KBPS,
    CAN_50KBPS,
    CAN_80KBPS,
    CAN_83K3BPS,
    CAN_95KBPS,
    CAN_100KBPS,
    CAN_125KBPS,
    CAN_200KBPS,
    CAN_250KBPS,
    CAN_500KBPS,
    CAN_666KBPS,
    CAN_800KBPS,
    CAN_1000KBPS
} MCP_BITTIME_SETUP;

struct CAN_Mock
{
    bool initialised;
    uint8_t CS_Pin;

    static bool mayInitialise;
    static bool message_available;
    static bool may_send_message;

    static CAN_Frame rx_frame;
    static CAN_Frame latest_tx_frame;

    CAN_Mock(uint8_t _CS_Pin)
        : CS_Pin(_CS_Pin)
    {
    }

    uint8_t begin(uint32_t speedset)
    {
        if (!mayInitialise)
            return CAN_FAILINIT;

        return CAN_OK;
    }

    uint8_t checkReceive()
    {
        return (message_available ? CAN_MSGAVAIL : CAN_NOMSG);
    }

    uint8_t readMsgBuf(uint8_t *len, uint8_t *buf)
    {
        // Set length
        memcpy(len, &rx_frame.can_dlc, sizeof(rx_frame.can_dlc));

        // Set data
        memcpy(buf, &rx_frame.data, rx_frame.can_dlc);

        // No more messages pls
        message_available = false;
        return 0;
    }

    uint8_t sendMsgBuf(uint32_t id, uint8_t ext, uint8_t len, uint8_t *buf)
    {
        latest_tx_frame.can_id = id;
        latest_tx_frame.can_dlc = len;
        memcpy(&latest_tx_frame.data, buf, 8);

        if (!may_send_message)
            return CAN_SENDMSGTIMEOUT;

        return CAN_OK;
    }

    uint32_t getCanId()
    {
        return rx_frame.can_id;
    }

    static void set_packet_rx(CAN_Frame frame);
};
#endif /* mocks_CAN_Mock_CAN_Mock_hpp */