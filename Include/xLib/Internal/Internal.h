/**
 * \file  Internal.h
 * \brief for internal use
 *
 * \internal
 */


#pragma once

#include <xLib/Core/Core.h>


namespace xl::internal
{

//-------------------------------------------------------------------------------------------------
///\name Macroses
///\{
#define xPUBLIC_STATIC public
    ///< for visual convenience
#define xPRIVATE_STATIC private
    ///< for visual convenience
#define xPLATFORM_IMPL private
    ///< platform implementation code
///\}
//-------------------------------------------------------------------------------------------------
///\name Enums
///\{
namespace enums
{

template<
	typename CrossT,
	typename ImplT
	>
struct Item
    /// enum values
{
	const CrossT cross {}; ///< crossplatform value
	const ImplT  impl {};  ///< implementation (native) value
};

template<
	typename     CrossT,
	typename     ImplT,
	std::csize_t SizeT
	>
class Types
    /// convert implementation (native) <-> crossplatform values
{
public:
	// TOOD: array -> map
    const Item<CrossT, ImplT> items[SizeT] {};
        ///< crossplatform to implementation (native) values

    CrossT
    toCross(std::cssize_t a_idx) const
    {
        return static_cast<CrossT>(items[a_idx].cross);
    }
        ///< implementation (native) value to crossplatform
    ImplT
    toImpl(std::cssize_t a_idx) const
    {
        return static_cast<ImplT>(items[a_idx].impl);
    }
        ///< crossplatform value to implementation (native)
};

} // namespace
///\}
//-------------------------------------------------------------------------------------------------

} // namespace
