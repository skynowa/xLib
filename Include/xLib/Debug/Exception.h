/**
 * \file  Exception.h
 * \brief exception
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, debug)

class Exception
    /// exception
{
public:
                      Exception() = default;
    virtual          ~Exception() = default;

    std::ctstring_t & what() const;
        ///< get message
    template<typename T>
    Exception &       operator << (const T &msgT);

private:
    std::tstring_t    _msgT;
        ///< message
};

xNAMESPACE_END2(xl, debug)
//-------------------------------------------------------------------------------------------------
#include "Exception.inl"
