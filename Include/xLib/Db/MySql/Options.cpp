/**
 * \file  Options.cpp
 * \brief
 */


#include <xLib/Db/MySql/Options.h>

#include <xLib/Core/Type/Types.h>
#include <xLib/Fs/Config.h>
//-------------------------------------------------------------------------------------------------
namespace
{

const uint32_t connectTimeout {60};
const bool     isReconnect    {true};
const char     initCommand[]  {"SET autocommit=1"};

const std::map<mysql_option, xl::cptr_cvoid_t> optionsDefault
{
	{MYSQL_OPT_COMPRESS,        0 /* not used */},
	{MYSQL_OPT_CONNECT_TIMEOUT, &connectTimeout},
	{MYSQL_OPT_RECONNECT,       &isReconnect},
	{MYSQL_INIT_COMMAND,        &initCommand}
};

} // namespace
//-------------------------------------------------------------------------------------------------

namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Options::Options() :
	host        {xT("127.0.0.1")},
	user        {},
	password    {},
	db          {},
	port        {3306},
	unixSocket  {},
	charset     {xT("utf8mb4")},
	isCompress  {true},
	options     {::optionsDefault}
{
}
//-------------------------------------------------------------------------------------------------
Options::Options(
	std::ctstring_t &a_host,
	std::ctstring_t &a_user,
	std::ctstring_t &a_password,
	std::ctstring_t &a_db,
	cuint_t          a_port,
	std::ctstring_t &a_unixSocket,
	std::ctstring_t &a_charset,
	cbool_t          a_isCompress,
	const std::map<mysql_option, cptr_cvoid_t> &a_options
) :
	host        {a_host},
	user        {a_user},
	password    {a_password},
	db          {a_db},
	port        {a_port},
	unixSocket  {a_unixSocket},
	charset     {a_charset},
	isCompress  {a_isCompress},
	options     {a_options}
{
}
//-------------------------------------------------------------------------------------------------
Options::Options(
	std::ctstring_t &a_configPath	///< Config file path
)
{
	Config config(a_configPath);
	config.read();

	host       = config.value(xT("host"),       xT("127.0.0.1"));
	user       = config.value(xT("user"),       xT(""));
	password   = config.value(xT("password"),   xT(""));
	db         = config.value(xT("db"),         xT(""));
	port       = config.value(xT("port"),       3306U);
	unixSocket = config.value(xT("unixSocket"), xT(""));
	charset    = config.value(xT("charset"),    xT("utf8mb4"));
	isCompress = config.value(xT("isCompress"), true);
	options    = ::optionsDefault;
}
//-------------------------------------------------------------------------------------------------

} // namespace
