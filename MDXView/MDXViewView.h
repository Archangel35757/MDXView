
// MDXViewView.h : interface of the CMDXViewView class
//

#pragma once
#include <SDL.h>

// Include the OpenGL headers



class CMDXViewView : public CView
{
protected: // create from serialization only
	CMDXViewView();
	DECLARE_DYNCREATE(CMDXViewView)

// Attributes
public:
	CMDXViewDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMDXViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:



// Generated message map functions
protected:
	SDL_Window* m_sdlScreen;

	//{{AFX_MSG(CMDXViewView)
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()



};

#ifndef _DEBUG  // debug version in MDXViewView.cpp
inline CMDXViewDoc* CMDXViewView::GetDocument() const
   { return reinterpret_cast<CMDXViewDoc*>(m_pDocument); }
#endif

