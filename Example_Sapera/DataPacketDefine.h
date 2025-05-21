#pragma once
struct Header
{
	short PacketCode;
	short PacketSize;
};

#define PACKET_CODE_GRAB_CNT							 101
#define PACKET_CODE_GRAB_START							 102
#define PACKET_CODE_GRAB_STOP							 103
#define PACKET_CODE_SNAP							 104