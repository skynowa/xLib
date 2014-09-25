/**
 * \file  StdError.h
 * \brief standard C library last error
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, debug)

class StdError
    /// standard C library last error
{
public:
    static
    bool_t         isSuccess() xWARN_UNUSED_RV;
        ///< is error code success
    static
    int_t          get() xWARN_UNUSED_RV;
        ///< get the calling thread's last-error code value
    static
    void_t         set(cint_t &code);
        ///< set the last error code for the calling thread
    static
    void_t         reset();
        ///< set last error code to 0
    static
    std::tstring_t format() xWARN_UNUSED_RV;
        ///< get as string
    static
    std::tstring_t format(cint_t &code) xWARN_UNUSED_RV;
        ///< get last error as string

private:
                   StdError();
        ///< constructor
                  ~StdError() {}
        ///< destructor

    static
    int_t          _stdCodeSuccess() xWARN_UNUSED_RV;
        ///< native success code

    xNO_COPY_ASSIGN(StdError)

xPLATFORM:
    static
    std::tstring_t _format_impl(cint_t &code) xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "StdError.inl"
#endif
