/****************************************************************************
* Class name:  CxDebugger
* Description: debbuger
* File name:   CxDebugger.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.11.2009 16:39:23
*
*****************************************************************************/


#ifndef xLib_Debug_CxDebuggerH
#define xLib_Debug_CxDebuggerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Debug/CxReport.h>
//---------------------------------------------------------------------------
class CxReport;

class CxDebugger :
    public CxNonCopyable
{
    public:
        static BOOL    bGetEnabled       ();
        static BOOL    bSetEnabled       (const BOOL cbFlag);
        static BOOL    bIsPresent        ();
        static BOOL    bBreak            ();

        static BOOL    bSetLogPath       (const tString &csFilePath);
        static tString sGetLogPath       ();
        static BOOL    bReportMake       (const CxReport &crpReport);
        static BOOL    bTrace            (LPCTSTR pcszFormat, ...);
        static BOOL    bTrace            (const tString &csMsg);
        static BOOL    bBeep             (const ULONG culFrequency = 800, const ULONG culDuration = 100);

    private:
        static BOOL    _ms_bIsEnabled;
        static tString _ms_sLogPath;

                       CxDebugger        ();
        virtual       ~CxDebugger        ();

        static BOOL    _bMsgboxPlain     (const CxReport &crpReport);
        static BOOL    _bMsgboxFormated  (const CxReport &crpReport);

        static BOOL    _bStdoutPlain     (const CxReport &crpReport);
        static BOOL    _bStdoutHtml      (const CxReport &crpReport);

        static BOOL    _bLoggingPlain    (const CxReport &crpReport);
        static BOOL    _bLoggingHtml     (const CxReport &crpReport);
};
//---------------------------------------------------------------------------
#endif    //xLib_Debug_CxDebuggerH
