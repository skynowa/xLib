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
class CxDebugger : public CxNonCopyable {
    public:
        static BOOL  bGetEnabled  ();
        static BOOL  bSetEnabled  (BOOL bFlag);
        static BOOL  bIsPresent   ();
        static BOOL  bBreak       ();

        static BOOL  bReportMake  (const CxReport &crpReport);
        static BOOL  bTrace       (LPCTSTR pcszFormat, ...);
        static BOOL  bTrace       (const tString &csMsg);

        //MessageBeep

        template<class T>
        static VOID  vStdVectorPrintT  (const std::vector<T> &cvecT);

        template<class T1, class T2>
        static VOID  vStdMapPrintT     (const std::map<T1, T2> &cmapT);

        template<class T1, class T2>
        static VOID  vStdMultiMapPrintT(const std::multimap<T1, T2> &cmmapT);

    private:
        static BOOL  _ms_bIsEnabled;

                     CxDebugger   ();
        virtual     ~CxDebugger   ();

        static BOOL  bMsgboxPlain (const CxReport &crpReport);
        static BOOL  bMsgboxRtf   (const CxReport &crpReport);

        static BOOL  bStdoutPlain (const CxReport &crpReport);
        static BOOL  bStdoutHtml  (const CxReport &crpReport);

        static BOOL  bLoggingPlain(const CxReport &crpReport);
        static BOOL  bLoggingHtml (const CxReport &crpReport);
};
//---------------------------------------------------------------------------
#include <Debug/CxDebugger.inl>
//---------------------------------------------------------------------------
#endif    //xLib_Debug_CxDebuggerH


//http://www.csharp-examples.net/string-format-datetime/

/*
http://lifeforce4.wordpress.com/


0 = default colour
1 = bold
4 = underlined
5 = flashing text
7 = reverse field

31 = red
32 = green
33 = orange
34 = blue
35 = purple
36 = cyan
37 = grey

40 = black background
41 = red background
42 = green background
43 = orange background
44 = blue background
45 = purple background
46 = cyan background
47 = grey background
90 = dark grey
91 = light red
92 = light green
93 = yellow
94 = light blue
95 = light purple
96 = turquoise
100 = dark grey background
101 = light red background
102 = light green background
103 = yellow background
104 = light blue background
105 = light purple background
106 = turquoise background
*/

