/**
 * \file  Environment.cpp
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
#endif


namespace xl::system
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Environment::Environment(
	std::ctstring_t &a_varName
) :
	_varName{a_varName}
{
    xTEST(_isVarValid());
}
//-------------------------------------------------------------------------------------------------
bool_t
Environment::isExists() const
{
    xCHECK_RET(_varName.empty(), false);

    return _isExists_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Environment::var() const
{
    xCHECK_RET(!isExists(), std::tstring_t());

    return _var_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Environment::setVar(
    std::ctstring_t &a_value
) const
{
    xTEST_EQ(_isValueValid(a_value), true);

    _setVar_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
void_t
Environment::removeVar() const
{
    xCHECK_DO(!isExists(), return);

    _removeVar_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public / tools
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
Environment::setVars(
    const std::set<std::pair_tstring_t> &a_vars ///< vars ({"HOME=/usr/home","LOGNAME=home"})
)
{
	for (const auto &[name, value] : a_vars) {
		Environment env(name);
		env.setVar(value);
	}
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
    std::ctstring_t &a_varName
)
{
    return _expandStrings_impl(a_varName);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Environment::varPath(
	std::vec_tstring_t *out_dirPaths
)
{
    xTEST_PTR(out_dirPaths);

	std::ctstring_t varName =
	#if   xENV_WIN
		xT("Path");
	#elif xENV_UNIX
		xT("PATH");
	#endif

	std::ctstring_t &varSep =
	#if   xENV_WIN
		Const::semicolon();
	#elif xENV_UNIX
		Const::colon();
	#endif

	Environment env(varName);

	String::split(env.var(), varSep, out_dirPaths);

	Algos::vectorUnique(*out_dirPaths);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Environment::_isVarValid() const
{
    xCHECK_RET(_varName.empty(),                                      false);
    xCHECK_RET(_varName.find(Const::equal()) != std::tstring_t::npos, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Environment::_isValueValid(
    std::ctstring_t &a_varValue
) const
{
    xCHECK_RET(a_varValue.size() >= _envMax, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
