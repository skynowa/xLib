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
    xTEST_EQ(_separator.empty(), false);
    xTEST_EQ(_fileExt.empty(), false);
    xTEST_EQ(_filePath.empty(), true);
    xTEST_EQ(a_filePath.empty(), false);

    setPath( Path(a_filePath).setExt(_fileExt) );
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Config::~Config()
{
    flush();
}
//-------------------------------------------------------------------------------------------------
void_t
Config::createDefault(
    std::ctstring_t &a_content
) const
{
    xTEST_NA(a_content);

    File::textWrite(path(), a_content, File::OpenMode::omWrite);
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
    xTEST_EQ(a_filePath.empty(), false);

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
Config::flush() const
{
    File::textWrite(path(), _separator, _config, File::OpenMode::omWrite);
}
//-------------------------------------------------------------------------------------------------
void_t
Config::clear()
{
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
    std::map_tstring_t cfg;
    File::textRead(path(), _separator, &cfg);

    xCHECK_RET(cfg.end() == cfg.find(a_key), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Config::keyClear(
    std::ctstring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);

    setValueStr(a_key, std::tstring_t());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::keyDelete(
   std::ctstring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);

    // read from file
    File::textRead(path(), _separator, &_config);
    xCHECK_DO(_config.end() == _config.find(a_key), return);

    // delete from std::map_tstring_t
    _config.erase(a_key);

    // write to file
    File::textWrite(path(), _separator, _config, File::OpenMode::omWrite);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: value
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Config::valueStr(
    std::ctstring_t &a_key,
    std::ctstring_t &a_defaultValue
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_NA(a_defaultValue);

    std::tstring_t sRv;
    _read(a_key, a_defaultValue, &sRv);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setValueStr(
    std::ctstring_t &a_key,
    std::ctstring_t &a_value
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_NA(a_value);

    _write(a_key, a_value);
}
//-------------------------------------------------------------------------------------------------
long_t
Config::valueInt(
    std::ctstring_t &a_key,
    clong_t         &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    return String::cast<long_t>( valueStr(a_key, String::cast(a_defaultValue)) );
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setValueInt(
    std::ctstring_t &a_key,
    clong_t         &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    setValueStr(a_key, String::cast(a_value));
}
//-------------------------------------------------------------------------------------------------
double
Config::valueFloat(
    std::ctstring_t &a_key,
    cdouble_t       &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    return String::cast<double>( valueStr(a_key, String::cast(a_defaultValue)) );
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setValueFloat(
    std::ctstring_t &a_key,
    cdouble_t       &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    setValueStr(a_key, String::cast(a_value));
}
//-------------------------------------------------------------------------------------------------
bool_t
Config::valueBool(
    std::ctstring_t &a_key,
    cbool_t         &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    std::tstring_t str;

    str = valueStr(a_key, String::castBool(a_defaultValue));

    return String::castBool(str);
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setValueBool(
    std::ctstring_t &a_key,
    cbool_t         &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    std::tstring_t value;

    value = String::castBool(a_value);

    setValueStr(a_key, value);
}
//-------------------------------------------------------------------------------------------------
std::ustring_t
Config::valueBin(
    std::ctstring_t &a_key,
    std::custring_t &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    std::tstring_t sRv;

    std::tstring_t hexStr = valueStr(a_key, std::tstring_t(a_defaultValue.begin(),
        a_defaultValue.end()));

    // hexStr -> usRv
    sRv = String::cast(hexStr, 16);

    return std::ustring_t(sRv.begin(), sRv.end());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setValueBin(
    std::ctstring_t &a_key,
    std::custring_t &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    // value (std::ustring_t) -> hexStr (std::tstring_t)
    std::tstring_t hexStr;

    hexStr = String::cast( std::tstring_t(a_value.begin(), a_value.end()), 16);

    setValueStr(a_key, hexStr);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Config::_read(
    std::ctstring_t &a_key,
    std::ctstring_t &a_defaultValue,
    std::tstring_t  *a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);
    xTEST_PTR(a_value);

    // read from file
    File::textRead(path(), _separator, &_config);

    // read to std::map_tstring_t
    const auto it = _config.find(a_key);
    if (it == _config.end()) {
        _write(a_key, a_defaultValue);

        *a_value = a_defaultValue;
    } else {
        *a_value = it->second;
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Config::_write(
    std::ctstring_t &a_key,
    std::ctstring_t &a_value
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_NA(a_value);

    // write to std::map_tstring_t
    auto it = _config.find(a_key);
    if (it == _config.end()) {
        _config.insert( {a_key, a_value} );
    } else {
        it->second = a_value;
    }

    // write to file
    File::textWrite(path(), _separator, _config, File::OpenMode::omWrite);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
