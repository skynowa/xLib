/**
 * \file  Env.cpp
 * \brief system environment variables
 */


#include "Env.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Fs/Config.h>

#if   xENV_WIN
    #include "Platform/Win/Env_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Env_unix.inl"
#endif


namespace xl::system
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Env::Env(
	std::ctstring_t &a_name
) :
	Env{{}, a_name}
{
}
//-------------------------------------------------------------------------------------------------
Env::Env(
	std::ctstring_t &a_prefix,
	std::ctstring_t &a_name
) :
	_prefix_name{a_prefix + a_name}
{
    xTEST(_isNameValid());
}
//-------------------------------------------------------------------------------------------------
/* static */
Env
Env::path()
{
	std::ctstring_t name =
	#if   xENV_WIN
		xT("Path");
	#elif xENV_UNIX
		xT("PATH");
	#endif

	return Env(name);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Env::str() const /* final */
{
    return _prefix_name + Const::equal() + value();
}
//-------------------------------------------------------------------------------------------------
bool_t
Env::isExists() const
{
    xCHECK_RET(_prefix_name.empty(), false);

    return _isExists_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Env::value() const
{
    xCHECK_RET(!isExists(), std::tstring_t());

    return _value_impl();
}
//-------------------------------------------------------------------------------------------------
std::vec_tstring_t
Env::values() const
{
    xCHECK_RET(!isExists(), std::vec_tstring_t{});

    std::vec_tstring_t items;
    String::split(value(), _envsSeparator(), &items);

    return std::move(items);
}
//-------------------------------------------------------------------------------------------------
void_t
Env::setValue(
    std::ctstring_t &a_value
) const
{
	xTEST(_isValueValid(a_value));

    _setValue_impl(a_value);
}
//-------------------------------------------------------------------------------------------------
void_t
Env::remove() const
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
Env::_envMax()
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
Env::_envsSeparator()
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
Env::_isNameValid() const
{
    xCHECK_RET(_prefix_name.empty(),                                      false);
    xCHECK_RET(_prefix_name.find(Const::equal()) != std::tstring_t::npos, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Env::_isValueValid(
    std::ctstring_t &a_value
) const
{
    xCHECK_RET(a_value.size() >= _envMax(), false);

    return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Envs
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Envs::Envs() :
	Envs(xT(""))
{
}
//-------------------------------------------------------------------------------------------------
Envs::Envs(
	std::ctstring_t &a_prefix
) :
	_prefix{a_prefix}
{
}
//-------------------------------------------------------------------------------------------------
void_t
Envs::setVars(
	const std::tstring_t &a_envFilePath ///< file with vars ({"HOME=/usr/home","LOGNAME=home"})
) const
{
	Config config(a_envFilePath);
	config.read();

	for (const auto &[it_name, it_value] : config.get() ) {
		Env env(_prefix, it_name);
		env.setValue(it_value);
	}
}
//-------------------------------------------------------------------------------------------------
void_t
Envs::setVars(
    const std::set<std::pair_tstring_t> &a_vars ///< vars ({"HOME=/usr/home","LOGNAME=home"})
) const
{
	for (const auto &[it_name, it_value] : a_vars) {
		Env env(_prefix, it_name);
		env.setValue(it_value);
	}
}
//-------------------------------------------------------------------------------------------------
std::vec_tstring_t
Envs::vars() const
{
    return std::move( _vars_impl() );
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Envs::findFirstOf(
	std::cvec_tstring_t &a_names ///< var names
) const
{
	xCHECK_RET(a_names.empty(), std::tstring_t{});

	for (const auto &it_name : a_names) {
		Env env(_prefix, it_name);
		bool_t bRv = env.isExists();
		xCHECK_DO(!bRv, continue);

		return env.value();
	}

	return {};
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Envs::expandVars(
    std::ctstring_t &a_strWithVars
)
{
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
        std::ctstring_t &expandedEnvValue = Env(envName).value();

        // replace envVar(%var%) by expandedEnvVar
        sRv.replace(startSepPos, rawEnvName.size(), expandedEnvValue);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
