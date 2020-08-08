
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "includes.h"
#include <mmsystem.h>

#include "MDXView.h"
#include "MDXViewDoc.h"
#include "MDXViewView.h"
#include "MDXViewTreeView.h"
#include "model.h"
#include "wintalk.h"
#include "text.h"
#include "clipboard.h"
#include "textures.h"
#include "script.h"
#include "image.h"

#include "SOF2NPCViewer.h"
#include "splash.h"
#include "files.h"
#include "r_common.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static void XLS_To_SP(void);

#define PLAY_LAME_WAV							\
		if ( !PlaySound("k:\\util\\bhr_l.bin",	\
						NULL,					\
						SND_FILENAME|SND_ASYNC	\
						)						\
			)									\
		{										\
			/* error, but ignore that */		\
		}

////////////////////////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMainFrame::OnCbnSelchangeCombo1)
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
	ON_COMMAND(ID_FILE_BATCHCONVERT, &CMainFrame::OnFileBatchConvert)
	ON_COMMAND(ID_FILE_WRITEIDEAL, &CMainFrame::OnFileWriteIdeal)
	ON_COMMAND(ID_FILE_READIDEAL, &CMainFrame::OnFileReadIdeal)
	ON_COMMAND(ID_FILE_RESETVIEWPARAMS, &CMainFrame::OnFileResetViewParams)
	ON_COMMAND(ID_FILE_REFRESHTEXTURES, &CMainFrame::OnFileRefreshTextures)
	ON_COMMAND(ID_FILE_WRITESCRIPT, &CMainFrame::OnFileWriteScript)
	ON_UPDATE_COMMAND_UI(ID_FILE_WRITESCRIPT, &CMainFrame::OnUpdateFileWriteScript)
	ON_COMMAND(ID_FILE_READSCRIPT, &CMainFrame::OnFileReadScript)
	ON_COMMAND(ID_FILE_VIEW_SOF2_NPCS, &CMainFrame::OnFileViewSof2Npcs)
	ON_UPDATE_COMMAND_UI(ID_FILE_VIEW_SOF2_NPCS, &CMainFrame::OnUpdateFileViewSof2Npcs)
	ON_COMMAND(ID_FILE_VIEW_JK2_BOTS, &CMainFrame::OnFileViewJk2Bots)
	ON_COMMAND(ID_FILE_PRINT3D, &CMainFrame::OnFilePrint3D)

	ON_COMMAND(ID_EDIT_CUT, &CMainFrame::OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, &CMainFrame::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CMainFrame::OnEditPaste)
	ON_COMMAND(ID_EDIT_BKGRNDCOLOR, &CMainFrame::OnEditBkgrndColor)
	ON_COMMAND(ID_EDIT_WIRECOLOR, &CMainFrame::OnEditWireColor)
	ON_COMMAND(ID_EDIT_SETFLOOR_ABS, &CMainFrame::OnEditSetfloorAbs)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SETFLOOR_ABS, &CMainFrame::OnUpdateEditSetfloorAbs)
	ON_COMMAND(ID_EDIT_SETFLOOR_CURRENT, &CMainFrame::OnEditSetfloorCurrent)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SETFLOOR_CURRENT, &CMainFrame::OnUpdateEditSetfloorCurrent)
	ON_COMMAND(ID_EDIT_SET_BONE_WEIGHT_THRESHOLD, &CMainFrame::OnEditSetBoneWeightThreshold)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SET_BONE_WEIGHT_THRESHOLD, &CMainFrame::OnUpdateEditSetBoneWeightThreshold)
	ON_COMMAND(ID_EDIT_ALLOWSKELETONOVERRIDES, &CMainFrame::OnEditAllowSkeletonOverrides)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ALLOWSKELETONOVERRIDES, &CMainFrame::OnUpdateEditAllowSkeletonOverrides)
	ON_COMMAND(IDM_EDIT_TOPMOST, &CMainFrame::OnEditTopmost)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_TOPMOST, &CMainFrame::OnUpdateEditTopmost)

	ON_COMMAND(ID_VIEW_WIREFRAME, &CMainFrame::OnViewWireframe)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WIREFRAME, &CMainFrame::OnUpdateViewWireframe)
	ON_COMMAND(ID_VIEW_ALPHA, &CMainFrame::OnViewAlpha)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALPHA, &CMainFrame::OnUpdateViewAlpha)
	ON_COMMAND(ID_VIEW_BILINEAR, &CMainFrame::OnViewBilinear)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BILINEAR, &CMainFrame::OnUpdateViewBilinear)
	ON_COMMAND(ID_VIEW_INTERPOLATE, &CMainFrame::OnViewInterpolate)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INTERPOLATE, &CMainFrame::OnUpdateViewInterpolate)
	ON_COMMAND(ID_VIEW_ORIGIN, &CMainFrame::OnViewOrigin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ORIGIN, &CMainFrame::OnUpdateViewOrigin)
	ON_COMMAND(ID_VIEW_ORIGINS_AS_RGB, &CMainFrame::OnViewOriginsAsRGB)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ORIGINS_AS_RGB, &CMainFrame::OnUpdateViewOriginsAsRGB)
	ON_COMMAND(ID_VIEW_BONE_HILITE, &CMainFrame::OnBoneHilite)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BONE_HILITE, &CMainFrame::OnUpdateBoneHilite)
	ON_COMMAND(ID_VIEW_BONE_WEIGHT_FILTERING, &CMainFrame::OnViewBoneWeightFiltering)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BONE_WEIGHT_FILTERING, &CMainFrame::OnUpdateViewBoneWeightFiltering)
	ON_COMMAND(ID_VIEW_WIRE_OVERLAY_SURF_HILITE, &CMainFrame::OnViewWireOverlaySurfHilite)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WIRE_OVERLAY_SURF_HILITE, &CMainFrame::OnUpdateViewWireOverlaySurfHilite)
	ON_COMMAND(ID_VIEW_SURFACEHILITEWITHBONEREFS, &CMainFrame::OnViewSurfaceHiliteWithBoneRefs)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SURFACEHILITEWITHBONEREFS, &CMainFrame::OnUpdateViewSurfaceHiliteWithBoneRefs)
	ON_COMMAND(ID_VIEW_VERTEX_BONE_WEIGHTING, &CMainFrame::OnViewVertexBoneWeighting)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VERTEX_BONE_WEIGHTING, &CMainFrame::OnUpdateViewVertexBoneWeighting)
	ON_COMMAND(ID_VIEW_TRIANGLE_INDEXES, &CMainFrame::OnViewTriangleIndexes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TRIANGLE_INDEXES, &CMainFrame::OnUpdateViewTriangleIndexes)
	ON_COMMAND(ID_VIEW_VERTEX_INDEXES, &CMainFrame::OnViewVertexIndexes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VERTEX_INDEXES, &CMainFrame::OnUpdateViewVertexIndexes)
	ON_COMMAND(ID_VIEW_NORMALS, &CMainFrame::OnViewNormals)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NORMALS, &CMainFrame::OnUpdateViewNormals)
	ON_COMMAND(ID_VIEW_TAG_SURFACES, &CMainFrame::OnViewTagSurfaces)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TAG_SURFACES, &CMainFrame::OnUpdateViewTagSurfaces)
	ON_COMMAND(ID_VIEW_RULER, &CMainFrame::OnViewRuler)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RULER, &CMainFrame::OnUpdateViewRuler)
	ON_COMMAND(ID_VIEW_BBOX, &CMainFrame::OnViewBbox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BBOX, &CMainFrame::OnUpdateViewBbox)
	ON_COMMAND(ID_VIEW_FLOOR, &CMainFrame::OnViewFloor)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FLOOR, &CMainFrame::OnUpdateViewFloor)
	ON_COMMAND(ID_VIEW_FORCE_WHITE, &CMainFrame::OnViewForceWhite)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FORCE_WHITE, &CMainFrame::OnUpdateViewForceWhite)
	ON_COMMAND(ID_VIEW_UVSEAMS_OPEN_EDGES, &CMainFrame::OnViewUVSeamsOpenEdges)
	ON_UPDATE_COMMAND_UI(ID_VIEW_UVSEAMS_OPEN_EDGES, &CMainFrame::OnUpdateViewUVSeamsOpenEdges)
	ON_COMMAND(ID_VIEW_UNSHADOWABLESURFACES, &CMainFrame::OnViewUnshadowableSurfaces)
	ON_UPDATE_COMMAND_UI(ID_VIEW_UNSHADOWABLESURFACES, &CMainFrame::OnUpdateViewUnshadowableSurfaces)
	ON_COMMAND(ID_VIEW_DOUBLESIDEDPOLYS, &CMainFrame::OnViewDoublesidedPolys)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DOUBLESIDEDPOLYS, &CMainFrame::OnUpdateViewDoublesidedPolys)
	ON_COMMAND(ID_VIEW_VERTEX_COLOR, &CMainFrame::OnViewVertexColor)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VERTEX_COLOR, &CMainFrame::OnUpdateViewVertexColor)
	ON_COMMAND(ID_VIEW_UV_MAPPING, &CMainFrame::OnViewUVMapping)
	ON_UPDATE_COMMAND_UI(ID_VIEW_UV_MAPPING, &CMainFrame::OnUpdateViewUVMapping)
	ON_COMMAND(ID_VIEW_BONE_WEIGHTS, &CMainFrame::OnViewBoneWeights)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BONE_WEIGHTS, &CMainFrame::OnUpdateViewBoneWeights)
	ON_COMMAND(ID_VIEW_SCREENSHOT_FILE, &CMainFrame::OnViewScreenshotFile)
	ON_COMMAND(ID_VIEW_SCREENSHOTTOCLIPBOARD, &CMainFrame::OnViewScreenshotToClipboard)
	ON_COMMAND(ID_VIEW_SCREENSHOT_CLEAN, &CMainFrame::OnViewScreenshotClean)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SCREENSHOT_CLEAN, &CMainFrame::OnUpdateViewScreenshotClean)
	ON_COMMAND(ID_VIEW_FOVCYCLE, &CMainFrame::OnViewFovCycle)
	ON_COMMAND(ID_VIEW_LOD0, &CMainFrame::OnViewLod0)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOD0, &CMainFrame::OnUpdateViewLod0)
	ON_COMMAND(ID_VIEW_LOD1, &CMainFrame::OnViewLod1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOD1, &CMainFrame::OnUpdateViewLod1)
	ON_COMMAND(ID_VIEW_LOD2, &CMainFrame::OnViewLod2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOD2, &CMainFrame::OnUpdateViewLod2)
	ON_COMMAND(ID_VIEW_LOD3, &CMainFrame::OnViewLod3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOD3, &CMainFrame::OnUpdateViewLod3)
	ON_COMMAND(ID_VIEW_LOD4, &CMainFrame::OnViewLod4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOD4, &CMainFrame::OnUpdateViewLod4)
	ON_COMMAND(ID_VIEW_LOD5, &CMainFrame::OnViewLod5)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOD5, &CMainFrame::OnUpdateViewLod5)
	ON_COMMAND(ID_VIEW_LOD6, &CMainFrame::OnViewLod6)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOD6, &CMainFrame::OnUpdateViewLod6)
	ON_COMMAND(ID_VIEW_LOD7, &CMainFrame::OnViewLod7)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOD7, &CMainFrame::OnUpdateViewLod7)
	ON_COMMAND(ID_VIEW_LOD8, &CMainFrame::OnViewLod8)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOD8, &CMainFrame::OnUpdateViewLod8)
	ON_COMMAND(ID_VIEW_LOD9, &CMainFrame::OnViewLod9)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOD9, &CMainFrame::OnUpdateViewLod9)
	ON_COMMAND(ID_VIEW_PICMIP0, &CMainFrame::OnPicmip0)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PICMIP0, &CMainFrame::OnUpdatePicmip0)
	ON_COMMAND(ID_VIEW_PICMIP1, &CMainFrame::OnPicmip1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PICMIP1, &CMainFrame::OnUpdatePicmip1)
	ON_COMMAND(ID_VIEW_PICMIP2, &CMainFrame::OnPicmip2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PICMIP2, &CMainFrame::OnUpdatePicmip2)
	ON_COMMAND(ID_VIEW_PICMIP3, &CMainFrame::OnPicmip3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PICMIP3, &CMainFrame::OnUpdatePicmip3)
	ON_COMMAND(ID_VIEW_PICMIP4, &CMainFrame::OnPicmip4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PICMIP4, &CMainFrame::OnUpdatePicmip4)
	ON_COMMAND(ID_VIEW_PICMIP5, &CMainFrame::OnPicmip5)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PICMIP5, &CMainFrame::OnUpdatePicmip5)
	ON_COMMAND(ID_VIEW_PICMIP6, &CMainFrame::OnPicmip6)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PICMIP6, &CMainFrame::OnUpdatePicmip6)
	ON_COMMAND(ID_VIEW_PICMIP7, &CMainFrame::OnPicmip7)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PICMIP7, &CMainFrame::OnUpdatePicmip7)
	ON_COMMAND(ID_VIEW_GL_DRIVERINFO, &CMainFrame::OnViewGLDriverInfo)
	ON_COMMAND(ID_ANIMATION_START, &CMainFrame::OnAnimationStart)
	ON_COMMAND(ID_ANIMATION_STARTFORCEWRAP, &CMainFrame::OnAnimationStartForceWrap)
	ON_COMMAND(ID_ANIMATION_STOP, &CMainFrame::OnAnimationStop)
	ON_COMMAND(ID_ANIMATION_REWIND, &CMainFrame::OnAnimationRewind)
	ON_COMMAND(ID_ANIMATION_ENDFRAME, &CMainFrame::OnAnimationEndFrame)
	ON_COMMAND(ID_ANIMATION_PREVFRAME, &CMainFrame::OnAnimationPrevFrame)
	ON_COMMAND(ID_ANIMATION_NEXTFRAME, &CMainFrame::OnAnimationNextFrame)
	ON_COMMAND(ID_ANIMATION_FASTER, &CMainFrame::OnAnimationFaster)
	ON_COMMAND(ID_ANIMATION_SLOWER, &CMainFrame::OnAnimationSlower)
	ON_COMMAND(ID_ANIMATION_LERPING, &CMainFrame::OnAnimationLerping)
	ON_UPDATE_COMMAND_UI(ID_ANIMATION_LERPING, &CMainFrame::OnUpdateAnimationLerping)
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
	m_bmpToolbarHi.DeleteObject();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if ( !m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME) )
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

	// ===========================================================
	m_bmpToolbarHi.LoadBitmap(IDB_TOOLBARHI);
	m_wndToolBar.SetBitmap((HBITMAP)m_bmpToolbarHi);
	// ===========================================================

	//**********************************	
	//the width of the combo box
	#define COMBOBOX_WIDTH 175 
	CRect rect(0, 0, 0, 0);
	GetClientRect(rect);

	//set up the ComboBox control as a snap mode select box
	//
	//First get the index of the placeholder's position in the toolbar
	int index = 0;
	while (m_wndToolBar.GetItemID(index) != ID_VIEW_MATERIAL_MAP) index++;

	//next convert that button to a seperator and get its position
	m_wndToolBar.SetButtonInfo(index, ID_VIEW_MATERIAL_MAP, TBBS_SEPARATOR, COMBOBOX_WIDTH);
	m_wndToolBar.GetItemRect(index, &rect);

	//expand the rectangle to allow the combo box room to drop down
	rect.top += 2;
	rect.bottom += 200;

	HWND toolbarHWnd = m_wndToolBar.GetSafeHwnd();
	CWnd *parentCWnd = m_wndToolBar.GetSafeOwner(m_wndToolBar.GetOwner(), &toolbarHWnd);

	// then Create the combo box and show it
	if (!m_wndToolBar.m_wndComboBox.CreateEx(NULL, "ComboBox", NULL, WS_CHILD | WS_VISIBLE |
		CBS_DROPDOWNLIST | CBS_HASSTRINGS | CBS_AUTOHSCROLL,
		rect, &m_wndToolBar, IDC_COMBO1))
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}

	m_wndToolBar.m_wndComboBox.ShowWindow(SW_SHOW);

	m_wndToolBar.m_wndComboBox.AddString("Default Lit");
	m_wndToolBar.m_wndComboBox.AddString("Diffuse Color");
	m_wndToolBar.m_wndComboBox.AddString("Specular Color");
	m_wndToolBar.m_wndComboBox.AddString("Normal/Displacement");
	m_wndToolBar.m_wndComboBox.AddString("Ambient Occlusion");
	m_wndToolBar.m_wndComboBox.AddString("Roughness/Gloss");
	m_wndToolBar.m_wndComboBox.AddString("Metalness");
	m_wndToolBar.m_wndComboBox.AddString("Reflectance");

	CString str;
	CSize	sz;
	CDC* pDC = m_wndToolBar.m_wndComboBox.GetDC();

	m_wndToolBar.m_wndComboBox.GetLBText(0, str);
	sz = pDC->GetTextExtent(str);
	m_wndToolBar.m_wndComboBox.SetItemHeight(-1, 29);

	/*
	CFont font;
	VERIFY(font.CreateFont(
	14,                       // nHeight
	0,                        // nWidth
	0,                        // nEscapement
	0,                        // nOrientation
	FW_NORMAL,                // nWeight
	FALSE,                    // bItalic
	FALSE,                    // bUnderline
	0,                        // cStrikeOut
	ANSI_CHARSET,             // nCharSet
	OUT_DEFAULT_PRECIS,       // nOutPrecision
	CLIP_DEFAULT_PRECIS,      // nClipPrecision
	DEFAULT_QUALITY,          // nQuality
	DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
	_T("Tahoma")));            // lpszFacename

	m_wndToolBar.m_wndComboBox.SetFont(&font);

	font.DeleteObject();
	*/

	m_wndToolBar.m_wndComboBox.SetSeparator(0);
	m_wndToolBar.m_wndComboBox.SetSepLineStyle(PS_SOLID);
	m_wndToolBar.m_wndComboBox.SetHorizontalMargin(1);

	m_wndToolBar.m_wndComboBox.SetCurSel(0);

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

	// set the active pane to the MDXViewView pane
	m_mainSplitter.SetActivePane(0, 1);

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


afx_msg void CMainFrame::OnCbnSelchangeCombo1(void)
{
	int nSel = m_wndToolBar.m_wndComboBox.GetCurSel();

	if (-1 != nSel)
	{
		CString str;
		m_wndToolBar.m_wndComboBox.GetLBText(nSel, str);
		AfxMessageBox("Selected: " + str, MB_OK);
	}

	return;
}


//////////////////////////////////
// FILE MENU
//////////////////////////////////
void CMainFrame::OnFileOpen()
{
	LPCSTR psFullPathedFilename = InputLoadFileName("",		// LPCSTR psInitialLoadName, 
		"Load Model",										// LPCSTR psCaption,
		Filename_PathOnly(Model_GetFullPrimaryFilename()),	//	"S:\\baseq3\\models\\test\\bonehier",	// LPCSTR psInitialDir, 
		Model_GetSupportedTypesFilter(true)					// LPCSTR psFilter
	);

	if (psFullPathedFilename)
	{
		GetActiveDocument()->OnOpenDocument(psFullPathedFilename);
	}
}


#define sJK3BASEDIR "c:\\ja\\base\\"
void CMainFrame::OnFileBatchConvert()
{
	LPCSTR psBasePathToCopy = sJK3BASEDIR;
	if (!GetYesNo("Warning: base path not known yet, shall I assume ' " sJK3BASEDIR " ' ?"))
	{
		psBasePathToCopy = GetString("Enter suitable base path\n\n( format example: \"" sJK3BASEDIR "\" )");
		if (!psBasePathToCopy)
			return;
	}

	// Scan for list of available .GLM files
	char **ppsGLMFiles;
	int iGLMFiles;

	ppsGLMFiles =	//ri.FS_ListFiles( "shaders", ".shader", &iSkinFiles );
		Sys_ListFiles(psBasePathToCopy,		// const char *directory, 
			"/",		// const char *extension, 
			"*.glm",		// char *filter, 
			&iGLMFiles,	// int *numfiles, 
			qfalse		// qboolean wantsubs 
		);

	if (!iGLMFiles)
	{
		WarningBox(va("WARNING: no GLM files found in '%s'\n", psBasePathToCopy));
		return;
	}

	for (int i = 0; i<iGLMFiles; i++)
	{
		char sFileName[128];

		string strThisGLMFile(ppsGLMFiles[i]);

		Com_sprintf(sFileName, sizeof(sFileName), "%s%s", psBasePathToCopy, strThisGLMFile.c_str());
		StatusMessage(va("Scanning GLM file %d/%d: \"%s\"...", i + 1, iGLMFiles, sFileName));

		// Load in this GLM file
		GetActiveDocument()->OnOpenDocument(sFileName);

		// Save compressed GLM file
		StatusMessage(va("Saving compressed GLM file %d/%d: \"%s\"...", i + 1, iGLMFiles, sFileName));
		Model_Save(sFileName);
	}

	Sys_FreeFileList(ppsGLMFiles);
}


void CMainFrame::OnFileWriteIdeal()
{
	if (GetYesNo(va("Write \"<modelname>.ideal\" file\n\nAre you sure?")))
	{
		AppVars_WriteIdeal();
	}
}


void CMainFrame::OnFileReadIdeal()
{
	AppVars_ReadIdeal();
}


void CMainFrame::OnFileResetViewParams()
{
	AppVars_ResetViewParams();
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnFileRefreshTextures()
{
	TextureList_Refresh();
	m_mainSplitter.Invalidate(false);
}


extern void Filename_AddToMRU(LPCSTR psFilename);
void CMainFrame::OnFileWriteScript()
{
	LPCSTR psFullPathedFilename = InputSaveFileName(va("%s%s", Filename_WithoutExt(Model_GetFullPrimaryFilename()), Script_GetExtension()),	// LPCSTR psInitialSaveName, 
		"Write Script",			// LPCSTR psCaption, 
		Filename_PathOnly(Model_GetFullPrimaryFilename()),	//LPCSTR psInitialPath,
		Script_GetFilter(),		// LPCSTR psFilter
		Script_GetExtension()	// LPCSTR psExtension
	);
	if (psFullPathedFilename)
	{
		CWaitCursor wait;

		if (Script_Write(psFullPathedFilename))
		{
			Filename_AddToMRU(psFullPathedFilename);
		}
	}
}


void CMainFrame::OnUpdateFileWriteScript(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(Model_Loaded());
}


void CMainFrame::OnFileReadScript()
{
	LPCSTR psFullPathedFilename = InputLoadFileName("",				// LPCSTR psInitialLoadName, 
		"Read Script",	// LPCSTR psCaption,
		Filename_PathOnly(Model_GetFullPrimaryFilename()),	//	"S:\\baseq3\\models\\test\\bonehier",	// LPCSTR psInitialDir, 
		Script_GetFilter()			// LPCSTR psFilter
	);
	if (psFullPathedFilename)
	{
		CWaitCursor wait;

		if (Script_Read(psFullPathedFilename))
		{
			Filename_AddToMRU(psFullPathedFilename);
		}
	}
}


#define sSOF2BASEDIR "d:\\basesof2\\"
void CMainFrame::OnFileViewSof2Npcs()
{
	if (!gamedir[0])
	{
		LPCSTR psBasePathToCopy = sSOF2BASEDIR;
		if (!GetYesNo("Warning: base path not known yet, shall I assume ' " sSOF2BASEDIR " ' ?"))
		{
			psBasePathToCopy = GetString("Enter suitable base path\n\n( format example: \"" sSOF2BASEDIR "\" )");
			if (!psBasePathToCopy)
				return;
		}

		strcpy(gamedir, psBasePathToCopy);
	}

	CString strScript;
	CSOF2NPCViewer Viewer(true, &strScript, gamedir);

	Model_StopAnim();	// or the screen update stops the GDI stuff from showing up

	if (Viewer.DoModal() == IDOK)
	{
		if (Gallery_Active())
		{
			// pick this up in the timer loop now...
			//
			//			CString strCaption;
			//			while (GalleryRead_ExtractEntry(strCaption, strScript))
			//			{
			//				OutputDebugString(va("\"%s\" (script len %d)\n",(LPCSTR)strCaption,strScript.GetLength()));
			//			}
			extern CString strGalleryErrors;
			extern CString strGalleryWarnings;
			extern CString strGalleryInfo;

			strGalleryErrors = strGalleryWarnings = strGalleryInfo = "";
			Model_StopAnim();
			gbTextInhibit = AppVars.bCleanScreenShots;	//true;
			return;
		}
		else
		{
			// normal double-click on a single template list entry...
			//
			if (!strScript.IsEmpty())
			{
				strScript += "\n\n\n";
				//SendStringToNotepad(strScript,"temp.txt");

				string strOutputFileName(va("%s\\%s", scGetTempPath(), "temp.mvs"));

				int iReturn = SaveFile(strOutputFileName.c_str(), (LPCSTR)strScript, strScript.GetLength());
				if (iReturn != -1)
				{
					extern bool Document_ModelLoadPrimary(LPCSTR psFilename);
					Document_ModelLoadPrimary(strOutputFileName.c_str());
				}
			}
		}
	}
}


void CMainFrame::OnUpdateFileViewSof2Npcs(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}


#define sJK2BASEDIR "d:\\base\\"
void CMainFrame::OnFileViewJk2Bots()
{
	if (!gamedir[0])
	{
		LPCSTR psBasePathToCopy = sJK2BASEDIR;
		if (!GetYesNo("Warning: base path not known yet, shall I assume ' " sJK2BASEDIR " ' ?"))
		{
			psBasePathToCopy = GetString("Enter suitable base path\n\n( format example: \"" sJK2BASEDIR "\" )");
			if (!psBasePathToCopy)
				return;
		}

		strcpy(gamedir, psBasePathToCopy);
	}

	CString strScript;
	CSOF2NPCViewer Viewer(false, &strScript, gamedir);

	Model_StopAnim();	// or the screen update stops the GDI stuff from showing up

	if (Viewer.DoModal() == IDOK)
	{
		if (Gallery_Active())
		{
			// pick this up in the timer loop now...
			//
			//			CString strCaption;
			//			while (GalleryRead_ExtractEntry(strCaption, strScript))
			//			{
			//				OutputDebugString(va("\"%s\" (script len %d)\n",(LPCSTR)strCaption,strScript.GetLength()));
			//			}
			extern CString strGalleryErrors;
			extern CString strGalleryWarnings;
			extern CString strGalleryInfo;

			strGalleryErrors = strGalleryWarnings = strGalleryInfo = "";
			Model_StopAnim();
			gbTextInhibit = AppVars.bCleanScreenShots;	//true;
			return;
		}
		else
		{
			// normal double-click on a single template list entry...
			//
			if (!strScript.IsEmpty())
			{
				strScript += "\n\n\n";
				//SendStringToNotepad(strScript,"temp.txt");

				string strOutputFileName(va("%s\\%s", scGetTempPath(), "temp.mvs"));

				int iReturn = SaveFile(strOutputFileName.c_str(), (LPCSTR)strScript, strScript.GetLength());
				if (iReturn != -1)
				{
					extern bool Document_ModelLoadPrimary(LPCSTR psFilename);
					Document_ModelLoadPrimary(strOutputFileName.c_str());
				}
			}
		}
	}
}


void CMainFrame::OnFilePrint3D()
{
	AfxMessageBox(ID_FILE_PRINT3D);
	// TODO: Add your command handler code here

}


///////////////////////////////
// EDIT MENU
///////////////////////////////
void CMainFrame::OnEditCut()
{
	// TODO: Add your command handler code here
}


void CMainFrame::OnEditCopy()
{
	OnViewScreenshotToClipboard();
}


void CMainFrame::OnEditPaste()
{
	// TODO: Add your command handler code here
}


void CMainFrame::OnEditBkgrndColor()
{
	CHOOSECOLOR cc;
	static COLORREF  crefs[16];

	memset(&cc, 0, sizeof(cc));

	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = AppVars.hWnd;

	cc.lpCustColors = crefs;
	cc.rgbResult = AppVars._B << 16 | AppVars._G << 8 | AppVars._R;	//  COLORREF     rgbResult; 
	cc.Flags = CC_RGBINIT | CC_ANYCOLOR | CC_SOLIDCOLOR | /*CC_FULLOPEN | */ 0;

	if (ChooseColor(&cc))
	{
		DWORD d = cc.rgbResult;
		AppVars._B = (cc.rgbResult >> 16) & 0xFF;
		AppVars._G = (cc.rgbResult >> 8) & 0xFF;
		AppVars._R = (cc.rgbResult >> 0) & 0xFF;

		m_mainSplitter.Invalidate(false);
	}
}


void CMainFrame::OnEditWireColor()
{
	CHOOSECOLOR cc;
	static COLORREF  crefs[16];

	memset(&cc, 0, sizeof(cc));

	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = AppVars.hWnd;

	cc.lpCustColors = crefs;
	cc.rgbResult = AppVars._Bwire << 16 | AppVars._Gwire << 8 | AppVars._Rwire;	//  COLORREF     rgbResult; 
	cc.Flags = CC_RGBINIT | CC_ANYCOLOR | CC_SOLIDCOLOR | /*CC_FULLOPEN | */ 0;

	if (ChooseColor(&cc))
	{
		DWORD d = cc.rgbResult;
		AppVars._Bwire = (cc.rgbResult >> 16) & 0xFF;
		AppVars._Gwire = (cc.rgbResult >> 8) & 0xFF;
		AppVars._Rwire = (cc.rgbResult >> 0) & 0xFF;

		m_mainSplitter.Invalidate(false);
	}
}


void CMainFrame::OnEditSetfloorAbs()
{
	LPCSTR psPrompt = "Input new floor value, e.g. \"-50\"";
	LPCSTR psFloorZ = GetString(psPrompt);

	if (psFloorZ)
	{
		AppVars.fFloorZ = atof(psFloorZ);
		m_mainSplitter.Invalidate(false);
	}
}


void CMainFrame::OnUpdateEditSetfloorAbs(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(AppVars.bFloor && Model_Loaded());
}


void CMainFrame::OnEditSetfloorCurrent()
{
	AppVars.fFloorZ = Model_GetLowestPointOnPrimaryModel();
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateEditSetfloorCurrent(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(AppVars.bFloor && Model_Loaded());
}


void CMainFrame::OnEditSetBoneWeightThreshold()
{
	bool bAgain = true;

	do
	{
		LPCSTR psPrompt = "Input new bone-weight-threshhold percentage, e.g. \"50\", which will cause all bone-weights below that value to be ignored\n\n( Input must be within the range 0..100 )";
		LPCSTR psPercent = GetString(psPrompt);

		if (psPercent)
		{
			AppVars.fBoneWeightThreshholdPercent = atof(psPercent);
			if (AppVars.fBoneWeightThreshholdPercent < 0.0f
				||
				AppVars.fBoneWeightThreshholdPercent > 100.0f
				)
			{
				PLAY_LAME_WAV;
				ErrorBox(va("%f is not within the range 0..100 now, is it?\n\nDuh!!!!!!!!!!!", AppVars.fBoneWeightThreshholdPercent));
			}
			else
			{
				bAgain = false;
				m_mainSplitter.Invalidate(false);
			}
		}
	} while (bAgain);
}


void CMainFrame::OnUpdateEditSetBoneWeightThreshold(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(AppVars.bBoneWeightThreshholdingActive && Model_Loaded());	//model_loaded check not nec., but matches others on menu
}


void CMainFrame::OnEditAllowSkeletonOverrides()
{
	AppVars.bAllowGLAOverrides = !AppVars.bAllowGLAOverrides;
}


void CMainFrame::OnUpdateEditAllowSkeletonOverrides(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bAllowGLAOverrides);
}


void CMainFrame::OnEditTopmost()
{
	AppVars.bAlwaysOnTop = !AppVars.bAlwaysOnTop;

	SetWindowPos(AppVars.bAlwaysOnTop ? &wndTopMost : &wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}


void CMainFrame::OnUpdateEditTopmost(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bAlwaysOnTop);
}


/////////////////////////////////////
// VIEW MENU
/////////////////////////////////////
void CMainFrame::OnViewWireframe()
{
	AppVars.bWireFrame = !AppVars.bWireFrame;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewWireframe(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bWireFrame);
}


void CMainFrame::OnViewAlpha()
{
	AppVars.bUseAlpha = !AppVars.bUseAlpha;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewAlpha(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bUseAlpha);
}


void CMainFrame::OnViewBilinear()
{
	AppVars.bBilinear = !AppVars.bBilinear;
	TextureList_SetFilter();
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewBilinear(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bBilinear);
}


void CMainFrame::OnViewInterpolate()
{
	AppVars.bInterpolate = !AppVars.bInterpolate;
	m_mainSplitter.Invalidate(false);
}

void CMainFrame::OnUpdateViewInterpolate(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bInterpolate);
}


void CMainFrame::OnViewOrigin()
{
	AppVars.bOriginLines = !AppVars.bOriginLines;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewOrigin(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bOriginLines);
}


void CMainFrame::OnViewOriginsAsRGB()
{
	AppVars.bShowOriginsAsRGB = !AppVars.bShowOriginsAsRGB;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewOriginsAsRGB(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bShowOriginsAsRGB);
}


void CMainFrame::OnBoneHilite()
{
	AppVars.bBoneHighlight = !AppVars.bBoneHighlight;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateBoneHilite(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bBoneHighlight);
}


void CMainFrame::OnViewBoneWeightFiltering()
{
	AppVars.bBoneWeightThreshholdingActive = !AppVars.bBoneWeightThreshholdingActive;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewBoneWeightFiltering(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bBoneWeightThreshholdingActive);
}


void CMainFrame::OnViewWireOverlaySurfHilite()
{
	AppVars.bSurfaceHighlight = !AppVars.bSurfaceHighlight;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewWireOverlaySurfHilite(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bSurfaceHighlight);
}


void CMainFrame::OnViewSurfaceHiliteWithBoneRefs()
{
	AppVars.bSurfaceHighlightShowsBoneWeighting = !AppVars.bSurfaceHighlightShowsBoneWeighting;
	m_mainSplitter.Invalidate(false);
}


// only allow this option if surface highlighting is on...
void CMainFrame::OnUpdateViewSurfaceHiliteWithBoneRefs(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(AppVars.bSurfaceHighlight);
	pCmdUI->SetCheck(AppVars.bSurfaceHighlightShowsBoneWeighting);
}


void CMainFrame::OnViewBoneWeights()
{
	// TODO: Add your command handler code here
}


void CMainFrame::OnUpdateViewBoneWeights(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}


void CMainFrame::OnViewTriangleIndexes()
{
	AppVars.bTriIndexes = !AppVars.bTriIndexes;
	m_mainSplitter.Invalidate(false);
}


// only allow this option if surface highlighting is on...
void CMainFrame::OnUpdateViewTriangleIndexes(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(AppVars.bSurfaceHighlight);
	pCmdUI->SetCheck(AppVars.bTriIndexes);
}


void CMainFrame::OnViewVertexIndexes()
{
	AppVars.bVertIndexes = !AppVars.bVertIndexes;
	m_mainSplitter.Invalidate(false);
}


// only allow this option if surface highlighting is on...
void CMainFrame::OnUpdateViewVertexIndexes(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(AppVars.bSurfaceHighlight);
	pCmdUI->SetCheck(AppVars.bVertIndexes);
}


void CMainFrame::OnViewVertexBoneWeighting()
{
	AppVars.bVertWeighting = !AppVars.bVertWeighting;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewVertexBoneWeighting(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bVertWeighting);
	pCmdUI->Enable(AppVars.bVertIndexes);
}


void CMainFrame::OnViewNormals()
{
	AppVars.bVertexNormals = !AppVars.bVertexNormals;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewNormals(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bVertexNormals);
}


void CMainFrame::OnViewTagSurfaces()
{
	AppVars.bShowTagSurfaces = !AppVars.bShowTagSurfaces;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewTagSurfaces(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bShowTagSurfaces);
}


void CMainFrame::OnViewRuler()
{
	AppVars.bRuler = !AppVars.bRuler;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewRuler(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bRuler);
}


void CMainFrame::OnViewBbox()
{
	AppVars.bBBox = !AppVars.bBBox;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewBbox(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bBBox);
}


void CMainFrame::OnViewFloor()
{
	AppVars.bFloor = !AppVars.bFloor;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewFloor(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bFloor);
}


void CMainFrame::OnViewForceWhite()
{
	AppVars.bForceWhite = !AppVars.bForceWhite;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewForceWhite(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bForceWhite);
}


void CMainFrame::OnViewUVSeamsOpenEdges()
{
	if (true/*!stricmp(scGetUserName(),"scork")*/)
	{
		AppVars.bUVSeamsHighlight = !AppVars.bUVSeamsHighlight;
		m_mainSplitter.Invalidate(false);
	}
}


void CMainFrame::OnUpdateViewUVSeamsOpenEdges(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bUVSeamsHighlight);
	pCmdUI->Enable(TRUE/*!stricmp(scGetUserName(),"scork")*/);
}


void CMainFrame::OnViewUnshadowableSurfaces()
{
	AppVars.bShowUnshadowableSurfaces = !AppVars.bShowUnshadowableSurfaces;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewUnshadowableSurfaces(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bShowUnshadowableSurfaces);
}


void CMainFrame::OnViewDoublesidedPolys()
{
	AppVars.bShowPolysAsDoubleSided = !AppVars.bShowPolysAsDoubleSided;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewDoublesidedPolys(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bShowPolysAsDoubleSided);
}


void CMainFrame::OnViewVertexColor()
{
	// TODO: Add your command handler code here
}


void CMainFrame::OnUpdateViewVertexColor(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}


void CMainFrame::OnViewUVMapping()
{
	// TODO: Add your command handler code here
}


void CMainFrame::OnUpdateViewUVMapping(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}


LPCSTR GetYearAsString(void)
{
	static char sTemp[20];
	time_t ltime;

	time(&ltime);

	struct tm *today = localtime(&ltime);

	strftime(sTemp, sizeof(sTemp), "%Y", today);

	return &sTemp[0];
}


void CMainFrame::OnViewScreenshotFile()
{
	if (Model_Loaded())
	{
		CWaitCursor wait;

		// slightly iffy here, I'm going to assume that the rendering context is still valid from last time.
		// I can't do much else because I need to supply DC shit that I don't have in order to issue an OnDraw
		//	command to do it legally, so fuck it...
		//
		gbTextInhibit = AppVars.bCleanScreenShots;	//true;
		{
			ModelList_Render(g_iScreenWidth, g_iScreenHeight);	// render to back buffer

																// generate a filename...
																//
			char sBaseName[MAX_PATH];
			sprintf(sBaseName, Filename_WithoutPath(Filename_PathOnly(Model_GetFullPrimaryFilename())));
			//
			// look for a numbered slot to snapshot to...
			//
#define NUM_SAVE_SLOTS 1000
			for (int iName = 0; iName<NUM_SAVE_SLOTS; iName++)
			{
				char sFilename[MAX_PATH];

				if (iName == NUM_SAVE_SLOTS)
				{
					ErrorBox(va("Couldn't find a free save slot! (tried %d slots)", NUM_SAVE_SLOTS));
				}

				sprintf(sFilename, "c:\\%s_%03d.bmp", sBaseName, iName);

				if (!FileExists(sFilename))
				{
					ScreenShot(sFilename, va("(C) Raven Software %s", GetYearAsString()));
					BMP_Free();
					break;
				}
			}
		}
		gbTextInhibit = false;
	}
	else
	{
		ErrorBox("No model loaded to work out path from!\n\n( So duhhhh... why try to take a snapshot? )");
	}

	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnViewScreenshotToClipboard()
{
	if (Model_Loaded())
	{
		CWaitCursor wait;

		// slightly iffy here, I'm going to assume that the rendering context is still valid from last time.
		// I can't do much else because I need to supply DC shit that I don't have in order to issue an OnDraw
		//	command to do it legally, so fuck it...
		//
		gbTextInhibit = AppVars.bCleanScreenShots;	//true;
		{
			ModelList_Render(g_iScreenWidth, g_iScreenHeight);	// render to back buffer

			ScreenShot(NULL, va("(C) Raven Software %s", GetYearAsString()));
		}
		gbTextInhibit = false;

		void *pvDIB;
		int iBytes;
		if (BMP_GetMemDIB(pvDIB, iBytes))
		{
			ClipBoard_SendDIB(pvDIB, iBytes);
		}
		BMP_Free();
	}

	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnViewScreenshotClean()
{
	AppVars.bCleanScreenShots = !AppVars.bCleanScreenShots;
}


void CMainFrame::OnUpdateViewScreenshotClean(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(AppVars.bCleanScreenShots);
}


void CMainFrame::OnViewFovCycle()
{
	AppVars.dFOV = (AppVars.dFOV == 10.0f) ? 80.0f : (AppVars.dFOV == 80.0f) ? 90 : 10.0f;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnViewLod0()
{
	AppVars.iLOD = 0;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewLod0(CCmdUI *pCmdUI)
{
	OnUpdateViewLod(pCmdUI, 0);
}


void CMainFrame::OnViewLod1()
{
	AppVars.iLOD = 1;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewLod1(CCmdUI *pCmdUI)
{
	OnUpdateViewLod(pCmdUI, 1);
}


void CMainFrame::OnViewLod2()
{
	AppVars.iLOD = 2;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewLod2(CCmdUI *pCmdUI)
{
	OnUpdateViewLod(pCmdUI, 2);
}


void CMainFrame::OnViewLod3()
{
	AppVars.iLOD = 3;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewLod3(CCmdUI *pCmdUI)
{
	OnUpdateViewLod(pCmdUI, 3);
}


void CMainFrame::OnViewLod4()
{
	AppVars.iLOD = 4;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewLod4(CCmdUI *pCmdUI)
{
	OnUpdateViewLod(pCmdUI, 4);
}


void CMainFrame::OnViewLod5()
{
	AppVars.iLOD = 5;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewLod5(CCmdUI *pCmdUI)
{
	OnUpdateViewLod(pCmdUI, 5);
}


void CMainFrame::OnViewLod6()
{
	AppVars.iLOD = 6;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewLod6(CCmdUI *pCmdUI)
{
	OnUpdateViewLod(pCmdUI, 6);
}


void CMainFrame::OnViewLod7()
{
	AppVars.iLOD = 7;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewLod7(CCmdUI *pCmdUI)
{
	OnUpdateViewLod(pCmdUI, 7);
}


void CMainFrame::OnViewLod8()
{
	AppVars.iLOD = 8;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewLod8(CCmdUI *pCmdUI)
{
	OnUpdateViewLod(pCmdUI, 8);
}


void CMainFrame::OnViewLod9()
{
	AppVars.iLOD = 9;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdateViewLod9(CCmdUI *pCmdUI)
{
	OnUpdateViewLod(pCmdUI, 9);
}


void CMainFrame::OnUpdateViewLod(CCmdUI *pCmdUI, int lod)
{
	if (Model_Loaded())
	{
		if (AppVars.Container.iNumLODs > lod)
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
	else
		pCmdUI->Enable(FALSE);
}


void CMainFrame::OnPicmip0()
{
	TextureList_ReMip(0);
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdatePicmip0(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(TextureList_GetMip() == 0);
}


void CMainFrame::OnPicmip1()
{
	TextureList_ReMip(1);
	m_mainSplitter.Invalidate(false);
}

void CMainFrame::OnUpdatePicmip1(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(TextureList_GetMip() == 1);
}

void CMainFrame::OnPicmip2()
{
	TextureList_ReMip(2);
	m_mainSplitter.Invalidate(false);
}

void CMainFrame::OnUpdatePicmip2(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(TextureList_GetMip() == 2);
}

void CMainFrame::OnPicmip3()
{
	TextureList_ReMip(3);
	m_mainSplitter.Invalidate(false);
}

void CMainFrame::OnUpdatePicmip3(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(TextureList_GetMip() == 3);
}

void CMainFrame::OnPicmip4()
{
	TextureList_ReMip(4);
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdatePicmip4(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(TextureList_GetMip() == 4);
}


void CMainFrame::OnPicmip5()
{
	TextureList_ReMip(5);
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdatePicmip5(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(TextureList_GetMip() == 5);
}


void CMainFrame::OnPicmip6()
{
	TextureList_ReMip(6);
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdatePicmip6(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(TextureList_GetMip() == 6);
}


void CMainFrame::OnPicmip7()
{
	TextureList_ReMip(7);
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnUpdatePicmip7(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(TextureList_GetMip() == 7);
}


void CMainFrame::OnViewGLDriverInfo()
{
	InfoBox(va("%s", GL_GetInfo()));
}


/////////////////////////////////////
// ANIMATION MENU
/////////////////////////////////////
void CMainFrame::OnAnimationStart()
{
	Model_StartAnim();
}


void CMainFrame::OnAnimationStartForceWrap()
{
	Model_StartAnim(true);
}


void CMainFrame::OnAnimationStop()
{
	Model_StopAnim();
}


void CMainFrame::OnAnimationRewind()
{
	ModelList_Rewind();
}


void CMainFrame::OnAnimationEndFrame()
{
	ModelList_GoToEndFrame();
}


void CMainFrame::OnAnimationPrevFrame()
{
	ModelList_StepFrame(-1);
}


void CMainFrame::OnAnimationNextFrame()
{
	ModelList_StepFrame(1);
}


void CMainFrame::OnAnimationFaster()
{
	AppVars.dAnimSpeed *= ANIM_FASTER;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnAnimationSlower()
{
	AppVars.dAnimSpeed *= ANIM_SLOWER;
	m_mainSplitter.Invalidate(false);
}


void CMainFrame::OnAnimationLerping()
{
	OnViewInterpolate();
}

void CMainFrame::OnUpdateAnimationLerping(CCmdUI *pCmdUI)
{
	OnUpdateViewInterpolate(pCmdUI);
}