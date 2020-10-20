
#ifndef __SCIDK_API_C_H
#define __SCIDK_API_C_H

#include "NIErrorCode.h"


#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#ifdef RPAPI_EXPORTS
    #include "ftd2xx.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


#ifdef _WINDOWS
    #ifdef SCIDK_API_EXPORTS
        #define SCIDK_API extern "C" __declspec(dllexport) // __declspec(dllexport)
    #else
        #define SCIDK_API __declspec(dllimport)
    #endif
#else
    #ifdef SCIDK_API_EXPORTS
        #define SCIDK_API __attribute__((visibility("default")))
    #else
        #define SCIDK_API
    #endif
#endif


	typedef int NI_HANDLE ;


	typedef struct NI_IIC_HANDLE
	{
		int device_handle;
		uint32_t __IICBASEADDRESS;
		uint32_t __IICBASEADDRESS_STATUS;
	} NI_IIC_HANDLE;

	#define REG_ACCESS  0
	#define STREAMING 1
	

#define MAX_NUMBER_OF_DEVICE (100)



SCIDK_API NI_RESULT SCIDK_ConnectUSB(char *SN, NI_HANDLE *handle);


SCIDK_API NI_RESULT NI_CloseConnection(NI_HANDLE *handle);

SCIDK_API NI_RESULT NI_USBEnumerate(char *pvArg1, char* board_model, unsigned int *numDevs);

SCIDK_API NI_RESULT NI_WriteReg(uint32_t value,
								uint32_t address,
	NI_HANDLE * handle	);

SCIDK_API NI_RESULT NI_ReadReg(uint32_t *value,
	uint32_t address,
	NI_HANDLE * handle	);

SCIDK_API NI_RESULT NI_WriteData(uint32_t *value,
	uint32_t length,
	uint32_t address,
	uint32_t BusMode,
	uint32_t timeout_ms,
	NI_HANDLE * handle,
	uint32_t *written_data);

SCIDK_API NI_RESULT NI_ReadData(uint32_t *value,
	uint32_t length,
	uint32_t address,
	uint32_t BusMode,
	uint32_t timeout_ms,
	NI_HANDLE * handle,
	uint32_t *read_data,
	uint32_t *valid_data );

SCIDK_API NI_RESULT NI_IICUser_OpenController(uint32_t ControlAddress, 
	uint32_t StatusAddress, 
	NI_HANDLE * handle,
	NI_IIC_HANDLE *IIC_Handle);
SCIDK_API NI_RESULT NI_IICUser_ReadData(uint8_t address, 
	uint8_t *value, 
	int32_t len, 
	uint8_t *value_read, 
	int32_t len_read, 
	NI_IIC_HANDLE *IIC_Handle);
SCIDK_API NI_RESULT NI_IICUser_WriteData(uint8_t address, 
	uint8_t *value, 
	int32_t len, 
	NI_IIC_HANDLE *IIC_Handle);
SCIDK_API char *ReadFirmwareInformationApp(NI_HANDLE * handle);
#ifdef __cplusplus
}
#endif

#endif // __SCIDK_API_C_H