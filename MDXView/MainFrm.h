
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "MainToolBar.h"


class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	CSplitterWnd m_mainSplitter;
	bool m_bInitSplitter;


// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMainToolBar		m_wndToolBar;
	CStatusBar			m_wndStatusBar;
	CBitmap				m_bmpToolbarHi;

// Generated message map functions
protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnFileOpen();
	afx_msg void OnFileBatchConvert();
	afx_msg void OnFileWriteIdeal();
	afx_msg void OnFileReadIdeal();
	afx_msg void OnFileResetViewParams();
	afx_msg void OnFileRefreshTextures();
	afx_msg void OnFileWriteScript();
	afx_msg void OnUpdateFileWriteScript(CCmdUI *pCmdUI);
	afx_msg void OnFileReadScript();
	afx_msg void OnFileViewSof2Npcs();
	afx_msg void OnUpdateFileViewSof2Npcs(CCmdUI *pCmdUI);
	afx_msg void OnFileViewJk2Bots();
	afx_msg void OnFilePrint3D();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditBkgrndColor();
	afx_msg void OnEditWireColor();
	afx_msg void OnEditSetfloorAbs();
	afx_msg void OnUpdateEditSetfloorAbs(CCmdUI *pCmdUI);
	afx_msg void OnEditSetfloorCurrent();
	afx_msg void OnUpdateEditSetfloorCurrent(CCmdUI *pCmdUI);
	afx_msg void OnEditSetBoneWeightThreshold();
	afx_msg void OnUpdateEditSetBoneWeightThreshold(CCmdUI *pCmdUI);
	afx_msg void OnEditAllowSkeletonOverrides();
	afx_msg void OnUpdateEditAllowSkeletonOverrides(CCmdUI *pCmdUI);
	afx_msg void OnEditTopmost();
	afx_msg void OnUpdateEditTopmost(CCmdUI *pCmdUI);
	afx_msg void OnViewWireframe();
	afx_msg void OnUpdateViewWireframe(CCmdUI *pCmdUI);
	afx_msg void OnViewAlpha();
	afx_msg void OnUpdateViewAlpha(CCmdUI *pCmdUI);
	afx_msg void OnViewBilinear();
	afx_msg void OnUpdateViewBilinear(CCmdUI *pCmdUI);
	afx_msg void OnViewInterpolate();
	afx_msg void OnUpdateViewInterpolate(CCmdUI *pCmdUI);
	afx_msg void OnViewOrigin();
	afx_msg void OnUpdateViewOrigin(CCmdUI *pCmdUI);
	afx_msg void OnViewOriginsAsRGB();
	afx_msg void OnUpdateViewOriginsAsRGB(CCmdUI *pCmdUI);
	afx_msg void OnBoneHilite();
	afx_msg void OnUpdateBoneHilite(CCmdUI *pCmdUI);
	afx_msg void OnViewBoneWeightFiltering();
	afx_msg void OnUpdateViewBoneWeightFiltering(CCmdUI *pCmdUI);
	afx_msg void OnViewWireOverlaySurfHilite();
	afx_msg void OnUpdateViewWireOverlaySurfHilite(CCmdUI *pCmdUI);
	afx_msg void OnViewSurfaceHiliteWithBoneRefs();
	afx_msg void OnUpdateViewSurfaceHiliteWithBoneRefs(CCmdUI *pCmdUI);
	afx_msg void OnViewTriangleIndexes();
	afx_msg void OnUpdateViewTriangleIndexes(CCmdUI *pCmdUI);
	afx_msg void OnViewBoneWeights();
	afx_msg void OnUpdateViewBoneWeights(CCmdUI *pCmdUI);
	afx_msg void OnViewVertexIndexes();
	afx_msg void OnUpdateViewVertexIndexes(CCmdUI *pCmdUI);
	afx_msg void OnViewVertexBoneWeighting();
	afx_msg void OnUpdateViewVertexBoneWeighting(CCmdUI *pCmdUI);
	afx_msg void OnViewNormals();
	afx_msg void OnUpdateViewNormals(CCmdUI *pCmdUI);
	afx_msg void OnViewTagSurfaces();
	afx_msg void OnUpdateViewTagSurfaces(CCmdUI *pCmdUI);
	afx_msg void OnViewRuler();
	afx_msg void OnUpdateViewRuler(CCmdUI *pCmdUI);
	afx_msg void OnViewBbox();
	afx_msg void OnUpdateViewBbox(CCmdUI *pCmdUI);
	afx_msg void OnViewFloor();
	afx_msg void OnUpdateViewFloor(CCmdUI *pCmdUI);
	afx_msg void OnViewForceWhite();
	afx_msg void OnUpdateViewForceWhite(CCmdUI *pCmdUI);
	afx_msg void OnViewUVSeamsOpenEdges();
	afx_msg void OnUpdateViewUVSeamsOpenEdges(CCmdUI *pCmdUI);
	afx_msg void OnViewUnshadowableSurfaces();
	afx_msg void OnUpdateViewUnshadowableSurfaces(CCmdUI *pCmdUI);
	afx_msg void OnViewDoublesidedPolys();
	afx_msg void OnUpdateViewDoublesidedPolys(CCmdUI *pCmdUI);
	afx_msg void OnViewVertexColor();
	afx_msg void OnUpdateViewVertexColor(CCmdUI *pCmdUI);
	afx_msg void OnViewUVMapping();
	afx_msg void OnUpdateViewUVMapping(CCmdUI *pCmdUI);
	afx_msg void OnViewScreenshotFile();
	afx_msg void OnViewScreenshotToClipboard();
	afx_msg void OnViewScreenshotClean();
	afx_msg void OnUpdateViewScreenshotClean(CCmdUI *pCmdUI);
	afx_msg void OnViewFovCycle();
	afx_msg void OnViewLod0();
	afx_msg void OnUpdateViewLod0(CCmdUI *pCmdUI);
	afx_msg void OnViewLod1();
	afx_msg void OnUpdateViewLod1(CCmdUI *pCmdUI);
	afx_msg void OnViewLod2();
	afx_msg void OnUpdateViewLod2(CCmdUI *pCmdUI);
	afx_msg void OnViewLod3();
	afx_msg void OnUpdateViewLod3(CCmdUI *pCmdUI);
	afx_msg void OnViewLod4();
	afx_msg void OnUpdateViewLod4(CCmdUI *pCmdUI);
	afx_msg void OnViewLod5();
	afx_msg void OnUpdateViewLod5(CCmdUI *pCmdUI);
	afx_msg void OnViewLod6();
	afx_msg void OnUpdateViewLod6(CCmdUI *pCmdUI);
	afx_msg void OnViewLod7();
	afx_msg void OnUpdateViewLod7(CCmdUI *pCmdUI);
	afx_msg void OnViewLod8();
	afx_msg void OnUpdateViewLod8(CCmdUI *pCmdUI);
	afx_msg void OnViewLod9();
	afx_msg void OnUpdateViewLod9(CCmdUI *pCmdUI);
	afx_msg void OnPicmip0();
	afx_msg void OnUpdatePicmip0(CCmdUI *pCmdUI);
	afx_msg void OnPicmip1();
	afx_msg void OnUpdatePicmip1(CCmdUI *pCmdUI);
	afx_msg void OnPicmip2();
	afx_msg void OnUpdatePicmip2(CCmdUI *pCmdUI);
	afx_msg void OnPicmip3();
	afx_msg void OnUpdatePicmip3(CCmdUI *pCmdUI);
	afx_msg void OnPicmip4();
	afx_msg void OnUpdatePicmip4(CCmdUI *pCmdUI);
	afx_msg void OnPicmip5();
	afx_msg void OnUpdatePicmip5(CCmdUI *pCmdUI);
	afx_msg void OnPicmip6();
	afx_msg void OnUpdatePicmip6(CCmdUI *pCmdUI);
	afx_msg void OnPicmip7();
	afx_msg void OnUpdatePicmip7(CCmdUI *pCmdUI);
	afx_msg void OnViewGLDriverInfo();
	afx_msg void OnAnimationStart();
	afx_msg void OnAnimationStartForceWrap();
	afx_msg void OnAnimationStop();
	afx_msg void OnAnimationRewind();
	afx_msg void OnAnimationEndFrame();
	afx_msg void OnAnimationPrevFrame();
	afx_msg void OnAnimationNextFrame();
	afx_msg void OnAnimationFaster();
	afx_msg void OnAnimationSlower();
	afx_msg void OnAnimationLerping();
	afx_msg void OnUpdateAnimationLerping(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	void StatusMessage(LPCTSTR psMessage);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

protected:

private:
	void OnUpdateViewLod(CCmdUI *pCmdUI, int lod);

public:


};


