#pragma once


#include <ntifs.h>
#include <ntddk.h> /* Include before wdm.h */
#include <wdm.h>
#include <wdmsec.h>
#include <initguid.h>

#ifndef _DRIVER_PROJECT_

#	define _DRIVER_PROJECT_

#endif


#ifdef Debug

#	define DEBUG_PRINT(_msg_)		DbgPrint("-- Done Elevating handles \n");

#else

#	define DEBUG_PRINT(_msg_)

#endif



extern	UNICODE_STRING	DevName;
extern	UNICODE_STRING	DosDevName;
extern	PDEVICE_OBJECT	device;


EXTERN_C_START


DRIVER_INITIALIZE	DriverEntry;
DRIVER_UNLOAD		DriverUnload;

DRIVER_DISPATCH		CreateDispatch;
DRIVER_DISPATCH		CloseDispatch;
DRIVER_DISPATCH		DeviceControlDispatch;


EXTERN_C_END






//#ifdef ALLOC_PRAGMA
////#pragma alloc_text (PAGE, KMHelperQueueInitialize)
//#endif


