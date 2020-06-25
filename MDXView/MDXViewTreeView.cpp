// MDXViewTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "includes.h"
#include "MDXView.h"
#include "GetString.h"

#include "MDXViewTreeView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMDXViewTreeView* gMDXViewTreeViewHandle = NULL;

//////////////////////////////////////////////////////////
// CMDXViewTreeView

IMPLEMENT_DYNCREATE(CMDXViewTreeView, CTreeView)

CMDXViewTreeView::CMDXViewTreeView()
{

}

CMDXViewTreeView::~CMDXViewTreeView()
{
}

BEGIN_MESSAGE_MAP(CMDXViewTreeView, CTreeView)
END_MESSAGE_MAP()


// CMDXViewTreeView diagnostics

#ifdef _DEBUG
void CMDXViewTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMDXViewTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG


// CMDXViewTreeView message handlers


BOOL CMDXViewTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class

	if (!CTreeView::PreCreateWindow(cs))
		return FALSE;

	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;
	return TRUE;
}


BOOL CMDXViewTreeView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL b = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	gMDXViewTreeViewHandle = this;

	return b;
}


HTREEITEM CMDXViewTreeView::GetRootItem(void)
{
	return GetTreeCtrl().GetRootItem();
}


BOOL CMDXViewTreeView::DeleteAllItems()
{
	return GetTreeCtrl().DeleteAllItems();
}


HTREEITEM CMDXViewTreeView::InsertItem(LPCTSTR psName, HTREEITEM hParent, UINT32 uiUserData, HTREEITEM hInsertAfter)
{
	if (hParent == NULL)
	{
		hParent = TVI_ROOT;
	}

	HTREEITEM hTreeItem = GetTreeCtrl().InsertItem(psName, hParent, hInsertAfter);
	assert(hTreeItem);
	GetTreeCtrl().SetItemData(hTreeItem, uiUserData);

	return hTreeItem;
}


void CMDXViewTreeView::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CTreeView::PostNcDestroy();
}


void CMDXViewTreeView::UpdateUI(CMenu* pMenu)
{
	CCmdUI state;
	state.m_pMenu = pMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
		state.m_nIndex++)
	{
		state.m_nID = pMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // menu separator or invalid cmd - ignore it

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// possibly a popup menu, route to first item of that popup
			state.m_pSubMenu = pMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // first item of popup can't be routed to
			}
			state.DoUpdate(this, FALSE);    // popups are never auto disabled
		}
		else
		{
			// normal menu item
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, state.m_nID < 0xF000);
		}

		// adjust for menu deletions and additions
		UINT nCount = pMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}


HTREEITEM		ghTreeItem_RButtonMenu = NULL;	// rather tacky, but I blame MS's API weakness...
TreeItemData_t	gTreeItemData;



// returns NULL if CANCEL, else input string
LPCSTR GetString(LPCSTR psPrompt, LPCSTR psDefault, bool bLowerCaseTheResult)
{
	return LPCSTR();	
	static CString strReturn;

	CGetString Input(psPrompt, &strReturn, psDefault);
	if (Input.DoModal() == IDOK)
	{
		strReturn.TrimLeft();
		strReturn.TrimRight();

		if (bLowerCaseTheResult)
			strReturn.MakeLower();

		return (LPCSTR)strReturn;
	}

	return NULL;
}


