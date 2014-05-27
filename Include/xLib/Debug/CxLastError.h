/**
 * \file  CxLastError.h
 * \brief system last error
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, debug)

class CxLastError
    /// system last error
{
public:
    static
    bool_t         isSuccess() xWARN_UNUSED_RV;
        ///< is error code success
    static
    ulong_t        get() xWARN_UNUSED_RV;
        ///< get the calling thread's last-error code value
    static
    void_t         set(culong_t &code);
        ///< set the last error code for the calling thread
    static
    void_t         reset();
        ///< set last error code to success value (0)
    static
    std::tstring_t format() xWARN_UNUSED_RV;
        ///< get as string
    static
    std::tstring_t format(culong_t &code) xWARN_UNUSED_RV;
        ///< get last error as string

private:
                   CxLastError();
        ///< constructor
                  ~CxLastError() {}
        ///< destructor

    static
    ulong_t        _nativeCodeSuccess() xWARN_UNUSED_RV;
        ///< native success code

    xNO_COPY_ASSIGN(CxLastError)

xPLATFORM:
    static
    bool_t         _isSuccess_impl() xWARN_UNUSED_RV;
    static
    ulong_t        _get_impl() xWARN_UNUSED_RV;
    static
    void_t         _set_impl(culong_t &code);
    static
    std::tstring_t _format_impl(culong_t &a_code) xWARN_UNUSED_RV;
    static
    ulong_t        _nativeCodeSuccess_impl() xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#include "CxLastError.inl"
