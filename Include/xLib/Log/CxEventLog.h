/**
 * \file  CxEventLog.h
 * \brief logging to system event log
 */


#ifndef xLib_Log_CxEventLogH
#define xLib_Log_CxEventLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxEventLog :
    public CxNonCopyable
{
    public:
                CxEventLog();
           ///< constructor
       virtual ~CxEventLog();
           ///< destructor

    private:

};
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxEventLogH
