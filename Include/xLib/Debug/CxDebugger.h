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

        template<class T>
        static VOID    vStdVectorPrintT  (const std::vector<T> &cvecT);

        template<class T1, class T2>
        static VOID    vStdMapPrintT     (const std::map<T1, T2> &cmapT);

        template<class T1, class T2>
        static VOID    vStdMultiMapPrintT(const std::multimap<T1, T2> &cmmapT);

    private:
        static BOOL    _ms_bIsEnabled;
        static tString _ms_sLogPath;

                       CxDebugger        ();
        virtual       ~CxDebugger        ();

        static BOOL    _bMsgboxPlain     (const CxReport &crpReport);
        static BOOL    _bMsgboxRtf       (const CxReport &crpReport);

        static BOOL    _bStdoutPlain     (const CxReport &crpReport);
        static BOOL    _bStdoutHtml      (const CxReport &crpReport);

        static BOOL    _bLoggingPlain    (const CxReport &crpReport);
        static BOOL    _bLoggingHtml     (const CxReport &crpReport);
};
//---------------------------------------------------------------------------
#include <Debug/CxDebugger.inl>
//---------------------------------------------------------------------------
#endif    //xLib_Debug_CxDebuggerH


/*
#include  <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <windows.h>

BOOL create_console(void)
{
  FreeConsole();
  if (AllocConsole())
  {
    int hCrt = _open_osfhandle((long) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    *stdout = *(::_fdopen(hCrt, "w"));
    ::setvbuf(stdout, NULL, _IONBF, 0);
    *stderr = *(::_fdopen(hCrt, "w"));
    ::setvbuf(stderr, NULL, _IONBF, 0);
    return TRUE;
  }
  return FALSE;
}

usage:

#ifdef DEBUG
  create_console();
#endif // DEBUG
*/
