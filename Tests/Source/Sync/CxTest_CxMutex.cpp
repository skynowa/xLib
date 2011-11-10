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
BOOL
CxTest_CxMutex::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_ENV_WIN)
    const std::string_t csName = CxString::sCreateGuid();


    CxMutex mtMutex;

    //-------------------------------------
    //hGetHandle
    {
        m_hRes = mtMutex.hGetHandle();
        xASSERT(NULL == m_hRes);
    }

    //-------------------------------------
    //bCreate
    {
        const LPSECURITY_ATTRIBUTES lpcsaAttributes = NULL;
        const BOOL                  cbInitialOwner  = FALSE;

        m_bRes = mtMutex.bCreate(lpcsaAttributes, cbInitialOwner, csName.c_str());
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bOpen
    {
        const ULONG culAccess       = MUTEX_ALL_ACCESS;
        const BOOL  cbInheritHandle = FALSE;

        m_bRes = mtMutex.bOpen(culAccess, cbInheritHandle,  csName.c_str());
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bWait
    {
        const ULONG culTimeout = 1000;

        m_bRes = mtMutex.bWait(culTimeout);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bRelease
    {
        m_bRes = mtMutex.bRelease();
        xTEST_DIFF(FALSE, m_bRes);
    }
#elif defined(xOS_ENV_UNIX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
