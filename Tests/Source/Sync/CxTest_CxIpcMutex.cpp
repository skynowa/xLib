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


    xTEST_CASE("CxIpcMutex::hGet", cullCaseLoops)
    {
        CxIpcMutex mtMutex;

        CxIpcMutex::handle_t hRv;

        hRv = mtMutex.hHandle();
        ////xTEST_EQ(false, hRv.bIsValid());
    }

    xTEST_CASE("CxIpcMutex::create", 1)
    {
        CxIpcMutex mtMutex;

        mtMutex.create(csName);
    }

    xTEST_CASE("CxIpcMutex::vOpen", 1)
    {
        CxIpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.vOpen(csName);
    }

    xTEST_CASE("CxIpcMutex::vLock CxIpcMutex::vUnlock", cullCaseLoops)
    {
        const ulong_t culTimeout = 1000UL;

        CxIpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.vLock(culTimeout);
        mtMutex.vUnlock();
    }
}
//---------------------------------------------------------------------------
