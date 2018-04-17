#pragma once
class CVCDRomCtrl
{
public:
	CVCDRomCtrl(void);
	~CVCDRomCtrl(void);

	HRESULT DisMount(LPCWSTR lpszFile);
	HRESULT Mount(LPCWSTR lpDiskPath, CHAR cLatter, BOOL bMountRestart/* = TRUE*/);
	BOOL	IsMount(LPCWSTR lpDiskPath);
	CHAR GetMountLatter(LPCWSTR lpszFile);
	HRESULT DisMountAll();
	BOOL  DeviceValid();
};

