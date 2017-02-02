/**
 * \file   Algos.cpp
 * \brief  Algorithms
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Algos.h"
#endif


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Algos::startsWith(
    std::ctstring_t &a_value,
    std::ctstring_t &a_prefix
)
{
    return a_value.size() >= a_prefix.size() && a_value.substr(0, a_prefix.size()) == a_prefix;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Algos::endsWith(
    std::ctstring_t &a_value,
    std::ctstring_t &a_suffix
)
{
    return a_value.size() >= a_suffix.size() &&
        a_value.substr(a_value.size() - a_suffix.size(), a_suffix.size()) == a_suffix;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Algos::contains(
    std::ctstring_t &a_value,
    std::ctstring_t &a_infix
)
{
    return a_value.find(a_infix) != std::tstring_t::npos;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
