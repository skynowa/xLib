/**
 * \file   xInternal.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Internal/xInternal.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

xNAMESPACE2_BEGIN(NxInternal, NxEnum)

struct Type
{
    ssize_t cross;
    ssize_t impl;
};

template<std::csize_t sizeT>
struct Types
    ///< convert implementation (native) <-> crossplatform values
{
    Type values[sizeT]; ///< crossplatform to native values

    template<class T>
    T toCross(std::cssize_t &a_value) const
    {
        return static_cast<T>( this->values[a_value].cross );
    }
        ///< implementation (native) value to crossplatform
    template<class T>
    T toImpl(std::cssize_t &a_value) const
    {
        return static_cast<T>( this->values[a_value].impl );
    }
        ///< crossplatform value to implementation (native)
};

xNAMESPACE2_END(NxInternal, NxEnum)

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
