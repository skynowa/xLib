/****************************************************************************
* Class name:  CxLastError
* Description: system last error
* File name:   CxLastError.h
* Compilers:   Visual C++ 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25 січ. 2011 11:01:46
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Debug_CxLastErrorH
#define xLib_Debug_CxLastErrorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxLastError : public CxNonCopyable  {
    public:
        static ULONG   ulGet      ();
        static BOOL    bSet       (ULONG ulCode);
        static BOOL    bReset     ();
        static tString sFormat    (ULONG ulCode);

        /*
        GetErrorMode
        SetErrorMode
        SetThreadErrorMode
        */

    private:
                       CxLastError();
        virtual       ~CxLastError();
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxLastErrorH
