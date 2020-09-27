/**
 * \file  Com.h
 * \brief Component Object Model (COM)
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
#if xENV_WIN

namespace xl::core
{

class Com
    /// Component Object Model (COM)
{
public:
///@name ctors, dtor
///@{
	explicit  Com(const COINIT concurrencyModel);
	virtual  ~Com();

	xNO_COPY_ASSIGN(Com)
///@}
};

} // namespace

#endif
//-------------------------------------------------------------------------------------------------
