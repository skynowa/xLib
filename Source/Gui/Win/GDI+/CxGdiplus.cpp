/****************************************************************************
* Class name:  CxGdiplus
* Description: GDI+
* File name:   CxGdiplus.cpp
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.05.2010 15:58:39
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Gui/Win/GDI+/CxGdiplus.h>

using namespace Gdiplus;


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxGdiplus (comment)
CxGdiplus::CxGdiplus() : 
	_m_pulToken(0)
{
	Gdiplus::GdiplusStartupInput siStartupInput;

	Gdiplus::Status stRes = Gdiplus::GdiplusStartup(&_m_pulToken, &siStartupInput, NULL);
	/*DEBUG*/xASSERT_DO(Gdiplus::Ok == stRes, return);
}
//---------------------------------------------------------------------------
//TODO: - ~CxGdiplus (comment)
CxGdiplus::~CxGdiplus() {
	Gdiplus::GdiplusShutdown(_m_pulToken);	
	/*DEBUG*/// n/a

	_m_pulToken = NULL;
}
//---------------------------------------------------------------------------
