// GLView.cpp : Defines the exported functions for the DLL application.
//

#include "StdAfx.h"
#include "GLView.h"
#include "GLShader.h"
#include "GLProgram.h"
#include "includes.h"
#include "Textures.h"
#include <iostream>
#include <string>

using std::cout;
using std::cerr;
using std::endl;


#define degreesToRadians(x) x*(3.141592f/180.0f)


//*********************************************************************
// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
static const GLfloat g_uv_buffer_data[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};
//*********************************************************************

// This is the constructor of a class that has been exported.
// see GLView.h for the class definition
CGLView::CGLView()
{
	m_hWnd = NULL;
	m_hDC = NULL;
	m_hGLRC = NULL;

	m_iViewWidth	= 100;
	m_iViewHeight	= 100;

	m_TimerHandle_Update100FPS = 0;

	nRange = 100;
	m_bAntiAlias = true;

	ambiLight[0] = 0.3f;
	ambiLight[1] = 0.3f;
	ambiLight[2] = 0.3f;
	ambiLight[3] = 1.0f;

	diffLight[0] = 0.7f;
	diffLight[1] = 0.7f;
	diffLight[2] = 0.7f;
	diffLight[3] = 1.0f;

	specLight[0] = 1.0f;
	specLight[1] = 1.0f;
	specLight[2] = 1.0f;
	specLight[3] = 1.0f;

	// gradient background color
	bgTopR = 77;
	bgTopG  =77;
	bgTopB = 77;
	bgBotR = 236;
	bgBotG = 233;
	bgBotB = 216;


	m_bGradientBg = true;

	m_pProgram = NULL;

	return;
}

CGLView::~CGLView()
{
	if (m_pProgram)
		delete m_pProgram;
}

void CGLView::SetWindow(HWND ihWnd)
{
	m_hWnd = ihWnd;
}

void CGLView::Resize(unsigned short iWidth, unsigned short iHeight)
{
	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	GLint viewport[4];


	// setup viewport, projection etc.:
	/* Prevent a divide by zero*/
	if(iHeight == 0)
		iHeight = 1;


	winH = (GLdouble)iHeight;
	winW = (GLdouble)iWidth;

	m_iViewWidth = iWidth;
	m_iViewHeight = iHeight;

	wglMakeCurrent(m_hDC, m_hGLRC);

	glViewport (0, 0, (GLsizei)iWidth, (GLsizei)iHeight);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	if (iWidth <= iHeight)
		glOrtho (-nRange, nRange, -nRange*iHeight/iWidth, nRange*iHeight/iWidth, -nRange*10000, nRange*10000);
	else
		glOrtho (-nRange*iWidth/iHeight, nRange*iWidth/iHeight, -nRange, nRange, -nRange*10000, nRange*10000);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();


	// store limits for gradient background
	glGetDoublev (GL_PROJECTION_MATRIX, projMatrix);
	glGetDoublev (GL_MODELVIEW_MATRIX, modelMatrix);
	glGetIntegerv (GL_VIEWPORT, viewport);
	gluUnProject (0, 0, 1, modelMatrix, projMatrix, viewport,
		&win_xmin, &win_ymin, &winz);
	gluUnProject (iWidth, iHeight, 1, modelMatrix, projMatrix, viewport,
		&win_xmax, &win_ymax, &winz);

	wglMakeCurrent(NULL,NULL);

}

void CGLView::Refresh( void)
{
	::InvalidateRect(m_hWnd, NULL, FALSE);
}

void CGLView::RenderScene(void)
{
/*	wglMakeCurrent(m_hDC, m_hGLRC);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawGradientBackground();	
	DoAntialiasing();
	Setup3DEnvironment();	

	glPushMatrix();
	{
		//Draw stuff here
		glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);

		glColor4ub(125, 255, 255, 255);
		DrawTorus(30, 20, 50, 25, false);
	}
	glPopMatrix();

	SwapBuffers(m_hDC);
	wglMakeCurrent(NULL, NULL);

	GLint *versionMAJ;
	GLint *versionMIN;
	char buffer[50];
	//sprintf(buffer, "OpenGL %d.%d", glGetIntegerv(GL_MAJOR_VERSION, versionMAJ), glGetIntegerv(GL_MINOR_VERSION, versionMIN));
	//MessageBoxA(0, buffer, "OpenGL", MB_OK);
*/
	wglMakeCurrent(m_hDC, m_hGLRC);
	//--------------------------------
	// clear buffer
	glClearColor((float)1 / ((float)256 / (float)AppVars._R), (float)1 / ((float)256 / (float)AppVars._G), (float)1 / ((float)256 / (float)AppVars._B), 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetData();

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	//---------------------------------------------------------------------

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the cube!
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // From index 0 to 12*3 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//---------------------------------------------------------------------

	// unbind VBOs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//--------------------------------
	glFlush();
	SwapBuffers(m_hDC);
	wglMakeCurrent(NULL, NULL);
}

bool CGLView::SetupGLContext(bool iSetPixelFormat)
{
	BOOL bResult;

	if (m_hWnd == NULL)
	{
		return false;
	}

	m_hDC = ::GetDC(m_hWnd);

	if (iSetPixelFormat)
	{
		bResult = SetPixelFormat(m_hDC);
	}

	/*
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);
*/


	if (!bResult) 
		return false;

	// --- OpenGL 3.x ---
	HGLRC tempContext = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, tempContext);

	int major, minor;
	GetGLVersion(&major, &minor);

	if (major < 3 || (major == 3 && minor < 3))
		AfxMessageBox(_T("OpenGL 3.3 is not supported!"));

	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,	// WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, // WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB | WGL_CONTEXT_CORE_PROFILE_BIT_ARB, //0x9126 , 0x00000001,
		0
	};

	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if (wglCreateContextAttribsARB != NULL)
	{
		m_hGLRC = wglCreateContextAttribsARB(m_hDC, 0, attribs);
	}

	wglMakeCurrent(m_hDC, m_hGLRC);

	InitAPI();

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(tempContext);

	if (!m_hGLRC)
	{
		AfxMessageBox(_T("OpenGL 3.x RC was not created!"));
		return false;
	}

	OnceOnly_GLVarsInit();

	return true;
}


int CGLView::SetPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd; /* = {
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd 
		1,                                // version number 
		PFD_DRAW_TO_WINDOW |              // support window 
		PFD_SUPPORT_OPENGL |              // support OpenGL 
		PFD_DOUBLEBUFFER,                 // double buffered 
		PFD_TYPE_RGBA,                    // RGBA type 
		32,                               // 32-bit color depth 
		0, 0, 0, 0, 0, 0,                 // color bits ignored 
		0,                                // no alpha buffer 
		0,                                // shift bit ignored 
		0,                                // no accumulation buffer 
		0, 0, 0, 0,                       // accum bits ignored 
		32,                               // 32-bit z-buffer     
		8,                                // 8-bit stencil buffer 
		0,                                // no auxiliary buffer 
		PFD_MAIN_PLANE,                   // main layer 
		0,                                // reserved 
		0, 0, 0                           // layer masks ignored 
	};
*/

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int  iPixelFormat; 

	// get the device context's best, available pixel format match 
	if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
	{
		MessageBox(m_hWnd, _T("ChoosePixelFormat Failed"), NULL, MB_ICONERROR);
		return 0;
	}

	// make that match the device context's current pixel format 
	if(::SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
	{
		MessageBox(m_hWnd, _T("SetPixelFormat Failed"), NULL, MB_ICONERROR);
		return 0;
	}

	return 1;
}


/*
void CGLView::Setup3DEnvironment()
{
	// Enable Depth Testing
	glEnable(GL_DEPTH_TEST);
	// Enable lighting
	glEnable(GL_LIGHTING);
	
	GLfloat position[] = {0.0f, 0.0f, 3.0f, 0.0f};
	GLfloat lmodel_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat local_view[] = {0.0f};

	// Setup and enable light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);
}

void CGLView::DoAntialiasing()
{
	if(m_bAntiAlias)
	{
		glEnable (GL_POINT_SMOOTH);
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
		glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
		glLineWidth(1.5125f);
		glDepthFunc(GL_ALWAYS);
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable (GL_LINE_SMOOTH);
		glLineWidth (1.2125f);
		glDepthFunc(GL_LESS);
		glDisable (GL_BLEND);
	}
}

void CGLView::DrawGradientBackground()
{
	//gradient background
	glPushAttrib(GL_ENABLE_BIT);
	glDisable (GL_DEPTH_TEST);
	glDisable (GL_LIGHTING);
	glDisable (GL_TEXTURE_2D);
	glShadeModel (GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK ,GL_FILL);
	glBegin (GL_POLYGON);
	//glColor3ub (51, 51, 101);
	glColor3ub (bgTopR, bgTopG, bgTopB);
	glVertex3d (win_xmin, win_ymax, winz);
	glVertex3d (win_xmax, win_ymax, winz);
	//glColor3ub (171, 172, 193);
	if(m_bGradientBg)
	{
		glColor3ub (bgBotR, bgBotG, bgBotB);
	}
	glVertex3d (win_xmax, win_ymin, winz);
	glVertex3d (win_xmin, win_ymin, winz);
	glEnd ();
	glPopAttrib();
	//end gradient background
}

void CGLView::InitDisplayLists()
{
}


#include <cmath>
//helper function to draw torus removes 'glut' dependency
void CGLView::DrawTorus(int numMajor, int numMinor, float majorRadius, float minorRadius, bool bShaded)
{
	static double PI = 3.1415926535897932384626433832795;
	double majorStep = 2.0 * PI / numMajor;
	double minorStep = 2.0 * PI / numMinor;
	int i, j;

	GLfloat opacity = 255;

	GLfloat ambiMat[4] = { 0.2f, 0.5f, 0.7f, opacity };

	GLfloat diffMat[4] = { 0.7f, 0.7f, 0.7f, opacity };

	GLfloat specMat[4] = { 1.0f, 1.0f, 1.0f, opacity };

	GLfloat specRef[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLint shine;

	shine = 128;

	opacity = 255;


	// Enable Material
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LESS);

	//Setup Material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiMat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffMat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specMat);


	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specRef);
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS, shine);

	if(!bShaded)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}


	for (i = 0; i < numMajor; ++i) 
	{
		double a0 = i * majorStep;
		double a1 = a0 + majorStep;
		GLdouble x0 = cos(a0);
		GLdouble y0 = sin(a0);
		GLdouble x1 = cos(a1);
		GLdouble y1 = sin(a1);

		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j <= numMinor; ++j) {
			double b = j * minorStep;
			GLdouble c = cos(b);
			GLdouble r = minorRadius * c + majorRadius;
			GLdouble z = minorRadius * sin(b);

			glNormal3d(x0 * c, y0 * c, z / minorRadius);
			glTexCoord2d(i / (GLdouble) numMajor, j / (GLdouble) numMinor);
			glVertex3d(x0 * r, y0 * r, z);

			glNormal3d(x1 * c, y1 * c, z / minorRadius);
			glTexCoord2d((i + 1) / (GLdouble) numMajor, j / (GLdouble) numMinor);
			glVertex3d(x1 * r, y1 * r, z);
		}
		glEnd();
	}
}
*/

void CGLView::PrepareScene(HDC hdc)
{
	wglMakeCurrent(m_hDC, m_hGLRC);
	//---------------------------------
	// White background
	//glClearColor (1.0, 1.0, 1.0, 0.0);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

	// Set the background color
	glClearColor((float)1 / ((float)256 / (float)AppVars._R), (float)1 / ((float)256 / (float)AppVars._G), (float)1 / ((float)256 / (float)AppVars._B), 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	m_pProgram =	new CGLProgram();
	m_pVertSh =		new CGLShader(GL_VERTEX_SHADER);
	m_pFragSh =		new CGLShader(GL_FRAGMENT_SHADER);

	if (!m_pVertSh->Load(_T("minimal.vert")))
		AfxMessageBox(_T("Vertex shader loading error!"));

	if (!m_pFragSh->Load(_T("minimal.frag")))
		AfxMessageBox(_T("Fragment shader loading error!"));

	if (!m_pVertSh->Compile())
		AfxMessageBox(_T("Vertex shader compiling error!"));

	if (!m_pFragSh->Compile())
		AfxMessageBox(_T("Fragment shader compiling error!"));

	m_pProgram->AttachShader(m_pVertSh);
	m_pProgram->AttachShader(m_pFragSh);

	m_pProgram->BindAttribLocation(0, "vertexPosition_modelspace");
	m_pProgram->BindAttribLocation(1, "vertexUV");

	if (!m_pProgram->Link())
		AfxMessageBox(_T("Program linking error!"));

	m_pProgram->Use();

	SetData();
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLView::DestroyScene()
{
	wglMakeCurrent(m_hDC, m_hGLRC);
	//--------------------------------
	m_pProgram->DetachShader(m_pVertSh);
	m_pProgram->DetachShader(m_pFragSh);

	delete m_pProgram;
	m_pProgram = NULL;

	delete m_pVertSh;
	m_pVertSh = NULL;
	delete m_pFragSh;
	m_pFragSh = NULL;

	wglMakeCurrent(NULL, NULL);
	//--------------------------------
	if (m_hGLRC)
	{
		wglDeleteContext(m_hGLRC);
		m_hGLRC = NULL;
	}
}


void CGLView::SetData()
{
	// Get a handle for our "MVP" uniform
	GLuint MatrixID = m_pProgram->GetUniformLocation("MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.01 unit <-> 1000 units
	glm::mat4 Projection = glm::perspective(degreesToRadians(45.0f), m_iViewWidth / (float)m_iViewHeight, 0.01f, 1000.0f);

	// Camera matrix
	/*	glm::mat4 View		 = glm::lookAt(
	glm::vec3(0, 0, -10), // Camera is at (4,3,3), in World Space
	glm::vec3(0,0,0), // and looks at the origin
	glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	*/

	// View matrix
	glm::mat4 T0 = glm::mat4(1.0f);
	glm::mat4 T1 = glm::mat4(1.0f);
	glm::vec3 t0 = glm::vec3(0, 0, 10 - AppVars.zPos);
	glm::vec3 t1 = glm::vec3(-AppVars.xPos, -AppVars.yPos, 0);
	T0 = glm::translate(T0, t0);
	T1 = glm::translate(T1, t1);

	glm::mat4 View = inverse(T1 * glm::mat4(1.0f) * T0);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f) * AppVars.tballMat4;

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

	GLuint Texture = loadBMP_custom("uvtemplate.bmp");

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(Texture, 0);

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// create VBO
	glGenBuffers(1, &m_vboID);    // for vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// create uvBuffer
	glGenBuffers(1, &m_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

}


void CGLView::InitAPI()
{
	int wgl_ext_count = 0;
	GLint n = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	PFNGLGETSTRINGIPROC glGetStringi = 0;
	glGetStringi = (PFNGLGETSTRINGIPROC)wglGetProcAddress("glGetStringi");

	char buffer[256] = { 0 };
	sprintf(buffer, _T("Number of OpenGL Extensions found:  %i"), (int)n);
//	AfxMessageBox(buffer);

	FILE* pFile = fopen(_T("extensions.txt"), _T("w"));

	for (GLint i = 0; i<n; i++)
	{
		const char* extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
		if (pFile != NULL)
		{
			fprintf(pFile, _T("Ext %d: %s\n"), i, extension);
		}
	}

	m_hDC = wglGetCurrentDC();

	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");

	const char* wgl_ext_string = wglGetExtensionsStringARB(m_hDC);
	char* token = strtok((char*)wgl_ext_string, " ");
	if (pFile)
	{
		if (wgl_ext_string != NULL)
		{
			while (token != NULL)
			{
				wgl_ext_count++;
				fprintf(pFile, _T(" %s\n"), token); //printing each token
				token = strtok(NULL, " ");
			}
		}
		fclose(pFile);
	}
	else
		fclose(pFile);

	sprintf(buffer, _T("Number of WGL Extensions found:  %i"), wgl_ext_count);
//	AfxMessageBox(buffer);

	// record vendor strings for later display... (this is the latest installed OpenGL driver info-- not v3.3 used by the App)
	//---------------------------------------------
	csGLVendor = glGetString(GL_VENDOR);
	csGLRenderer = glGetString(GL_RENDERER);
	csGLVersion = glGetString(GL_VERSION);
	csGLExtensions = glGetString(GL_EXTENSIONS);
	//---------------------------------------------


	// Program
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	glUniform1iv = (PFNGLUNIFORM1IVPROC)wglGetProcAddress("glUniform1iv");
	glUniform2iv = (PFNGLUNIFORM2IVPROC)wglGetProcAddress("glUniform2iv");
	glUniform3iv = (PFNGLUNIFORM3IVPROC)wglGetProcAddress("glUniform3iv");
	glUniform4iv = (PFNGLUNIFORM4IVPROC)wglGetProcAddress("glUniform4iv");
	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	glUniform1fv = (PFNGLUNIFORM1FVPROC)wglGetProcAddress("glUniform1fv");
	glUniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)wglGetProcAddress("glVertexAttrib1f");
	glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)wglGetProcAddress("glVertexAttrib1fv");
	glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)wglGetProcAddress("glVertexAttrib2fv");
	glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)wglGetProcAddress("glVertexAttrib3fv");
	glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)wglGetProcAddress("glVertexAttrib4fv");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)wglGetProcAddress("glGetActiveUniform");

	// Shader
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");

	// Texture
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");

	// VBO
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glBufferSubData = (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubData");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");

	// VAO
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
}

void CGLView::GetGLVersion(int* major, int* minor)
{
	// for all versions
	char* ver = (char*)glGetString(GL_VERSION); // ver = "3.3.0"

	*major = ver[0] - '0';
	if (*major >= 3)
	{
		// for GL 3.x
		glGetIntegerv(GL_MAJOR_VERSION, major);		// major = 3
		glGetIntegerv(GL_MINOR_VERSION, minor);		// minor = 3
	}
	else
	{
		*minor = ver[2] - '0';
	}

	// GLSL
	ver = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);	// 3.3 NVIDIA via Cg compiler
}


GLuint CGLView::loadBMP_custom(const char * imagepath)
{
	// Open the file
	FILE * file = fopen(imagepath, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(m_bmpHeader, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}

	if (m_bmpHeader[0] != 'B' || m_bmpHeader[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	m_bmpDataPos	= *(int*)&(m_bmpHeader[0x0A]);
	m_bmpImageSize	= *(int*)&(m_bmpHeader[0x22]);
	m_bmpWidth		= *(int*)&(m_bmpHeader[0x12]);
	m_bmpHeight		= *(int*)&(m_bmpHeader[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (m_bmpImageSize == 0)
		m_bmpImageSize = m_bmpWidth*m_bmpHeight * 3; // 3 : one byte for each Red, Green and Blue component

	if (m_bmpDataPos == 0)
		m_bmpDataPos = 54; // The BMP header is done that way

	m_bmpData = new unsigned char[m_bmpImageSize];

	// Read the actual data from the file into the buffer
	fread(m_bmpData, 1, m_bmpImageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_bmpWidth, m_bmpHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, m_bmpData);

	// Poor filtering, or ...
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering.
	(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return textureID;
}