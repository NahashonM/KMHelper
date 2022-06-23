
#include "Driver.h"



NTSTATUS InitVersionSpecificData()
{
	NTSTATUS status;
	RTL_OSVERSIONINFOW versionInfo;

	status = RtlGetVersion(&versionInfo);

	if (!NT_SUCCESS(status))
	{
		if (versionInfo.dwMajorVersion == 10)
		{
			switch (versionInfo.dwBuildNumber)
			{
				case 19042:
				case 19041:
				{

				}
				break;

				case 18362:
				{

				}
				break;

				default:
					status = STATUS_UNSUCCESSFUL;
					break;

			}
		}
	}

	return status;
}