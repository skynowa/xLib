/**
 * \file  ScopeExit.h
 * \brief Scope exit
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class ScopeExit
	///< Scope exit
{
public:
	explicit
	ScopeExit(std::function<void()> a_functor) :
		_functor(a_functor)
	{
	}

   ~ScopeExit()
	{
		_functor();
	}

private:
	std::function<void()> _functor;
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
