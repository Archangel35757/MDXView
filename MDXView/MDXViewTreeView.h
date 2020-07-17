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
	afx_msg void OnTreeModelUnboltme();
	afx_msg void OnTreeModelExpandall();
	afx_msg void OnTreeModelCollapseall();
	afx_msg void OnTreeModelFindany();


	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void R_ApplyToTreeItem(void(*pFunction) (HTREEITEM hTreeItem), HTREEITEM hTreeItem, bool bProcessSiblings = false, bool bSkipProcessingOfInitialItem = false);
	static void ExpandTreeItem(HTREEITEM hTreeItem);
	static void CollapseTreeItem(HTREEITEM hTreeItem);
	static void SearchTreeItem(HTREEITEM hTreeItem);


public:
	BOOL	  DeleteAllItems();
	HTREEITEM InsertItem(LPCTSTR psName, HTREEITEM hParent, UINT32 uiUserData = NULL, HTREEITEM hInsertAfter = TVI_LAST);
	HTREEITEM GetRootItem();


	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


extern CMDXViewTreeView* gMDXViewTreeViewHandle;
LPCSTR GetString(LPCSTR psPrompt, LPCSTR psDefault = NULL, bool bLowerCaseTheResult = true);


