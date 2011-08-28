/**
 * \file  CxSystemLog.h
 * \brief logging to system log
 */


#ifndef xLib_Log_CxEventLogH
#define xLib_Log_CxEventLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxSystemLog :
    public CxNonCopyable
    /// logging to system event log
{
    public:
                CxSystemLog();
           ///< constructor
       virtual ~CxSystemLog();
           ///< destructor

    private:

};
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxEventLogH
