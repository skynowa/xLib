/**
 * \file   CxTest_CxMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxMutex.h>


//---------------------------------------------------------------------------
CxTest_CxMutex::CxTest_CxMutex() {

}
//---------------------------------------------------------------------------
CxTest_CxMutex::~CxTest_CxMutex() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxMutex::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    const std::tstring_t csName = CxString::sCreateGuid();


    

    //-------------------------------------
    //hGet
    {
        ////CxMutex::handle_t hRv = mtMutex.hGet();
        ////xTEST_EQ(false, hRv.bIsValid());
    }

    //-------------------------------------
    //bCreate
    {
        CxMutex mtMutex;

        m_bRv = mtMutex.bCreate(csName);
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bLock, bUnlock
    {
        const ulong_t culTimeout = 1000UL;

        CxMutex mtMutex;

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
