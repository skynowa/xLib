/**
 * \file  CxStdError.h
 * \brief standard C library last error
 */


#ifndef xLib_Debug_CxStdErrorH
#define xLib_Debug_CxStdErrorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxStdError :
    public CxNonCopyable
    /// standard C library last error
{
    public:
        static INT          iGet       ();
            ///< get the calling thread's last-error code value
        static std::tstring sGet       ();
            ///< get as string
        static BOOL         bSet       (const INT ciCode);
            ///< set the last error code for the calling thread
        static BOOL         bReset     ();
            ///< set last error code to 0
        static std::tstring sFormat    (const INT ciCode);
            ///< get last error as string

    private:
                            CxStdError();
            ///< constructor
        virtual            ~CxStdError();
            ///< destructor
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxStdErrorH
