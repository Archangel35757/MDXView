// Filename:-	model.cpp
//
// non-format specific model routines entry point, calls format-specific code from within here
//
// ( This is the nice clean gateway module into all the evil crap I have to call from other codebases )
//

#include "stdafx.h"
#include "includes.h"
#include "MDXViewTreeView.h"
#include "glm_code.h"
#include "R_Model.h"
//#include "R_Surface.h"
#include "textures.h"
#include "TEXT.H"
#include "sequence.h"
#include "script.h"
#include "shader.h"
#include "skins.h"
//
#include "model.h"


static int	Model_MultiSeq_GetSeqHint(ModelContainer_t *pContainer, bool bPrimary);
static void Model_MultiSeq_SetSeqHint(ModelContainer_t *pContainer, bool bPrimary, int iHint);
static bool Model_MultiSeq_EnsureSeqHintLegal(ModelContainer_t *pContainer, int iFrame, bool bPrimary);


#define sERROR_MODEL_NOT_LOADED		"Error: Model not loaded, you shouldn't get here! -Ste"
#define sERROR_CONTAINER_NOT_FOUND	"Error: Could not resolve model handle to container ptr, you shouldn't get here! -Ste"
#define sSECONDARY_ANIM_STATS_STRING "(Secondary anim)"	// try and keep this fairly short, since it occupies roughly the same space as "bolt: <boltname>"

#define POINT_SCALE 64.0f
#define POINT_ST_SCALE	16384.0f

ModViewAppVars_t AppVars;

bool gbRenderInhibit = false;	// MUST stay in this state except when loading a model

// some protos...
//
static void ModelDraw_InfoText_Totals(void);
static void ModelDraw_InfoText_Header(void);



double getDoubleTime(void)
{
	return (double)clock() / (double)CLOCKS_PER_SEC;
}




void AppVars_OnceOnlyInit(void)
{
	AppVars.bFinished = false;
	AppVars.bBilinear = true;
	AppVars.bInterpolate = true;
	AppVars.bUseAlpha = false;
	AppVars.bWireFrame = false;
	AppVars.bOriginLines = false;
	AppVars.bBBox = false;
	AppVars.bFloor = false;
	AppVars.fFloorZ = -50;
	AppVars.bRuler = false;
	AppVars.bBoneHighlight = true;
	AppVars.bBoneWeightThreshholdingActive = false;
	AppVars.fBoneWeightThreshholdPercent = 5.0f;	// 
	AppVars.bSurfaceHighlight = true;
	AppVars.bSurfaceHighlightShowsBoneWeighting = false;
	AppVars.bTriIndexes = false;
	AppVars.bVertIndexes = false;
	AppVars.bVertWeighting = false;
	AppVars.bAtleast1VertWeightDisplayed = false;
	AppVars.bVertexNormals = false;
	AppVars.bShowOriginsAsRGB = true;
	AppVars.bForceWhite = false;
	AppVars.bCleanScreenShots = true;
	AppVars.bFullPathsInSequenceTreeitems = false;
	AppVars.bCrackHighlight = false;
	AppVars.bShowUnshadowableSurfaces = false;
	AppVars.bAllowGLAOverrides = false;
	AppVars.bShowPolysAsDoubleSided = true;

	// mousewheel
	AppVars.zDelta = 0;
	AppVars.bMouseWheel = false;

	// trackball stuff
	AppVars.tballMat4   = glm::mat4(1.0f);
	AppVars.lastQuat[1] = AppVars.lastQuat[2] = AppVars.lastQuat[3] = 0.0f;
	AppVars.currQuat[1] = AppVars.currQuat[2] = AppVars.currQuat[3] = 0.0f; // rotation tracking quaternions
	AppVars.lastQuat[0] = AppVars.currQuat[0] = 1.0f;

	// crap...
	//
	//	AppVars.iSurfaceNumToHighlight = iITEMHIGHLIGHT_NONE;
	//	AppVars.hModelToHighLight	= NULL;
	//	AppVars.hModelLastLoaded	= NULL;
	AppVars.bAlwaysOnTop = false;
	AppVars.bSortSequencesByAlpha = false;

	AppVars.iLOD = 0;

	//	AppVars_ResetViewParams();

	AppVars._R = AppVars._G = AppVars._B = 256 / 5;	// dark grey

	AppVars.dAnimSpeed = 0.05;	// so 1/this = 20 = 20FPS
								//	AppVars.dTimeStamp1			= getDoubleTime();
	AppVars.fFramefrac = 0.0f;
	AppVars.bAnimate = false;
	AppVars.bForceWrapWhenAnimating = false;

	//	AppVars_Delete();
}
