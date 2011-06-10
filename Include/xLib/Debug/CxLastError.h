/****************************************************************************
* Class name:  CxLastError
* Description: system last error
* File name:   CxLastError.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     25 січ. 2011 11:01:46
*
*****************************************************************************/


#ifndef xLib_Debug_CxLastErrorH
#define xLib_Debug_CxLastErrorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxLastError :
    public CxNonCopyable
{
    public:
        static ULONG   ulGet      ();
        static tString sGet       ();
        static BOOL    bSet       (const ULONG culCode);
        static BOOL    bReset     ();
        static tString sFormat    (const ULONG culCode);

        #if xTODO
            GetErrorMode
            SetErrorMode
            SetThreadErrorMode
        #endif

    private:
                       CxLastError();
        virtual       ~CxLastError();
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxLastErrorH
