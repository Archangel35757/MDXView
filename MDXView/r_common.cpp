// Filename:	r_common.cpp
//

#include "stdafx.h"
#include "includes.h"
#include "r_common.h"


refimport_t ri;


void Com_Printf(const char *format, ...)
{
	va_list		argptr;
	static char		string[16][1024];
	static int index = 0;

	index = (++index) & 15;

	va_start(argptr, format);
	vsprintf(string[index], format, argptr);
	va_end(argptr);

	OutputDebugString(string[index]);
	//	assert(0);
	ErrorBox(string[index]);
}

void Q_strncpyz(char *dest, LPCSTR src, int destlen)
{
	strncpy(dest, src, destlen);
	dest[destlen - 1] = '\0';
}

float Com_Clamp(float min, float max, float value) {
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}


/*
============
COM_SkipPath
============
*/
char *COM_SkipPath(char *pathname)
{
	char	*last;

	last = pathname;
	while (*pathname)
	{
		if (*pathname == '/')
			last = pathname + 1;
		pathname++;
	}
	return last;
}

/*
============
COM_StripExtension
============
*/
void COM_StripExtension(const char *in, char *out) {
	while (*in && *in != '.') {
		*out++ = *in++;
	}
	*out = 0;
}

/*
==================
COM_DefaultExtension
==================
*/
void COM_DefaultExtension(char *path, int maxSize, const char *extension) {
	char	oldPath[MAX_QPATH];
	char    *src;

	//
	// if path doesn't have a .EXT, append extension
	// (extension should include the .)
	//
	src = path + strlen(path) - 1;

	while (*src != '/' && src != path) {
		if (*src == '.') {
			return;                 // it has an extension
		}
		src--;
	}

	Q_strncpyz(oldPath, path, sizeof(oldPath));
	Com_sprintf(path, maxSize, "%s%s", oldPath, extension);
}


void QDECL Com_sprintf(char *dest, int size, const char *fmt, ...) {
	int		len;
	va_list		argptr;
	char	bigbuffer[32000];	// big, but small enough to fit in PPC stack

	va_start(argptr, fmt);
	len = vsprintf(bigbuffer, fmt, argptr);
	va_end(argptr);
	if (len >= sizeof(bigbuffer)) {
		Com_Error(ERR_FATAL, "Com_sprintf: overflowed bigbuffer");
	}
	if (len >= size) {
		Com_Printf("Com_sprintf: overflow of %i in %i ( string: \"%s\" )\n", len, size, bigbuffer);
	}
	Q_strncpyz(dest, bigbuffer, size);
}


int    LongSwap(int l)
{
	byte    b1, b2, b3, b4;

	b1 = l & 255;
	b2 = (l >> 8) & 255;
	b3 = (l >> 16) & 255;
	b4 = (l >> 24) & 255;

	return ((int)b1 << 24) + ((int)b2 << 16) + ((int)b3 << 8) + b4;
}