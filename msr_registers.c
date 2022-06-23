
#include "Driver.h"

#include "Public.h"
#include "routines.h"




NTSTATUS ReadMSRRegister(PKMH_REGISTER reg, unsigned long long* value) {

	if (reg == NULL) return STATUS_INVALID_PARAMETER;

	//
	// get physical cpu groups => USHORT KeQueryActiveGroupCount();
	// get logical cpu count in group =>  ULONG KeQueryActiveProcessorCountEx( USHORT GroupNumber ); [0 invalid group]
	// get affinity mask of logical cpus in group => KAFFINITY KeQueryGroupAffinity(USHORT GroupNumber); [0 if invalid group number]
	//
	


	//KAFFINITY affinity = 0;
	//KAFFINITY KeSetSystemAffinityThreadEx(KAFFINITY Affinity);
	*value = __readmsr(reg->address);

	return STATUS_SUCCESS;
}


NTSTATUS WriteMSRRegister(PKMH_REGISTER reg) {

	if (reg == NULL) return STATUS_INVALID_PARAMETER;
		

	SHORT groupCount = KeQueryActiveGroupCount() - 1;
	for (; groupCount >= 0; groupCount--) {
		LONG logicalCpuCount = KeQueryActiveProcessorCountEx(groupCount) - 1;

		for (; logicalCpuCount >= 0; logicalCpuCount--) {
			__writemsr(reg->address, reg->value);
		}
	}

	return STATUS_SUCCESS;
}



