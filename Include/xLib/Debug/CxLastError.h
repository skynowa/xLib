/**
 * \file  CxLastError.h
 * \brief system last error
 */


#ifndef xLib_Debug_CxLastErrorH
#define xLib_Debug_CxLastErrorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxLastError :
    public CxNonCopyable
    /// system last error
{
    public:
        static ULONG   ulGet      ();
        static std::tstring sGet       ();
        static BOOL    bSet       (const ULONG culCode);
        static BOOL    bReset     ();
        static std::tstring sFormat    (const ULONG culCode);

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
