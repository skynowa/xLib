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
#if xOS_ENV_WIN
    const std::tstring_t csName = CxString::sCreateGuid();


    CxMutex mtMutex;

    //-------------------------------------
    //hGetHandle
    {
        m_hRes = mtMutex.hGet();
        xASSERT(NULL == m_hRes);
    }

    //-------------------------------------
    //bCreate
    {
        const LPSECURITY_ATTRIBUTES lpcsaAttributes = NULL;
        const bool                  cbInitialOwner  = false;

        m_bRes = mtMutex.bCreate(lpcsaAttributes, cbInitialOwner, csName.c_str());
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bWait
    {
        const ulong_t culTimeout = 1000;

        m_bRes = mtMutex.bWait(culTimeout);
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bRelease
    {
        m_bRes = mtMutex.bRelease();
        xTEST_EQ(true, m_bRes);
    }
#elif xOS_ENV_UNIX

#endif

    return true;
}
//---------------------------------------------------------------------------
