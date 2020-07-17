
// MDXViewView.h : interface of the CMDXViewView class
//

#pragma once

#include "trackball.h"

// Include the OpenGL headers
#include "GLView.h"



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
	//{{AFX_MSG(CMDXViewView)
	afx_msg void OnDestroy();
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

private:
	CGLView* m_pGLView;

public:
	virtual void OnInitialUpdate();


};

#ifndef _DEBUG  // debug version in MDXViewView.cpp
inline CMDXViewDoc* CMDXViewView::GetDocument() const
   { return reinterpret_cast<CMDXViewDoc*>(m_pDocument); }
#endif

