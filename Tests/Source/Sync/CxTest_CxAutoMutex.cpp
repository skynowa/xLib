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
bool
CxTest_CxAutoMutex::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    #if xOS_ENV_WIN
        //-------------------------------------
        //CxAutoMutex
        xTEST_CASE(cullBlockLoops)
        {
            CxMutex mtMutex;

            CxAutoMutex objAutoMutex(mtMutex);
        }
    #elif xOS_ENV_UNIX

    #endif

    return true;
}
//---------------------------------------------------------------------------
