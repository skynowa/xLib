/**
 * \file  Exception.h
 * \brief exception
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::debug
{

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

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Exception.inl"
