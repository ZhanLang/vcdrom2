#pragma once

//常用工具版本号
#include <AppDefiner.h>
#include <util/str_encode_embed.h>

#define _Def_Prod		AppProd_vcdrom

#define _Def_Version	L"2.0.1.6"
#define _Def_Packet		2016


#define _Def_Oper		0
#define nDefNum			2

//api.jwhss.com
#define _Def_ApiHost	str_encode_embed<nDefNum,'a','p','i','.','j','w','h','s','s','.','c','o','m'>()

#define _Def_UpdateHost str_encode_embed<nDefNum,'u','p','d','a','t','e','.','j','w','h','s','s','.','c','o','m'>()


//vcdrom2/update
#define _Def_Update_NetApi str_encode_embed<nDefNum,'v','c','d','r','o','m','2','/','u','p','d','a','t','e'>()


#define _DefAppName L"VCDRom"


#define _Def_HostClassName ustr_encode_embed<nDefNum,'{','7','1','7','7','9','5','E','E','-','1','7','0','1','-','4','6','6','6','-','9','6','F','F','-','9','D','E','F','A','E','1','1','0','F','7','7','}'>()