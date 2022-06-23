#include "driver.h"


void DriverUnload(PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);


	if (device)
	{
		DbgPrint("Deleting Device Dos name\n");
		IoDeleteSymbolicLink(&DosDevName);

		DbgPrint("Deleting device\n");
		IoDeleteDevice(device);
	}

	DbgPrint("Driver Unloaded\n");
}