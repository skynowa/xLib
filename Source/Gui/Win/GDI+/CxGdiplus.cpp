/**
 * \file  CxGdiplus.cpp
 * \brief GDI+
 */


#include <xLib/Gui/Win/GDI+/CxGdiplus.h>

#if defined(xOS_ENV_WIN)
#include <GDIPlus.h>

#pragma comment (lib, "Gdiplus.lib")


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxGdiplus::CxGdiplus() :
    _m_pulToken(0)
{
    Gdiplus::GdiplusStartupInput siStartupInput;

    Gdiplus::Status stRes = Gdiplus::GdiplusStartup(&_m_pulToken, &siStartupInput, NULL);
    /*DEBUG*/xASSERT_DO(Gdiplus::Ok == stRes, return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxGdiplus::~CxGdiplus() {
    Gdiplus::GdiplusShutdown(_m_pulToken);
    /*DEBUG*/// n/a

    _m_pulToken = NULL;
}
//---------------------------------------------------------------------------
#elif defined(xOS_ENV_UNIX)

#endif
