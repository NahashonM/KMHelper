
#include "Driver.h"

/*++
	A driver's EvtCleanupCallback event callback function 
	removes the driver's references on an object so that the object can be deleted.
--*/

VOID KMHelperEvtDriverContextCleanup(_In_ WDFOBJECT DriverObject)

{
    UNREFERENCED_PARAMETER(DriverObject);

	DbgPrint("Driver Evt ContextCleanup \n");

    //PAGED_CODE();

    //TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");

    //
    // Stop WPP Tracing
    //
    //WPP_CLEANUP(WdfDriverWdmGetDriverObject((WDFDRIVER)DriverObject));
}
