#pragma once
// --- ogl.h ---
#include <windows.h> // required by OpenGL and must be included before gl.h
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/wgl/glext.h"
#include "../include/wgl/wglext.h"

#pragma comment(lib,"opengl32.lib")

// Include GLM
#define GLM_FORCE_RADIANS
#include "../include/glm/glm/glm.hpp"
#include "../include/glm/glm/gtc/matrix_transform.hpp"
#include "../include/glm/glm/gtc/type_ptr.hpp"

using namespace glm;

extern HDC g_hDC;
extern HGLRC g_hRC;

extern CString csGLVendor;
extern CString csGLRenderer;
extern CString csGLVersion;
extern CString csGLExtensions;

//----------------
// Program
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM1IVPROC glUniform1iv;
extern PFNGLUNIFORM2IVPROC glUniform2iv;
extern PFNGLUNIFORM3IVPROC glUniform3iv;
extern PFNGLUNIFORM4IVPROC glUniform4iv;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM1FVPROC glUniform1fv;
extern PFNGLUNIFORM2FVPROC glUniform2fv;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;

// Shader
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;

// Textures
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

// VBO
extern PFNGLGENBUFFERSPROC  glGenBuffers;
extern PFNGLBINDBUFFERPROC	glBindBuffer;
extern PFNGLBUFFERDATAPROC	glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

// VAO
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

// WGL
extern PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;



//GL_BITS_H
//**************************************************************************
HGLRC	GL_GenerateRC(HDC hDC, bool bDoubleBuffer = true);
//GLuint	GL_BindImage	(CImage *image);
void	GL_Enter3D(double dFOV, int iWindowWidth, int iWindowDepth, bool bWireFrame, bool bCLS = true);
void	GL_Enter2D(int iWindowWidth, int iWindowDepth, bool bCLS = true);
void	GL_Exit2D(void);
int		GL_GetCorrectedDim(int iDim);
char*	GL_GetCorrectedDimString(int iDim);
LPCSTR	GL_GetInfo(void);


#ifdef _DEBUG
#define ASSERT_GL AssertGL(__FILE__,__LINE__)
void	AssertGL(const char *sFile, int iLine);
#else
#define ASSERT_GL
#endif

typedef struct tagFRECT
{
	float	left;
	float    top;
	float    right;
	float    bottom;
} FRECT, FAR *LPFRECT;
//**************************************************************************

