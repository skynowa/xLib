/****************************************************************************
* Class name:  CWorkThread
* Description: work thread
* File name:   CWorkThread.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     10.12.2009 22:10:16
*
*****************************************************************************/


#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxTraceLog.h>
#include <xLib/Log/CxFileLog.h>


//---------------------------------------------------------------------------
#define WM_TEST_MSG_1  (WM_USER + 100)
//---------------------------------------------------------------------------

#if defined(xOS_WIN)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CWorkThread
CWorkThread::CWorkThread(
    const BOOL cbAutoDelete
) :
    CxThread (cbAutoDelete),
    m_uiIndex(0),
    _m_clLog (FALSE)
{
}
//---------------------------------------------------------------------------
//DONE: ~CWorkThread
CWorkThread::~CWorkThread() {

}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: uiOnRun
UINT
CWorkThread::uiOnRun(
    VOID *pData
)
{
    //xTRACEV(xT("Start thread: #%i\n"), m_uiIndex);

    UINT uiRes = 0;
    BOOL bRes  = FALSE;

    //bIsCurrent
    bRes = pthT->bIsCurrent();
    xASSERT_NOT_EQ(FALSE, m_bRes);

    for (size_t i = 0; i < /*(*piParam)*/10; ++ i, ++ uiRes) {
        bRes = bIsTimeToExit();
        xCHECK_DO(TRUE == bRes, break);

        for (size_t i = 0; i < 20; i ++) {
            //xTRACEV(xT("*\n"));
            ::Sleep(1000);
        }
    }

    //xTRACEV(xT("End thread: #%i\n"), m_uiIndex);

    return uiRes;
}
//---------------------------------------------------------------------------
//DONE: vOnEnter
VOID
CWorkThread::vOnEnter() {
    //LOG("vOnEnter");
}
//---------------------------------------------------------------------------
//DONE: vOnExit
VOID
CWorkThread::vOnExit() {
    //LOG("vOnExit");

    BOOL bRes = FALSE;

    ////bRes = thpTP->bPushTask(NULL);	//if (TRUE == bRes)		//bRelease
    /////*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
