/**
 * \file   Operators.h
 * \brief  type operators
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T>
T &operator ++ (T &value);

template<typename T>
T &operator -- (T &value);

} // namespace
//-------------------------------------------------------------------------------------------------

#include "Operators.inl"
