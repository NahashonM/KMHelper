#pragma once

/*++
	Defines Offsets for required fields in Opaque structs

--*/

#include <ntdef.h>

typedef struct _OFFSETS_
{
	ULONG	EPROCESS_HandleTablePtr;
	ULONG	EPROCESS_DirectoryTableBase;

	ULONG	HANDLETABLE_TableCode;
}OFFSETS, *POFFSETS;