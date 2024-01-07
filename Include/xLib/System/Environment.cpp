/**
 * \file  Environment.cpp
 * \brief system environment variables
 */


#include "Environment.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
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
*    public / constants
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::csize_t Environment::_envMax
	#if   xENV_WIN
		#if   xCOMPILER_MS
			{_MAX_ENV};
		#else
			{32767}; // custom define
		#endif
	#elif xENV_UNIX
		{32767}; // custom define
	#endif

std::ctstring_t Environment::_separator =
	#if   xENV_WIN
		Const::semicolon();
	#elif xENV_UNIX
		Const::colon();
	#endif
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Environment::Environment(
	std::ctstring_t &a_name
) :
	_name{a_name}
{
    xTEST(_isVarValid());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Environment::str() const /* final */
{
    return _name + Const::equal() + var();
}
//-------------------------------------------------------------------------------------------------
bool_t
Environment::isExists() const
{
    xCHECK_RET(_name.empty(), false);

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
	xTEST(_isValueValid(a_value));

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
Environment::vars(
    std::vec_tstring_t *a_values
)
{
    xTEST_PTR(a_values);

    xCHECK_DO(a_values != nullptr, a_values->clear());

    _vars_impl(a_values);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Environment::expandVars(
    std::ctstring_t &a_strWithVars
)
{
	// Win: Same as ::ExpandEnvironmentStrings()

    std::tstring_t sRv = a_strWithVars;

	// TODO: [unix] "$" as separator: $VAR, ${VAR}
    std::ctstring_t sep = xT("%");

    for ( ; ; ) {
        // find from left two first chars '%'
        std::csize_t startSepPos = sRv.find(sep);
        xCHECK_DO(startSepPos == std::tstring_t::npos, break);

        std::csize_t stopSepPos = sRv.find(sep, startSepPos + sep.size());
        xCHECK_DO(stopSepPos == std::tstring_t::npos, break);

        // copy %var% to temp string
        std::ctstring_t &rawEnvVar = String::cut(sRv, startSepPos, stopSepPos + sep.size());
        xTEST(!rawEnvVar.empty());

        std::ctstring_t &envVar = String::trimChars(rawEnvVar, sep);

        // expand var to temp string
        std::ctstring_t &expandedEnvVar = Environment(envVar).var();

        // replace envVar(%var%) by expandedEnvVar
        sRv.replace(startSepPos, rawEnvVar.size(), expandedEnvVar);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Environment::varPath(
	std::vec_tstring_t *out_dirPaths
)
{
    xTEST_PTR(out_dirPaths);

	std::ctstring_t name =
	#if   xENV_WIN
		xT("Path");
	#elif xENV_UNIX
		xT("PATH");
	#endif

	Environment env(name);

	String::split(env.var(), _separator, out_dirPaths);
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
    xCHECK_RET(_name.empty(),                                      false);
    xCHECK_RET(_name.find(Const::equal()) != std::tstring_t::npos, false);

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
