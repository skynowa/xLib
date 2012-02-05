/**
 * \file  CxGdiplus.cpp
 * \brief GDI+
 */


#include <xLib/Gui/Win/GDI+/CxGdiplus.h>

#if xOS_ENV_WIN

#include <GDIPlus.h>

#if !xCOMPILER_MINGW32
    #pragma comment (lib, "Gdiplus.lib")
#endif



xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxGdiplus::CxGdiplus() :
    _m_pulToken(NULL)
{
    Gdiplus::GdiplusStartupInput siStartupInput;

    Gdiplus::Status stRes = Gdiplus::GdiplusStartup(&_m_pulToken, &siStartupInput, NULL);
    /*DEBUG*/xASSERT_DO(Gdiplus::Ok == stRes, return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxGdiplus::~CxGdiplus() {
    (void)Gdiplus::GdiplusShutdown(_m_pulToken);

    _m_pulToken = NULL;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
