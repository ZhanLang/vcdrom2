#pragma once
#define IOCTL_PLUGIN_DEVICE		CTL_CODE(FILE_DEVICE_BUS_EXTENDER,0x001,METHOD_BUFFERED,FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_PLUGOUT_DEVICE	CTL_CODE(FILE_DEVICE_BUS_EXTENDER,0x002,METHOD_BUFFERED,FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_EJECT_DEVICE		CTL_CODE(FILE_DEVICE_BUS_EXTENDER,0x003,METHOD_BUFFERED,FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_IS_DEVICE_PRESENT	CTL_CODE(FILE_DEVICE_BUS_EXTENDER,0x004,METHOD_BUFFERED,FILE_READ_DATA|FILE_WRITE_DATA)

#define IOCTL_LIST_DEVICES					CTL_CODE(FILE_DEVICE_BUS_EXTENDER,0x011,METHOD_BUFFERED,FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_PLUGIN_DEVICE_RETURN_WAITHANDLE		CTL_CODE(FILE_DEVICE_BUS_EXTENDER,0x012,METHOD_BUFFERED,FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_QUERY_DRIVER_VERSION		CTL_CODE(FILE_DEVICE_BUS_EXTENDER,0x013,METHOD_BUFFERED,FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_SOFT_PLUGOUT_DEVICE	CTL_CODE(FILE_DEVICE_BUS_EXTENDER,0x019,METHOD_BUFFERED,FILE_READ_DATA|FILE_WRITE_DATA)

//#define WINCDEMU_DEBUG_LOGGING_SUPPORT
#ifdef WINCDEMU_DEBUG_LOGGING_SUPPORT
#define IOCTL_SET_DEBUG_LOG_DIR		CTL_CODE(FILE_DEVICE_BUS_EXTENDER,0x021,METHOD_BUFFERED,FILE_READ_DATA|FILE_WRITE_DATA)
#endif

#define IOCTL_VDEV_IS_AUTORUN_DISABLED		CTL_CODE(FILE_DEVICE_VIRTUAL_DISK,0x014,METHOD_BUFFERED,FILE_READ_DATA)
#define IOCTL_VDEV_GET_IMAGE_PATH		CTL_CODE(FILE_DEVICE_VIRTUAL_DISK,0x015,METHOD_BUFFERED,FILE_READ_DATA)
#define IOCTL_VDEV_GET_MMC_PROFILE		CTL_CODE(FILE_DEVICE_VIRTUAL_DISK,0x016,METHOD_BUFFERED,FILE_READ_DATA)
#define IOCTL_VDEV_SET_MMC_PROFILE		CTL_CODE(FILE_DEVICE_VIRTUAL_DISK,0x018,METHOD_BUFFERED,FILE_READ_DATA)
#define IOCTL_VDEV_MOUNT_IMAGE			CTL_CODE(FILE_DEVICE_VIRTUAL_DISK,0x019,METHOD_BUFFERED,FILE_READ_DATA)	//Data contains NULL-terminated path or empty string to unmount the image

#include "../wcdversion.h"
#define WINCDEMU_DRIVER_VERSION_CURRENT	WINCDEMU_VER_INT


struct VirtualCDRecord
{
	unsigned DriveLetter;
	unsigned ImageNameOffset;
	
	unsigned short HandleCount, RefCount, DeviceRefCount, Reserved;
};

struct VirtualCDRecordHeader
{
	enum {CurrentVersion = 2};
	unsigned Version;
	unsigned TotalSize;
	unsigned RecordCount;
#pragma warning( push )
#pragma warning( disable : 4200 )
	VirtualCDRecord Records[0];
#pragma warning( pop )
};

#define MAX_STR_SIZE 512
struct VirtualCDMountParams
{
	wchar_t wszFilePath[MAX_STR_SIZE];
	unsigned StructureVersion;
	bool DisableAutorun;
	char SuggestedDriveLetter;
	bool KeepAfterRestart;
	unsigned short MMCProfile;

	enum {CurrentVersion = 4};
};

struct GUIDAndVersion
{
	GUID Guid;
	unsigned Version;
};

// {6e1ec3ac-d9cc-423e-8862-bade124324c8}
#ifdef SKIP_WINCDEMU_GUID_DEFINITION
extern GUID GUID_BazisVirtualCDBus;
extern GUID GUID_WinCDEmuDrive;
#else


//{0982746E-D162-4C33-8D43-2D3C3C64227B}
GUID GUID_BazisVirtualCDBus = { 0x982746e, 0xd162, 0x4c33, { 0x8d, 0x43, 0x2d, 0x3c, 0x3c, 0x64, 0x22, 0x7b }};
// {B4B4772B-4A26-4FE4-836D-6AE6EC104089}
GUID GUID_WinCDEmuDrive = { 0xb4b4772b, 0x4a26, 0x4fe4, { 0x83, 0x6d, 0x6a, 0xe6, 0xec, 0x10, 0x40, 0x89 } };

/*
GUID GUID_BazisVirtualCDBus = {0x6E1EC3AC, 0xd9cc, 0x423e, {0x88, 0x62, 0xba, 0xde, 0x12, 0x43, 0x24, 0xc8 } };
GUID GUID_WinCDEmuDrive = { 0x98f41ee4, 0x819b, 0x46fb, { 0xb1, 0x40, 0xa7, 0xf6, 0x7c, 0x5b, 0xc0, 0x91 } };
*/
#endif