
// MDXViewView.cpp : implementation of the CMDXViewView class
//

#include "stdafx.h"
#include "includes.h"
#include <string>
#include <mmsystem.h>  // for timeGettime()

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MDXView.h"
#endif

#include "MDXViewDoc.h"
#include "MDXViewTreeView.h"
#include "text.h"
#include "drag.h"
#include "wintalk.h"
#include "textures.h"
#include "sof2npcviewer.h"	// for gallery stuff
#include "clipboard.h"		// for clipboard

#include "MDXViewView.h"

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

		m_TimerHandle_Update100FPS = SetTimer(	th_100FPS,	// UINT nIDEvent, 
												10,			// UINT nElapse, (in milliseconds)
												NULL		// void (CALLBACK EXPORT* lpfnTimer)(HWND, UINT, UINT, DWORD) 
		);

		if (!m_TimerHandle_Update100FPS)
		{
			ErrorBox("Warning: no Timer available for CMDXViewView update!");
		}

		CRect rect;
		GetClientRect(&rect);
		m_pGLView->m_iViewWidth = rect.Width();
		m_pGLView->m_iViewHeight = rect.Height();
		m_pGLView->Resize(rect.Width(), rect.Height());

		m_pGLView->PrepareScene(m_pGLView->m_hDC);
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

	if (m_pGLView->m_hGLRC && m_pGLView->m_hDC)
	{
		if (wglMakeCurrent(m_pGLView->m_hDC, m_pGLView->m_hGLRC))
		{
			ModelList_Render(m_pGLView->m_iViewWidth, m_pGLView->m_iViewHeight);

			SwapBuffers(pDC->GetSafeHdc());
			//VERIFY(wglMakeCurrent(m_hDC,NULL));
		}
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

BOOL CMDXViewView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	g_iScreenWidth = 0;
	g_iScreenHeight = 0;
	m_TimerHandle_Update100FPS = 0;

	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


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


int Sys_Milliseconds(void)
{
	static bool bInitialised = false;
	static int sys_timeBase;

	int sys_curtime;

	if (!bInitialised)
	{
		sys_timeBase = timeGetTime();
		bInitialised = true;
	}
	sys_curtime = timeGetTime() - sys_timeBase;

	return sys_curtime;
}

float GetFloatTime(void)
{
	float fTime = (float)Sys_Milliseconds() / 1000.0f;	// reduce to game-type seconds

	return fTime;
}


// should be called roughly at 100 times per second... (which is enough for our needs when lerping is factored in)
//
int giGalleryItemsRemaining = 0;	// declared here so StatusMessage can reference it (which is pretty tacky.... again).
CString strGalleryErrors;
CString strGalleryWarnings;
CString strGalleryInfo;

void Gallery_AddError(LPCSTR psText)
{
	strGalleryErrors += psText;
}
void Gallery_AddInfo(LPCSTR psText)
{
	strGalleryInfo += psText;
}
void Gallery_AddWarning(LPCSTR psText)
{
	strGalleryWarnings += psText;
}


void CMDXViewView::OnTimer(UINT nIDEvent)
{
	if (nIDEvent != th_100FPS)
	{
		CView::OnTimer(nIDEvent);
		return;
	}


	// otherwise, it's one of our timer events, so...


	{ // new bit, poll the remote control stuff 10 times per second (it's also done in OnIdle(), but that's not always fast enough when animating)
		static	float fTime = 0.0f;
		float fTimeNow = GetFloatTime();

#define UPDATE_FRAMES_PER_SECOND 10.0f

		if (fTimeNow - fTime > 1.0f / UPDATE_FRAMES_PER_SECOND)
		{
			fTime = fTimeNow;
			//			OutputDebugString(va("Time = %f seconds\n",GetFloatTime()));

			if (WinTalk_HandleMessages())
			{
				// app exit requested
				AppVars.bAnimate = qfalse;	// groan... stop the animation so the app doesn't spend all it's time
											//				in the render loop. This allows the App::OnIdle() version
											//				of the Wintalk_HandleMessages() handler to get a look in,
											//				and therefore spot that an exit is being requested.
			}
		}
	}

	//	if (!DraggingMouse()) 
	{
		if (ModelList_Animation())
		{
			// one or more models have updated frames (or lerping)...
			//
			Invalidate(false);
		}
	}


	if (Gallery_Active())
	{
		extern bool gbInRenderer;
		if (!gbInRenderer)
		{
			static bool bAlreadyHere = false;
			if (!bAlreadyHere)	// jic.
			{
				bAlreadyHere = true;

				extern int giRenderCount;
				static CString strCaption;
				static CString strScript;

				static bool bSnapshotTakingPlace = false;
				if (!bSnapshotTakingPlace)
				{
					int iRemainingPlusOne = GalleryRead_ExtractEntry(strCaption, strScript);
					if (iRemainingPlusOne)	// because 0 would be fail/empty
					{
						giGalleryItemsRemaining = iRemainingPlusOne - 1;
						StatusMessage(va("( Gallery: %d remaining )", giGalleryItemsRemaining));
						OutputDebugString(va("\"%s\" (script len %d)\n", (LPCSTR)strCaption, strScript.GetLength()));

						strScript += "\n";

						string strOutputFileName(va("%s\\%s", scGetTempPath(), "temp.mvs"));

						int iReturn = SaveFile(strOutputFileName.c_str(), (LPCSTR)strScript, strScript.GetLength());
						if (iReturn != -1)
						{
							extern bool Document_ModelLoadPrimary(LPCSTR psFilename);
							if (Document_ModelLoadPrimary(strOutputFileName.c_str()))
							{
								if (Model_Loaded())
								{
									ModelHandle_t hModel = AppVars.Container.hModel;

									Model_Sequence_Lock(hModel, Gallery_GetSeqToLock(), true, false);
								}

								giRenderCount = 0;
								bSnapshotTakingPlace = true;
							}
						}
					}
					else
					{
						// all done...
						//
						gbTextInhibit = false;
						Gallery_Done();
						StatusMessage(NULL);
						//
						// report...
						//
						CString strReport;

						if (!strGalleryErrors.IsEmpty())
						{
							strReport += "====================== Errors: ===================\n\n";
							strReport += strGalleryErrors;
							strReport += "\n\n";
						}

						if (!strGalleryWarnings.IsEmpty())
						{
							strReport += "====================== Warnings: ===================\n\n";
							strReport += strGalleryWarnings;
							strReport += "\n\n";
						}

						if (!strGalleryInfo.IsEmpty())
						{
							strReport += "====================== Info: ===================\n\n";
							strReport += strGalleryInfo;
							strReport += "\n\n";
						}

						if (!strReport.IsEmpty())
						{
							strReport.Insert(0, "The following messages appeared during gallery-snapshots....\n\n");
						}
						else
						{
							strReport = va("All gallery-snapshots done\n\nOutput dir was: \"%s\\n", Gallery_GetOutputDir());
						}

						SendStringToNotepad(strReport, "gallery_report.txt");
					}
				}
				else
				{
					if (giRenderCount == 2)	// ... so it's rendered to back buffer for snapshot, and front for user
					{
						//
						// generate a filename...
						//				
						char sOutputFileName[MAX_PATH];
						CString strBaseName(strCaption);
						while (strBaseName.Replace("\t", " "));
						while (strBaseName.Replace("  ", " "));
						sprintf(&sOutputFileName[0], "%s\\%s.bmp", Gallery_GetOutputDir(), (LPCTSTR)strBaseName);
						ScreenShot(sOutputFileName,/*strCaption*/strBaseName);
						BMP_Free();

						bSnapshotTakingPlace = false;	// trigger next snapshot
					}
					else
					{
						Invalidate(false);	// cause another screen update until render count satisfied
					}
				}

				bAlreadyHere = false;
			}
		}
	}
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