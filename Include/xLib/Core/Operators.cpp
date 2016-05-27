/**
 * \file   Operators.cpp
 * \brief  Type operators
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Operators.h"
#endif


xNAMESPACE_BEGIN2(xlib, core)


/*******************************************************************************
*   global
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
xINLINE T &
operator ++ (T &a_value)
{
    return a_value = static_cast<T>(a_value + 1);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
xINLINE T &
operator -- (T &a_value)
{
    return a_value = static_cast<T>(a_value - 1);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
