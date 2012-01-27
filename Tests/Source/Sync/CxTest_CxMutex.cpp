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
        ////CxMutex::TxHandle hRes = mtMutex.hGet();
        ////xTEST_EQ(false, hRes.bIsValid());
    }

    //-------------------------------------
    //bCreate
    {
        CxMutex mtMutex;

        m_bRes = mtMutex.bCreate(csName);
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bLock, bUnlock
    {
        const ulong_t culTimeout = 1000UL;

        CxMutex mtMutex;

        m_bRes = mtMutex.bCreate(csName);
        xTEST_EQ(true, m_bRes);

        m_bRes = mtMutex.bLock(culTimeout);
        xTEST_EQ(true, m_bRes);

        m_bRes = mtMutex.bUnlock();
        xTEST_EQ(true, m_bRes);
    }

    return true;
}
//---------------------------------------------------------------------------
