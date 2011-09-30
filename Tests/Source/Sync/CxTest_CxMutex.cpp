/****************************************************************************
* Class name:  CxTest_CxMutex
* Description: test CxMutex
* File name:   CxTest_CxMutex.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


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
    const std::tstring csName = CxString::sCreateGuid();


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
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bOpen
    {
        const ULONG culAccess       = MUTEX_ALL_ACCESS;
        const BOOL  cbInheritHandle = FALSE;

        m_bRes = mtMutex.bOpen(culAccess, cbInheritHandle,  csName.c_str());
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bWait
    {
        const ULONG culTimeout = 1000;

        m_bRes = mtMutex.bWait(culTimeout);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bRelease
    {
        m_bRes = mtMutex.bRelease();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }
#elif defined(xOS_ENV_UNIX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
