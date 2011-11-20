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
xNAMESPACE_BEGIN(NxLib)

class CxConsoleLog :
    public CxNonCopyable
    /// logging to console
{
    public:
        explicit                 CxConsoleLog(const bool bIsUseTimeStr);
            ///< constructor
        virtual                 ~CxConsoleLog();
            ///< destructor

        bool                     bWrite      (const tchar *pcszFormat, ...);
            ///< write

    private:
        static CxCriticalSection _ms_csConsole;        ///< critical section
        bool                     _m_bIsUseTimeStr;    ///< is use time string
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxConsoleLogH
