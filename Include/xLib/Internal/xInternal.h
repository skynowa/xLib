/**
 * \file   xInternal.h
 * \brief  for internal use
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, internal)
//-------------------------------------------------------------------------------------------------
///@name Macroses
///@{
#define xPLATFORM_IMPL private
    ///< for platform code
///@}
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(enums)

template<class crossT, class implT>
struct Type
    ///< enum values
{
    crossT cross;  ///< crossplatform value
    implT  impl;   ///< implementation (native) value
};

template<class crossT, class implT, std::csize_t sizeT>
struct Types
    ///< convert implementation (native) <-> crossplatform values
{
    Type<crossT, implT> values[sizeT]; ///< crossplatform to implementation (native) values

    crossT
    toCross(std::cssize_t &a_value) const
    {
        return static_cast<crossT>( this->values[a_value].cross );
    }
        ///< implementation (native) value to crossplatform
    implT
    toImpl(std::cssize_t &a_value) const
    {
        return static_cast<implT>( this->values[a_value].impl );
    }
        ///< crossplatform value to implementation (native)
};

xNAMESPACE_END(enums)
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_END(xlib, internal)
//-------------------------------------------------------------------------------------------------
