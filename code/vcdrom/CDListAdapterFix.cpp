#include "StdAfx.h"
#include "CDListAdapterFix.h"



CCDListAdapterFix::CCDListAdapterFix(SListView* pOwner, CCDList cdList)
{
	m_owner = pOwner;
	m_cdList = cdList;
}


CCDListAdapterFix::~CCDListAdapterFix(void)
{
}

void CCDListAdapterFix::getView(int position, SWindow * pItem, pugi::xml_node xmlTemplate)
{
	if (pItem->GetChildrenCount() == 0)
	{
		pItem->InitFromXml(xmlTemplate);
		m_item.Add(pItem);
	}

	subscribeEvent(pItem->FindChildByName(L"listUnmount"));
	subscribeEvent(pItem->FindChildByName(L"listMount"));
	subscribeEvent(pItem->FindChildByName(L"ListRemove"));

	if (position % 2 == 0) //Ë«ÊýÇ³»Æ
	{
		pItem->SetAttribute(L"colorNormal", L"#fafafa  ",TRUE);
		pItem->SetAttribute(L"colorSelected", L"#fafafa  ",TRUE);
		pItem->SetAttribute(L"colorHover", L"#fafafa  ",TRUE);
	}
// 	else
// 	{
// 		pItem->SetAttribute(L"colorNormal", L"#fafafa  ",TRUE);
// 		pItem->SetAttribute(L"colorSelected", L"#fafafa  ",TRUE);
// 		pItem->SetAttribute(L"colorHover", L"#fafafa  ",TRUE);
// 	}

	CD_ITEM item = m_cdList[position];

	if ( item.bMount )
	{
		pItem->FindChildByName(L"listUnmount")->SetVisible(TRUE);
		pItem->FindChildByName(L"listMount")->SetVisible(FALSE);
		pItem->FindChildByName(L"ListRemove")->SetVisible(TRUE);
	}

	if ( item.hIcon )
	{
		pItem->FindChildByName2<SIconWnd>(L"icon")->SetIcon(item.hIcon);
	}
	SStatic* pText = pItem->FindChildByName2<SStatic>(L"path");
	pText->SetWindowText( item.strPath );

	 pText = pItem->FindChildByName2<SStatic>(L"name");
	pText->SetWindowText( item.strLabel );
}

int CCDListAdapterFix::getCount()
{
	return m_cdList.size();
}

void CCDListAdapterFix::subscribeEvent(SWindow* pWnd)
{
	pWnd->GetEventSet()->subscribeEvent(EventCmd::EventID, Subscriber(&CCDListAdapterFix::OnButtonClick, this) );
}

bool CCDListAdapterFix::OnButtonClick(EventCmd *pEvt)
{
	SStringT sName = pEvt->sender->GetName();

	return m_owner->FireEvent(*pEvt);
}
