/****************************************************************************
* Class name:  CWorkThread
* Description: ������� �����
* File name:   CWorkThread.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     10.12.2009 22:10:16
*
*****************************************************************************/


#if defined(xOS_WIN)
#include "CWorkThread.h"

#include <xLib/CxString.h>
#include <xLib/Sync/CxThreadPool.h>
//---------------------------------------------------------------------------


/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CWorkThread
CWorkThread::CWorkThread(BOOL bIsPaused, BOOL bAutoDelete, BOOL bIsUsingCOM) :
    CxThread (bIsPaused, bAutoDelete, bIsUsingCOM),
    m_uiIndex(0)
{
}
//---------------------------------------------------------------------------
//TODO: ~CWorkThread
CWorkThread::~CWorkThread() {

}
//---------------------------------------------------------------------------



/****************************************************************************
*    Protected methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: uiOnRun
UINT CWorkThread::uiOnRun(VOID *pData) {
    /*LOG*/_m_clLog.bWrite(xT("Start thread: #%i\n"), m_uiIndex);

    UINT uiRes = 0;
    BOOL bRes  = FALSE;

    std::vector<tString> *pvecsThis = static_cast<std::vector<tString> *>(pData);
    /*DEBUG*/xASSERT_RET(NULL != pvecsThis, 0);

    for (UINT i = 0; i < pvecsThis->size(); i ++, uiRes ++) {
        //-------------------------------------
        //�� ���� �� ����� ��� ���������������
        bRes = bIsTimeToExit();
        xCHECK_DO(FALSE == bRes, break);


        /*LOG*/_m_clLog.bWrite(xT("%i: %s\n"), i, pvecsThis->at(i).c_str());
        bSleep(500);
    }

    /*LOG*///_m_clLog.bWrite(xT("End thread: #%i\n"), m_uiIndex);

    return uiRes;
}
//---------------------------------------------------------------------------
//TODO: vOnEnter
VOID CWorkThread::vOnEnter() {
    //LOG("vOnEnter");
}
//---------------------------------------------------------------------------
//TODO: vOnExit
VOID CWorkThread::vOnExit() {
    //LOG("vOnExit");
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
