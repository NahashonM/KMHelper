
#include "driver.h"
#include "Public.h"


UNICODE_STRING	DevName;
UNICODE_STRING	DosDevName;
PDEVICE_OBJECT	device		= NULL;


NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT  DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);
	
    NTSTATUS status	= STATUS_SUCCESS;


	DEBUG_PRINT("KMHelper Entry \n");

	DriverObject->DriverUnload = DriverUnload;				// Register Driver Unload Routine

	
	DEBUG_PRINT("-- Creating KMHelper Device \n");

	RtlInitUnicodeString(&DevName, DEVICE_NAME);
	RtlInitUnicodeString(&DosDevName, DOS_NAME);

	DEBUG_PRINT("Creating Device \\Device\\KMHelper\n");
	status = IoCreateDevice(DriverObject, (ULONG)0, &DevName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &device);

	if (!NT_SUCCESS(status))
	{
		DEBUG_PRINT("Create Device Failed\n");
		return status;
	}


	DEBUG_PRINT("Creating Dos Device symbolic link \\DosDevices\\KMHelper\n");
	if (!NT_SUCCESS(status = IoCreateSymbolicLink(&DosDevName, &DevName)))
	{
		DEBUG_PRINT("Create Dos Device symbolic link Failed\n");
		IoDeleteDevice(device);
		return status;
	}


	DEBUG_PRINT("Setting up device major functions\n");
	DriverObject->MajorFunction[IRP_MJ_CREATE]			= CreateDispatch;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]			= CloseDispatch;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]	= DeviceControlDispatch;

	device->Flags |= DO_DIRECT_IO;
	device->Flags &= ~DO_DEVICE_INITIALIZING;
	//PsSetCreateProcessNotifyRoutine();
	//PsSetCreateThreadNotifyRoutineEx();
	//PsSetLoadImageNotifyRoutine()


	DEBUG_PRINT("Driver Init Success\n");
	
	return status;

}

