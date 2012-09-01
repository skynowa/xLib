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
/*virtual*/
bool
CxTest_CxIpcMutex::bUnit(
    const ulonglong_t cullCaseLoops
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

        m_bRv = mtMutex.bCreate(csName);
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    // bOpen
    {
        CxIpcMutex mtMutex;

        m_bRv = mtMutex.bCreate(csName);
        xTEST_EQ(true, m_bRv);

        m_bRv = mtMutex.bOpen(csName);
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    // bLock, bUnlock
    {
        const ulong_t culTimeout = 1000UL;

        CxIpcMutex mtMutex;

        m_bRv = mtMutex.bCreate(csName);
        xTEST_EQ(true, m_bRv);

        m_bRv = mtMutex.bLock(culTimeout);
        xTEST_EQ(true, m_bRv);

        m_bRv = mtMutex.bUnlock();
        xTEST_EQ(true, m_bRv);
    }

    return true;
}
//---------------------------------------------------------------------------
