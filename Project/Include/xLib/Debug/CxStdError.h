/**
 * \file  CxStdError.h
 * \brief standard C library last error
 */


#pragma once

#ifndef xLib_CxStdErrorH
#define xLib_CxStdErrorH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxStdError :
    public CxNonCopyable
    /// standard C library last error
{
public:
    static bool_t         isSuccess() xWARN_UNUSED_RV;
        ///< is error code success
    static int_t          get() xWARN_UNUSED_RV;
        ///< get the calling thread's last-error code value
    static void_t         set(cint_t &code);
        ///< set the last error code for the calling thread
    static void_t         reset();
        ///< set last error code to 0
    static std::tstring_t format() xWARN_UNUSED_RV;
        ///< get as string
    static std::tstring_t format(cint_t &code) xWARN_UNUSED_RV;
        ///< get last error as string

private:
                          CxStdError();
        ///< constructor
    virtual              ~CxStdError() {}
        ///< destructor
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Debug/CxStdError.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxStdErrorH
