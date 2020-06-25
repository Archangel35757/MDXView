
// MDXViewView.cpp : implementation of the CMDXViewView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MDXView.h"
#endif

#include "MDXViewDoc.h"
#include "MDXViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMDXViewView

IMPLEMENT_DYNCREATE(CMDXViewView, CView)

BEGIN_MESSAGE_MAP(CMDXViewView, CView)
END_MESSAGE_MAP()

// CMDXViewView construction/destruction

CMDXViewView::CMDXViewView()
{
	// TODO: add construction code here

}

CMDXViewView::~CMDXViewView()
{
}

BOOL CMDXViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style &= ~WS_HSCROLL;
	cs.style &= ~WS_VSCROLL;

	return CView::PreCreateWindow(cs);
}

// CMDXViewView drawing

void CMDXViewView::OnDraw(CDC* /*pDC*/)
{
	CMDXViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMDXViewView diagnostics

#ifdef _DEBUG
void CMDXViewView::AssertValid() const
{
	CView::AssertValid();
}

void CMDXViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDXViewDoc* CMDXViewView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDXViewDoc)));
	return (CMDXViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CMDXViewView message handlers
