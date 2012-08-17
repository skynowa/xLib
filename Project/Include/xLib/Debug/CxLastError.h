/**
 * \file  CxLastError.h
 * \brief system last error
 */


#ifndef xLib_Debug_CxLastErrorH
#define xLib_Debug_CxLastErrorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxLastError :
    private CxNonCopyable
    /// system last error
{
    public:
        static ulong_t        ulGet      ();
            ///< get the calling thread's last-error code value
        static std::tstring_t sGet       ();
            ///< get as string
        static bool           bSet       (const ulong_t culCode);
            ///< set the last error code for the calling thread
        static bool           bReset     ();
            ///< set last error code to 0
        static std::tstring_t sFormat    (const ulong_t culCode);
            ///< get last error as string

    private:
                              CxLastError();
            ///< constructor
        virtual              ~CxLastError();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxLastErrorH
