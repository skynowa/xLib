/**
 * \file  CxConsoleLog.h
 * \brief logging to console
 */


#ifndef xLib_Log_CxConsoleLogH
#define xLib_Log_CxConsoleLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMutex;

class CxConsoleLog :
    private CxNonCopyable
    /// logging to console
{
    public:
        explicit                 CxConsoleLog(const bool bIsUseTimeStr);
            ///< constructor
        virtual                 ~CxConsoleLog();
            ///< destructor

        bool                     bWrite      (const tchar_t *pcszFormat, ...);
            ///< write

    private:
        static CxMutex _ms_csConsole;        ///< critical section
        bool                     _m_bIsUseTimeStr;    ///< is use time string
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxConsoleLogH
