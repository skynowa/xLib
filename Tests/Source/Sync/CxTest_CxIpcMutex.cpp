/**
 * \file   CxTest_CxIpcMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxIpcMutex.h>


//---------------------------------------------------------------------------
CxTest_CxIpcMutex::CxTest_CxIpcMutex() {

}
//---------------------------------------------------------------------------
CxTest_CxIpcMutex::~CxTest_CxIpcMutex() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxIpcMutex::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csName = xT("mutex_name_a");


    //-------------------------------------
    // hGet
    {
        CxIpcMutex mtMutex;

        CxIpcMutex::handle_t hRv;

        hRv = mtMutex.hGet();
        ////xTEST_EQ(false, hRv.bIsValid());
    }

    //-------------------------------------
    // bCreate
    {
        CxIpcMutex mtMutex;

        mtMutex.vCreate(csName);
    }

    //-------------------------------------
    // bOpen
    {
        CxIpcMutex mtMutex;

        mtMutex.vCreate(csName);
        mtMutex.vOpen(csName);
    }

    //-------------------------------------
    // bLock, bUnlock
    {
        const ulong_t culTimeout = 1000UL;

        CxIpcMutex mtMutex;

        mtMutex.vCreate(csName);
        mtMutex.vLock(culTimeout);
        mtMutex.vUnlock();
    }
}
//---------------------------------------------------------------------------
