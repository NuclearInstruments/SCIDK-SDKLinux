#ifdef _WINDOWS
    #include "stdafx.h"
#endif

#include "../include/ftd2xx.h"
#include<iostream>
#include <time.h>
#include <string.h>

#include "../include/FTDI_CPP_DLL.h"


#ifdef _WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif


#include <stdexcept>

using namespace std;

namespace NIUSBPHY
{

	NI_USBPHY::NI_USBPHY()
	{
		int i;
		i=1;
		return;
	}
	NI_USBPHY::~NI_USBPHY()
	{
		int i;
		i=1;
		return;
	}
NI_RESULT NI_USBPHY::EnumerateUsbDevice (char *pvArg1, char *board_model, unsigned int *numDevs)
{

	char Buffer[255];
	unsigned int i;
	FT_STATUS ftStatus;
	int count;
	int q = 0;

	ftStatus = FT_ListDevices(&count, NULL, FT_LIST_NUMBER_ONLY);
	pvArg1[0] = '\0';
	if (ftStatus == FT_OK)
	{

		for (i=0;i<count;i++)
		{
			FT_ListDevices((PVOID)i, Buffer, FT_LIST_BY_INDEX | FT_OPEN_BY_DESCRIPTION);
			if (ftStatus == FT_OK) {
				if (strcmp(Buffer, board_model)==0)
				{
					FT_ListDevices((PVOID)i, Buffer, FT_LIST_BY_INDEX | FT_OPEN_BY_SERIAL_NUMBER);
					if (ftStatus == FT_OK) {
						sprintf(pvArg1, "%s%s;", pvArg1, Buffer);
						q++;
					}
					
				}
			}		
		}
	}
	else
	{
		return NI_ERROR_INTERFACE;
	}

	//remove last ;
	if (q > 0)
		pvArg1[strlen(pvArg1) - 1] = '\0';

	*numDevs = q;

	return NI_OK;
}


NI_RESULT NI_USBPHY::OpenDeviceBySerialNumber (char *SN)
{
	FT_STATUS ftStatus;
	ftStatus = FT_OpenEx(SN,FT_OPEN_BY_SERIAL_NUMBER,&ftHandle); 
	if (ftStatus == FT_OK) { 
		ConnectionStatus = NI_CONNECTED;
		if (FT_ResetDevice(ftHandle) != FT_OK)
			return NI_ERROR_INTERFACE;
		if (FT_SetBitMode(ftHandle,0xFF,FT_BITMODE_SYNC_FIFO) != FT_OK)
			return NI_ERROR_INTERFACE;
		if (FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0, 0) != FT_OK)
			return NI_ERROR_INTERFACE;
		if (FT_SetTimeouts(ftHandle, 4000, 4000) != FT_OK)
			return NI_ERROR_INTERFACE;
		if (FT_Purge(ftHandle, FT_PURGE_RX) != FT_OK)
			return NI_ERROR_INTERFACE;
		if (FT_Purge(ftHandle, FT_PURGE_TX) != FT_OK)
			return NI_ERROR_INTERFACE;

		return NI_OK;
	} 
	else { 
		ConnectionStatus = NI_NOTCONNECTED;
		return NI_ERROR_INTERFACE;
	} 

}

NI_RESULT NI_USBPHY::CloseConnection ()
{
	FT_STATUS ftStatus;
	ftStatus = FT_Close(ftHandle); 
	if (ftStatus == FT_OK) { 
		return NI_OK;
	}
	else
	{
		return NI_ERROR_INTERFACE;
	}
}
NI_RESULT NI_USBPHY::WriteToFPGA (unsigned int *d, unsigned int addr, unsigned int length, unsigned int BusMode, unsigned int timeout_ms)
{
		unsigned char h[200];
		unsigned int ll;
		unsigned int aa;
		unsigned int wbtot;
		DWORD translen;
		DWORD bytewritten;
		int currentpointer=0;
		unsigned char *d_byte;

		if (ConnectionStatus != NI_CONNECTED)
			return NI_ERROR_NOTCONNECTED;

		if (length > 16777216)
			return NI_ERROR_TRANSFER_MAX_LENGTH;


		d_byte = (unsigned char*) d;

		//FT_Purge(ftHandle, FT_PURGE_TX);
			

		ll = length -1;
		aa = addr;

		//HEADER PACCHETTO
		h[0] = 0xFF;
		h[1] = 0x00;
		h[2] = 0xAB;
		
		if (BusMode==0)
			h[3] = 0xF0;
		else
			h[3] = 0xF2;

		h[4] = (aa >> 24) & 0xFF;
		h[5] = (aa >> 16) & 0xFF;
		h[6] = (aa >> 8) & 0xFF;
		h[7] = (aa >> 0) & 0xFF;
		h[8] = (ll >> 16) & 0xFF;
		h[9] = (ll >> 8) & 0xFF;
		h[10] = (ll >> 0) & 0xFF;

		wbtot = 0;
		translen = 4* length;
		if(FT_Write(ftHandle,h,11, &bytewritten))
			return NI_ERROR_INTERFACE;

		do
		{
			if(FT_Write(ftHandle,&d_byte[currentpointer],translen, &bytewritten))
				return NI_ERROR_INTERFACE;
			translen = translen - bytewritten;
			currentpointer = currentpointer + bytewritten;
			wbtot++;
		}while(translen > 0);


		return NI_OK;
	
}


NI_RESULT NI_USBPHY::ReadFromFPGA (unsigned int *d, unsigned int addr, unsigned int length, unsigned int BusMode, unsigned int timeout_ms)
{
		unsigned char h[200];
		unsigned int ll;
		unsigned int aa;
		unsigned int wbtot;
		DWORD translen;
		DWORD byteread;
		DWORD bytewritten;
		int currentpointer=0;
		unsigned char *d_byte;
        DWORD lpdwAmountInRxQueue;
        DWORD lpdwAmountInTxQueue;
        DWORD lpdwEventStatus; 
		if (ConnectionStatus != NI_CONNECTED)
			return NI_ERROR_NOTCONNECTED;

		if (length > 16777216)
			return NI_ERROR_TRANSFER_MAX_LENGTH;


		d_byte = (unsigned char*) d;

		//FT_Purge(ftHandle, FT_PURGE_TX);
		//FT_Purge(ftHandle, FT_PURGE_RX);
			

		ll = length -1;
		aa = addr;

		//HEADER PACCHETTO
		h[0] = 0xFF;
		h[1] = 0x00;
		h[2] = 0xAB;
		if (BusMode == 0)
			h[3] = 0xF1;
		else
			h[3] = 0xF3;

		h[4] = (aa >> 24) & 0xFF;
		h[5] = (aa >> 16) & 0xFF;
		h[6] = (aa >> 8) & 0xFF;
		h[7] = (aa >> 0) & 0xFF;
		h[8] = (ll >> 16) & 0xFF;
		h[9] = (ll >> 8) & 0xFF;
		h[10] = (ll >> 0) & 0xFF;

		wbtot = 0;
		translen = 4* length;
		if(FT_Write(ftHandle,h,11, &bytewritten))
			return NI_ERROR_INTERFACE;

        //printf("<><><> %d %d \n",addr, length);
        do{
		        
            FT_GetStatus(ftHandle, &lpdwAmountInRxQueue,
                         &lpdwAmountInTxQueue, 
                         &lpdwEventStatus);
            
        //    printf("-- %d %d -- \n",lpdwAmountInRxQueue, translen);
            uint32_t min = lpdwAmountInRxQueue > translen ? translen : lpdwAmountInRxQueue;
            if (lpdwAmountInRxQueue > 0){ 
                if(FT_Read(ftHandle,&d_byte[currentpointer],min, &byteread))
                    return NI_ERROR_INTERFACE;
                translen = translen - byteread;
                currentpointer = currentpointer + byteread;
                wbtot++;            
            } else {
                Sleep(10);
            }
		}while(translen > 0);

        //flush
        FT_GetStatus(ftHandle, &lpdwAmountInRxQueue,
             &lpdwAmountInTxQueue, 
             &lpdwEventStatus);
        
        if (lpdwAmountInRxQueue>0) {
        //        printf("==== %d ====\n",lpdwAmountInRxQueue);
            char *dummy = (char*) malloc(lpdwAmountInRxQueue+1);
            if(FT_Read(ftHandle,dummy,lpdwAmountInRxQueue, &byteread))
                return NI_ERROR_INTERFACE;
            free(dummy);
        
        }
        //printf("..............\n",addr, length);

		return NI_OK;
}
NI_RESULT NI_USBPHY::WriteReg (unsigned int regVal, unsigned int addr)
{

	return WriteToFPGA(&regVal, addr,1,0,1);

}

NI_RESULT NI_USBPHY::ReadReg (unsigned int *regVal, unsigned int addr)
{

	return ReadFromFPGA(regVal, addr,1, 0, 4);

}

}