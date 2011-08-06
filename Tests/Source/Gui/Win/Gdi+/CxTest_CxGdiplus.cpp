/****************************************************************************
* Class name:  CxTest_CxGdiplus
* Description: test CxGdiplus
* File name:   CxTest_CxGdiplus.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Gui/Win/Gdi+/CxTest_CxGdiplus.h>


#if defined(xOS_WIN)
    //---------------------------------------------------------------------------
    //DONE: CxTest_CxGdiplus
    CxTest_CxGdiplus::CxTest_CxGdiplus() {

    }
    //---------------------------------------------------------------------------
    //DONE: ~CxTest_CxGdiplus
    CxTest_CxGdiplus::~CxTest_CxGdiplus() {

    }
    //---------------------------------------------------------------------------
    //DONE: bUnit ()
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
#elif defined(xOS_LINUX)

#endif
