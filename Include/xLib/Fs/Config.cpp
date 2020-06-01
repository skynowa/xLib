/**
 * \file  Config.inl
 * \brief config file
 */


#include "Config.h"

#include <xLib/Core/String.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/File.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public: creation
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Config::Config() :
	Config( Path::exe() )
{
}
//-------------------------------------------------------------------------------------------------
Config::Config(
    std::ctstring_t &a_filePath
) :
    _separator{ Const::equal() },
    _fileExt  { Path::fileExt(Path::FileExt::seConfig) }
{
    xTEST(!_separator.empty());
    xTEST(!_fileExt.empty());
    xTEST(_filePath.empty());
    xTEST(!a_filePath.empty());

    setPath( Path(a_filePath).setExt(_fileExt) );
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Config::~Config()
{
    save();
}
//-------------------------------------------------------------------------------------------------
void_t
Config::createDefault(
    std::cmap_tstring_t &a_content
) const
{
    xTEST_NA(a_content);

    File::textWrite(path(), _separator, a_content, File::OpenMode::Write);
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Config::path() const
{
    xTEST_EQ(_filePath.empty(), false);

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setPath(
    std::ctstring_t &a_filePath
)
{
    xTEST(!a_filePath.empty());

    Dir( Path(a_filePath).dir() ).pathCreate();

    _filePath = a_filePath;
}
//-------------------------------------------------------------------------------------------------
std::map_tstring_t &
Config::get()
{
    return _config;
}
//-------------------------------------------------------------------------------------------------
void_t
Config::read()
{
    if ( !File::isExists(path()) ) {
		return;
    }

    File::textRead(path(), _separator, &_config);
    _config.erase(Const::strEmpty());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::save() const
{
	xCHECK_DO(_config.empty(), return);

    File::textWrite(path(), _separator, _config, File::OpenMode::Write);
}
//-------------------------------------------------------------------------------------------------
void_t
Config::clear()
{
	_config.clear();
    File::clear(path());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::remove()
{
    // file
    File::remove( path() );

    // std::map_tstring_t
    _config.clear();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: key
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Config::keyIsExists(
    std::ctstring_t &a_key
) const
{
    return (_config.find(a_key) != _config.end());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::keyClear(
    std::ctstring_t &a_key
)
{
    xTEST(!a_key.empty());

    setValue(a_key, std::tstring_t());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::keyDelete(
   std::ctstring_t &a_key
)
{
    xTEST(!a_key.empty());

    _config.erase(a_key);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: value
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Config::value(
    std::ctstring_t &a_key,
	cptr_ctchar_t    a_defaultValue
)
{
    xTEST(!a_key.empty());
    xTEST_NA(a_defaultValue);

    auto it = _config.find(a_key);
    if (it == _config.end()) {
    	return a_defaultValue;
    }

    return it->second;
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setValue(
    std::ctstring_t &a_key,
	cptr_ctchar_t    a_value
)
{
    xTEST(!a_key.empty());
    xTEST_NA(a_value);

    _config[a_key] = a_value;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Config::value(
    std::ctstring_t &a_key,
    std::ctstring_t &a_defaultValue
)
{
    xTEST(!a_key.empty());
    xTEST_NA(a_defaultValue);

    auto it = _config.find(a_key);
    if (it == _config.end()) {
    	return a_defaultValue;
    }

    return it->second;
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setValue(
    std::ctstring_t &a_key,
    std::ctstring_t &a_value
)
{
    xTEST(!a_key.empty());
    xTEST_NA(a_value);

    _config[a_key] = a_value;
}
//-------------------------------------------------------------------------------------------------
long_t
Config::value(
    std::ctstring_t &a_key,
    clong_t         &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    return String::cast<long_t>( value(a_key, String::cast(a_defaultValue)) );
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setValue(
    std::ctstring_t &a_key,
    clong_t         &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    _config[a_key] = String::cast(a_value);
}
//-------------------------------------------------------------------------------------------------
double
Config::value(
    std::ctstring_t &a_key,
    cdouble_t       &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    return String::cast<double>( value(a_key, String::cast(a_defaultValue)) );
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setValue(
    std::ctstring_t &a_key,
    cdouble_t       &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    _config[a_key] = String::cast(a_value);
}
//-------------------------------------------------------------------------------------------------
bool_t
Config::value(
    std::ctstring_t &a_key,
    cbool_t         &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    return String::castBool( value(a_key, String::castBool(a_defaultValue)) );
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setValue(
    std::ctstring_t &a_key,
    cbool_t         &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    _config[a_key] = String::castBool(a_value);
}
//-------------------------------------------------------------------------------------------------
std::ustring_t
Config::value(
    std::ctstring_t &a_key,
    std::custring_t &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    std::tstring_t sRv;

    std::tstring_t hexStr = value(a_key, std::tstring_t(a_defaultValue.begin(),
        a_defaultValue.end()));

    // hexStr -> usRv
    sRv = String::cast(hexStr, 16);

    return std::ustring_t(sRv.begin(), sRv.end());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setValue(
    std::ctstring_t &a_key,
    std::custring_t &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    // value (std::ustring_t) -> hexStr (std::tstring_t)

    _config[a_key] = String::cast( std::tstring_t(a_value.begin(), a_value.end()), 16);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

xNAMESPACE_END2(xl, fs)
