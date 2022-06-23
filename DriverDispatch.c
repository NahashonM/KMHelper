
#include "Driver.h"
#include "Public.h"
#include "routines.h"


#define MDL_BIGGER_THAN(_mdl_, _sz_)	(MmGetMdlByteCount(_mdl_) > _sz_ )
#define MDL_LESS_THAN(_mdl_, _sz_)		(MmGetMdlByteCount(_mdl_) < _sz_ )


NTSTATUS CreateDispatch(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	DEBUG_PRINT("-- Dispatch Create\n");

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IofCompleteRequest(Irp, IO_NO_INCREMENT);


	return STATUS_SUCCESS;
}


NTSTATUS CloseDispatch(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	
	DEBUG_PRINT("-- Dispatch Close\n");

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IofCompleteRequest(Irp, IO_NO_INCREMENT);


	return STATUS_SUCCESS;
}


NTSTATUS DeviceControlDispatch(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	NTSTATUS			status			= STATUS_SUCCESS;
	PIO_STACK_LOCATION	stackLocation	= IoGetCurrentIrpStackLocation(Irp);


	if (stackLocation->MajorFunction == IRP_MJ_DEVICE_CONTROL)
	{

		switch ((ULONG)stackLocation->Parameters.DeviceIoControl.IoControlCode)
		{
			case IOCTL_TEST_CODE1:
				{
					status = STATUS_SUCCESS;
				} break;

			case KMHELPER_ELEVATE_HANDLE:					// Elevate handle ioctl
				{
					DEBUG_PRINT("-- Elevating handles \n");

					status = ElevateHandles( (PKMH_ELEVATE_HANDLE_INPUT)Irp->AssociatedIrp.SystemBuffer );

				} break;

			case KMHELPER_OPEN_PROCESS:						// Open Process IOCTL
				{
					DEBUG_PRINT("-- Open Process IOCTL\n");

					PHANDLE	outBuffer	= (PHANDLE)MmGetSystemAddressForMdlSafe(Irp->MdlAddress, NormalPagePriority | MdlMappingNoExecute);
					
					if (outBuffer != NULL)	
						status = OpenProcess((PKMH_OPEN_PROCESS_INPUT)Irp->AssociatedIrp.SystemBuffer, outBuffer);

				} break; 


			case KMHELPER_GET_EPROCESS:						// Get Process Eprocess IOCTL
			{
				DEBUG_PRINT("-- Get Process Eprocess IOCTL\n");

				void* outBuffer = MmGetSystemAddressForMdlSafe(Irp->MdlAddress, NormalPagePriority | MdlMappingNoExecute);

				if (outBuffer != NULL) {
					if (MDL_LESS_THAN(Irp->MdlAddress, sizeof(unsigned long long)))
						status = STATUS_BUFFER_TOO_SMALL;
					else
						status = PsLookupProcessByProcessId
						( 
							((PKMH_GET_EPROCESS_INPUT)Irp->AssociatedIrp.SystemBuffer)->pid, 
							(PEPROCESS*)outBuffer
						);
				}
			} break;

//
//--------------------------- Processor Registers ( 0x80 - 0x8F ) -----------------------------------
//

			case KMHELPER_READ_REG_CR:						// Read Cr Registers
			{
				DEBUG_PRINT("-- Read CR_x Register \n");

				void* outBuffer = MmGetSystemAddressForMdlSafe(Irp->MdlAddress, NormalPagePriority | MdlMappingNoExecute);

				if (outBuffer != NULL) {
					if (MDL_LESS_THAN(Irp->MdlAddress, sizeof(unsigned long long)))
						status = STATUS_BUFFER_TOO_SMALL;
					else 
						status = ReadControlRegister(	(PKMH_REGISTER)Irp->AssociatedIrp.SystemBuffer,
														(unsigned long long*) outBuffer					);
				}

			} break;

			case KMHELPER_READ_REG_MSR:						// Read Msr Register
			{
					DEBUG_PRINT("-- Read Msr Register \n");

					void* outBuffer = MmGetSystemAddressForMdlSafe(Irp->MdlAddress, NormalPagePriority | MdlMappingNoExecute);

					if (outBuffer != NULL) {
						if (MDL_LESS_THAN(Irp->MdlAddress, sizeof(unsigned long long)))
							status = STATUS_BUFFER_TOO_SMALL;
						else
							status = ReadMSRRegister(	(PKMH_REGISTER)Irp->AssociatedIrp.SystemBuffer,
														(unsigned long long*) outBuffer);
					}
				} break;
			
			case KMHELPER_WRITE_REG_CR:						// Write Cr Registers
			{
				DEBUG_PRINT("-- Write CR_x Register \n");
				status = WriteControlRegister(  (PKMH_REGISTER)Irp->AssociatedIrp.SystemBuffer  );

			} break;

			case KMHELPER_WRITE_REG_MSR:					// Write Msr Register
			{
				DEBUG_PRINT("-- Write Msr Register \n");
				status = WriteMSRRegister(  (PKMH_REGISTER)Irp->AssociatedIrp.SystemBuffer );

			} break;


//
//--------------------------- Default -----------------------------------
//

			default:
				DEBUG_PRINT("-- Dispatch invalid control code\n");

				status = STATUS_INVALID_PARAMETER;
				break;
		}

	}

	Irp->IoStatus.Status		= status;
	Irp->IoStatus.Information	= 0;
	
	IofCompleteRequest(Irp, IO_NO_INCREMENT);

	return status;
}