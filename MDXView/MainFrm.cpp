
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "includes.h"

#include "MDXView.h"
#include "MDXViewDoc.h"
#include "MDXViewView.h"
#include "MDXViewTreeView.h"
#include "model.h"

#include "SOF2NPCViewer.h"
#include "splash.h"
#include "files.h"
#include "r_common.h"

#include <SDL.h>

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
			sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers


extern bool gbMainFrameInitialised;
extern bool gbSplashScreenRunning;
void CMainFrame::StatusMessage(LPCTSTR psMessage)
{
	if (this && gbMainFrameInitialised)
	{
		extern int giGalleryItemsRemaining;
		//m_wndStatusBar.SetWindowText((psMessage && psMessage[0]) ? psMessage : (Gallery_Active() ? va("( Gallery: %d remaining )", giGalleryItemsRemaining) : "Ready"));
	}
	else
	{
		if (gbSplashScreenRunning)
		{
			CSplashWnd::StatusMessage(psMessage);
		}
	}
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	//calculate client size 
	CRect cr;
	GetClientRect(&cr);

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	//return m_mainSplitter.Create(this, 1, 2, CSize(100, 100), pContext);
	if (!m_mainSplitter.CreateStatic(this, 1, 2))
	{
		MessageBox("Error setting up splitter frames!",
			"Init Error!", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// The views for each pane must be created 
	if (!m_mainSplitter.CreateView(0, 0, RUNTIME_CLASS(CMDXViewTreeView),
		CSize(cr.Width() / 5, cr.Height()), pContext))
	{
		MessageBox("Error setting up splitter view", "ERROR", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	if (!m_mainSplitter.CreateView(0, 1, RUNTIME_CLASS(CMDXViewView),
		CSize(cr.Width(), cr.Height()), pContext))
	{
		MessageBox("Error setting up splitter view", "ERROR", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//change flag to show splitter created
	m_bInitSplitter = true;

	//return TRUE instead of the parent method since that would not show our window
	return TRUE;
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	CRect cr;
	GetWindowRect(&cr);

	if (m_bInitSplitter && nType != SIZE_MINIMIZED)
	{
		m_mainSplitter.SetRowInfo(0, cy, 0);
		m_mainSplitter.SetColumnInfo(0, cr.Width() / 2, 50);
		m_mainSplitter.SetColumnInfo(1, cr.Width() / 2, 50);

		m_mainSplitter.RecalcLayout();
	}
}
