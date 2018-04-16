#pragma once
#include <helper/SAdapterBase.h>

enum
{
	CD_STATUS_START,
	CD_STATUS_STOP,
};

struct CD_ITEM 
{
	SStringT strLabel;   //����
	SStringT strPath;	//·��
	TCHAR	 cDrive;
	HICON	 hIcon;
	SStringT strTime;	//������ʱ��
	BOOL	bMount;		//�Ƿ���أ�ʧЧ��ֱ���Ƴ��б�
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

