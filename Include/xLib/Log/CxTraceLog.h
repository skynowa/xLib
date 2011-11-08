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
class CxTraceLog :
    public CxNonCopyable
    /// tracing
{
    public:
        explicit CxTraceLog (const BOOL cbIsUseTimeStr);
            ///< constructor
        virtual ~CxTraceLog ();
            ///< destructor

        BOOL     bSetEnabled(const BOOL cbFlag);
            ///< set enabled
        BOOL     bWrite     (const char_t *pcszFormat, ...);
            ///< write

    private:
        BOOL     _m_bIsEnable;        ///< is enabled
        BOOL     _m_bIsUseTimeStr;    ///< is use time string
};
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxTraceLogH
