/**
 * \file   Operators.h
 * \brief  type operators
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T>
T &operator ++ (T &value);
    ///< increment type
template<typename T>
T &operator -- (T &value);
    ///< decrement type

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
