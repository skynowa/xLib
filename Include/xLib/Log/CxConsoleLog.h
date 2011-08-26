/**
 * \file  CxConsoleLog.h
 * \brief logging to console
 */


#ifndef xLib_Log_CxConsoleLogH
#define xLib_Log_CxConsoleLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
class CxConsoleLog :
    public CxNonCopyable
    /// logging to console
{
    public:
                                 CxConsoleLog(BOOL bIsUseTimeStr);
        virtual                 ~CxConsoleLog();

        BOOL                     bWrite      (LPCTSTR pcszFormat, ...);

    private:
    #if defined(xOS_WIN)
        static CxCriticalSection _ms_csConsole;
    #elif defined(xOS_LINUX)

    #endif

        BOOL                     _m_bIsUseTimeStr;
};
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxConsoleLogH
