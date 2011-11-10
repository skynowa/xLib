/****************************************************************************
* Class name:  CxTest_CxAutoMutex
* Description: test CxAutoMutex
* File name:   CxTest_CxAutoMutex.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxAutoMutex.h>


//---------------------------------------------------------------------------
CxTest_CxAutoMutex::CxTest_CxAutoMutex() {

}
//---------------------------------------------------------------------------
CxTest_CxAutoMutex::~CxTest_CxAutoMutex() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxAutoMutex::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    #if defined(xOS_ENV_WIN)
        //-------------------------------------
        //CxAutoMutex
        xTEST_BLOCK(cullBlockLoops)
        {
            CxMutex mtMutex;

            CxAutoMutex objAutoMutex(mtMutex);
        }
    #elif defined(xOS_ENV_UNIX)

    #endif

    return TRUE;
}
//---------------------------------------------------------------------------
