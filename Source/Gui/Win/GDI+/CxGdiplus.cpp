/****************************************************************************
* Class name:  CxGdiplus
* Description: GDI+
* File name:   CxGdiplus.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.05.2010 15:58:39
*
*****************************************************************************/


#include <xLib/Gui/Win/GDI+/CxGdiplus.h>

using namespace Gdiplus;


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxGdiplus
CxGdiplus::CxGdiplus() :
    _m_pulToken(0)
{
    Gdiplus::GdiplusStartupInput siStartupInput;

    Gdiplus::Status stRes = Gdiplus::GdiplusStartup(&_m_pulToken, &siStartupInput, NULL);
    /*DEBUG*/xASSERT_DO(Gdiplus::Ok == stRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxGdiplus
/*virtual*/
CxGdiplus::~CxGdiplus() {
    Gdiplus::GdiplusShutdown(_m_pulToken);
    /*DEBUG*/// n/a

    _m_pulToken = NULL;
}
//---------------------------------------------------------------------------
