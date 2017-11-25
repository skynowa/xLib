/**
 * \file   Algos.cpp
 * \brief  Algorithms
 */


#include "Algos.h"


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Algos::startsWith(
    std::ctstring_t &a_value,
    std::ctstring_t &a_prefix
)
{
    return a_value.size() >= a_prefix.size() && a_value.substr(0, a_prefix.size()) == a_prefix;
}
//-------------------------------------------------------------------------------------------------
bool_t
Algos::endsWith(
    std::ctstring_t &a_value,
    std::ctstring_t &a_suffix
)
{
    return a_value.size() >= a_suffix.size() &&
        a_value.substr(a_value.size() - a_suffix.size(), a_suffix.size()) == a_suffix;
}
//-------------------------------------------------------------------------------------------------
bool_t
Algos::contains(
    std::ctstring_t &a_value,
    std::ctstring_t &a_infix
)
{
    return a_value.find(a_infix) != std::tstring_t::npos;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
