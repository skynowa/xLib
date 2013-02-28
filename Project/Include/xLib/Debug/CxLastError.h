/**
 * \file  CxLastError.h
 * \brief system last error
 */


#ifndef xLib_Debug_CxLastErrorH
#define xLib_Debug_CxLastErrorH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxLastError :
    private CxNonCopyable
    /// system last error
{
public:
    static ulong_t        get        () xWARN_UNUSED_RV;
        ///< get the calling thread's last-error code value
    static std::tstring_t toString   () xWARN_UNUSED_RV;
        ///< get as string
    static void           set        (const ulong_t &culCode);
        ///< set the last error code for the calling thread
    static void           reset      ();
        ///< set last error code to 0
    static std::tstring_t format     (const ulong_t &culCode) xWARN_UNUSED_RV;
        ///< get last error as string

private:
                          CxLastError();
        ///< constructor
    virtual              ~CxLastError();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Debug_CxLastErrorH
