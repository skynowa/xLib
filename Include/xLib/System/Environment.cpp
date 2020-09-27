/**
 * \file  Environment.inl
 * \brief system environment variables
 */


#include "Environment.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/Debugger.h>

#if   xENV_WIN
    #include "Platform/Win/Environment_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Environment_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/Environment_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/Environment_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/Environment_apple.inl"
    #endif
#endif


namespace xl::system
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Environment::isExists(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_RET(a_varName.empty(), false);

    return _isExists_impl(a_varName);
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Environment::isVarValid(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_RET(a_varName.empty(),                                   false);
    xCHECK_RET(a_varName.find(Const::equal()) != std::string::npos, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Environment::isValueValid(
    std::ctstring_t &a_varValue
)
{
    xTEST_NA(a_varValue);

    xCHECK_RET(a_varValue.size() >= xENV_MAX, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Environment::var(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_RET(!isExists(a_varName), std::tstring_t());

    return _var_impl(a_varName);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Environment::setVar(
    std::ctstring_t &a_varName,
    std::ctstring_t &a_value
)
{
    xTEST_EQ(isVarValid(a_varName), true);
    xTEST_EQ(isVarValid(a_value), true);

    _setVar_impl(a_varName, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Environment::setVars(
    const std::set<std::pair_tstring_t> &a_vars ///< vars ({"HOME=/usr/home","LOGNAME=home"})
)
{
	for (const auto &[name, value] : a_vars) {
		setVar(name, value);
	}
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Environment::deleteVar(
    std::ctstring_t &a_varName
)
{
    xTEST_NA(a_varName);

    xCHECK_DO(!isExists(a_varName), return);

    _deleteVar_impl(a_varName);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Environment::values(
    std::vec_tstring_t *a_values
)
{
    xTEST_PTR(a_values);

    xCHECK_DO(a_values != nullptr, a_values->clear());

    _values_impl(a_values);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Environment::expandStrings(
    std::ctstring_t &a_var
)
{
    xTEST_EQ(a_var.empty(), false);

    return _expandStrings_impl(a_var);
}
//-------------------------------------------------------------------------------------------------

} // namespace
