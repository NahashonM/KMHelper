
#include "Public.h"
#include "routines.h"


#include <intrin.h>



NTSTATUS ReadControlRegister(PKMH_REGISTER reg, unsigned long long *value) {

	if (reg == NULL) return STATUS_INVALID_PARAMETER;

	NTSTATUS status = STATUS_SUCCESS;

	switch (reg->address) {
		case 0:
			*value = __readcr0();
			break;
		case 2:
			*value = __readcr2();
			break;
		case 3:
			*value = __readcr3();
			break;
		case 4:
			*value = __readcr4();
			break;
		case 8:
			*value = __readcr8();
			break;

		default:
			status = STATUS_INVALID_ADDRESS;
	}
	
	return status;
}


NTSTATUS WriteControlRegister(PKMH_REGISTER reg) {

	if (reg == NULL) return STATUS_INVALID_PARAMETER;
	NTSTATUS status = STATUS_SUCCESS;

	switch (reg->address) {
	case 0:
		__writecr0(reg->value);
		break;
	case 3:
		__writecr3(reg->value);
		break;
	case 4:
		__writecr4(reg->value);
		break;
	case 8:
		__writecr8(reg->value);
		break;
	default:
		status = STATUS_INVALID_ADDRESS;
	}

	return status;
}

