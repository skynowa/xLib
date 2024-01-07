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
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Environment::Environment(
	std::ctstring_t &a_name
) :
	_name{a_name}
{
    xTEST(_isNameValid());
}
//-------------------------------------------------------------------------------------------------
/* static */
Environment
Environment::path()
{
	std::ctstring_t name =
	#if   xENV_WIN
		xT("Path");
	#elif xENV_UNIX
		xT("PATH");
	#endif

	return Environment(name);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Environment::str() const /* final */
{
    return _name + Const::equal() + value();
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
Environment::value() const
{
    xCHECK_RET(!isExists(), std::tstring_t());

    return _value_impl();
}
//-------------------------------------------------------------------------------------------------
std::vec_tstring_t
Environment::values() const
{
    xCHECK_RET(!isExists(), std::vec_tstring_t{});

    std::vec_tstring_t items;
    String::split(value(), _envsSeparator(), &items);

    return std::move(items);
}
//-------------------------------------------------------------------------------------------------
void_t
Environment::setValue(
    std::ctstring_t &a_value
) const
{
	xTEST(_isValueValid(a_value));

    _setValue_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
void_t
Environment::remove() const
{
    xCHECK_DO(!isExists(), return);

    _remove_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::csize_t
Environment::_envMax()
{
	return
	#if   xENV_WIN
		#if   xCOMPILER_MS
			{_MAX_ENV};
		#else
			{32767}; // custom define
		#endif
	#elif xENV_UNIX
		{32767}; // custom define
	#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t
Environment::_envsSeparator()
{
	return
	#if   xENV_WIN
		Const::semicolon();
	#elif xENV_UNIX
		Const::colon();
	#endif
}
//-------------------------------------------------------------------------------------------------
bool_t
Environment::_isNameValid() const
{
    xCHECK_RET(_name.empty(),                                      false);
    xCHECK_RET(_name.find(Const::equal()) != std::tstring_t::npos, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Environment::_isValueValid(
    std::ctstring_t &a_value
) const
{
    xCHECK_RET(a_value.size() >= _envMax(), false);

    return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Environments
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Environments::setVars(
    const std::set<std::pair_tstring_t> &a_vars ///< vars ({"HOME=/usr/home","LOGNAME=home"})
) const
{
	for (const auto &[it_name, it_value] : a_vars) {
		Environment env(it_name);
		env.setValue(it_value);
	}
}
//-------------------------------------------------------------------------------------------------
std::vec_tstring_t
Environments::vars() const
{
    return std::move( _vars_impl() );
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Environments::expandVars(
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
        std::ctstring_t &rawEnvName = String::cut(sRv, startSepPos, stopSepPos + sep.size());
        xTEST(!rawEnvName.empty());

        std::ctstring_t &envName = String::trimChars(rawEnvName, sep);

        // expand var to temp string
        std::ctstring_t &expandedEnvValue = Environment(envName).value();

        // replace envVar(%var%) by expandedEnvVar
        sRv.replace(startSepPos, rawEnvName.size(), expandedEnvValue);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
