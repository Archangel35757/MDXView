// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GLVIEW_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GLVIEW_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
// We add the condition WIN32 for UNIX/Linux portability

/*
#ifdef GLVIEW_EXPORTS
#ifdef WIN32
#define GLVIEW_API __declspec(dllexport)
#else
#define GLVIEW_API
#endif
#else
#ifdef WIN32
#define GLVIEW_API __declspec(dllimport)
#else
#define GLVIEW_API
#endif
#endif
*/


#include "ogl.h"
#include <TCHAR.H>  // for unicode support
#include "trackball.h"

class CGLProgram;
class CGLShader;

//Class CGLView handles all OpenGL operations
class CGLView 
{
public:
	CGLView(void);
	virtual ~CGLView(void);

	void SetWindow(HWND ihWnd);

	bool SetupGLContext(bool iSetPixelFormat);
	void Resize(unsigned short iWidth, unsigned short iHeight);
	void PrepareScene(HDC hdc);		// Scene preparation stuff
	void RenderScene(void);
	void Refresh(void);
	void DestroyScene();			// Cleanup

	HWND m_hWnd;
	HDC  m_hDC;
	HGLRC m_hGLRC;

	int		m_iViewWidth;
	int		m_iViewHeight;
	UINT	m_TimerHandle_Update100FPS;

protected:
	void SetData(void);
	void InitAPI(void);
	void GetGLVersion(int* major, int* minor);
	int SetPixelFormat(HDC hdc);

//	void Setup3DEnvironment();
//	void DrawGradientBackground();
//	void InitDisplayLists();
//	void DoAntialiasing();

	GLuint m_vboID;				// ID of geometry VBO
	GLuint m_uvBuffer;			// ID of uv buffer VBO
	CGLProgram* m_pProgram;			// Program
	CGLShader*  m_pVertSh;			// Vertex shader
	CGLShader*  m_pFragSh;			// Fragment shader

	GLuint loadBMP_custom(const char * imagepath);
	// Data read from the header of the BMP file
	//------------------------------------------
	unsigned char	m_bmpHeader[54];		// Each BMP file begins by a 54-bytes header
	unsigned int	m_bmpDataPos;			// Position in the file where the actual data begins
	unsigned int	m_bmpWidth, m_bmpHeight;
	unsigned int	m_bmpImageSize;			// = width*height*3
	unsigned char * m_bmpData; 				// Actual RGB data
	//------------------------------------------


private:
//	void DrawTorus(int numMajor, int numMinor, float majorRadius, float minorRadius, bool bShaded = true);

	GLdouble nRange;	
	GLdouble win_xmax,
		win_xmin,
		win_ymax,
		win_ymin,
		winz,
		winH,
		winW;

	bool m_bGradientBg;
	bool m_bAntiAlias;

	GLubyte bgTopR;
	GLubyte bgTopG;
	GLubyte bgTopB;
	GLubyte bgBotR;
	GLubyte bgBotG;
	GLubyte bgBotB;

	GLfloat ambiLight[4];
	GLfloat diffLight[4];
	GLfloat specLight[4];

};

