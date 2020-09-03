/**
 * \file  NativeError.h
 * \brief system last error
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, debug)

class NativeError
    /// system last error
{
public:
	xNO_DEFAULT_CONSTRUCT(NativeError)
	xNO_COPY_ASSIGN(NativeError)

    static
    bool_t         isSuccess();
        ///< is error code success
    static
    ulong_t        get();
        ///< get the calling thread's last-error code value
    static
    void_t         set(culong_t &code);
        ///< set the last error code for the calling thread
    static
    void_t         reset();
        ///< set last error code to success value (0)
    static
    std::tstring_t format();
        ///< get as string
    static
    std::tstring_t format(culong_t &code);
        ///< get last error as string

private:
    static
    ulong_t        _nativeCodeSuccess();
        ///< native success code

xPLATFORM_IMPL:
    static
    bool_t         _isSuccess_impl();
    static
    ulong_t        _get_impl();
    static
    void_t         _set_impl(culong_t &code);
    static
    std::tstring_t _format_impl(culong_t &a_code);
    static
    ulong_t        _nativeCodeSuccess_impl();
};

xNAMESPACE_END2(xl, debug)
//-------------------------------------------------------------------------------------------------
