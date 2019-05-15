#pragma once

#include <Tlhelp32.h>

#include <string>
#include <map>
#include <vector>
#include <json/json.h>
#include <arith/AES.h>
namespace msdk{;
namespace msapi{;
//枚举安全软件
enum //序号和软件扫描引擎中的一致
{
	Antivirus_Rav	  = 1,	//瑞星杀毒
	Antivirus_King	  = 8,	//金山杀毒

	Antivirus_360Safe = 1242,	//360安全卫士
	Antivirus_360Sd	  = 1243,	//360杀毒
	Antivirus_Biadu	  = 1244,	//百度卫士
	Antivirus_BaiduSd = 1245,	//百度杀毒
	Antivirus_QQMgr	  = 1246,	//腾讯电脑管家

	Antivirus_HipsDaemon = 1247,//火绒
	Antivirus_2345Safe = 1248	//2345安全卫士
};


//const char* avs = "[{ \"code\":1,\"name\":\"ravmond.exe\"},{\"code\":8,\"name\":\"kxescore.exe\"},{\"code\":1242,\"name\":\"ZhuDongFangYU.exe\"},{\"code\":1243,\"name\":\"360sdupd.exe\"},{\"code\":1244,\"name\":\"BaiduAnSvc.exe\"},{\"code\":1245,\"name\":\"BaiduSdSvc.exe\"},{\"code\":1246,\"name\":\"QQPCRTP.exe\"},{\"code\":1247,\"name\":\"HipsDaemon.exe\"},{\"code\":1248,\"name\":\"2345SafeSvc.exe\"}]";
const char* davs = "sSGdvIwkVSaCWMP6F0y7J87+ubC1bhL3Z3hlmejSyntXkzVHi4yNYJhioqbCqhuDWPZk9H9xBKTMdzMqkqy+pLr3+HmVBNrlDy/1BxZvpiZVkysA9qa4xosWCuQCa2zWtx8A8jplgthTOWq59Na4qQpJlUMogvQX2wsbB6IpI6N7AaQsNs3vGzgqFDhxHSVbqmnXmTf8cNuSg5JY/p4dOCNpAt1clCq62eSZj126cjyn+LFXtO6q3a4h582zk7olkjvkg4K2t73poWGskks9QN07MS9VKwlm3713+EikNpO5RWSZI34OsULxbOCl3+Z3rVYFoaa/tjRi3NYutgewqtpcSQ0ysYTzbINELWlbaLP7aUYzDZn/qwrRzYIBEPw/dYBZHo4g+f6yQWCZBM3DCpKKZdlJNFmMsdiO53i9B9d15M3hEk8tW/L+kGj6xOBk";
class CEnumAntivirus
{
public:
	std::map<int, std::wstring> m_ProcessMap;
	CEnumAntivirus()
	{
		//std::string sEnc = AES::EncryptionAES("MyCreateFileTemp","MyCreateFileExec", avs);
		std::string sDec = AES::DecryptionAES("MyCreateFileTemp","MyCreateFileExec", davs);

		Json::Value Root;
		if ( Json::Reader().parse(sDec, Root))
		{
			for ( int i = 0; i < Root.size() ; i++)
			{
				Json::Value v = Root[i];
				INT nCode = v["code"].asInt();
				std::wstring sName = v["name"].asWString();
				m_ProcessMap[nCode] = sName;
			}
		}
	}

	BOOL Enum( std::vector<int>& antivirus)
	{
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (INVALID_HANDLE_VALUE == hSnapshot) 
			return FALSE;

		PROCESSENTRY32W pe = { sizeof(PROCESSENTRY32W) };
		for (BOOL fOk = Process32FirstW(hSnapshot, &pe); fOk; fOk = Process32NextW(hSnapshot, &pe)) 
		{
			std::map<int, std::wstring>::iterator it = m_ProcessMap.begin();
			for (  ; it != m_ProcessMap.end() ; it++ )
			{
				if ( 0 == wcsicmp(pe.szExeFile, it->second.c_str()) )
					antivirus.push_back(it->first);
			}
		}
		CloseHandle(hSnapshot);

		return TRUE;
	}

	//以;号隔开
	std::basic_string<TCHAR> Enum( )
	{
		std::basic_string<TCHAR> sRet;
		std::vector<int> antivirus;
		if ( Enum( antivirus ) )
		{
			std::vector<int>::iterator it = antivirus.begin();
			for ( ; it != antivirus.end() ; it++)
			{
				TCHAR sFormat[ MAX_PATH ] = { 0 };
				_stprintf(sFormat, _T("%d;"), *it);
				sRet.append( sFormat );
			}
		}

		return sRet;
	}

	BOOL Has( INT antivirus) 
	{
		if ( m_ProcessMap.find( antivirus ) == m_ProcessMap.end() )
			return FALSE;

		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (INVALID_HANDLE_VALUE == hSnapshot) 
			return FALSE;

		BOOL bFind = FALSE;

		std::wstring s = m_ProcessMap.find(antivirus)->second;
		PROCESSENTRY32W pe = { sizeof(PROCESSENTRY32W) };
		for (BOOL fOk = Process32FirstW(hSnapshot, &pe); fOk; fOk = Process32NextW(hSnapshot, &pe)) 
		{
			if ( 0 == wcsicmp(pe.szExeFile, s.c_str()) )
			{
				bFind = TRUE;
				break;
			}
		}
		CloseHandle(hSnapshot);

		return bFind;
	}
};};};