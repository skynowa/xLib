/****************************************************************************
* Class name:  CxTraceLog
* Description: tracing
* File name:   CxTraceLog.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.06.2009 17:45:21
*
*****************************************************************************/


#ifndef xLib_Log_CxTraceLogH
#define xLib_Log_CxTraceLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
class CxTraceLog :
    public CxNonCopyable
{
    public:
        explicit CxTraceLog (BOOL bIsUseTimeStr);
        virtual ~CxTraceLog ();

        BOOL     bSetEnabled(BOOL bFlag);
        BOOL     bWrite     (LPCTSTR pcszFormat, ...);

    private:
        BOOL     _m_bIsEnable;
        BOOL     _m_bIsUseTimeStr;
};
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxTraceLogH
