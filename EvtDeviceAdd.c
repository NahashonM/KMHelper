
#include "Driver.h"

//Routine Description:
//
//    EvtDeviceAdd is called by the framework in response to AddDevice
//    call from the PnP manager. We create and initialize a device object to
//    represent a new instance of the device.
//
//Arguments:
//
//    Driver - Handle to a framework driver object created in DriverEntry
//
//    DeviceInit - Pointer to a framework-allocated WDFDEVICE_INIT structure.
//
//Return Value:
//
//    NTSTATUS
//
//

NTSTATUS KMHelperEvtDeviceAdd(_In_ WDFDRIVER Driver, _Inout_ PWDFDEVICE_INIT DeviceInit)
{
	
    NTSTATUS status;

	UNREFERENCED_PARAMETER(Driver);
	UNREFERENCED_PARAMETER(DeviceInit);

	DbgPrint("Driver Evt Device Add\n");

    //TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");
	//
    status = KMHelperCreateDevice(DeviceInit);
	//
    //TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Exit");

    return status;
}
