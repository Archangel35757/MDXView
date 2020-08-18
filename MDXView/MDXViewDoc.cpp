
// MDXViewDoc.cpp : implementation of the CMDXViewDoc class
//

#include "stdafx.h"
#include "includes.h"
#include "script.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MDXView.h"
#endif

#include "MDXViewDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMDXViewDoc

IMPLEMENT_DYNCREATE(CMDXViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CMDXViewDoc, CDocument)
END_MESSAGE_MAP()


// CMDXViewDoc construction/destruction
CMDXViewDoc* g_pDocument = NULL;
CMDXViewDoc::CMDXViewDoc()
{
	g_pDocument = this;
}

CMDXViewDoc::~CMDXViewDoc()
{
}

BOOL CMDXViewDoc::OnNewDocument()
{
	Model_Delete();

	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMDXViewDoc serialization

void CMDXViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMDXViewDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMDXViewDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMDXViewDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMDXViewDoc diagnostics

#ifdef _DEBUG
void CMDXViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMDXViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////////////////
// CMDXViewDoc commands

CString strLastRealDocName;
CMDXViewDoc* gpLastOpenedMDXViewDoc = NULL;

void SetDocumentName(LPCSTR psDocName)
{
	if (gpLastOpenedMDXViewDoc)
	{
		// make absolutely fucking sure this bastard does as it's told...
		//
		gpLastOpenedMDXViewDoc->SetPathName(psDocName, false);
		gpLastOpenedMDXViewDoc->SetTitle(psDocName);
	}
}

LPCSTR LengthenFilenameW95W98(LPCSTR psFilename)
{
	// need to do this for Xmen models when running from a batch file under W95/98...
	//
	static char sDest[1024];
	sDest[0] = '\0';
	DWORD dwCount = GetLongPathName(psFilename, sDest, sizeof(sDest));

	return sDest;
}


// allows main doc code to be called by wintalk command
//
bool Document_ModelLoadPrimary(LPCSTR psFilename)
{
	return !!(!g_pDocument ? NULL : g_pDocument->OnOpenDocument(psFilename));
}

BOOL CMDXViewDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	string str = LengthenFilenameW95W98(lpszPathName);
	if (str.empty())	// if it was empty, then arg didn't eval to a filename (eg "#startminimized"), so return original
	{
		str = lpszPathName;
	}
	lpszPathName = str.c_str();

	if (strstr(lpszPathName, "#startminimized"))
	{
		extern bool gbStartMinimized;
		gbStartMinimized = true;

		OnNewDocument();

		// None of this shit works, because whatever you set the current document to MS overrides it with a derived name,
		//	and since the CWinApp class can't even ask what it's own fucking document pointer is without doing a hundred
		//	lines of shit deep within MFC then I'm going to fuck the whole lot off by storing a pointer which I can then
		//	use later in the CWinApp class to override the doc name. 
		//
		// All this fucking bollocks was because MS insists on doing their own switch-comparing so I can't pass in 'real'
		//	switches, I have to use this '#' crap. Stupid fucking incompetent MS dickheads. Like how hard would it be to
		//	pass command line switches to the app instead of just filenames?
		//
		strLastRealDocName = "Untitled";
		SetPathName(strLastRealDocName, false);	// I shouldn't have to do this, but MFC doesn't do it for some reason
		SetTitle(strLastRealDocName);
		gpLastOpenedMDXViewDoc = this;
		return true;
	}

	//	if (!CDocument::OnOpenDocument(lpszPathName))
	//		return FALSE;

	// check for script file first...
	//
	if (lpszPathName && !stricmp(&lpszPathName[strlen(lpszPathName) - 4], ".mvs"))
	{
		Script_Read(lpszPathName);			// this will recurse back into this function
		SetPathName(lpszPathName, true);	// add script file to MRU
		SetPathName(strLastRealDocName);	// DOESN'T WORK!: set doc/app name to last real model load, not the script name
		return true;
	}

	if (lpszPathName && Model_LoadPrimary(lpszPathName))
	{
		strLastRealDocName = lpszPathName;
		strLastRealDocName.Replace("/", "\\");
		SetPathName(strLastRealDocName, true);
		return true;
	}
	// model existed, but had some sort of error...
	//

	OnNewDocument();

	strLastRealDocName = "Untitled";
	SetPathName(strLastRealDocName, false);	// I shouldn't have to do this, but MFC doesn't do it for some reason
	return false;
}
