#pragma once
#include <helper/SAdapterBase.h>

enum
{
	CD_STATUS_START,
	CD_STATUS_STOP,
};

struct CD_ITEM 
{
	CD_ITEM()
	{
		cDrive = 0;
		hIcon = 0;
		bMount = FALSE;
	}
	SStringT strLabel;   //描述
	SStringT strPath;	//路径
	TCHAR	 cDrive;
	HICON	 hIcon;
	SStringT strTime;	//最后挂载时间
	BOOL	bMount;		//是否挂载，失效的直接移除列表

	bool operator < (CD_ITEM const& _A) const//升序排列
	{
		return false;
	}

	bool operator ==(CD_ITEM const& _A) const
	{
		return strPath.CompareNoCase(_A.strPath) == 0;
	}
};

/*
inline bool operator < (const CD_ITEM& l, const CD_ITEM& r)
{
	return l.strPath.CompareNoCase( r.strPath) < 0;
}
*/


// inline bool operator == (const CD_ITEM& l, const CD_ITEM& r)
// {
// 	return l.strPath.CompareNoCase( r.strPath) == 0;
// }


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
	void unsubscribeEvent( SWindow* pWnd);
	bool OnButtonClick(EventCmd *pEvt);
};

