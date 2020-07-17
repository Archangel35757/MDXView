// Filename:-	drag.cpp
//
#include "stdafx.h"
#include "includes.h"
//#include "model.h"
//
#include "drag.h"
#include "trackball.h"


const float MOUSE_ROT_SCALE  = 0.5f;
const float MOUSE_ZPOS_SCALE = 0.1f;
const float MOUSE_XPOS_SCALE = 0.1f;
const float MOUSE_YPOS_SCALE = 0.1f;


int m_x, m_y;
extern int g_iScreenHeight;
extern int g_iScreenWidth;


void zoomCameraDelta(int delta)
{
	AppVars.zPos -= ((float)(delta) / 120.0f);

	if (AppVars.zPos<-1000.f) AppVars.zPos = -1000.f;
	if (AppVars.zPos> 1000.f) AppVars.zPos = 1000.f;
}

/*! commands to handle mouse dragging, uses key_flags defines above */
void start_drag( mkey_enum keyFlags, int x, int y )
{
	m_x = x;
	m_y = y;
}

static bool drag_actual(  mkey_enum keyFlags, int x, int y )
{
	bool bRepaintAndSetCursor = false;

	//trackball variables
	float p1x, p1y, p2x, p2y;


	if ( keyFlags != 0 )
	{
		if ( keyFlags & KEY_LBUTTON )
		{				
			if ((x != m_x) || (y != m_y))
			{
				short s = GetAsyncKeyState(VK_MENU); // ALT key (Panning)
				if (s & 0x8000)
				{
					AppVars.xPos += ((float)(x - m_x)/10.f) * MOUSE_XPOS_SCALE;
					AppVars.yPos -= ((float)(y - m_y)/10.f) * MOUSE_YPOS_SCALE;
				}
				else
				{
					s = GetAsyncKeyState(0x5A);	// Z key
					if (s & 0x8000)
					{
						AppVars.rotAngleZ += (float)(x - m_x) * MOUSE_ROT_SCALE;
//						AppVars.rotAngleZ += (float)(y - m_y) * MOUSE_ROT_SCALE;
						if (AppVars.rotAngleZ> 360.0f) AppVars.rotAngleZ=AppVars.rotAngleZ-360.0f;
						if (AppVars.rotAngleZ<-360.0f) AppVars.rotAngleZ=AppVars.rotAngleZ+360.0f;
					}
					else
					{
						AppVars.rotAngleY += (float)(x - m_x) * MOUSE_ROT_SCALE;
						AppVars.rotAngleX += (float)(y - m_y) * MOUSE_ROT_SCALE;
						if (AppVars.rotAngleY> 360.0f) AppVars.rotAngleY=AppVars.rotAngleY-360.0f;
						if (AppVars.rotAngleY<-360.0f) AppVars.rotAngleY=AppVars.rotAngleY+360.0f;
						if (AppVars.rotAngleX> 360.0f) AppVars.rotAngleX=AppVars.rotAngleX-360.0f;
						if (AppVars.rotAngleX<-360.0f) AppVars.rotAngleX=AppVars.rotAngleX+360.0f;

						p1x = (2.0*m_x - g_iScreenWidth) / g_iScreenWidth;
						p1y = (g_iScreenHeight - 2.0*m_y) / g_iScreenHeight;
						p2x = (2.0*x - g_iScreenWidth) / g_iScreenWidth;
						p2y = (g_iScreenHeight - 2.0*y) / g_iScreenHeight;
						trackball(AppVars.lastQuat, p1x, p1y, p2x, p2y);
						add_quats(AppVars.lastQuat, AppVars.currQuat, AppVars.currQuat);
						//magic
						build_glmrotmatrix(AppVars.tballMat4, AppVars.currQuat);
					}
				}
				bRepaintAndSetCursor = true;
			}
		} else
		if ( keyFlags & KEY_MBUTTON )
		{
			if ((x != m_x) || (y != m_y))
			{
				AppVars.xPos += ((float)(x - m_x)/10.f) * MOUSE_XPOS_SCALE;
				AppVars.yPos -= ((float)(y - m_y)/10.f) * MOUSE_YPOS_SCALE;
			
				bRepaintAndSetCursor = true;
			}
		} else
		if ( keyFlags & KEY_RBUTTON ) 
		{
			if ( y != m_y )
			{
				AppVars.zPos += ((float)(y - m_y)/10.f) * MOUSE_ZPOS_SCALE;

				if (AppVars.zPos<-1000.f) AppVars.zPos=-1000.f;
				if (AppVars.zPos> 1000.f) AppVars.zPos= 1000.f;
				
				bRepaintAndSetCursor = true;
			}
		}
	}
	else
	{
		if (AppVars.bMouseWheel)
		{
			zoomCameraDelta(AppVars.zDelta);
			bRepaintAndSetCursor = true;
		}
		AppVars.bMouseWheel = false;
	}

	return bRepaintAndSetCursor;
}


bool gbScrollLockActive = false;
bool drag(  mkey_enum keyFlags, int x, int y )
{
	bool bRepaintAndSetCursor = false;

	float xPos		= AppVars.xPos;
	float yPos		= AppVars.yPos;
	float zPos		= AppVars.zPos;
	float rotAngleX = AppVars.rotAngleX;
	float rotAngleY = AppVars.rotAngleY;
	float rotAngleZ = AppVars.rotAngleZ;

	SHORT s = GetKeyState(VK_SCROLL);
	if (s&1)
	{
//		OutputDebugString("scroll lock ON\n");

		if (!gbScrollLockActive)
		{
			// reset vars when first activating...
			AppVars.xPos_SCROLL = AppVars.yPos_SCROLL  = AppVars.zPos_SCROLL = 0.0f;
			AppVars.rotAngleX_SCROLL = AppVars.rotAngleY_SCROLL = AppVars.rotAngleZ_SCROLL = 0.0f;

			AppVars.xPos_SCROLL = AppVars.xPos;
			AppVars.yPos_SCROLL = AppVars.yPos;
			AppVars.zPos_SCROLL = AppVars.zPos;

			//gbScrollLockActive = true;
		}		
	}
	else
	{
//		OutputDebugString("scroll lock OFF\n");

		gbScrollLockActive = false;
	}

	bool b = drag_actual(  keyFlags, x, y );

	if (gbScrollLockActive)
	{					
		#define BLAHBLAH(arg)	AppVars.arg ## _SCROLL += (AppVars.arg - arg); AppVars.arg = arg;

		BLAHBLAH(xPos);
		BLAHBLAH(yPos);
		BLAHBLAH(zPos);
//		BLAHBLAH(rotAngleX);
//		BLAHBLAH(rotAngleY);
//		BLAHBLAH(rotAngleZ);
	}

	return b;
}


void end_drag(  mkey_enum keyFlags, int x, int y )
{
}

///////////////////// eof /////////////////////

