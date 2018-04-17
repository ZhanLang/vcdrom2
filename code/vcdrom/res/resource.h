//stamp:0e9ead89c6424113
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#pragma once
#include <res.mgr/snamedvalue.h>
#define ROBJ_IN_CPP \
namespace SOUI \
{\
    const _R R;\
    const _UIRES UIRES;\
}
namespace SOUI
{
	class _UIRES{
		public:
		class _UIDEF{
			public:
			_UIDEF(){
				XML_INIT = _T("UIDEF:XML_INIT");
			}
			const TCHAR * XML_INIT;
		}UIDEF;
		class _LAYOUT{
			public:
			_LAYOUT(){
				XML_MAINWND = _T("LAYOUT:XML_MAINWND");
				XML_DLG_BUSY = _T("LAYOUT:XML_DLG_BUSY");
				XML_DLG_MOUNT = _T("LAYOUT:XML_DLG_MOUNT");
				XML_DLG_DRIVE = _T("LAYOUT:XML_DLG_DRIVE");
			}
			const TCHAR * XML_MAINWND;
			const TCHAR * XML_DLG_BUSY;
			const TCHAR * XML_DLG_MOUNT;
			const TCHAR * XML_DLG_DRIVE;
		}LAYOUT;
		class _values{
			public:
			_values(){
				string = _T("values:string");
				color = _T("values:color");
				skin = _T("values:skin");
			}
			const TCHAR * string;
			const TCHAR * color;
			const TCHAR * skin;
		}values;
		class _IMG{
			public:
			_IMG(){
				traymenu_icons = _T("IMG:traymenu_icons");
				image_bk_png = _T("IMG:image_bk_png");
				image_popwndframe_png = _T("IMG:image_popwndframe_png");
				image_sys_close_png = _T("IMG:image_sys_close_png");
				image_sys_menu_png = _T("IMG:image_sys_menu_png");
				image_sys_min_png = _T("IMG:image_sys_min_png");
				image_vscrollbar_png = _T("IMG:image_vscrollbar_png");
				image_hscrollbar_png = _T("IMG:image_hscrollbar_png");
				image_checking_png = _T("IMG:image_checking_png");
				image_edit_png = _T("IMG:image_edit_png");
				image_edit_dropdown_png = _T("IMG:image_edit_dropdown_png");
				image_sys_close_min_png = _T("IMG:image_sys_close_min_png");
				image_checkbox_png = _T("IMG:image_checkbox_png");
				image_default_scrollbar_png = _T("IMG:image_default_scrollbar_png");
			}
			const TCHAR * traymenu_icons;
			const TCHAR * image_bk_png;
			const TCHAR * image_popwndframe_png;
			const TCHAR * image_sys_close_png;
			const TCHAR * image_sys_menu_png;
			const TCHAR * image_sys_min_png;
			const TCHAR * image_vscrollbar_png;
			const TCHAR * image_hscrollbar_png;
			const TCHAR * image_checking_png;
			const TCHAR * image_edit_png;
			const TCHAR * image_edit_dropdown_png;
			const TCHAR * image_sys_close_min_png;
			const TCHAR * image_checkbox_png;
			const TCHAR * image_default_scrollbar_png;
		}IMG;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
			}
			const TCHAR * ICON_LOGO;
		}ICON;
		class _translator{
			public:
			_translator(){
				lang_cn = _T("translator:lang_cn");
				lang_jp = _T("translator:lang_jp");
			}
			const TCHAR * lang_cn;
			const TCHAR * lang_jp;
		}translator;
		class _SMENU{
			public:
			_SMENU(){
				menu_tray = _T("SMENU:menu_tray");
			}
			const TCHAR * menu_tray;
		}SMENU;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"BtnRemoveAll",65548},
		{L"BtnselImage",65547},
		{L"ListRemove",65546},
		{L"_name_start",65535},
		{L"btn_close",65538},
		{L"btn_menu",65536},
		{L"btn_min",65537},
		{L"checkOpen",65551},
		{L"icon",65540},
		{L"listMount",65545},
		{L"listUnmount",65544},
		{L"lv_cd_fix",65539},
		{L"lv_letter_fix",65550},
		{L"name",65541},
		{L"path",65542},
		{L"title",65549},
		{L"title_os_time",65543}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			BtnRemoveAll = namedXmlID[0].strName;
			BtnselImage = namedXmlID[1].strName;
			ListRemove = namedXmlID[2].strName;
			_name_start = namedXmlID[3].strName;
			btn_close = namedXmlID[4].strName;
			btn_menu = namedXmlID[5].strName;
			btn_min = namedXmlID[6].strName;
			checkOpen = namedXmlID[7].strName;
			icon = namedXmlID[8].strName;
			listMount = namedXmlID[9].strName;
			listUnmount = namedXmlID[10].strName;
			lv_cd_fix = namedXmlID[11].strName;
			lv_letter_fix = namedXmlID[12].strName;
			name = namedXmlID[13].strName;
			path = namedXmlID[14].strName;
			title = namedXmlID[15].strName;
			title_os_time = namedXmlID[16].strName;
		}
		 const wchar_t * BtnRemoveAll;
		 const wchar_t * BtnselImage;
		 const wchar_t * ListRemove;
		 const wchar_t * _name_start;
		 const wchar_t * btn_close;
		 const wchar_t * btn_menu;
		 const wchar_t * btn_min;
		 const wchar_t * checkOpen;
		 const wchar_t * icon;
		 const wchar_t * listMount;
		 const wchar_t * listUnmount;
		 const wchar_t * lv_cd_fix;
		 const wchar_t * lv_letter_fix;
		 const wchar_t * name;
		 const wchar_t * path;
		 const wchar_t * title;
		 const wchar_t * title_os_time;
		}name;

		class _id{
		public:
		const static int BtnRemoveAll	=	65548;
		const static int BtnselImage	=	65547;
		const static int ListRemove	=	65546;
		const static int _name_start	=	65535;
		const static int btn_close	=	65538;
		const static int btn_menu	=	65536;
		const static int btn_min	=	65537;
		const static int checkOpen	=	65551;
		const static int icon	=	65540;
		const static int listMount	=	65545;
		const static int listUnmount	=	65544;
		const static int lv_cd_fix	=	65539;
		const static int lv_letter_fix	=	65550;
		const static int name	=	65541;
		const static int path	=	65542;
		const static int title	=	65549;
		const static int title_os_time	=	65543;
		}id;

		class _string{
		public:
		const static int title	=	0;
		const static int ver	=	1;
		}string;

		class _color{
		public:
		const static int blue	=	0;
		const static int gray	=	1;
		const static int green	=	2;
		const static int red	=	3;
		const static int white	=	4;
		}color;

	};

#ifdef R_IN_CPP
	 extern const _R R;
	 extern const _UIRES UIRES;
#else
	 extern const __declspec(selectany) _R & R = _R();
	 extern const __declspec(selectany) _UIRES & UIRES = _UIRES();
#endif//R_IN_CPP
}
