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
    const ulonglong_t cullCaseLoops
)
{
    #if xOS_ENV_WIN
        //-------------------------------------
        //CxAutoMutex
        xTEST_CASE(cullCaseLoops)
        {
            CxMutex mtMutex;

            CxAutoMutex objAutoMutex(mtMutex);
        }
    #elif xOS_ENV_UNIX

    #endif

    return true;
}
//---------------------------------------------------------------------------
