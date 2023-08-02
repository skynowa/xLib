/**
 * \file  IGet.h
 * \brief Getter
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

template<typename T>
class IGet
    /// Getter
{
public:
///\name operators
///\{
			 IGet() = default;
	virtual ~IGet() = default;
///\}

    virtual T get() const = 0;
        ///< get
};

} // namespace
//-------------------------------------------------------------------------------------------------
