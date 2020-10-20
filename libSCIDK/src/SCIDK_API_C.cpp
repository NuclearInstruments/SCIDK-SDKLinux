
#ifdef _WINDOWS
    #include "stdafx.h"
#endif

#include "../include/SCIDK_API_C.h"
#include "../include/FTDI_CPP_DLL.h"
#include <math.h>
#include <stdlib.h>

using namespace NIUSBPHY;
struct 
{
	NI_USBPHY *niSciDK_HAL;
	int valid;
	unsigned int SN;
} Devices[MAX_NUMBER_OF_DEVICE];



SCIDK_API NI_RESULT SCIDK_ConnectUSB(char *SN, NI_HANDLE *handle)
{
	int newdevid;
   
	int i;
	unsigned int reg;
	newdevid =-1;

		for (i=0;i<MAX_NUMBER_OF_DEVICE;i++)
		{
			if (Devices[i].valid == 0)
			{
				newdevid = i;
				break;
			}
		}
		if (newdevid == -1)
		{
			return NI_TOO_MANY_DEVICES_CONNECTED;
		}
		else
		{
			*handle = newdevid;
			Devices[*handle].niSciDK_HAL = new NI_USBPHY () ;


			if (Devices[*handle].niSciDK_HAL->OpenDeviceBySerialNumber (SN) == NI_OK )
			{
				Devices[*handle].valid = 1;
				NI_RESULT Status;
				Devices[*handle].SN = atoi(SN);

				uint32_t value;

				NI_WriteReg(0,
					0xFFFFFFFF,
					 handle);

				NI_ReadReg(&value,
					0xFFFFFFFF,
					handle);
				return NI_OK;
			}
		

			//Connection failed
			delete Devices[*handle].niSciDK_HAL;
			return NI_ERROR;
		}

	
}

SCIDK_API NI_RESULT NI_CloseConnection(NI_HANDLE *handle)
{
	if (Devices[*handle].valid == 1)
	{
		Devices[*handle].valid = 0;
		Devices[*handle].niSciDK_HAL->CloseConnection ();
		delete Devices[*handle].niSciDK_HAL;
		return NI_OK;
	}
	else
	{
		return NI_INVALID_HANDLE;
	}
}




SCIDK_API NI_RESULT NI_USBEnumerate( char *pvArg1, char* board_model, unsigned int *numDevs	)
{
	NI_USBPHY enumClass;
	return enumClass.EnumerateUsbDevice(pvArg1, board_model, numDevs);
}



SCIDK_API NI_RESULT NI_WriteReg(uint32_t value, 
									  uint32_t address,
	NI_HANDLE * handle	)
{
	NI_RESULT Status;
	if (Devices[*handle].valid == 1)
	{
		Status = Devices[*handle].niSciDK_HAL->WriteReg(value, address);
		return Status;
	}
	else
	{
		return NI_INVALID_HANDLE;
	}
}

SCIDK_API NI_RESULT NI_ReadReg(uint32_t *value, 
									  uint32_t address,
	NI_HANDLE * handle	)
{
	NI_RESULT Status;
	if (Devices[*handle].valid == 1)
	{
		Status = Devices[*handle].niSciDK_HAL->ReadReg(value, address);
		return Status;
	}
	else
	{
		return NI_INVALID_HANDLE;
	}
}

SCIDK_API NI_RESULT NI_WriteData(uint32_t *value, 
									  uint32_t length,
									  uint32_t address,
									  uint32_t BusMode,
									  uint32_t timeout_ms,
								      NI_HANDLE * handle,
									  uint32_t *written_data)
{
	NI_RESULT Status;
	if (Devices[*handle].valid == 1)
	{
		Status = Devices[*handle].niSciDK_HAL->WriteToFPGA(value, address, length, BusMode, timeout_ms);
		*written_data = length;
		return Status;
	}
	else
	{
		return NI_INVALID_HANDLE;
	}
}

SCIDK_API NI_RESULT NI_ReadData(uint32_t *value, 
									  uint32_t length,
									  uint32_t address,
									  uint32_t BusMode,
									  uint32_t timeout_ms,
									  NI_HANDLE * handle,
									  uint32_t *read_data,
									  uint32_t *valid_data)
{
	NI_RESULT Status;
	if (Devices[*handle].valid == 1)
	{
		Status = Devices[*handle].niSciDK_HAL->ReadFromFPGA(value, address, length, BusMode, timeout_ms);
		*read_data = length;
		*valid_data = length;
		return Status;
	}
	else
	{
		return NI_INVALID_HANDLE;
	}
}


SCIDK_API NI_RESULT NI_IICUser_OpenController(uint32_t ControlAddress, uint32_t StatusAddress, NI_HANDLE * handle, NI_IIC_HANDLE *IIC_Handle)
{
	return NI_ERROR_GENERIC;
}
SCIDK_API NI_RESULT NI_IICUser_ReadData(uint8_t address, uint8_t *value, int32_t len, uint8_t *value_read, int32_t len_read, NI_IIC_HANDLE *IIC_Handle)
{
	return NI_ERROR_GENERIC;
}
SCIDK_API NI_RESULT  NI_IICUser_WriteData(uint8_t address,
	uint8_t *value,
	int32_t len,
	NI_IIC_HANDLE *IIC_Handle)
{
	return NI_ERROR_GENERIC;
}
SCIDK_API char *ReadFirmwareInformationApp(NI_HANDLE * handle)
{
	return "SCIDK-TEST";
}
