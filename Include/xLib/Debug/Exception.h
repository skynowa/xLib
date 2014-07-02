/**
 * \file  Exception.h
 * \brief exception
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, debug)

class Exception
    /// exception
{
public:
                      Exception() {}
        ///< constructor
    virtual          ~Exception() {}
        ///< destructor

    std::ctstring_t & what() const xWARN_UNUSED_RV;
        ///< get message
    template<class T>
    Exception &     operator << (const T &msgT);
        ///< put message

private:
    std::tstring_t    _msgT;
        ///< message
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#include "Exception.inl"
