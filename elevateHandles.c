
#include "Driver.h"
#include "Public.h"
#include "routines.h"


NTSTATUS	ElevateHandles(PKMH_ELEVATE_HANDLE_INPUT input)
{
	NTSTATUS	status = STATUS_SUCCESS;
	PEPROCESS	pEprocess = NULL;
	void* handleTable = NULL;

	DbgPrint("-- mysterious call \n");

	// find process
	status = PsLookupProcessByProcessId(input->ownerPID, &pEprocess);

	if (status != STATUS_SUCCESS)
	{
		DbgPrint("-- Cannot find process e(%x)\n", status);
		return status;
	}


	ObReferenceObject(pEprocess);

	DbgPrint("-- PID %llx eprocess = %llx \n", (LONGLONG)input->ownerPID, (ULONGLONG)pEprocess);


	handleTable = *(void**)((UCHAR*)pEprocess + 0x570);


	DbgPrint("-- Handle Table Address = %llx \n", (ULONGLONG)handleTable);

	LONGLONG i = 0;
	LONGLONG handleCount = (input->count > 0) ? input->count : 0 /* replace with maximum handle count */;

	while (i < handleCount)
	{
		HANDLE		handle;
		ACCESS_MASK	desiredAccess;
		void* handleAddress = NULL;

		if (handleCount > 0)		// user has specified specific handles
		{
			if (input->listType == HANDLE_LIST_VALUES)
			{
				handle = input->u.list.handleList[i];

				desiredAccess = input->u.list.access_mask;
				handleAddress = ExpLookUpHandleTableEntry(handleTable, input->u.list.handleList[i]);
			}
			else
			{
				handle = input->u.pair_list[i].handle;

				desiredAccess = input->u.pair_list[i].access_mask;
				handleAddress = ExpLookUpHandleTableEntry(handleTable, input->u.pair_list[i].handle);
			}

			i++;
		}
		else						// user has not specified handles
		{
			handleAddress = ExpLookUpHandleTableEntry(handleTable, (HANDLE)(i << 2));
			break;
		}

		if (!handleAddress)
		{
			status = STATUS_UNSUCCESSFUL;
			break;
		}

		DbgPrint("-- Handle %llx Address = %llx \n", (ULONGLONG)handle, (ULONGLONG)handleAddress);


		// Elevate the handle		
#		ifdef _AMD64_
			((PULONG64)handleAddress)[1] = (((PULONG64)handleAddress)[1] & 0xFE000000) | (0x1FFFFFF & desiredAccess);
#		else
#		endif


	}

	ObDereferenceObject(pEprocess);

	return status;
}