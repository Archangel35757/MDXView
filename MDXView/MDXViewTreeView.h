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

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL DeleteAllItems();
	HTREEITEM InsertItem(LPCTSTR psName, HTREEITEM hParent, UINT32 uiUserData = NULL, HTREEITEM hInsertAfter = TVI_LAST);
	HTREEITEM GetRootItem();



};


extern CMDXViewTreeView* gMDXViewTreeViewHandle;
LPCSTR GetString(LPCSTR psPrompt, LPCSTR psDefault = NULL, bool bLowerCaseTheResult = true);


