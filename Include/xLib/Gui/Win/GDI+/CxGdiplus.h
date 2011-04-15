/****************************************************************************
* Class name:  CxGdiplus
* Description: GDI+
* File name:   CxGdiplus.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.05.2010 15:58:39
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_GdiPlus_CxGdiplusH
#define xLib_GdiPlus_CxGdiplusH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <GDIPlus.h>

#pragma comment (lib, "Gdiplus.lib")
//---------------------------------------------------------------------------
class CxGdiplus : public CxNonCopyable {
	public:
		          CxGdiplus();
	             ~CxGdiplus();
	private:
		ULONG_PTR _m_pulToken;
};
//---------------------------------------------------------------------------
#endif //xLib_GdiPlus_CxGdiplusH
