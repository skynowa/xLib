/**
 * \file  Config.inl
 * \brief config file
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Config.h"
#endif

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
xINLINE
Config::Config() :
    _separator(Const::equal()),
    _fileExt  ( Path::fileExt(Path::seConfig) ),
    _filePath (),
    _config   ()
{
    xTEST_EQ(_separator.empty(), false);
    xTEST_EQ(_fileExt.empty(), false);
    xTEST_EQ(_filePath.empty(), true);

    setPath( Path( Path::exe() ).setExt(_fileExt) );
}
//-------------------------------------------------------------------------------------------------
xINLINE
Config::Config(
    std::ctstring_t &a_filePath
) :
    _separator(Const::equal()),
    _fileExt  ( Path::fileExt(Path::seConfig) ),
    _filePath (),
    _config   ()
{
    xTEST_EQ(_separator.empty(), false);
    xTEST_EQ(_fileExt.empty(), false);
    xTEST_EQ(_filePath.empty(), true);
    xTEST_EQ(a_filePath.empty(), false);

    setPath( Path(a_filePath).setExt(_fileExt) );
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Config::~Config()
{
    flush();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Config::createDefault(
    std::ctstring_t &a_content
) const
{
    xTEST_NA(a_content);

    File::textWrite(path(), a_content, File::omWrite);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Config::path() const
{
    xTEST_EQ(_filePath.empty(), false);

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Config::setPath(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(), false);

    Dir( Path(a_filePath).dir() ).pathCreate();

    _filePath = a_filePath;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::map_tstring_t &
Config::get()
{
    return _config;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Config::flush() const
{
    File::textWrite(path(), _separator, _config, File::omWrite);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Config::clear()
{
    File::clear(path());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
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
xINLINE bool_t
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
xINLINE std::tstring_t
Config::keyReadString(
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
xINLINE void_t
Config::keyWriteString(
    std::ctstring_t &a_key,
    std::ctstring_t &a_value
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_NA(a_value);

    _write(a_key, a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE long_t
Config::keyReadInt(
    std::ctstring_t &a_key,
    clong_t         &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    return String::cast<long_t>( keyReadString(a_key, String::cast(a_defaultValue)) );
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Config::keyWriteInt(
    std::ctstring_t &a_key,
    clong_t         &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    keyWriteString(a_key, String::cast(a_value));
}
//-------------------------------------------------------------------------------------------------
xINLINE double
Config::keyReadFloat(
    std::ctstring_t &a_key,
    cdouble_t       &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    return String::cast<double>( keyReadString(a_key, String::cast(a_defaultValue)) );
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Config::keyWriteFloat(
    std::ctstring_t &a_key,
    cdouble_t       &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    keyWriteString(a_key, String::cast(a_value));
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Config::keyReadBool(
    std::ctstring_t &a_key,
    cbool_t         &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    std::tstring_t str;

    str = keyReadString(a_key, String::castBool(a_defaultValue));

    bool_t bRv = String::castBool(str);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Config::keyWriteBool(
    std::ctstring_t &a_key,
    cbool_t         &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    std::tstring_t value;

    value = String::castBool(a_value);

    keyWriteString(a_key, value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ustring_t
Config::keyReadBin(
    std::ctstring_t &a_key,
    std::custring_t &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    std::tstring_t sRv;

    std::tstring_t hexStr = keyReadString(a_key, std::tstring_t(a_defaultValue.begin(),
        a_defaultValue.end()));

    // hexStr -> usRv
    sRv = String::cast(hexStr, 16);

    return std::ustring_t(sRv.begin(), sRv.end());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Config::keyWriteBin(
    std::ctstring_t &a_key,
    std::custring_t &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    // value (std::ustring_t) -> hexStr (std::tstring_t)
    std::tstring_t hexStr;

    hexStr = String::cast( std::tstring_t(a_value.begin(), a_value.end()), 16);

    keyWriteString(a_key, hexStr);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Config::keyClear(
    std::ctstring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);

    keyWriteString(a_key, std::tstring_t());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
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
    File::textWrite(path(), _separator, _config, File::omWrite);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
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
    std::map_tstring_t::const_iterator it = _config.find(a_key);
    if (it == _config.end()) {
        _write(a_key, a_defaultValue);

        *a_value = a_defaultValue;
    } else {
        *a_value = it->second;
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Config::_write(
    std::ctstring_t &a_key,
    std::ctstring_t &a_value
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_NA(a_value);

    // write to std::map_tstring_t
    std::map_tstring_t::iterator it = _config.find(a_key);
    if (it == _config.end()) {
        _config.insert( std::pair<std::tstring_t, std::tstring_t>(a_key, a_value) );
    } else {
        it->second = a_value;
    }

    // write to file
    File::textWrite(path(), _separator, _config, File::omWrite);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
