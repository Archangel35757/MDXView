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
	//{{AFX_MSG_MAP(CMDXViewTreeView)
//	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_TREE_MODEL_EXPANDALL, &CMDXViewTreeView::OnTreeModelExpandAll)
	ON_COMMAND(IDM_TREE_MODEL_COLLAPSEALL, &CMDXViewTreeView::OnTreeModelCollapseAll)
	ON_COMMAND(IDM_TREE_MODEL_INFO, &CMDXViewTreeView::OnTreeModelInfo)
	ON_COMMAND(IDM_TREE_MODEL_UNBOLTME, &CMDXViewTreeView::OnTreeModelUnboltMe)
	ON_UPDATE_COMMAND_UI(IDM_TREE_MODEL_UNBOLTME, &CMDXViewTreeView::OnUpdateTreeModelUnboltMe)
	ON_COMMAND(IDM_TREE_MODEL_FINDANY, &CMDXViewTreeView::OnTreeModelFindAny)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(IDR_TREE_BONES_EXPANDALL, &CMDXViewTreeView::OnTreeBonesExpandAll)
	ON_COMMAND(ID_BONES_FIND, &CMDXViewTreeView::OnBonesFind)
	ON_COMMAND(ID_BONES_CLEARSECONDARYANIM, &CMDXViewTreeView::OnBonesClearSecondaryAnim)
	ON_UPDATE_COMMAND_UI(ID_BONES_CLEARSECONDARYANIM, &CMDXViewTreeView::OnUpdateBonesClearSecondaryAnim)
	ON_COMMAND(ID_ETHNIC_EXPANDALL, &CMDXViewTreeView::OnEthnicExpandAll)
	ON_COMMAND(ID_ETHNIC_APPLY_SKIN, &CMDXViewTreeView::OnEthnicApplySkin)
	ON_COMMAND(ID_ETHNIC_APPLY_SKIN_SURFACEPREFS, &CMDXViewTreeView::OnEthnicApplySkinSurfacePrefs)
	ON_UPDATE_COMMAND_UI(ID_ETHNIC_APPLY_SKIN_SURFACEPREFS, &CMDXViewTreeView::OnUpdateEthnicApplySkinSurfacePrefs)
	ON_COMMAND(ID_ETHNIC_APPLY_SKIN_SURFACEDEFAULTS, &CMDXViewTreeView::OnEthnicApplySkinSurfaceDefaults)
	ON_UPDATE_COMMAND_UI(ID_GLMBONE_TITLE, &CMDXViewTreeView::OnUpdateGlmBoneTitle)
	ON_COMMAND(ID_GLMBONE_INFO, &CMDXViewTreeView::OnGlmBoneInfo)
	ON_COMMAND(ID_GLMBONE_BOLTMODEL_REPLACE, &CMDXViewTreeView::OnGlmBoneBoltModelReplace)
	ON_COMMAND(ID_GLMBONE_BOLTMODEL_ADD, &CMDXViewTreeView::OnGlmBoneBoltModelAdd)
	ON_COMMAND(ID_GLMBONE_DELETEALLBOLTEDMODELS, &CMDXViewTreeView::OnGlmBoneDeleteAllBoltedModels)
	ON_UPDATE_COMMAND_UI(ID_GLMBONE_DELETEALLBOLTEDMODELS, &CMDXViewTreeView::OnUpdateGlmBoneDeleteAllBoltedModels)
	ON_COMMAND(ID_GLMBONE_SECONDARY_ANIMSTART, &CMDXViewTreeView::OnGlmBoneSecondaryAnimStart)
	ON_UPDATE_COMMAND_UI(ID_GLMBONE_SECONDARY_ANIMSTART, &CMDXViewTreeView::OnUpdateGlmBoneSecondaryAnimStart)
	ON_UPDATE_COMMAND_UI(ID_GLMSURFACE_TITLE, &CMDXViewTreeView::OnUpdateGlmSurfaceTitle)
	ON_COMMAND(ID_GLMSURFACE_INFO, &CMDXViewTreeView::OnGlmSurfaceInfo)
	ON_COMMAND(ID_GLMSURFACE_ON, &CMDXViewTreeView::OnGlmSurfaceOn)
	ON_UPDATE_COMMAND_UI(ID_GLMSURFACE_ON, &CMDXViewTreeView::OnUpdateGlmSurfaceOn)
	ON_COMMAND(ID_GLMSURFACE_OFF, &CMDXViewTreeView::OnGlmSurfaceOff)
	ON_UPDATE_COMMAND_UI(ID_GLMSURFACE_OFF, &CMDXViewTreeView::OnUpdateGlmSurfaceOff)
	ON_COMMAND(ID_GLMSURFACE_NODESCENDANTS, &CMDXViewTreeView::OnGlmSurfaceNoDescendants)
	ON_UPDATE_COMMAND_UI(ID_GLMSURFACE_NODESCENDANTS, &CMDXViewTreeView::OnUpdateGlmSurfaceNoDescendants)
	ON_COMMAND(ID_GLMSURFACE_SETASROOT, &CMDXViewTreeView::OnGlmSurfaceSetAsRoot)
	ON_UPDATE_COMMAND_UI(ID_GLMSURFACE_SETASROOT, &CMDXViewTreeView::OnUpdateGlmSurfaceSetAsRoot)
	ON_COMMAND(ID_GLMSURFACE_CLEARROOT, &CMDXViewTreeView::OnGlmSurfaceClearRoot)
	ON_UPDATE_COMMAND_UI(ID_GLMSURFACE_CLEARROOT, &CMDXViewTreeView::OnUpdateGlmSurfaceClearRoot)
	ON_COMMAND(ID_GLMSURFACE_BOLTMODEL_REPLACE, &CMDXViewTreeView::OnGlmSurfaceBoltModelReplace)
	ON_UPDATE_COMMAND_UI(ID_GLMSURFACE_BOLTMODEL_REPLACE, &CMDXViewTreeView::OnUpdateGlmSurfaceBoltModelReplace)
	ON_COMMAND(ID_GLMSURFACE_BOLTMODEL_ADD, &CMDXViewTreeView::OnGlmSurfaceBoltModelAdd)
	ON_UPDATE_COMMAND_UI(ID_GLMSURFACE_BOLTMODEL_ADD, &CMDXViewTreeView::OnUpdateGlmSurfaceBoltModelAdd)
	ON_COMMAND(ID_GLMSURFACE_DELETEALLBOLTEDMODELS, &CMDXViewTreeView::OnGlmSurfaceDeleteAllBoltedModels)
	ON_UPDATE_COMMAND_UI(ID_GLMSURFACE_DELETEALLBOLTEDMODELS, &CMDXViewTreeView::OnUpdateGlmSurfaceDeleteAllBoltedModels)
	ON_UPDATE_COMMAND_UI(ID_GLMTAGSURFACE_TITLE, &CMDXViewTreeView::OnUpdateGlmTagSurfaceTitle)
	ON_COMMAND(ID_GLMTAGSURFACE_INFO, &CMDXViewTreeView::OnGlmTagSurfaceInfo)
	ON_COMMAND(ID_GLMTAGSURFACE_BOLTMODEL_REPLACE, &CMDXViewTreeView::OnGlmTagSurfaceBoltModelReplace)
	ON_COMMAND(ID_GLMTAGSURFACE_BOLTMODEL_ADD, &CMDXViewTreeView::OnGlmTagSurfaceBoltModelAdd)
	ON_COMMAND(ID_GLMTAGSURFACE_DELETEALLBOLTEDMODELS, &CMDXViewTreeView::OnGlmTagSurfaceDeleteAllBoltedModels)
	ON_UPDATE_COMMAND_UI(ID_GLMTAGSURFACE_DELETEALLBOLTEDMODELS, &CMDXViewTreeView::OnUpdateGlmTagSurfaceDeleteAllBoltedModels)
	ON_COMMAND(ID_G2SKIN_EXPANDALL, &CMDXViewTreeView::OnG2SkinExpandAll)
	ON_COMMAND(ID_G2SKIN_VALIDATE, &CMDXViewTreeView::OnG2SkinValidate)
	ON_COMMAND(ID_G2SKINS_EXPANDALL, &CMDXViewTreeView::OnG2SkinsExpandAll)
	ON_COMMAND(ID_G2SKINS_VALIDATE, &CMDXViewTreeView::OnG2SkinsValidate)
	ON_COMMAND(ID_OLDSKIN_VALIDATE, &CMDXViewTreeView::OnOldSkinValidate)
	ON_COMMAND(ID_OLDSKIN_APPLY, &CMDXViewTreeView::OnOldSkinApply)
	ON_COMMAND(ID_OLDSKINS_VALIDATE, &CMDXViewTreeView::OnOldSkinsValidate)
	ON_COMMAND(ID_SHADERVARIANT_APPLY, &CMDXViewTreeView::OnShaderVariantApply)
	ON_UPDATE_COMMAND_UI(ID_SEQ_TITLE, &CMDXViewTreeView::OnUpdateSeqTitle)
	ON_COMMAND(ID_SEQ_LOCK, &CMDXViewTreeView::OnSeqLock)
	ON_UPDATE_COMMAND_UI(ID_SEQ_LOCK, &CMDXViewTreeView::OnUpdateSeqLock)
	ON_COMMAND(ID_SEQ_UNLOCK, &CMDXViewTreeView::OnSeqUnlock)
	ON_UPDATE_COMMAND_UI(ID_SEQ_UNLOCK, &CMDXViewTreeView::OnUpdateSeqUnlock)
	ON_COMMAND(ID_SEQ_MULTILOCK, &CMDXViewTreeView::OnSeqMultiLock)
	ON_UPDATE_COMMAND_UI(ID_SEQ_MULTILOCK, &CMDXViewTreeView::OnUpdateSeqMultiLock)
	ON_COMMAND(ID_SEQ_MULTILOCK_DELETE, &CMDXViewTreeView::OnSeqMultiLockDelete)
	ON_UPDATE_COMMAND_UI(ID_SEQ_MULTILOCK_DELETE, &CMDXViewTreeView::OnUpdateSeqMultiLockDelete)
	ON_COMMAND(ID_SEQ_LOCK_SECONDARY, &CMDXViewTreeView::OnSeqLockSecondary)
	ON_UPDATE_COMMAND_UI(ID_SEQ_LOCK_SECONDARY, &CMDXViewTreeView::OnUpdateSeqLockSecondary)
	ON_COMMAND(ID_SEQ_UNLOCK_SECONDARY, &CMDXViewTreeView::OnSeqUnlockSecondary)
	ON_UPDATE_COMMAND_UI(ID_SEQ_UNLOCK_SECONDARY, &CMDXViewTreeView::OnUpdateSeqUnlockSecondary)
	ON_COMMAND(ID_SEQ_MULTILOCK_SECONDARY, &CMDXViewTreeView::OnSeqMultiLockSecondary)
	ON_UPDATE_COMMAND_UI(ID_SEQ_MULTILOCK_SECONDARY, &CMDXViewTreeView::OnUpdateSeqMultiLockSecondary)
	ON_COMMAND(ID_SEQ_MULTILOCK_SECONDARY_DELETE, &CMDXViewTreeView::OnSeqMultiLockSecondaryDelete)
	ON_UPDATE_COMMAND_UI(ID_SEQ_MULTILOCK_SECONDARY_DELETE, &CMDXViewTreeView::OnUpdateSeqMultiLockSecondaryDelete)
	ON_COMMAND(ID_SEQS_VIEWFULLPATH, &CMDXViewTreeView::OnSeqsViewFullPath)
	ON_COMMAND(ID_SEQS_SORTALPHABETICALLY, &CMDXViewTreeView::OnSeqsSortAlphabetically)
	ON_UPDATE_COMMAND_UI(ID_SEQS_SORTALPHABETICALLY, &CMDXViewTreeView::OnUpdateSeqsSortAlphabetically)
	ON_COMMAND(ID_SEQS_UNLOCKALL, &CMDXViewTreeView::OnSeqsUnlockAll)
	ON_UPDATE_COMMAND_UI(ID_SEQS_UNLOCKALL, &CMDXViewTreeView::OnUpdateSeqsUnlockAll)
	ON_COMMAND(ID_SEQS_UNLOCK_PRIMARY, &CMDXViewTreeView::OnSeqsUnlockPrimary)
	ON_UPDATE_COMMAND_UI(ID_SEQS_UNLOCK_PRIMARY, &CMDXViewTreeView::OnUpdateSeqsUnlockPrimary)
	ON_COMMAND(ID_SEQS_UNLOCK_SECONDARY, &CMDXViewTreeView::OnSeqsUnlockSecondary)
	ON_UPDATE_COMMAND_UI(ID_SEQS_UNLOCK_SECONDARY, &CMDXViewTreeView::OnUpdateSeqsUnlockSecondary)
	ON_COMMAND(ID_MULTISEQS_UNLOCK_PRIMARY, &CMDXViewTreeView::OnMultiSeqsUnlockPrimary)
	ON_UPDATE_COMMAND_UI(ID_MULTISEQS_UNLOCK_PRIMARY, &CMDXViewTreeView::OnUpdateMultiSeqsUnlockPrimary)
	ON_COMMAND(ID_SEQS_DELETELAST_PRIMARY, &CMDXViewTreeView::OnSeqsDeleteLastPrimary)
	ON_UPDATE_COMMAND_UI(ID_SEQS_DELETELAST_PRIMARY, &CMDXViewTreeView::OnUpdateSeqsDeleteLastPrimary)
	ON_COMMAND(ID_SEQS_DELETEALL_PRIMARY, &CMDXViewTreeView::OnSeqsDeleteAllPrimary)
	ON_UPDATE_COMMAND_UI(ID_SEQS_DELETEALL_PRIMARY, &CMDXViewTreeView::OnUpdateSeqsDeleteAllPrimary)
	ON_COMMAND(ID_MULTISEQS_UNLOCK_SECONDARY, &CMDXViewTreeView::OnMultiSeqsUnlockSecondary)
	ON_UPDATE_COMMAND_UI(ID_MULTISEQS_UNLOCK_SECONDARY, &CMDXViewTreeView::OnUpdateMultiSeqsUnlockSecondary)
	ON_COMMAND(ID_SEQS_DELETELAST_SECONDARY, &CMDXViewTreeView::OnSeqsDeleteLastSecondary)
	ON_UPDATE_COMMAND_UI(ID_SEQS_DELETELAST_SECONDARY, &CMDXViewTreeView::OnUpdateSeqsDeleteLastSecondary)
	ON_COMMAND(ID_SEQS_DELETEALL_SECONDARY, &CMDXViewTreeView::OnSeqsDeleteAllSecondary)
	ON_UPDATE_COMMAND_UI(ID_SEQS_DELETEALL_SECONDARY, &CMDXViewTreeView::OnUpdateSeqsDeleteAllSecondary)
	ON_COMMAND(ID_TREE_SURFACES_EXPANDALL, &CMDXViewTreeView::OnTreeSurfacesExpandAll)
	ON_COMMAND(ID_TREE_SURFACES_FIND, &CMDXViewTreeView::OnTreeSurfacesFind)
	ON_COMMAND(ID_TREE_SURFACES_FIND_NEXT, &CMDXViewTreeView::OnTreeSurfacesFindNext)
	ON_COMMAND(ID_TREE_SURFACES_FIND_PREV, &CMDXViewTreeView::OnTreeSurfacesFindPrev)
	ON_COMMAND(ID_TREE_SURFACES_ALLDEFAULTOFF_OFF, &CMDXViewTreeView::OnTreeSurfacesAllDefaultoffOff)
	ON_UPDATE_COMMAND_UI(ID_TREE_SURFACES_ALLDEFAULTOFF_OFF, &CMDXViewTreeView::OnUpdateTreeSurfacesAllDefaultoffOff)
	ON_COMMAND(ID_TREE_SURFACES_ALLDEFAULTOFF_ON, &CMDXViewTreeView::OnTreeSurfacesAllDefaultoffOn)
	ON_UPDATE_COMMAND_UI(ID_TREE_SURFACES_ALLDEFAULTOFF_ON, &CMDXViewTreeView::OnUpdateTreeSurfacesAllDefaultoffOn)
	ON_COMMAND(ID_TREE_SURFACES_ALLDEFAULTOFF_DEFAULT, &CMDXViewTreeView::OnTreeSurfacesAllDefaultoffDefault)
	ON_COMMAND(ID_TREE_SURFACES_CLEAR_ROOT, &CMDXViewTreeView::OnTreeSurfacesClearRoot)
	ON_UPDATE_COMMAND_UI(ID_TREE_SURFACES_CLEAR_ROOT, &CMDXViewTreeView::OnUpdateTreeSurfacesClearRoot)
	//}}AFX_MSG_MAP
		ON_COMMAND(ID_TREE_TAGSURFACES_EXPANDALL, &CMDXViewTreeView::OnTreeTagSurfacesExpandAll)
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


void CMDXViewTreeView::ReEvalSequenceText(HTREEITEM hTreeItem)
{
	TreeItemData_t	TreeItemData;
	TreeItemData.uiData = gMDXViewTreeViewHandle->GetTreeCtrl().GetItemData(hTreeItem);

	if (TreeItemData.iItemType == TREEITEMTYPE_SEQUENCE)
	{
		LPCSTR psNewText = Model_Sequence_GetTreeName(TreeItemData.iModelHandle, TreeItemData.iItemNumber);

		gMDXViewTreeViewHandle->GetTreeCtrl().SetItemText(hTreeItem, psNewText);
	}
}


// 'bDefaultAll' overrides 'bOnOff' and means set-to-default-state...
//
void CMDXViewTreeView::SetTreeItemSurfaceState(HTREEITEM hTreeItem, bool bOnOff, bool bDefaultAll)
{
	TreeItemData_t	TreeItemData;
	TreeItemData.uiData = gMDXViewTreeViewHandle->GetTreeCtrl().GetItemData(hTreeItem);

	if (TreeItemData.iItemType == TREEITEMTYPE_GLM_SURFACE ||
		TreeItemData.iItemType == TREEITEMTYPE_GLM_TAGSURFACE
		)
	{
		LPCSTR psSurfaceName = GLMModel_GetSurfaceName(TreeItemData.iModelHandle, TreeItemData.iItemNumber);

		bool bSurfaceNameIncludesOFF = !stricmp("_off", &psSurfaceName[strlen(psSurfaceName) - 4]);

		if (bDefaultAll || bSurfaceNameIncludesOFF)
		{
			if (bDefaultAll)
				bOnOff = !bSurfaceNameIncludesOFF;

			if (bOnOff)
			{
				Model_GLMSurface_On(TreeItemData.iModelHandle, TreeItemData.iItemNumber);
			}
			else
			{
				Model_GLMSurface_Off(TreeItemData.iModelHandle, TreeItemData.iItemNumber);
			}
		}
	}
}


void CMDXViewTreeView::EnableTreeItemDefaultOFFSurface(HTREEITEM hTreeItem)
{
	SetTreeItemSurfaceState(hTreeItem, true, false);
}


void CMDXViewTreeView::DisableTreeItemDefaultOFFSurface(HTREEITEM hTreeItem)
{
	SetTreeItemSurfaceState(hTreeItem, false, false);
}


void CMDXViewTreeView::DefaultTreeItemDefaultOFFSurface(HTREEITEM hTreeItem)
{
	SetTreeItemSurfaceState(hTreeItem, false, true);
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


void CMDXViewTreeView::OnTreeModelExpandAll()
{
//	R_ApplyToTreeItem( ::ExpandTreeItem, GetTreeCtrl().GetRootItem(), true );
//	GetTreeCtrl().SelectSetFirstVisible(GetRootItem());
	R_ApplyToTreeItem(ExpandTreeItem, ghTreeItem_RButtonMenu);
	GetTreeCtrl().SelectSetFirstVisible(ghTreeItem_RButtonMenu);
}


void CMDXViewTreeView::OnTreeModelCollapseAll()
{
//	R_ApplyToTreeItem( ::CollapseTreeItem, GetTreeCtrl().GetRootItem(), true );
	R_ApplyToTreeItem(CollapseTreeItem, ghTreeItem_RButtonMenu, true);
}


void CMDXViewTreeView::OnTreeModelInfo()
{
	InfoBox(Model_Info(gTreeItemData.iModelHandle));
}


void CMDXViewTreeView::OnTreeModelUnboltMe()
{
	if (Model_DeleteBoltOn(gTreeItemData.iModelHandle))
	{
		Invalidate(false);
	}
}


void CMDXViewTreeView::OnUpdateTreeModelUnboltMe(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(Model_HasParent(gTreeItemData.iModelHandle));
}


void CMDXViewTreeView::OnTreeModelFindAny()
{
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

void CMDXViewTreeView::OnTreeBonesExpandAll()
{
	R_ApplyToTreeItem(ExpandTreeItem, ghTreeItem_RButtonMenu);
	GetTreeCtrl().SelectSetFirstVisible(ghTreeItem_RButtonMenu);
}


void CMDXViewTreeView::OnBonesFind()
{
	LPCSTR psSearch = GetString("Enter Bone name to search for...\n\n( Case insensitive, partial strings ok )");

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


void CMDXViewTreeView::OnBonesClearSecondaryAnim()
{
	Model_SetSecondaryAnimStart(gTreeItemData.iModelHandle, -1);
}


void CMDXViewTreeView::OnUpdateBonesClearSecondaryAnim(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((Model_GetSecondaryAnimStart(gTreeItemData.iModelHandle) != -1));
}


void CMDXViewTreeView::OnEthnicExpandAll()
{
	R_ApplyToTreeItem(ExpandTreeItem, ghTreeItem_RButtonMenu);
	GetTreeCtrl().SelectSetFirstVisible(ghTreeItem_RButtonMenu);
}


void CMDXViewTreeView::OnEthnicApplySkin()
{
	HTREEITEM hTreeItemParent = GetTreeCtrl().GetParentItem(ghTreeItem_RButtonMenu);
	CString strParentSkin = GetTreeCtrl().GetItemText(hTreeItemParent);
	CString strThisEthnic = GetTreeCtrl().GetItemText(ghTreeItem_RButtonMenu);

	Model_ApplyEthnicSkin(gTreeItemData.iModelHandle, strParentSkin, strThisEthnic, false, false);
}

void CMDXViewTreeView::OnEthnicApplySkinSurfacePrefs()
{
	HTREEITEM hTreeItemParent = GetTreeCtrl().GetParentItem(ghTreeItem_RButtonMenu);
	CString strParentSkin = GetTreeCtrl().GetItemText(hTreeItemParent);
	CString strThisEthnic = GetTreeCtrl().GetItemText(ghTreeItem_RButtonMenu);

	Model_ApplyEthnicSkin(gTreeItemData.iModelHandle, strParentSkin, strThisEthnic, true, true);
}


void CMDXViewTreeView::OnUpdateEthnicApplySkinSurfacePrefs(CCmdUI *pCmdUI)
{
	HTREEITEM hTreeItemParent = GetTreeCtrl().GetParentItem(ghTreeItem_RButtonMenu);
	CString strParentSkin = GetTreeCtrl().GetItemText(hTreeItemParent);

	pCmdUI->Enable(Model_SkinHasSurfacePrefs(gTreeItemData.iModelHandle, strParentSkin));
}


void CMDXViewTreeView::OnEthnicApplySkinSurfaceDefaults()
{
	HTREEITEM hTreeItemParent = GetTreeCtrl().GetParentItem(ghTreeItem_RButtonMenu);
	CString strParentSkin = GetTreeCtrl().GetItemText(hTreeItemParent);
	CString strThisEthnic = GetTreeCtrl().GetItemText(ghTreeItem_RButtonMenu);

	Model_ApplyEthnicSkin(gTreeItemData.iModelHandle, strParentSkin, strThisEthnic, false, true);
}


void CMDXViewTreeView::OnUpdateGlmBoneTitle(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(va("Bone:  %s", Model_GetBoneName(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber)));
}


void CMDXViewTreeView::OnGlmBoneInfo()
{
	InfoBox(Model_GLMBoneInfo(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber));
}


void CMDXViewTreeView::OnGlmBoneBoltModelReplace()
{
//	OutputDebugString("on command\n");
	LPCSTR psCaption = va("Bolt model to bone bolt-point '%s'", Model_GetBoltName(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true));	// bBoltIsBone

	LPCSTR psFullPathedFilename = InputLoadFileName("",				// LPCSTR psInitialLoadName, 
		psCaption,		// LPCSTR psCaption,
		Filename_PathOnly(Model_GetFullPrimaryFilename()),	//	"S:\\baseq3\\models\\test\\bonehier",	// LPCSTR psInitialDir,
		Model_GetSupportedTypesFilter()			// LPCSTR psFilter
	);

	if (psFullPathedFilename)
	{
		Model_LoadBoltOn(psFullPathedFilename, gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true, true);	// bBoltIsBone, bBoltReplacesAllExisting
	}
}


void CMDXViewTreeView::OnGlmBoneBoltModelAdd()
{
//	OutputDebugString("on command\n");
	LPCSTR psCaption = va("Bolt additional model to bone bolt-point '%s'", Model_GetBoltName(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true));	// bBoltIsBone

	LPCSTR psFullPathedFilename = InputLoadFileName("",				// LPCSTR psInitialLoadName, 
		psCaption,		// LPCSTR psCaption,
		Filename_PathOnly(Model_GetFullPrimaryFilename()),	//	"S:\\baseq3\\models\\test\\bonehier",	// LPCSTR psInitialDir,
		Model_GetSupportedTypesFilter()			// LPCSTR psFilter
	);

	if (psFullPathedFilename)
	{
		Model_LoadBoltOn(psFullPathedFilename, gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true, false);	// bBoltIsBone, bBoltReplacesAllExisting
	}
}


void CMDXViewTreeView::OnGlmBoneDeleteAllBoltedModels()
{
	if (Model_DeleteBoltOn(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true, -1))
	{
		Invalidate(false);	// or some changed items on the tree don't redraw until you click on them
	}
}


void CMDXViewTreeView::OnUpdateGlmBoneDeleteAllBoltedModels(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(Model_CountItemsBoltedHere(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true));	// bBoltIsBone
}


void CMDXViewTreeView::OnGlmBoneSecondaryAnimStart()
{
	//	InfoBox("Ignore this for now, Under construction");

	Model_SetSecondaryAnimStart(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber);
}


void CMDXViewTreeView::OnUpdateGlmBoneSecondaryAnimStart(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( gTreeItemData.iItemNumber != 0	// it's probably bad to be able to set first bone as secondary anim start?
		&&
		!(Model_GetSecondaryAnimStart(gTreeItemData.iModelHandle) == gTreeItemData.iItemNumber)
	);
}


void CMDXViewTreeView::OnUpdateGlmSurfaceTitle(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(va("Surface:  %s", Model_GetSurfaceName(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber)));
}


void CMDXViewTreeView::OnGlmSurfaceInfo()
{
	if (AppVars.bVertIndexes)
	{
		string	strInfo = Model_GLMSurfaceInfo(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false);
		strInfo += "\nSince you have display-vert-indexes on, do you want to see all vert data as well?\n";
		if (GetYesNo(strInfo.c_str()))
		{
			CWaitCursor wait;
			LPCSTR psInfoString = Model_GLMSurfaceVertInfo(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber);

			SendStringToNotepad(psInfoString, va("%s_%s_vertinfo.txt", Filename_WithoutPath(Filename_WithoutExt(Model_GetFilename(gTreeItemData.iModelHandle))), String_RemoveOccurences(Model_GetSurfaceName(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber), "*")));
		}
	}
	else
	{
		InfoBox(Model_GLMSurfaceInfo(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false));	// bShortVersionForTag
	}
}


void CMDXViewTreeView::OnGlmSurfaceOn()
{
	Model_GLMSurface_On(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber);
}


void CMDXViewTreeView::OnUpdateGlmSurfaceOn(CCmdUI *pCmdUI)
{
	SurfaceOnOff_t eOnOff = Model_GLMSurface_GetStatus(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber);
	pCmdUI->Enable(!(eOnOff == SURF_ON || eOnOff == SURF_INHERENTLYOFF));
}


void CMDXViewTreeView::OnGlmSurfaceOff()
{
	Model_GLMSurface_Off(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber);
}


void CMDXViewTreeView::OnUpdateGlmSurfaceOff(CCmdUI *pCmdUI)
{
	SurfaceOnOff_t eOnOff = Model_GLMSurface_GetStatus(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber);
	pCmdUI->Enable(!(eOnOff == SURF_OFF || eOnOff == SURF_INHERENTLYOFF));
}


void CMDXViewTreeView::OnGlmSurfaceNoDescendants()
{
	Model_GLMSurface_NoDescendants(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber);
}


void CMDXViewTreeView::OnUpdateGlmSurfaceNoDescendants(CCmdUI *pCmdUI)
{
	SurfaceOnOff_t eOnOff = Model_GLMSurface_GetStatus(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber);
	pCmdUI->Enable(!(eOnOff == SURF_NO_DESCENDANTS || eOnOff == SURF_INHERENTLYOFF));
}


void CMDXViewTreeView::OnGlmSurfaceSetAsRoot()
{
	Model_SetG2SurfaceRootOverride(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber);
}


void CMDXViewTreeView::OnUpdateGlmSurfaceSetAsRoot(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(Model_GetG2SurfaceRootOverride(gTreeItemData.iModelHandle) != gTreeItemData.iItemNumber);
}


void CMDXViewTreeView::OnGlmSurfaceClearRoot()
{
	Model_SetG2SurfaceRootOverride(gTreeItemData.iModelHandle, -1);
}


void CMDXViewTreeView::OnUpdateGlmSurfaceClearRoot(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(Model_GetG2SurfaceRootOverride(gTreeItemData.iModelHandle) == gTreeItemData.iItemNumber);
}


// this option is only available for tag surfaces, even though it's for the standard surface popup
//
void CMDXViewTreeView::OnGlmSurfaceBoltModelReplace()
{
	LPCSTR psCaption = va("Bolt model to surface-tag '%s'", Model_GetBoltName(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false));	// bBoltIsBone

	LPCSTR psFullPathedFilename = InputLoadFileName("",				// LPCSTR psInitialLoadName, 
		psCaption,		// LPCSTR psCaption,
		Filename_PathOnly(Model_GetFullPrimaryFilename()),	//	"S:\\baseq3\\models\\test\\bonehier",	// LPCSTR psInitialDir,
		Model_GetSupportedTypesFilter()			// LPCSTR psFilter
	);

	if (psFullPathedFilename)
	{
		Model_LoadBoltOn(psFullPathedFilename, gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false, true);	// bBoltIsBone, bBoltReplacesAllExisting
	}
}

// only enable this menu option if this surface is a tag...
//
void CMDXViewTreeView::OnUpdateGlmSurfaceBoltModelReplace(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(Model_SurfaceIsTag(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber));
}


void CMDXViewTreeView::OnGlmSurfaceBoltModelAdd()
{
	LPCSTR psCaption = va("Bolt additional model to surface-tag '%s'", Model_GetBoltName(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false));	// bBoltIsBone

	LPCSTR psFullPathedFilename = InputLoadFileName("",				// LPCSTR psInitialLoadName, 
		psCaption,		// LPCSTR psCaption,
		Filename_PathOnly(Model_GetFullPrimaryFilename()),	//	"S:\\baseq3\\models\\test\\bonehier",	// LPCSTR psInitialDir,
		Model_GetSupportedTypesFilter()			// LPCSTR psFilter
	);

	if (psFullPathedFilename)
	{
		Model_LoadBoltOn(psFullPathedFilename, gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false, false);	// bBoltIsBone, bBoltReplacesAllExisting
	}
}


void CMDXViewTreeView::OnUpdateGlmSurfaceBoltModelAdd(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(Model_SurfaceIsTag(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber));
}


// this option is only available for tag surfaces, even though it's for the standard surrface popup
//
void CMDXViewTreeView::OnGlmSurfaceDeleteAllBoltedModels()
{
	if (Model_DeleteBoltOn(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false, -1))	// bBoltIsBone
	{
		Invalidate(false);	// or some changed items on the tree don't redraw until you click on them
	}
}


// only enable this menu option if this surface is a tag, and has something bolted to it...
//
void CMDXViewTreeView::OnUpdateGlmSurfaceDeleteAllBoltedModels(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( Model_SurfaceIsTag(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber)
		&&
		Model_CountItemsBoltedHere(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false)
	);
}


void CMDXViewTreeView::OnUpdateGlmTagSurfaceTitle(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(va("Tag Surface:  %s", Model_GetSurfaceName(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber)));
}


void CMDXViewTreeView::OnGlmTagSurfaceInfo()
{
	InfoBox(Model_GLMSurfaceInfo(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true));	// bShortVersionForTag
}


void CMDXViewTreeView::OnGlmTagSurfaceBoltModelReplace()
{
//	OutputDebugString("on command\n");
	LPCSTR psCaption = va("Bolt model to surface-tag '%s'", Model_GetBoltName(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false));	// bBoltIsBone

	LPCSTR psFullPathedFilename = InputLoadFileName("",				// LPCSTR psInitialLoadName, 
		psCaption,		// LPCSTR psCaption,
		Filename_PathOnly(Model_GetFullPrimaryFilename()),	//	"S:\\baseq3\\models\\test\\bonehier",	// LPCSTR psInitialDir,
		Model_GetSupportedTypesFilter()			// LPCSTR psFilter
	);

	if (psFullPathedFilename)
	{
		Model_LoadBoltOn(psFullPathedFilename, gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false, true);	// bBoltIsBone, bBoltReplacesAllExisting
	}
}


void CMDXViewTreeView::OnGlmTagSurfaceBoltModelAdd()
{
//	OutputDebugString("on command\n");
	LPCSTR psCaption = va("Bolt additional model to surface-tag '%s'", Model_GetBoltName(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false));	// bBoltIsBone

	LPCSTR psFullPathedFilename = InputLoadFileName("",				// LPCSTR psInitialLoadName, 
		psCaption,		// LPCSTR psCaption,
		Filename_PathOnly(Model_GetFullPrimaryFilename()),	//	"S:\\baseq3\\models\\test\\bonehier",	// LPCSTR psInitialDir,
		Model_GetSupportedTypesFilter()			// LPCSTR psFilter
	);

	if (psFullPathedFilename)
	{
		Model_LoadBoltOn(psFullPathedFilename, gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false, false);	// bBoltIsBone, bBoltReplacesAllExisting
	}
}


void CMDXViewTreeView::OnGlmTagSurfaceDeleteAllBoltedModels()
{
	if (Model_DeleteBoltOn(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false, -1))
	{
		Invalidate(false);	// or some changed items on the tree don't redraw until you click on them
	}
}


void CMDXViewTreeView::OnUpdateGlmTagSurfaceDeleteAllBoltedModels(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(Model_CountItemsBoltedHere(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false));	// bBoltIsBone
}

void CMDXViewTreeView::OnG2SkinExpandAll()
{
	R_ApplyToTreeItem(ExpandTreeItem, ghTreeItem_RButtonMenu);
	GetTreeCtrl().SelectSetFirstVisible(ghTreeItem_RButtonMenu);
}


void CMDXViewTreeView::OnG2SkinValidate()
{
	Model_ValidateSkin(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber);
}

void CMDXViewTreeView::OnG2SkinsExpandAll()
{
	R_ApplyToTreeItem(ExpandTreeItem, ghTreeItem_RButtonMenu);
	GetTreeCtrl().SelectSetFirstVisible(ghTreeItem_RButtonMenu);
}


void CMDXViewTreeView::OnG2SkinsValidate()
{
	Model_ValidateSkin(gTreeItemData.iModelHandle, -1);
}


void CMDXViewTreeView::OnOldSkinValidate()
{
	Model_ValidateSkin(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber);
}


void CMDXViewTreeView::OnOldSkinApply()
{
	CString strSkin(GetTreeCtrl().GetItemText(ghTreeItem_RButtonMenu));
	Model_ApplyOldSkin(gTreeItemData.iModelHandle, strSkin);
}


void CMDXViewTreeView::OnOldSkinsValidate()
{
	Model_ValidateSkin(gTreeItemData.iModelHandle, -1);
}


void CMDXViewTreeView::OnShaderVariantApply()
{
	HTREEITEM hTreeItemMaterial = GetTreeCtrl().GetParentItem(ghTreeItem_RButtonMenu);
	HTREEITEM hTreeItemEthnic = GetTreeCtrl().GetParentItem(hTreeItemMaterial);
	HTREEITEM hTreeItemSkin = GetTreeCtrl().GetParentItem(hTreeItemEthnic);

	CString strMaterial(GetTreeCtrl().GetItemText(hTreeItemMaterial));
	CString strEthnic(GetTreeCtrl().GetItemText(hTreeItemEthnic));
	CString strSkin(GetTreeCtrl().GetItemText(hTreeItemSkin));

	int iVariant = gTreeItemData.iItemNumber;

	Model_ApplySkinShaderVariant(gTreeItemData.iModelHandle, strSkin, strEthnic, strMaterial, iVariant);
}


void CMDXViewTreeView::OnUpdateSeqTitle(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(va("Sequence:  %s", Model_Sequence_GetName(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber)));
}


void CMDXViewTreeView::OnSeqLock()
{
	Model_Sequence_Lock(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true);
}


void CMDXViewTreeView::OnUpdateSeqLock(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( !Model_Sequence_IsLocked(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true)
		&&
		!Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, true)
	);
}


void CMDXViewTreeView::OnSeqUnlock()
{
	Model_Sequence_UnLock(gTreeItemData.iModelHandle, true);
}


void CMDXViewTreeView::OnUpdateSeqUnlock(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( Model_Sequence_IsLocked(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true)
		&&
		!Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, true)
	);
}


void CMDXViewTreeView::OnSeqMultiLock()
{
	Model_MultiSeq_Add(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true);
}


void CMDXViewTreeView::OnUpdateSeqMultiLock(CCmdUI *pCmdUI)
{
	bool bActive = Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, true);
	int iNumSeqEntries = Model_MultiSeq_GetNumEntries(gTreeItemData.iModelHandle, true);

	if (bActive || iNumSeqEntries)
	{
		pCmdUI->SetText("Add to Multi-Lock sequences");
	}
	else
	{
		pCmdUI->SetText("Start Multi-Locking with this sequence");
	}

	pCmdUI->Enable( (bActive || !iNumSeqEntries)
		&&
		!Model_MultiSeq_AlreadyContains(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true)
	);
}


void CMDXViewTreeView::OnSeqMultiLockDelete()
{
	Model_MultiSeq_Delete(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true);
}


void CMDXViewTreeView::OnUpdateSeqMultiLockDelete(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, true)
		&&
		Model_MultiSeq_AlreadyContains(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, true)
	);
}


void CMDXViewTreeView::OnSeqLockSecondary()
{
	Model_Sequence_Lock(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false);
}


void CMDXViewTreeView::OnUpdateSeqLockSecondary(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( Model_SecondaryAnimLockingActive(gTreeItemData.iModelHandle)
		&&
		!Model_Sequence_IsLocked(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false)
		&&
		!Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, false)
	);
}


void CMDXViewTreeView::OnSeqUnlockSecondary()
{
	Model_Sequence_UnLock(gTreeItemData.iModelHandle, false);
}


void CMDXViewTreeView::OnUpdateSeqUnlockSecondary(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( Model_SecondaryAnimLockingActive(gTreeItemData.iModelHandle)
		&&
		Model_Sequence_IsLocked(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false)
		&&
		!Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, false)
	);
}


void CMDXViewTreeView::OnSeqMultiLockSecondary()
{
	Model_MultiSeq_Add(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false);
}


void CMDXViewTreeView::OnUpdateSeqMultiLockSecondary(CCmdUI *pCmdUI)
{
	bool bActive = Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, false);
	int iNumSeqEntries = Model_MultiSeq_GetNumEntries(gTreeItemData.iModelHandle, false);

	if (bActive || iNumSeqEntries)
	{
		pCmdUI->SetText("Add to Secondary Multi-Lock sequences");
	}
	else
	{
		pCmdUI->SetText("Start Secondary Multi-Locking with this sequence");
	}
	pCmdUI->Enable( Model_SecondaryAnimLockingActive(gTreeItemData.iModelHandle)
		&&
		(bActive || !iNumSeqEntries)
		&&
		!Model_MultiSeq_AlreadyContains(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false)
	);
}


void CMDXViewTreeView::OnSeqMultiLockSecondaryDelete()
{
	Model_MultiSeq_Delete(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false);
}


void CMDXViewTreeView::OnUpdateSeqMultiLockSecondaryDelete(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, false)
		&&
		Model_MultiSeq_AlreadyContains(gTreeItemData.iModelHandle, gTreeItemData.iItemNumber, false)
	);
}


void CMDXViewTreeView::OnSeqsViewFullPath()
{
	AppVars.bFullPathsInSequenceTreeitems = !AppVars.bFullPathsInSequenceTreeitems;

	R_ApplyToTreeItem(ReEvalSequenceText, GetTreeCtrl().GetRootItem()/* ghTreeItem_RButtonMenu */);
}


void CMDXViewTreeView::OnSeqsSortAlphabetically()
{
	AppVars.bSortSequencesByAlpha = !AppVars.bSortSequencesByAlpha;

	ModelTree_InsertSequences(gTreeItemData.iModelHandle, ghTreeItem_RButtonMenu);
}


void CMDXViewTreeView::OnUpdateSeqsSortAlphabetically(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bSortSequencesByAlpha);
}


void CMDXViewTreeView::OnSeqsUnlockAll()
{
	Model_Sequence_UnLock(gTreeItemData.iModelHandle, true);
	Model_Sequence_UnLock(gTreeItemData.iModelHandle, false);
	Model_MultiSeq_SetActive(gTreeItemData.iModelHandle, true, false);
	Model_MultiSeq_SetActive(gTreeItemData.iModelHandle, false, false);
}


void CMDXViewTreeView::OnUpdateSeqsUnlockAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( !Model_Sequence_IsLocked(gTreeItemData.iModelHandle, -1, true)
		||
		(
			Model_SecondaryAnimLockingActive(gTreeItemData.iModelHandle)
			&&
			!Model_Sequence_IsLocked(gTreeItemData.iModelHandle, -1, false)
		)
		||
		Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, true)
		||
		Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, false)
	);
}


void CMDXViewTreeView::OnSeqsUnlockPrimary()
{
	Model_Sequence_UnLock(gTreeItemData.iModelHandle, true);
}


void CMDXViewTreeView::OnUpdateSeqsUnlockPrimary(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( !Model_Sequence_IsLocked(gTreeItemData.iModelHandle, -1, true)
		&&
		!Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, true)
	);
}


void CMDXViewTreeView::OnSeqsUnlockSecondary()
{
	Model_Sequence_UnLock(gTreeItemData.iModelHandle, false);
}


void CMDXViewTreeView::OnUpdateSeqsUnlockSecondary(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( Model_SecondaryAnimLockingActive(gTreeItemData.iModelHandle)
		&&
		!Model_Sequence_IsLocked(gTreeItemData.iModelHandle, -1, false)
		&&
		!Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, false)
	);
}


void CMDXViewTreeView::OnMultiSeqsUnlockPrimary()
{
	Model_MultiSeq_SetActive(gTreeItemData.iModelHandle, true, !Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, true));
}


void CMDXViewTreeView::OnUpdateMultiSeqsUnlockPrimary(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, true));
}


void CMDXViewTreeView::OnSeqsDeleteLastPrimary()
{
	Model_MultiSeq_DeleteLast(gTreeItemData.iModelHandle, true);
}


void CMDXViewTreeView::OnUpdateSeqsDeleteLastPrimary(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, true)
		&&
		Model_MultiSeq_GetNumEntries(gTreeItemData.iModelHandle, true)
	);
}


void CMDXViewTreeView::OnSeqsDeleteAllPrimary()
{
	Model_MultiSeq_Clear(gTreeItemData.iModelHandle, true);
}


void CMDXViewTreeView::OnUpdateSeqsDeleteAllPrimary(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, true)
		&&
		Model_MultiSeq_GetNumEntries(gTreeItemData.iModelHandle, true)
	);
}


void CMDXViewTreeView::OnMultiSeqsUnlockSecondary()
{
	Model_MultiSeq_SetActive(gTreeItemData.iModelHandle, false, !Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, false));
}


void CMDXViewTreeView::OnUpdateMultiSeqsUnlockSecondary(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, false));
	pCmdUI->Enable(Model_SecondaryAnimLockingActive(gTreeItemData.iModelHandle));
}


void CMDXViewTreeView::OnSeqsDeleteLastSecondary()
{
	Model_MultiSeq_DeleteLast(gTreeItemData.iModelHandle, false);
}


void CMDXViewTreeView::OnUpdateSeqsDeleteLastSecondary(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, false)
		&&
		Model_MultiSeq_GetNumEntries(gTreeItemData.iModelHandle, false)
	);
}


void CMDXViewTreeView::OnSeqsDeleteAllSecondary()
{
	Model_MultiSeq_Clear(gTreeItemData.iModelHandle, false);
}


void CMDXViewTreeView::OnUpdateSeqsDeleteAllSecondary(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( Model_MultiSeq_IsActive(gTreeItemData.iModelHandle, false)
		&&
		Model_MultiSeq_GetNumEntries(gTreeItemData.iModelHandle, false)
	);
}


void CMDXViewTreeView::OnTreeSurfacesExpandAll()
{
	R_ApplyToTreeItem(ExpandTreeItem, ghTreeItem_RButtonMenu);
	GetTreeCtrl().SelectSetFirstVisible(ghTreeItem_RButtonMenu);
}


void CMDXViewTreeView::OnTreeSurfacesFind()
{
	LPCSTR psSearch = GetString("Enter Surface name to search for...\n\n( Case insensitive, partial strings ok )");

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


void CMDXViewTreeView::OnTreeSurfacesFindNext()
{
	// TODO: Add your command handler code here
}


void CMDXViewTreeView::OnTreeSurfacesFindPrev()
{
	// TODO: Add your command handler code here
}


void CMDXViewTreeView::OnTreeSurfacesAllDefaultoffOff()
{
	CWaitCursor wait;	// this function takes a while, because it loop-calls a function that normally only
						//	gets called occasionally, and re-evaluates the tree text

	R_ApplyToTreeItem(DisableTreeItemDefaultOFFSurface, ghTreeItem_RButtonMenu);
	Invalidate(false);
}


void CMDXViewTreeView::OnUpdateTreeSurfacesAllDefaultoffOff(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// not sure if this is worth filling in, maybe later
}


void CMDXViewTreeView::OnTreeSurfacesAllDefaultoffOn()
{
	CWaitCursor wait;	// this function takes a while, because it loop-calls a function that normally only
						//	gets called occasionally, and re-evaluates the tree text

	R_ApplyToTreeItem(EnableTreeItemDefaultOFFSurface, ghTreeItem_RButtonMenu);
	Invalidate(false);
}


void CMDXViewTreeView::OnUpdateTreeSurfacesAllDefaultoffOn(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// not sure if this is worth filling in, maybe later
}


void CMDXViewTreeView::OnTreeSurfacesAllDefaultoffDefault()
{
	CWaitCursor wait;	// this function takes a while, because it loop-calls a function that normally only
						//	gets called occasionally, and re-evaluates the tree text

	R_ApplyToTreeItem(DefaultTreeItemDefaultOFFSurface, ghTreeItem_RButtonMenu);
	Invalidate(false);
}


void CMDXViewTreeView::OnTreeSurfacesClearRoot()
{
	Model_SetG2SurfaceRootOverride(gTreeItemData.iModelHandle, -1);
}


void CMDXViewTreeView::OnUpdateTreeSurfacesClearRoot(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(Model_GetG2SurfaceRootOverride(gTreeItemData.iModelHandle) != -1);
}


void CMDXViewTreeView::OnTreeTagSurfacesExpandAll()
{
	R_ApplyToTreeItem(ExpandTreeItem, ghTreeItem_RButtonMenu);
	GetTreeCtrl().SelectSetFirstVisible(ghTreeItem_RButtonMenu);
}
