#include "StdAfx.h"
#include "GLShader.h"

CGLShader::CGLShader(GLenum shaderType)
{
	m_Type = shaderType;
	m_ID = glCreateShader(shaderType); 
	m_code = NULL;
}

CGLShader::~CGLShader(void)
{
	if(m_code) delete [] m_code;
	glDeleteShader(m_ID);
}

bool CGLShader::Load(CString fileName)
{
	m_code = FileRead(fileName);
	if(m_code) return true;
	else return false;
}

bool CGLShader::Compile(void)
{
	if(m_code == NULL) return false;
	const char * code = m_code;

	glShaderSource(m_ID, 1, &code, NULL);
	glCompileShader(m_ID);

	int param;
	glGetShaderiv(m_ID, GL_COMPILE_STATUS, &param);
	if(param == GL_TRUE) return true;
	else
	{
		CString* errStr = GetInfoLog();
		AfxMessageBox(*errStr);
		return false;
	}
}

char* CGLShader::FileRead(CString fileName) 
{
	FILE *fp;
	char *content = NULL;

	int count=0;

	if (!fileName.IsEmpty()) {
		fp = fopen(fileName,_T("rt"));
		if (fp != NULL) 
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);
			if (count > 0) 
			{
				content = new char [count+1];
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

CString* CGLShader::GetInfoLog()
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
	CString* retStr = NULL;

	glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = new char [infologLength];
        glGetShaderInfoLog(m_ID, infologLength, &charsWritten, infoLog);
		retStr = new CString(infoLog);
		delete [] infoLog;
    }
	return retStr;
}

void CGLShader::PrintInfoLog()
{
	CString* errStr = GetInfoLog();
	AfxMessageBox(*errStr);
}