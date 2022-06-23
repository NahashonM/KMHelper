
#include "Driver.h"
#include "Public.h"
#include "routines.h"



void* ExpLookUpHandleTableEntry(void* pHandleTable, HANDLE handle)
{
	ULONGLONG	handleRelativeOffset;
	ULONGLONG	tablePtr;
	ULONG		tableType;

	handleRelativeOffset = (ULONGLONG)handle & 0xFFFFFFFFFFFFFFFCui64;

	// Check to see if bigger than NextHandleNeedingPool
	if (handleRelativeOffset >= *(PULONG)pHandleTable)  return NULL;

	tablePtr = (ULONGLONG) * (void**)((PULONGLONG)pHandleTable + 1);
	tableType = (ULONG) * (PULONG)((PULONGLONG)pHandleTable + 1) & 3;

	// Secondary table
	if ((ULONG)tableType == 1)
#		ifdef _AMD64_
		return *(void***)(tablePtr + sizeof(void*) * (handleRelativeOffset >> 10) - 1) + 4 * (handleRelativeOffset & 0x3FF);
#		else
		return *(void***)(tablePtr + sizeof(void*) * (handleRelativeOffset >> 11) - 1) + 4 * (handleRelativeOffset & 0x3FF);
#		endif

	// Tertially handle table
	if ((ULONG)tableType)
#		ifdef _AMD64_
		return *(void***)(*(void***)(tablePtr + 8 * (handleRelativeOffset >> 19) - 2) + 8 * ((handleRelativeOffset >> 10) & 0x1FF)) + 4 * (handleRelativeOffset & 0x3FF);
#		else
		return *(void***)(*(void***)(tablePtr + 4 * (handleRelativeOffset >> 21) - 2) + 4 * ((handleRelativeOffset >> 11) & 0x1FF)) + 4 * (handleRelativeOffset & 0x3FF);
#		endif


	// Primary table	
#	ifdef _AMD64_
	return (void*)(tablePtr + 4 * handleRelativeOffset);
#	else
	return (void*)(tablePtr + 2 * handleRelativeOffset);
#	endif

}