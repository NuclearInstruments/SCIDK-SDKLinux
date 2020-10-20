#ifndef __NIERRORCODE_H
#define __NIERRORCODE_H
#include <stdint.h>

#pragma once
typedef uint32_t	NI_RESULT;

#define		NI_OK									0x00000000
#define		NI_ERROR_GENERIC						0x00000001
#define		NI_ERROR_INTERFACE						0x00000002
#define		NI_ERROR_FPGA							0x00000003
#define		NI_ERROR_TRANSFER_MAX_LENGTH			0x00000004
#define		NI_ERROR_NOTCONNECTED					0x00000005
#define		NI_NO_DATA_AVAILABLE					0x00000006
#define		NI_TOO_MANY_DEVICES_CONNECTED			0x00000007
#define		NI_INVALID_HANDLE						0x00000008

typedef uint32_t	NI_STATUS;
#define		NI_ONLINE				0x00000000
#define		NI_ERROR				0x00000001
#define		NI_OFFLINE				0x00000002

#define		NI_CONNECTED			0x00000001
#define		NI_NOTCONNECTED			0x00000000



typedef struct _tUSBDevice
{
	long id;
	char SN[64];
	char DESC[128];
} tUSBDevice;


#define		NI_CONNECT_USB									0x00000000

#endif // __NIERRORCODE_H