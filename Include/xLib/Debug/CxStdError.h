/**
 * \file  CxStdError.h
 * \brief standard C library last error
 */


#ifndef xLib_Debug_CxStdErrorH
#define xLib_Debug_CxStdErrorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxStdError :
    public CxNonCopyable
    /// standard C library last error
{
    public:
        static int          iGet      ();
            ///< get the calling thread's last-error code value
        static std::tstring sGet      ();
            ///< get as string
        static bool         bSet      (const int ciCode);
            ///< set the last error code for the calling thread
        static bool         bReset    ();
            ///< set last error code to 0
        static std::tstring sFormat   (const int ciCode);
            ///< get last error as string

    private:
                            CxStdError();
            ///< constructor
        virtual            ~CxStdError();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxStdErrorH
