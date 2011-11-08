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
        static ULONG        ulGet      ();
            ///< get the calling thread's last-error code value
        static std::string_t sGet       ();
            ///< get as string
        static BOOL         bSet       (const ULONG culCode);
            ///< set the last error code for the calling thread
        static BOOL         bReset     ();
            ///< set last error code to 0
        static std::string_t sFormat    (const ULONG culCode);
            ///< get last error as string

    private:
                            CxLastError();
            ///< constructor
        virtual            ~CxLastError();
            ///< destructor
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxLastErrorH
