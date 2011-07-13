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

#include <xLib/Sync/CxThreadPool.h>
//---------------------------------------------------------------------------
CxCriticalSection g_csCounter;
volatile size_t   g_uiLinesCount = 0;
//---------------------------------------------------------------------------


/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CWorkThread
CWorkThread::CWorkThread(BOOL bIsPaused, BOOL bAutoDelete) :
    CxThread    (bIsPaused, bAutoDelete),
    _m_clLog    (FALSE),
    m_uiIndex   (0)
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
    /*LOG*///_m_clLog.bWrite(xT("uiOnRun start: #%i"), m_uiIndex);

    UINT uiRes = 0;
    BOOL bRes  = FALSE;

    std::vector<tString> *pvecsThis = static_cast<std::vector<tString> *>(pData);
    /*DEBUG*/xASSERT_RET(NULL != pvecsThis, 0);

    ////for (UINT i = 0; i < pvecsThis->size(); i ++, uiRes ++) {
    ////	//-------------------------------------
    ////	//�� ���� �� ����� ��� ���������������
    ////	bRes = bIsTimeToExit();
    ////	xCHECK_DO(TRUE == bRes, break);
    ////

    ////	/*LOG*///_m_clLog.bWrite(xT("Thread #%i  %i: %s"), m_uiIndex, i, pvecsThis->at(i).c_str());
    ////	/*LOG*///_m_clLog.bWrite(xT("*"));
    ////	bSleep(300);
    ////}

    for (; ;) {
        //-------------------------------------
        //�� ���� �� ����� ��� ���������������
        bRes = bIsTimeToExit();
        xCHECK_DO(TRUE == bRes, break);

        {
            CxAutoCriticalSection CS(g_csCounter);

            if (g_uiLinesCount >= /*pvecsThis->size()*/100) {
                break;
            }

            /*LOG*/_m_clLog.bWrite(xT("Thread #%i  %i: %s"), m_uiIndex, g_uiLinesCount, pvecsThis->at(g_uiLinesCount).c_str());

            ++ g_uiLinesCount;
        }

        bSleep(1000);
    }


    /*LOG*///_m_clLog.bWrite(xT("uiOnRun stop: #%i"), m_uiIndex);

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
    //::OutputDebugString(xT("vOnExit (virtual)\n"));
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private methods
*
*****************************************************************************/

#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
