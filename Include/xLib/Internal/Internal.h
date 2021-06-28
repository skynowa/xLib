/**
 * \file   Internal.h
 * \brief  for internal use
 */


#pragma once

#include <xLib/Core/Core.h>


namespace xl::internal
{

//-------------------------------------------------------------------------------------------------
///@name Macroses
///@{
#define xPUBLIC_STATIC public
    ///< for visual convenience
#define xPRIVATE_STATIC private
    ///< for visual convenience
#define xPLATFORM_IMPL private
    ///< platform implementation code
///@}
//-------------------------------------------------------------------------------------------------
///@name Enum internals
///@{
namespace enums
{

template<typename crossT, typename implT>
struct Type
    ///< enum values
{
    crossT cross;  ///< crossplatform value
    implT  impl;   ///< implementation (native) value
};

template<
	typename     crossT,
	typename     implT,
	std::csize_t sizeT
	>
class Types
    ///< convert implementation (native) <-> crossplatform values
{
public:
    const Type<crossT, implT> values[sizeT]; ///< crossplatform to implementation (native) values

    crossT
    toCross(std::cssize_t a_value) const
    {
        return static_cast<crossT>( this->values[a_value].cross );
    }
        ///< implementation (native) value to crossplatform
    implT
    toImpl(std::cssize_t a_value) const
    {
        return static_cast<implT>( this->values[a_value].impl );
    }
        ///< crossplatform value to implementation (native)
};

} // namespace
///@}
//-------------------------------------------------------------------------------------------------

} // namespace
