#include "StdAfx.h"
#include "CDListAdapterFix.h"



CCDListAdapterFix::CCDListAdapterFix(SListView* pOwner, CCDList cdList)
{
	m_owner = pOwner;
	m_cdList = cdList;
}


CCDListAdapterFix::~CCDListAdapterFix(void)
{
	for ( int n = 0 ; n < m_item.GetCount() ; n++)
	{
		//subscribeEvent(m_item[n]->FindChildByName(L"listUnmount"));
		//subscribeEvent(m_item[n]->FindChildByName(L"listMount"));
		//subscribeEvent(m_item[n]->FindChildByName(L"ListRemove"));
		//subscribeEvent(m_item[n]->FindChildByName(L"listOpen"));
	}
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
	subscribeEvent(pItem->FindChildByName(L"listOpen"));

	if (position % 2 == 0) //Ë«ÊýÇ³»Æ
	{
	//	pItem->SetAttribute(L"colorNormal", L"#fafafa  ",TRUE);
		//pItem->SetAttribute(L"colorSelected", L"#fafafa  ",TRUE);
	//	pItem->SetAttribute(L"colorHover", L"#fafafa  ",TRUE);
	}

	CD_ITEM item = m_cdList[position];
	SStatic* pText = pItem->FindChildByName2<SStatic>(L"path");
	pText->SetWindowText( item.strPath );

	if ( item.bMount )
	{
		pItem->FindChildByName(L"listUnmount")->SetVisible(TRUE);
		pItem->FindChildByName(L"listMount")->SetVisible(FALSE);
		pItem->FindChildByName(L"ListRemove")->SetVisible(TRUE);
		pItem->FindChildByName(L"listOpen")->SetVisible(TRUE);

		SStringT strLabel; 
		strLabel.Format(L"%s (%c:)", item.strLabel, item.cDrive);
		pText = pItem->FindChildByName2<SStatic>(L"name");
		pText->SetWindowText( strLabel );

	}
	else
	{
		pItem->FindChildByName(L"listUnmount")->SetVisible(FALSE);
		pItem->FindChildByName(L"listMount")->SetVisible(TRUE);
		pItem->FindChildByName(L"ListRemove")->SetVisible(TRUE);
		pItem->FindChildByName(L"listOpen")->SetVisible(FALSE);

		pText = pItem->FindChildByName2<SStatic>(L"name");
		pText->SetWindowText( item.strLabel );
	}
	if ( item.hIcon )
	{
		pItem->FindChildByName2<SImageWnd>(L"defaultIcon")->SetVisible(FALSE);
		pItem->FindChildByName2<SIconWnd>(L"icon")->SetIcon(item.hIcon);
	}
	else
	{
		pItem->FindChildByName2<SIconWnd>(L"icon")->SetVisible(FALSE);
	}
}

int CCDListAdapterFix::getCount()
{
	return m_cdList.size();
}

void CCDListAdapterFix::subscribeEvent(SWindow* pWnd)
{
	pWnd->GetEventSet()->subscribeEvent(EventCmd::EventID, Subscriber(&CCDListAdapterFix::OnButtonClick, this) );
}

void CCDListAdapterFix::unsubscribeEvent(SWindow* pWnd)
{
	pWnd->GetEventSet()->unsubscribeEvent(EventCmd::EventID, Subscriber(&CCDListAdapterFix::OnButtonClick, this) );
}


bool CCDListAdapterFix::OnButtonClick(EventCmd *pEvt)
{
	SStringT sName = pEvt->sender->GetName();
	m_owner->FireEvent(*pEvt);
	this->notifyDataSetChanged();
	return true;
}
