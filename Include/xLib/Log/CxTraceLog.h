/**
 * \file  CxTraceLog.h
 * \brief tracing
 */


#ifndef xLib_Log_CxTraceLogH
#define xLib_Log_CxTraceLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxTraceLog :
    public CxNonCopyable
    /// tracing
{
    public:
        explicit CxTraceLog (const bool cbIsUseTimeStr);
            ///< constructor
        virtual ~CxTraceLog ();
            ///< destructor

        bool     bSetEnabled(const bool cbFlag);
            ///< set enabled
        bool     bWrite     (const tchar *pcszFormat, ...);
            ///< write

    private:
        bool     _m_bIsEnable;        ///< is enabled
        bool     _m_bIsUseTimeStr;    ///< is use time string
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxTraceLogH
