/*

	Device IO COntrol Codes and Struct definitions for passing data to and from the kernel

*/

#pragma once

#ifdef _DRIVER_
#include <ntdef.h>
typedef ULONG ACCESS_MASK;
#endif

#ifdef _DRIVER_PROJECT_

#	define		DEVICE_NAME		L"\\Device\\KMHelper"
#	define		DOS_NAME		L"\\DosDevices\\KMHelper"

#else

#	define		DEVICE_NAME		L"\\\\.\\KMHelper"

#endif 


#define		CTRL_CODE(_function_)	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800 | _function_, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define		IOCTL_TEST_CODE1					CTRL_CODE(0x1)

#define		KMHELPER_ELEVATE_HANDLE				CTRL_CODE(0x2)
#define		KMHELPER_WATCH_THREADS				CTRL_CODE(0x4)			// monitor thread creation
#define		KMHELPER_WATCH_PROCESS				CTRL_CODE(0x5)			// monitor process handle creation


#define		KMHELPER_READ_VIRTUAL_MEMORY		CTRL_CODE(0x40)
#define		KMHELPER_WRTIE_VIRTUAL_MEMORY		CTRL_CODE(0x41)
#define		KMHELPER_MAP_VIRTUAL_MEMORY			CTRL_CODE(0x42)

#define		KMHELPER_READ_KERNEL_MEMORY			CTRL_CODE(0x50)
#define		KMHELPER_WRTIE_KERNEL_MEMORY		CTRL_CODE(0x51)
#define		KMHELPER_MAP_KERNEL_MEMORY			CTRL_CODE(0x52)

#define		KMHELPER_READ_PHYSICAL_MEMORY		CTRL_CODE(0x60)			// map process VM to target
#define		KMHELPER_WRITE_PHYSICAL_MEMORY		CTRL_CODE(0x61)			// map process VM to target
#define		KMHELPER_MAP_PHYSICAL_MEMORY		CTRL_CODE(0x62)			// map Physical memory to target

#define		KMHELPER_OPEN_PROCESS				CTRL_CODE(0x70)			// Get handle to process from kernel mode
#define		KMHELPER_GET_EPROCESS				CTRL_CODE(0x71)			// Get eprocess structure of a process
#define		KMHELPER_MAP_PROCESS_MEMORY			CTRL_CODE(0x72)


//--------------------------- Processor Registers ( 0x80 - 0x8F ) -----------------------------------
#define		KMHELPER_READ_REG_CR				CTRL_CODE(0x80)
#define		KMHELPER_READ_REG_MSR				CTRL_CODE(0x81)

#define		KMHELPER_WRITE_REG_CR				CTRL_CODE(0x85)
#define		KMHELPER_WRITE_REG_MSR				CTRL_CODE(0x86)


#define HANDLE_LIST_VALUES						0
#define HANDLE_LIST_ACCESS_VALUE_PAIRS			1



typedef struct _KMH_ELEVATE_HANDLE_INPUT_
{
	HANDLE	ownerPID;						// Process owning the handle(s)
	int		count;							// number of handles in handleList	: { if == 0; { all handles of handleType are elevated }
	ULONG32	handleType;						// Type of handles to be considered	: { ignored if count >= 1 }
	ULONG32	listType;						// The type of handle list { 0 => access_mask : [handles], 1 => [access_mask : handle] }
	union
	{
		struct
		{
			ACCESS_MASK	access_mask;
			HANDLE		handleList[1];
		}list;

		struct
		{
			ACCESS_MASK		access_mask;
			HANDLE			handle;
		}pair_list[1];
	}u;
}KMH_ELEVATE_HANDLE_INPUT, * PKMH_ELEVATE_HANDLE_INPUT;



typedef struct _KMH_OPEN_PROCESS_INPUT_
{
	ULONG	processId;
	BOOLEAN		inHeritable;
	ACCESS_MASK	desiredAccess;
}KMH_OPEN_PROCESS_INPUT, * PKMH_OPEN_PROCESS_INPUT;



typedef struct _KMH_GET_EPROCESS_INPUT_
{
	HANDLE	pid;
}KMH_GET_EPROCESS_INPUT, *PKMH_GET_EPROCESS_INPUT;




typedef struct _KMH_REGISTER_ {
	ULONG		address;	// address of msr register or control register prefix (0,2,3,4,8)
	ULONGLONG	value;		// value to write
	int			core;		// msr registers only [-1=all, _0...n-1_ logical cpus]
}KMH_REGISTER, * PKMH_REGISTER;


typedef struct _MSR_REGISTER_ {
	KAFFINITY	group;		// CPU group(g) from n----n-1
	KAFFINITY	core;		// Cpu core in Group g from n---n-1
	ULONG		address;	// address of msr register or control register prefix (0,2,3,4,8)
	ULONGLONG	value;		// value to write
}MSR_REGISTER, * PMSR_REGISTER;
