/**
 * \file  CxLastError.h
 * \brief system last error
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxLastError :
    public CxNonCopyable
    /// system last error
{
public:
    static bool_t         isSuccess() xWARN_UNUSED_RV;
        ///< is error code success
    static ulong_t        get() xWARN_UNUSED_RV;
        ///< get the calling thread's last-error code value
    static void_t         set(culong_t &code);
        ///< set the last error code for the calling thread
    static void_t         reset();
        ///< set last error code to success value (0)
    static std::tstring_t format() xWARN_UNUSED_RV;
        ///< get as string
    static std::tstring_t format(culong_t &code) xWARN_UNUSED_RV;
        ///< get last error as string

private:
                          CxLastError();
        ///< constructor
    virtual              ~CxLastError() {}
        ///< destructor
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Debug/CxLastError.cpp>
#endif
