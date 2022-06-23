/*
	Worker Routines that fufill dispatched IO Control Codes

	#define no_init_all deprecated [ntddk.h 589. 1096 ]
*/

#pragma once

#include "Driver.h"
#include "Public.h"



extern	NTSTATUS	ElevateHandles(PKMH_ELEVATE_HANDLE_INPUT input);

extern	void*		ExpLookUpHandleTableEntry(void* pHandleTable, HANDLE handle);

extern	NTSTATUS	OpenProcess(PKMH_OPEN_PROCESS_INPUT input, PHANDLE out);


extern	NTSTATUS	ReadControlRegister(PKMH_REGISTER reg, unsigned long long* value);
extern	NTSTATUS	ReadMSRRegister(PKMH_REGISTER reg, unsigned long long* value);
extern	NTSTATUS	WriteControlRegister(PKMH_REGISTER reg);
extern	NTSTATUS	WriteMSRRegister(PKMH_REGISTER reg);