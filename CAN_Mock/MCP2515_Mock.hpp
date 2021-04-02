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

/* CAN payload length and DLC definitions according to ISO 11898-1 */
#define CAN_MAX_DLC 8
#define CAN_MAX_DLEN 8

struct can_frame
{
	uint32_t can_id; /* 32 bit CAN_ID + EFF/RTR/ERR flags */
	uint8_t can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
	uint8_t data[CAN_MAX_DLEN] __attribute__((aligned(8)));
};

enum CAN_CLOCK
{
	MCP_20MHZ,
	MCP_16MHZ,
	MCP_8MHZ
};

enum CAN_SPEED
{
	CAN_5KBPS,
	CAN_10KBPS,
	CAN_20KBPS,
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
	CAN_1000KBPS
};

struct MCP2515
{
	bool initialised;
	uint8_t CS_Pin;

	static bool mayInitialise;
	static bool message_available;
	static bool may_send_message;
	static bool may_set_mode;
	static bool may_set_bitrate;

	static can_frame rx_frame;
	static can_frame latest_tx_frame;

	enum ERROR
	{
		ERROR_OK = 0,
		ERROR_FAIL = 1,
		ERROR_ALLTXBUSY = 2,
		ERROR_FAILINIT = 3,
		ERROR_FAILTX = 4,
		ERROR_NOMSG = 5
	};

	MCP2515(uint8_t _CS_Pin);
	ERROR reset();
	ERROR setNormalMode();
	ERROR setBitrate(const CAN_SPEED canSpeed, CAN_CLOCK canClock);

	ERROR readMessage(can_frame *dst_frame);
	ERROR sendMessage(can_frame *frame);

	static void set_packet_rx(can_frame frame);
};

#include "../../lib/CAN_Interface/include/Packets.hpp"
#include "../../lib/CAN_Interface/include/CAN_Copy_Frame.hpp"

#endif /* mocks_CAN_Mock_CAN_Mock_hpp */