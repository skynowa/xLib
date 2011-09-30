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
        explicit                 CxConsoleLog(const BOOL bIsUseTimeStr);
            ///< constructor
        virtual                 ~CxConsoleLog();
        	///< destructor

        BOOL                     bWrite      (LPCTSTR pcszFormat, ...);
        	///< write

    private:
    #if defined(xOS_ENV_WIN)
        static CxCriticalSection _ms_csConsole;		///< critical section
    #endif

        BOOL                     _m_bIsUseTimeStr;	///< is use time string
};
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxConsoleLogH
