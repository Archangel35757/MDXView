
// MDXViewView.cpp : implementation of the CMDXViewView class
//

#include "stdafx.h"
#include "includes.h"
#include <mmsystem.h>  // for timeGettime()

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MDXView.h"
#endif

#include "MDXViewDoc.h"
#include "MDXViewView.h"
#include "drag.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool DraggingMouse();

int g_iScreenWidth = 0;
int g_iScreenHeight = 0;
int g_iViewAreaMouseX = 0;
int g_iViewAreaMouseY = 0;


// CMDXViewView

IMPLEMENT_DYNCREATE(CMDXViewView, CView)

BEGIN_MESSAGE_MAP(CMDXViewView, CView)
	//{{AFX_MSG_MAP(CMDXViewView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZING()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CMDXViewView construction/destruction

CMDXViewView::CMDXViewView()
{
	// TODO: add construction code here
	m_pGLView = new CGLView();
}

CMDXViewView::~CMDXViewView()
{
	if (m_pGLView)
	{
		delete m_pGLView;
	}
}

BOOL CMDXViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CS_OWNDC);
	cs.style &= ~WS_HSCROLL;
	cs.style &= ~WS_VSCROLL;

	return CView::PreCreateWindow(cs);
}

// CMDXViewView InitialUpdate
void CMDXViewView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	if (m_pGLView)
	{
		m_pGLView->SetWindow(GetSafeHwnd());
		m_pGLView->SetupGLContext(true);

		CRect rect;
		GetClientRect(&rect);
		m_pGLView->m_iViewWidth = rect.Width();
		m_pGLView->m_iViewHeight = rect.Height();
		m_pGLView->Resize(rect.Width(), rect.Height());

		//CDC* pDC = GetDC();
		m_pGLView->PrepareScene(m_pGLView->m_hDC);
		//ReleaseDC(pDC);
	}
}

// CMDXViewView Drawing

void CMDXViewView::OnDraw(CDC* pDC)
{
	CMDXViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	if (m_pGLView)
	{
		m_pGLView->RenderScene();
	}
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


int CMDXViewView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void CMDXViewView::OnDestroy()
{	
	CView::OnDestroy();
	// TODO: Add your message handler code here
//	CDC* pDC = GetDC();
	m_pGLView->DestroyScene();
//	ReleaseDC(pDC);
}


void CMDXViewView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_pGLView)
	{
		m_pGLView->Resize(cx, cy);
		g_iScreenWidth = cx;
		g_iScreenHeight = cy;
	}
	
}


void CMDXViewView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	CView::OnPrepareDC(pDC, pInfo);
}

BOOL CMDXViewView::OnEraseBkgnd(CDC* pDC)
{
	//This prevents the window from flickering
	return TRUE;

	//return CView::OnEraseBkgnd(pDC);
}


void CMDXViewView::OnSizing(UINT fwSide, LPRECT pRect)
{
	CView::OnSizing(fwSide, pRect);

	// TODO: Add your message handler code here
}


void CMDXViewView::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnTimer(nIDEvent);
}


bool sys_rbuttondown = false;
bool sys_lbuttondown = false;
bool sys_mbuttondown = false;
bool DraggingMouse()
{
	return !!(sys_rbuttondown || sys_lbuttondown || sys_mbuttondown);
}

POINT DragStartPoint;

void CMDXViewView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	GetCursorPos(&DragStartPoint);

	start_drag((mkey_enum)nFlags, DragStartPoint.x, DragStartPoint.y);
	SetCapture();
	ShowCursor(false);
	sys_lbuttondown = true;

//	CView::OnLButtonDown(nFlags, point);
}


void CMDXViewView::OnLButtonUp(UINT nFlags, CPoint point)
{
//	CView::OnLButtonUp(nFlags, point);

	if (sys_lbuttondown)
	{
		ReleaseCapture();
		ShowCursor(true);
		end_drag((mkey_enum)nFlags, point.x, point.y);
		sys_lbuttondown = false;
	}
}


void CMDXViewView::OnMButtonDown(UINT nFlags, CPoint point)
{
	GetCursorPos(&DragStartPoint);

	start_drag((mkey_enum)nFlags, DragStartPoint.x, DragStartPoint.y);
	SetCapture();
	ShowCursor(false);
	sys_mbuttondown = true;

//	CView::OnMButtonDown(nFlags, point);
}


void CMDXViewView::OnMButtonUp(UINT nFlags, CPoint point)
{
//	CView::OnMButtonUp(nFlags, point);

	if (sys_mbuttondown)
	{
		ReleaseCapture();
		ShowCursor(true);
		end_drag((mkey_enum)nFlags, point.x, point.y);
		sys_mbuttondown = false;
	}
}


void CMDXViewView::OnRButtonDown(UINT nFlags, CPoint point)
{
	GetCursorPos(&DragStartPoint);

	start_drag((mkey_enum)nFlags, DragStartPoint.x, DragStartPoint.y);
	SetCapture();
	ShowCursor(false);
	sys_rbuttondown = true;

//	CView::OnRButtonDown(nFlags, point);
}


void CMDXViewView::OnRButtonUp(UINT nFlags, CPoint point)
{
//	CView::OnRButtonUp(nFlags, point);

	if (sys_rbuttondown)
	{
		ReleaseCapture();
		ShowCursor(true);
		end_drag((mkey_enum)nFlags, point.x, point.y);
		sys_rbuttondown = false;
	}
}


void CMDXViewView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnRButtonDblClk(nFlags, point);
}


void CMDXViewView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);

	GetCursorPos(&point);

	if (!DraggingMouse())
	{
		ScreenToClient(&point);
		g_iViewAreaMouseX = point.x;
		g_iViewAreaMouseY = point.y;
		return;
	}


	static int _i = 0;
	//	OutputDebugString(va("(%d):   x:(%d) y:(%d)   (dragstart: %d %d)\n",_i++,point.x,point.y, DragStartPoint.x,DragStartPoint.y));

	if (drag((mkey_enum)nFlags, point.x, point.y))
	{
		SetCursorPos(DragStartPoint.x, DragStartPoint.y);
		//OutputDebugString("drag-painting\n");
		Invalidate(false);
		//UpdateWindow();		
	}
}


BOOL CMDXViewView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// wheel down = -ve, wheel up = +ve zDelta (test vals were +/-120, but just check sign)
	//
	OutputDebugString(va("zDelta = %d\n", zDelta));
	AppVars.zDelta = zDelta;
	AppVars.bMouseWheel = true;
	drag((mkey_enum)nFlags, pt.x, pt.y);
	Invalidate(true);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}