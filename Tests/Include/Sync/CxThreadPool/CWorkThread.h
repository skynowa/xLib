/****************************************************************************
* Class name:  CWorkThread
* Description: ������� �����
* File name:   CWorkThread.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     10.12.2009 22:10:16
*
*****************************************************************************/


#ifndef CWorkThreadH
#define CWorkThreadH
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxTraceLog.h>
#include <xLib/Log/CxFileLog.h>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
class CWorkThread :
    public CxThread
{
    public:
        size_t       m_uiIndex;

                     CWorkThread(BOOL bIsPaused, BOOL bAutoDelete, BOOL bIsUsingCOM);
        virtual     ~CWorkThread();

    protected:
        virtual UINT uiOnRun    (VOID *pData);	/*overload*/
        virtual VOID vOnEnter   ();			    /*overload*/
        virtual VOID vOnExit    ();			    /*overload*/

    private:
        CxConsoleLog _m_clLog;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif	//CWorkThreadH
