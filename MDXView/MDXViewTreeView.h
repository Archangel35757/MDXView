// MDXViewTreeView.h : header file
//

#pragma once


// CMDXViewTreeView view

class CMDXViewTreeView : public CTreeView
{
protected:
	CMDXViewTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMDXViewTreeView)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();

// Implementation
protected:
	virtual ~CMDXViewTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void UpdateUI(CMenu* pMenu);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMDXViewTreeView)
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTreeModelInfo();
	afx_msg void OnTreeModelUnboltMe();
	afx_msg void OnUpdateTreeModelUnboltMe(CCmdUI *pCmdUI);
	afx_msg void OnTreeModelExpandAll();
	afx_msg void OnTreeModelCollapseAll();
	afx_msg void OnTreeModelFindAny();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTreeBonesExpandAll();
	afx_msg void OnBonesFind();
	afx_msg void OnBonesClearSecondaryAnim();
	afx_msg void OnUpdateBonesClearSecondaryAnim(CCmdUI *pCmdUI);
	afx_msg void OnEthnicExpandAll();
	afx_msg void OnEthnicApplySkin();
	afx_msg void OnEthnicApplySkinSurfacePrefs();
	afx_msg void OnUpdateEthnicApplySkinSurfacePrefs(CCmdUI *pCmdUI);
	afx_msg void OnEthnicApplySkinSurfaceDefaults();
	afx_msg void OnUpdateGlmBoneTitle(CCmdUI *pCmdUI);
	afx_msg void OnGlmBoneInfo();
	afx_msg void OnGlmBoneBoltModelReplace();
	afx_msg void OnGlmBoneBoltModelAdd();
	afx_msg void OnGlmBoneDeleteAllBoltedModels();
	afx_msg void OnUpdateGlmBoneDeleteAllBoltedModels(CCmdUI *pCmdUI);
	afx_msg void OnGlmBoneSecondaryAnimStart();
	afx_msg void OnUpdateGlmBoneSecondaryAnimStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGlmSurfaceTitle(CCmdUI *pCmdUI);
	afx_msg void OnGlmSurfaceInfo();
	afx_msg void OnGlmSurfaceOn();
	afx_msg void OnUpdateGlmSurfaceOn(CCmdUI *pCmdUI);
	afx_msg void OnGlmSurfaceOff();
	afx_msg void OnUpdateGlmSurfaceOff(CCmdUI *pCmdUI);
	afx_msg void OnGlmSurfaceNoDescendants();
	afx_msg void OnUpdateGlmSurfaceNoDescendants(CCmdUI *pCmdUI);
	afx_msg void OnGlmSurfaceSetAsRoot();
	afx_msg void OnUpdateGlmSurfaceSetAsRoot(CCmdUI *pCmdUI);
	afx_msg void OnGlmSurfaceClearRoot();
	afx_msg void OnUpdateGlmSurfaceClearRoot(CCmdUI *pCmdUI);
	afx_msg void OnGlmSurfaceBoltModelReplace();
	afx_msg void OnUpdateGlmSurfaceBoltModelReplace(CCmdUI *pCmdUI);
	afx_msg void OnGlmSurfaceBoltModelAdd();
	afx_msg void OnUpdateGlmSurfaceBoltModelAdd(CCmdUI *pCmdUI);
	afx_msg void OnGlmSurfaceDeleteAllBoltedModels();
	afx_msg void OnUpdateGlmSurfaceDeleteAllBoltedModels(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGlmTagSurfaceTitle(CCmdUI *pCmdUI);
	afx_msg void OnGlmTagSurfaceInfo();
	afx_msg void OnGlmTagSurfaceBoltModelReplace();
	afx_msg void OnGlmTagSurfaceBoltModelAdd();
	afx_msg void OnGlmTagSurfaceDeleteAllBoltedModels();
	afx_msg void OnUpdateGlmTagSurfaceDeleteAllBoltedModels(CCmdUI *pCmdUI);
	afx_msg void OnG2SkinExpandAll();
	afx_msg void OnG2SkinValidate();
	afx_msg void OnG2SkinsExpandAll();
	afx_msg void OnG2SkinsValidate();
	afx_msg void OnOldSkinValidate();
	afx_msg void OnOldSkinApply();
	afx_msg void OnOldSkinsValidate();
	afx_msg void OnShaderVariantApply();
	afx_msg void OnUpdateSeqTitle(CCmdUI *pCmdUI);
	afx_msg void OnSeqLock();
	afx_msg void OnUpdateSeqLock(CCmdUI *pCmdUI);
	afx_msg void OnSeqUnlock();
	afx_msg void OnUpdateSeqUnlock(CCmdUI *pCmdUI);
	afx_msg void OnSeqMultiLock();
	afx_msg void OnUpdateSeqMultiLock(CCmdUI *pCmdUI);
	afx_msg void OnSeqMultiLockDelete();
	afx_msg void OnUpdateSeqMultiLockDelete(CCmdUI *pCmdUI);
	afx_msg void OnSeqLockSecondary();
	afx_msg void OnUpdateSeqLockSecondary(CCmdUI *pCmdUI);
	afx_msg void OnSeqUnlockSecondary();
	afx_msg void OnUpdateSeqUnlockSecondary(CCmdUI *pCmdUI);
	afx_msg void OnSeqMultiLockSecondary();
	afx_msg void OnUpdateSeqMultiLockSecondary(CCmdUI *pCmdUI);
	afx_msg void OnSeqMultiLockSecondaryDelete();
	afx_msg void OnUpdateSeqMultiLockSecondaryDelete(CCmdUI *pCmdUI);
	afx_msg void OnSeqsViewFullPath();
	afx_msg void OnSeqsSortAlphabetically();
	afx_msg void OnUpdateSeqsSortAlphabetically(CCmdUI *pCmdUI);
	afx_msg void OnSeqsUnlockAll();
	afx_msg void OnUpdateSeqsUnlockAll(CCmdUI *pCmdUI);
	afx_msg void OnSeqsUnlockPrimary();
	afx_msg void OnUpdateSeqsUnlockPrimary(CCmdUI *pCmdUI);
	afx_msg void OnSeqsUnlockSecondary();
	afx_msg void OnUpdateSeqsUnlockSecondary(CCmdUI *pCmdUI);
	afx_msg void OnMultiSeqsUnlockPrimary();
	afx_msg void OnUpdateMultiSeqsUnlockPrimary(CCmdUI *pCmdUI);
	afx_msg void OnSeqsDeleteLastPrimary();
	afx_msg void OnUpdateSeqsDeleteLastPrimary(CCmdUI *pCmdUI);
	afx_msg void OnSeqsDeleteAllPrimary();
	afx_msg void OnUpdateSeqsDeleteAllPrimary(CCmdUI *pCmdUI);
	afx_msg void OnMultiSeqsUnlockSecondary();
	afx_msg void OnUpdateMultiSeqsUnlockSecondary(CCmdUI *pCmdUI);
	afx_msg void OnSeqsDeleteLastSecondary();
	afx_msg void OnUpdateSeqsDeleteLastSecondary(CCmdUI *pCmdUI);
	afx_msg void OnSeqsDeleteAllSecondary();
	afx_msg void OnUpdateSeqsDeleteAllSecondary(CCmdUI *pCmdUI);
	afx_msg void OnTreeSurfacesExpandAll();
	afx_msg void OnTreeSurfacesFind();
	afx_msg void OnTreeSurfacesFindNext();
	afx_msg void OnTreeSurfacesFindPrev();
	afx_msg void OnTreeSurfacesAllDefaultoffOff();
	afx_msg void OnUpdateTreeSurfacesAllDefaultoffOff(CCmdUI *pCmdUI);
	afx_msg void OnTreeSurfacesAllDefaultoffOn();
	afx_msg void OnUpdateTreeSurfacesAllDefaultoffOn(CCmdUI *pCmdUI);
	afx_msg void OnTreeSurfacesAllDefaultoffDefault();
	afx_msg void OnTreeSurfacesClearRoot();
	afx_msg void OnUpdateTreeSurfacesClearRoot(CCmdUI *pCmdUI);
	afx_msg void OnTreeTagSurfacesExpandAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void R_ApplyToTreeItem(void(*pFunction) (HTREEITEM hTreeItem), HTREEITEM hTreeItem, bool bProcessSiblings = false, bool bSkipProcessingOfInitialItem = false);
	static void ExpandTreeItem(HTREEITEM hTreeItem);
	static void CollapseTreeItem(HTREEITEM hTreeItem);
	static void SearchTreeItem(HTREEITEM hTreeItem);
	static void ReEvalSequenceText(HTREEITEM hTreeItem);
	static void SetTreeItemSurfaceState(HTREEITEM hTreeItem, bool bOnOff, bool bDefaultAll);
	static void EnableTreeItemDefaultOFFSurface(HTREEITEM hTreeItem);
	static void DisableTreeItemDefaultOFFSurface(HTREEITEM hTreeItem);
	static void DefaultTreeItemDefaultOFFSurface(HTREEITEM hTreeItem);


public:
	BOOL	  DeleteAllItems();
	HTREEITEM InsertItem(LPCTSTR psName, HTREEITEM hParent, UINT32 uiUserData = NULL, HTREEITEM hInsertAfter = TVI_LAST);
	HTREEITEM GetRootItem();

};


extern CMDXViewTreeView* gMDXViewTreeViewHandle;
LPCSTR GetString(LPCSTR psPrompt, LPCSTR psDefault = NULL, bool bLowerCaseTheResult = true);


