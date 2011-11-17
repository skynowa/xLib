/**
 * \file   CxTest_CxGdiplus.cpp
 * \brief
 */


#include <Test/Gui/Win/Gdi+/CxTest_CxGdiplus.h>


#if xOS_ENV_WIN
//---------------------------------------------------------------------------
CxTest_CxGdiplus::CxTest_CxGdiplus() {

}
//---------------------------------------------------------------------------
CxTest_CxGdiplus::~CxTest_CxGdiplus() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxGdiplus::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    xTEST_BLOCK(cullBlockLoops)
    {
        CxGdiplus gpGdiPlus;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif
