#pragma once
#include <helper/SAdapterBase.h>

enum
{
	CD_STATUS_START,
	CD_STATUS_STOP,
};

struct CD_ITEM 
{
	SStringT strLabel;   //描述
	SStringT strPath;	//路径
	TCHAR	 cDrive;
	HICON	 hIcon;
	SStringT strTime;	//最后挂载时间
	BOOL	bMount;		//是否挂载，失效的直接移除列表
};

typedef std::vector<CD_ITEM>	CCDList;
class CCDListAdapterFix :
	public SAdapterBase
{
	SListView* m_owner;
	CCDList	 m_cdList;
	SArray<SWindow *> m_item;
public:
	CCDListAdapterFix(SListView* pOwner, CCDList cdList);
	~CCDListAdapterFix(void);
	virtual void getView(int position, SWindow * pItem, pugi::xml_node xmlTemplate);
	virtual int getCount();

private:
	void subscribeEvent( SWindow* pWnd);
	bool OnButtonClick(EventCmd *pEvt);
};

