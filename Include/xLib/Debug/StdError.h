/**
 * \file  StdError.h
 * \brief standard C library last error
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, debug)

class StdError
    /// standard C library last error
{
public:
	xNO_DEFAULT_CONSTRUCT(StdError)
	xNO_COPY_ASSIGN(StdError)

    static
    bool_t         isSuccess();
        ///< is error code success
    static
    int_t          get();
        ///< get the calling thread's last-error code value
    static
    void_t         set(cint_t &code);
        ///< set the last error code for the calling thread
    static
    void_t         reset();
        ///< set last error code to 0
    static
    std::tstring_t format();
        ///< get as string
    static
    std::tstring_t format(cint_t &code);
        ///< get last error as string

private:
    static
    int_t          _stdCodeSuccess();
        ///< native success code

xPLATFORM_IMPL:
    static
    std::tstring_t _format_impl(cint_t &code);
};

xNAMESPACE_END2(xl, debug)
//-------------------------------------------------------------------------------------------------
