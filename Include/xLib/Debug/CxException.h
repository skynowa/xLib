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
xNAMESPACE_BEGIN(NxLib)

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

    xNO_COPY_ASSIGN(CxException)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxException.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxExceptionH
