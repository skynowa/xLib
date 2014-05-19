/**
 * \file  CxException.h
 * \brief exception
 */


#pragma once

#ifndef xLib_CxExceptionH
#define xLib_CxExceptionH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, debug)

class CxException
    /// exception
{
public:
                      CxException() {}
        ///< constructor
    virtual          ~CxException() {}
        ///< destructor

    std::ctstring_t & what() const xWARN_UNUSED_RV;
        ///< get message
    template<class T>
    CxException &     operator << (const T &msgT);
        ///< put message

private:
    std::tstring_t    _msgT;
        ///< message
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#include "CxException.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxExceptionH
