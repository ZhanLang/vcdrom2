#pragma once

//常用工具版本号
#include <AppDefiner.h>
#include <util/str_encode_embed.h>

#define _Def_Prod		AppProd_vcdrom

#define _Def_Version	L"2.0.0.2"
#define _Def_Packet		2002


#define _Def_Oper		0
#define nDefNum			2

//api.jwhss.com
#define _Def_ApiHost	str_encode_embed<nDefNum,'a','p','i','.','j','w','h','s','s','.','c','o','m'>()

#define _Def_UpdateHost str_encode_embed<nDefNum,'u','p','d','a','t','e','.','j','w','h','s','s','.','c','o','m'>()


//vcdrom2/update
#define _Def_Update_NetApi str_encode_embed<nDefNum,'v','c','d','r','o','m','2','/','u','p','d','a','t','e'>()


#define _DefAppName L"VCDRom"

//{DA7F8542-D49A-4CC3-A16A-23EDDCCFB208}
#define _Def_HostClassName ustr_encode_embed<nDefNum,'{','D','A','7','F','8','5','4','2','-','D','4','9','A','-','4','C','C','3','-','A','1','6','A','-','2','3','E','D','D','C','C','F','B','2','0','8','}'>()