#include <stdio.h>
#include "../libSCIDK/include/SCIDK_API_C.h"

#define SCI_REG_Oscilloscope_0_FIFOADDRESS 0x0
#define SCI_REG_Oscilloscope_0_READ_STATUS 0x10000
#define SCI_REG_Oscilloscope_0_READ_POSITION 0x10001
#define SCI_REG_Oscilloscope_0_CONFIG_TRIGGER_MODE 0x10002
#define SCI_REG_Oscilloscope_0_CONFIG_PRETRIGGER 0x10003
#define SCI_REG_Oscilloscope_0_CONFIG_TRIGGER_LEVEL 0x10004
#define SCI_REG_Oscilloscope_0_CONFIG_ARM 0x10005
#define SCI_REG_Oscilloscope_0_CONFIG_DECIMATOR 0x10006


int main(int argc, char **argv)
{
    uint32_t reg_value;
	NI_HANDLE *handle = NULL;
	char devices[255];
	uint32_t data[4096];
	uint32_t rd;
	uint32_t vd;
	uint32_t dd;
	unsigned int found_devs = 0;

	handle = malloc(sizeof( NI_HANDLE));
	NI_USBEnumerate(devices, "SCIDK", &found_devs);
    printf("Found %d devices: %s\n", found_devs, devices);
	if (found_devs > 0)
	{
        
		if (SCIDK_ConnectUSB("0001", handle) == NI_OK)
		{
			NI_ReadReg(&reg_value, 0xFFFFFFFF, handle);
			printf("Reg value: %X\n", reg_value);
			NI_WriteReg(0x0FF, 0, handle);
			NI_ReadReg(&reg_value, 0, handle);
			printf("Reg 0 value: %X\n", reg_value);
			NI_WriteReg(0xFF, 1, handle);
			NI_ReadReg(&reg_value, 1, handle);
			printf("Reg 1 value: %X\n", reg_value);
			OSCILLOSCOPE_Oscilloscope_0_SET_PARAMETERS(1, 100, 1, 0, 0, 0, 0, 0, 0, 0, 340, handle);
			OSCILLOSCOPE_Oscilloscope_0_START(handle);
            while (1)
			{
				
				NI_ReadReg(&dd, 65536, handle);
				if (dd != 0)
				{
					NI_ReadData(data, 1024, SCI_REG_Oscilloscope_0_FIFOADDRESS, 0, 100, handle, &rd, &vd);
					printf("Read Segment: %d  -- %d,%d,%d,%d\n", vd, data[0], data[1], data[2], data[3]);
					OSCILLOSCOPE_Oscilloscope_0_START(handle);
				}
				else
				{
					printf("Notrigger\n");
				}
				

				
			}



        }
    }
	return 0;
}





int OSCILLOSCOPE_Oscilloscope_0_START(NI_HANDLE *handle)

{
	int r1 = NI_WriteReg(0, SCI_REG_Oscilloscope_0_CONFIG_ARM, handle);
	int r2 = NI_WriteReg(1, SCI_REG_Oscilloscope_0_CONFIG_ARM, handle);
	if ((r1 == 0) && (r2 == 0))
		return 0;
	else
		return -1;

}

int OSCILLOSCOPE_Oscilloscope_0_SET_PARAMETERS(int32_t decimator, int32_t pre, int32_t software_trigger, int32_t analog_trigger, int32_t digital0_trigger, int32_t digital1_trigger, int32_t digital2_trigger, int32_t digital3_trigger, int32_t trigger_channel, int32_t trigger_edge, int32_t trigger_level, NI_HANDLE *handle)
{
	int32_t triggermode = 0;
	int r_decimator = NI_WriteReg(decimator, SCI_REG_Oscilloscope_0_CONFIG_DECIMATOR, handle);
	int r_pre = NI_WriteReg(pre, SCI_REG_Oscilloscope_0_CONFIG_PRETRIGGER, handle);
	int r_triglevel = NI_WriteReg(trigger_level, SCI_REG_Oscilloscope_0_CONFIG_TRIGGER_LEVEL, handle);
	triggermode = (trigger_channel << 8) + (software_trigger << 7) + (trigger_edge << 3) + (software_trigger << 1) + analog_trigger + (digital0_trigger << 2) + (digital1_trigger << 2) + digital1_trigger + (digital2_trigger << 2) + (digital2_trigger << 1) + (digital3_trigger << 2) + (digital3_trigger << 1) + digital3_trigger;
	int r_triggermode = NI_WriteReg(triggermode, SCI_REG_Oscilloscope_0_CONFIG_TRIGGER_MODE, handle);
	if (r_decimator == 0 & r_pre == 0 & r_triglevel == 0 & r_triggermode == 0)
		return 0;
	else
		return -1;

}


