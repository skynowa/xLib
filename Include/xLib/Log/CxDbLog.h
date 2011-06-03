/****************************************************************************
* Class name:  CxDbLog
* Description: logging to DB
* File name:   CxDbLog.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.06.2009 17:55:15
*
*****************************************************************************/


#ifndef xLib_Log_CxDbLogH
#define xLib_Log_CxDbLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
class CxDbLog :
    public CxNonCopyable
{
    public:
                CxDbLog();
       virtual ~CxDbLog();

    private:
};
//---------------------------------------------------------------------------
#endif    //xLib_Log_CxDbLogH
