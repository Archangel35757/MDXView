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

// globals
CMDXViewTreeView* gMDXViewTreeViewHandle = NULL;
CString		strTreeItemTextToFind;
HTREEITEM	ghTreeItemFound;
HTREEITEM	ghTreeItemHeader;
HTREEITEM	ghTreeCurrentFind;	// if NZ, don't count finds until you've reached this (last find)


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
//	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_TREE_MODEL_EXPANDALL, &CMDXViewTreeView::OnTreeModelExpandall)
	ON_COMMAND(IDM_TREE_MODEL_COLLAPSEALL, &CMDXViewTreeView::OnTreeModelCollapseall)
	ON_COMMAND(IDM_TREE_MODEL_INFO, &CMDXViewTreeView::OnTreeModelInfo)
	ON_COMMAND(IDM_TREE_MODEL_UNBOLTME, &CMDXViewTreeView::OnTreeModelUnboltme)
	ON_COMMAND(IDM_TREE_MODEL_FINDANY, &CMDXViewTreeView::OnTreeModelFindany)
	ON_WM_LBUTTONDBLCLK()
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
	gMDXViewTreeViewHandle = NULL;	// tell rest of code not to bother trying to write to this now

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


//BOOL CMDXViewTreeView::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	return CTreeView::OnEraseBkgnd(pDC);
//}


void CMDXViewTreeView::OnSize(UINT nType, int cx, int cy)
{
	CTreeView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}


void CMDXViewTreeView::OnSizing(UINT fwSide, LPRECT pRect)
{
	CTreeView::OnSizing(fwSide, pRect);

	// TODO: Add your message handler code here
}


void CMDXViewTreeView::R_ApplyToTreeItem(void(*pFunction) (HTREEITEM hTreeItem), HTREEITEM hTreeItem, bool bProcessSiblings /* = false */, bool bSkipProcessingOfInitialItem /* = false */)
{
	if (hTreeItem)
	{
		if (!bSkipProcessingOfInitialItem)	// only has meaning for first item, inherently false from then on
		{
			// process item...
			//
			pFunction(hTreeItem);
		}

		// recurse child...
		//		
		R_ApplyToTreeItem(pFunction, GetTreeCtrl().GetChildItem(hTreeItem), true, false);

		if (bProcessSiblings)	// test only has meaning for entry arg, all others inherently true
		{
			// recurse sibling...
			//
			R_ApplyToTreeItem(pFunction, GetTreeCtrl().GetNextSiblingItem(hTreeItem), bProcessSiblings, false);
		}
	}
}

void CMDXViewTreeView::ExpandTreeItem(HTREEITEM hTreeItem)
{
	gMDXViewTreeViewHandle->GetTreeCtrl().Expand(hTreeItem, TVE_EXPAND);
}

void CMDXViewTreeView::CollapseTreeItem(HTREEITEM hTreeItem)
{
	gMDXViewTreeViewHandle->GetTreeCtrl().Expand(hTreeItem, TVE_COLLAPSE);
}

void CMDXViewTreeView::SearchTreeItem(HTREEITEM hTreeItem)
{
	// if doing a find-next, don't do anything in here until we've reached the prev find, then clear it
	if (ghTreeCurrentFind)
	{
		if (hTreeItem == ghTreeCurrentFind)
		{
			ghTreeCurrentFind = NULL;
		}
	}
	else
	{
		if (!ghTreeItemFound)	// so we find the first, not the last
		{
			CString strThisItem = gMDXViewTreeViewHandle->GetTreeCtrl().GetItemText(hTreeItem);

			strThisItem.MakeLower();
			if (strstr(strThisItem, strTreeItemTextToFind))
				ghTreeItemFound = hTreeItem;
		}
	}
}


void CMDXViewTreeView::OnRButtonDown(UINT nFlags, CPoint point)
{
	UINT nHitFlags = 0;
	HTREEITEM hTreeItem_Clicked = GetTreeCtrl().HitTest(point, &nHitFlags);

	// TODO: Add your message handler code here and/or call default
	UINT	nIDMenuResource = NULL;
	TreeItemData_t	TreeItemData = { 0 };

	if (!hTreeItem_Clicked)	// if we didn't physically click on something, see if there's anything selected
	{
		hTreeItem_Clicked = GetTreeCtrl().GetSelectedItem();
	}

	if (hTreeItem_Clicked)
	{
		TreeItemData.uiData = GetTreeCtrl().GetItemData(hTreeItem_Clicked);
	}
	else
	{
		hTreeItem_Clicked = GetTreeCtrl().GetRootItem();
		TreeItemData.iItemType = TREEITEMTYPE_MODELNAME;
//		TreeItemData.iModelHandle = Model_GetPrimaryHandle();	// default to primary if not clicked on something specific
	}

	switch (TreeItemData.iItemType)
	{
	case TREEITEMTYPE_MODELNAME:

		nIDMenuResource = IDR_TREEPOPUP_MODEL;
		break;
/*
	case TREEITEMTYPE_SURFACEHEADER:	// "surfaces"

		nIDMenuResource = IDR_TREEPOPUP_SURFACES;
		break;

	case TREEITEMTYPE_TAGSURFACEHEADER:	// "surfaces"

		nIDMenuResource = IDR_TREEPOPUP_TAGSURFACES;
		break;

	case TREEITEMTYPE_BONEHEADER:		// "bones"

		nIDMenuResource = IDR_TREEPOPUP_BONES;
		break;

	case TREEITEMTYPE_SEQUENCEHEADER:	// "sequences"

		nIDMenuResource = IDR_TREEPOPUP_SEQUENCES;
		break;

	case TREEITEMTYPE_GLM_SURFACE:

		nIDMenuResource = IDR_TREEPOPUP_GLMSURFACE;
		break;

	case TREEITEMTYPE_GLM_TAGSURFACE:

		nIDMenuResource = IDR_TREEPOPUP_GLMTAGSURFACE;
		break;

	case TREEITEMTYPE_GLM_BONE:
	case TREEITEMTYPE_GLM_BONEALIAS:	// not sure about this one...

		nIDMenuResource = IDR_TREEPOPUP_GLMBONE;
		break;

	case TREEITEMTYPE_SEQUENCE:

		nIDMenuResource = IDR_TREEPOPUP_SEQUENCE;
		break;

	case TREEITEMTYPE_SKINSHEADER:

		nIDMenuResource = IDR_TREEPOPUP_SKINS;
		break;

	case TREEITEMTYPE_OLDSKINSHEADER:

		nIDMenuResource = IDR_TREEPOPUP_OLDSKINS;
		break;

	case TREEITEMTYPE_SKIN:

		nIDMenuResource = IDR_TREEPOPUP_SKIN;
		break;

	case TREEITEMTYPE_OLDSKIN:

		nIDMenuResource = IDR_TREEPOPUP_OLDSKIN;
		break;

	case TREEITEMTYPE_SKINETHNIC:

		nIDMenuResource = IDR_TREEPOPUP_ETHNIC;
		break;

	case TREEITEMTYPE_SKINMATERIALSHADER:

		nIDMenuResource = IDR_TREEPOPUP_SHADERVARIANT;
		break;
*/
	}

	// do a popup?
	//
	if (nIDMenuResource)
	{
		// record globally for menu code to acces (tacky, I know...)
		//
		ghTreeItem_RButtonMenu = hTreeItem_Clicked;
		gTreeItemData = TreeItemData;	//		uiUserData_RButtonMenu= TreeItemData.uiData;	//uiTreeItemData;

		if (gTreeItemData.iModelHandle)	// don't do anything if no model loaded
		{
			CMenu theMenu;
			theMenu.LoadMenu(nIDMenuResource);
			CMenu* thePopup = theMenu.GetSubMenu(0);

			UpdateUI(thePopup);
			/*
			AfxGetApp()->OnIdle(1);

			----------
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

			-----------
			*/
			CPoint clientPoint = point;
			ClientToScreen(&clientPoint);
			thePopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, clientPoint.x, clientPoint.y, this);

			theMenu.DestroyMenu();
			return;
		}
	}

	CTreeView::OnRButtonDown(nFlags, point);
}


void CMDXViewTreeView::OnTreeModelExpandall()
{
	// TODO: Add your command handler code here
	//	R_ApplyToTreeItem( ::ExpandTreeItem, GetTreeCtrl().GetRootItem(), true );
	//	GetTreeCtrl().SelectSetFirstVisible(GetRootItem());
	R_ApplyToTreeItem(ExpandTreeItem, ghTreeItem_RButtonMenu);
	GetTreeCtrl().SelectSetFirstVisible(ghTreeItem_RButtonMenu);
}


void CMDXViewTreeView::OnTreeModelCollapseall()
{
	// TODO: Add your command handler code here
	//	R_ApplyToTreeItem( ::CollapseTreeItem, GetTreeCtrl().GetRootItem(), true );
	R_ApplyToTreeItem(CollapseTreeItem, ghTreeItem_RButtonMenu, true);
}


void CMDXViewTreeView::OnTreeModelInfo()
{
	// TODO: Add your command handler code here
}


void CMDXViewTreeView::OnTreeModelUnboltme()
{
	// TODO: Add your command handler code here
}


void CMDXViewTreeView::OnTreeModelFindany()
{
	// TODO: Add your command handler code here
	LPCSTR psSearch = GetString("Enter TreeItemText to search for...\n\n( Case insensitive, partial strings ok )");

	if (psSearch)
	{
		strTreeItemTextToFind = psSearch;
		ghTreeItemFound = NULL;
		ghTreeItemHeader = ghTreeItem_RButtonMenu;
		ghTreeCurrentFind = NULL;

		R_ApplyToTreeItem(SearchTreeItem, ghTreeItemHeader);

		if (ghTreeItemFound)
		{
			GetTreeCtrl().SelectSetFirstVisible(ghTreeItemFound);
			GetTreeCtrl().SelectItem(ghTreeItemFound);
		}
	}
}


void CMDXViewTreeView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	UINT nHitFlags = 0;
	HTREEITEM hTreeItem_Clicked = GetTreeCtrl().HitTest(point, &nHitFlags);

	TreeItemData_t	TreeItemData = { 0 };
	if (!hTreeItem_Clicked)	// if we didn't physically click on something, see if there's anything selected
	{
		hTreeItem_Clicked = GetTreeCtrl().GetSelectedItem();
	}

	if (hTreeItem_Clicked)
	{
		TreeItemData.uiData = GetTreeCtrl().GetItemData(hTreeItem_Clicked);

		if (TreeItemData.iModelHandle)	// valid?  (should be)
		{
			gTreeItemData.uiData = TreeItemData.uiData;	// may as well copy to global version
			ghTreeItem_RButtonMenu = hTreeItem_Clicked;

			switch (TreeItemData.iItemType)
			{
				case TREEITEMTYPE_SEQUENCE:
				{
					// multiseqlock or single lock?...
					//
					if (Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, true))
					{
						Model_MultiSeq_Add(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true);
					}
					else
					{
						Model_Sequence_Lock(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true);
						ModelList_Rewind();
					}
				}
				break;

				case TREEITEMTYPE_OLDSKIN:
				{
					CString strSkin(GetTreeCtrl().GetItemText(ghTreeItem_RButtonMenu));
					Model_ApplyOldSkin(gTreeItemData.iModelHandle, strSkin);
				}
				break;
			}
		}
	}
	else
	{
		hTreeItem_Clicked = GetTreeCtrl().GetRootItem();
		TreeItemData.iItemType = TREEITEMTYPE_MODELNAME;
//		TreeItemData.iModelHandle = Model_GetPrimaryHandle();	// default to primary if not clicked on something specific
	}

	CTreeView::OnLButtonDblClk(nFlags, point);
}
