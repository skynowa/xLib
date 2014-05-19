/**
 * \file  CxConfig.inl
 * \brief config file
 */


#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFile.h>


xNAMESPACE_BEGIN2(xlib, filesystem)

xNAMESPACE_ANONYM_BEGIN

std::ctstring_t fileExtDefault = xT("cfg");

xNAMESPACE_ANONYM_END

/**************************************************************************************************
*    public: creation
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxConfig::CxConfig() :
    _separator(CxConst::equal()),
    _fileExt  (::fileExtDefault),
    _filePath (),
    _config   ()
{
    xTEST_EQ(_separator.empty(), false);
    xTEST_EQ(_fileExt.empty(), false);
    xTEST_EQ(_filePath.empty(), true);

    setPath( CxPath( CxPath::exe() ).setExt(_fileExt) );
}
//-------------------------------------------------------------------------------------------------
inline
CxConfig::CxConfig(
    std::ctstring_t &a_filePath
) :
    _separator(CxConst::equal()),
    _fileExt  (::fileExtDefault),
    _filePath (),
    _config   ()
{
    xTEST_EQ(_separator.empty(), false);
    xTEST_EQ(_fileExt.empty(), false);
    xTEST_EQ(_filePath.empty(), true);
    xTEST_EQ(a_filePath.empty(), false);

    setPath( CxPath(a_filePath).setExt(_fileExt) );
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxConfig::~CxConfig()
{
    flush();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::createDefault(
    std::ctstring_t &a_content
) const
{
    xTEST_NA(a_content);

    CxFile::textWrite(path(), a_content, CxFile::omWrite);
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConfig::path() const
{
    xTEST_EQ(_filePath.empty(), false);

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::setPath(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(), false);

    CxDir( CxPath(a_filePath).dir() ).pathCreate();

    _filePath = a_filePath;
}
//-------------------------------------------------------------------------------------------------
inline std::map_tstring_t &
CxConfig::get()
{
    return _config;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::flush() const
{
    CxFile::textWrite(path(), _separator, _config, CxFile::omWrite);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::clear()
{
    CxFile::clear(path());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::remove()
{
    // file
    CxFile::remove( path() );

    // std::map_tstring_t
    _config.clear();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: key
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxConfig::keyIsExists(
    std::ctstring_t &a_key
) const
{
    std::map_tstring_t cfg;

    CxFile::textRead(path(), _separator, &cfg);

    xCHECK_RET(cfg.end() == cfg.find(a_key), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConfig::keyReadString(
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
inline void_t
CxConfig::keyWriteString(
    std::ctstring_t &a_key,
    std::ctstring_t &a_value
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_NA(a_value);

    _write(a_key, a_value);
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxConfig::keyReadInt(
    std::ctstring_t &a_key,
    clong_t         &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    return CxString::cast<long_t>( keyReadString(a_key, CxString::cast(a_defaultValue)) );
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::keyWriteInt(
    std::ctstring_t &a_key,
    clong_t         &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    keyWriteString(a_key, CxString::cast(a_value));
}
//-------------------------------------------------------------------------------------------------
inline double
CxConfig::keyReadFloat(
    std::ctstring_t &a_key,
    cdouble_t       &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    return CxString::cast<double>( keyReadString(a_key, CxString::cast(a_defaultValue)) );
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::keyWriteFloat(
    std::ctstring_t &a_key,
    cdouble_t       &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    keyWriteString(a_key, CxString::cast(a_value));
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxConfig::keyReadBool(
    std::ctstring_t &a_key,
    cbool_t         &a_defaultValue
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);

    std::tstring_t str;

    str = keyReadString(a_key, CxString::castBool(a_defaultValue));

    bool_t bRv = CxString::castBool(str);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::keyWriteBool(
    std::ctstring_t &a_key,
    cbool_t         &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    std::tstring_t value;

    value = CxString::castBool(a_value);

    keyWriteString(a_key, value);
}
//-------------------------------------------------------------------------------------------------
inline std::ustring_t
CxConfig::keyReadBin(
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
    sRv = CxString::cast(hexStr, 16);

    return std::ustring_t(sRv.begin(), sRv.end());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::keyWriteBin(
    std::ctstring_t &a_key,
    std::custring_t &a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_value);

    // value (std::ustring_t) -> hexStr (std::tstring_t)
    std::tstring_t hexStr;

    hexStr = CxString::cast( std::tstring_t(a_value.begin(), a_value.end()), 16);

    keyWriteString(a_key, hexStr);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::keyClear(
    std::ctstring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);

    keyWriteString(a_key, std::tstring_t());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::keyDelete(
   std::ctstring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);

    // read from file
    CxFile::textRead(path(), _separator, &_config);

    xCHECK_DO(_config.end() == _config.find(a_key), return);

    // delete from std::map_tstring_t
    _config.erase(a_key);

    // write to file
    CxFile::textWrite(path(), _separator, _config, CxFile::omWrite);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxConfig::_read(
    std::ctstring_t &a_key,
    std::ctstring_t &a_defaultValue,
    std::tstring_t  *a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);
    xTEST_PTR(a_value);

    // read from file
    CxFile::textRead(path(), _separator, &_config);

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
inline void_t
CxConfig::_write(
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
    CxFile::textWrite(path(), _separator, _config, CxFile::omWrite);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
