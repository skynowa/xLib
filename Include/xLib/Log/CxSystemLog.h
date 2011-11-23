/**
 * \file  CxSystemLog.h
 * \brief logging to system log
 */


#ifndef xLib_Log_CxEventLogH
#define xLib_Log_CxEventLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSystemLog :
    public CxNonCopyable
    /// logging to system event log
{
    public:
        enum ELevel
            /// log level
        {
            lvEmerg    = 0,
            lvAlert    = 1,
            lvCritical = 2,
            lvError    = 3,
            lvWarning  = 4,
            lvNotice   = 5,
            lvInfo     = 6,
            lvDebug    = 7
        };

        explicit CxSystemLog(const std::tstring_t &csLogName);
            ///< constructor
        virtual ~CxSystemLog();
            ///< destructor

        bool     bSetEnabled(const bool cbFlag);
            ///< set enabled
        bool     bWrite     (const ELevel lvLevel, const tchar_t *pcszFormat, ...);
            ///< write to log

    private:
        bool     _m_bIsEnable;        ///< is enabled

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxEventLogH
