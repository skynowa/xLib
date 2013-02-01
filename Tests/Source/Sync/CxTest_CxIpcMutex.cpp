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
CxTest_CxIpcMutex::unit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csName = xT("mutex_name_a");


    xTEST_CASE("CxIpcMutex::handle", cullCaseLoops)
    {
        CxIpcMutex mtMutex;

        CxIpcMutex::handle_t hRv;

        hRv = mtMutex.handle();
        ////xTEST_EQ(false, hRv.bIsValid());
    }

    xTEST_CASE("CxIpcMutex::create", 1)
    {
        CxIpcMutex mtMutex;

        mtMutex.create(csName);
    }

    xTEST_CASE("CxIpcMutex::open", 1)
    {
        CxIpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.open(csName);
    }

    xTEST_CASE("CxIpcMutex::lock CxIpcMutex::unlock", cullCaseLoops)
    {
        const ulong_t culTimeout = 1000UL;

        CxIpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.lock(culTimeout);
        mtMutex.unlock();
    }
}
//---------------------------------------------------------------------------
