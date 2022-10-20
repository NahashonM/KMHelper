
This driver gives processes that consume its ioctl's access to kernel objects.
The process gains unrestricted access to the entire system

**** Use with care ****

To compile for a specfic windows version not supported: 
make sure to check this page:

    https://www.vergiliusproject.com/

========================================================================
    Compilation
========================================================================
- SDK's and Tools
    Microsoft Visual Studio 2019
    Windows SDK 10.0.18362
    Windows Driver Kit 10.0.1832:


========================================================================
    KMHelper Project Overview
========================================================================

This is a summary of what you will find in each of the files that make up your project.

KMHelper.vcxproj
    This is the main project file for projects generated using an Application Wizard.
    It contains information about the version of the product that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

KMHelper.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard.
    It contains information about the association between the files in your project
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Public.h
    Header file to be shared with applications.

Driver.c & Driver.h
    DriverEntry and WDFDRIVER related functionality and callbacks.

Device.c & Device.h
    WDFDEVICE related functionality and callbacks.

Queue.c & Queue.h
    WDFQUEUE related functionality and callbacks.

Trace.h
    Definitions for WPP tracing.

/////////////////////////////////////////////////////////////////////////////


========================================================================
    Installation
========================================================================
Unless you have a signing certificate from microsoft, you will not be able to load the driver until you turn
on test signing
If test signing is turned on:
    To load the driver
        `sc create KMHelper type= kernel binPath= <path where the binary is generated>`
        
    To stop the driver
        `sc stop KMHelper`
        
    To unload the driver
        `sc delete KMHelper`
 
 **** Please note this driver is still in development and can cause a BSOD especially in untested windows versinos
 

