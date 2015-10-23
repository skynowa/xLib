/**
 * \file   Operators.h
 * \brief  type operators
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

template <class T>
T &operator ++ (T &value);
    ///< increment type
template <class T>
T &operator -- (T &value);
    ///< decrement type

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Operators.cpp"
#endif
