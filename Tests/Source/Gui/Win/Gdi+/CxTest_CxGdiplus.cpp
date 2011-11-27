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
bool
CxTest_CxGdiplus::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    /*DEBUG*/

    xTEST_CASE(cullCaseLoops)
    {
        CxGdiplus gpGdiPlus;
    }

    return true;
}
//---------------------------------------------------------------------------
#endif
