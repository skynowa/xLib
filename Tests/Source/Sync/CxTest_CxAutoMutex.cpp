/**
 * \file   CxTest_CxAutoMutex.cpp
 * \brief
 */


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
