#include "Driver.h"
#include "Public.h"


//
// Leaks process handles created in kernel mode to user mode
//
NTSTATUS OpenProcess(PKMH_OPEN_PROCESS_INPUT input, PHANDLE out)
{
	NTSTATUS			status		= STATUS_SUCCESS;
	CLIENT_ID			clientID;
	OBJECT_ATTRIBUTES	attribs;

	clientID.UniqueProcess	= (HANDLE)input->processId;
	clientID.UniqueThread	= (HANDLE)NULL ;

	InitializeObjectAttributes(&attribs, NULL, (input->inHeritable)? OBJ_INHERIT : 0 , NULL, NULL);

	status = ZwOpenProcess(out, input->desiredAccess, &attribs, &clientID);

	return status;
}

