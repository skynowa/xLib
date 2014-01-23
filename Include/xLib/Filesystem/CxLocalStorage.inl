/**
 * \file  CxLocalStorage.cpp
 * \brief ini
 */


#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFile.h>


xNAMESPACE_BEGIN(xlib)

/**************************************************************************************************
*    public: creation
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxLocalStorage::CxLocalStorage() :
    _separator(CxConst::equal()),
    _fileExt  (xT("ini")),
    _filePath (),
    _ini      ()
{
    xTEST_EQ(false, _separator.empty());
    xTEST_EQ(false, _fileExt.empty());
    xTEST_EQ(true,  _filePath.empty());

    setPath( CxPath( CxPath::exe() ).setExt(_fileExt) );
}
//-------------------------------------------------------------------------------------------------
inline
CxLocalStorage::CxLocalStorage(
    std::ctstring_t &a_filePath
) :
    _separator(CxConst::equal()),
    _fileExt  (xT("ini")),
    _filePath (),
    _ini      ()
{
    xTEST_EQ(false, _separator.empty());
    xTEST_EQ(false, _fileExt.empty());
    xTEST_EQ(true,  _filePath.empty());
    xTEST_EQ(false, a_filePath.empty());

    setPath( CxPath(a_filePath).setExt(_fileExt) );
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxLocalStorage::~CxLocalStorage()
{
    flush();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocalStorage::createDefault(
    std::ctstring_t &a_content
) const
{
    xTEST_NA(a_content);

    CxFile::textWrite(path(), a_content, CxFile::omWrite);
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxLocalStorage::path() const
{
    xTEST_EQ(_filePath.empty(), false);

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocalStorage::setPath(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(), false);

    CxDir( CxPath(a_filePath).dir() ).pathCreate();

    _filePath = a_filePath;
}
//-------------------------------------------------------------------------------------------------
inline std::map_tstring_t &
CxLocalStorage::get()
{
    return _ini;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocalStorage::flush() const
{
    CxFile::textWrite(path(), _separator, _ini, CxFile::omWrite);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocalStorage::clear()
{
    CxFile::clear(path());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocalStorage::remove()
{
    // file
    CxFile::remove( path() );

    // std::map_tstring_t
    _ini.clear();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: key
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxLocalStorage::keyIsExists(
    std::ctstring_t &a_key
) const
{
    std::map_tstring_t ini;

    CxFile::textRead(path(), _separator, &ini);

    xCHECK_RET(ini.end() == ini.find(a_key), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxLocalStorage::keyReadString(
    std::ctstring_t &a_key,
    std::ctstring_t &a_defaultValue
)
{
    xTEST_EQ(false, a_key.empty());
    xTEST_NA(a_defaultValue);

    std::tstring_t sRv;

    _read(a_key, a_defaultValue, &sRv);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocalStorage::keyWriteString(
    std::ctstring_t &a_key,
    std::ctstring_t &a_value
)
{
    xTEST_EQ(false, a_key.empty());
    xTEST_NA(a_value);

    _write(a_key, a_value);
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxLocalStorage::keyReadInt(
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
CxLocalStorage::keyWriteInt(
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
CxLocalStorage::keyReadFloat(
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
CxLocalStorage::keyWriteFloat(
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
CxLocalStorage::keyReadBool(
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
CxLocalStorage::keyWriteBool(
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
CxLocalStorage::keyReadBin(
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
CxLocalStorage::keyWriteBin(
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
CxLocalStorage::keyClear(
    std::ctstring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);

    keyWriteString(a_key, std::tstring_t());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocalStorage::keyDelete(
   std::ctstring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);

    // read from file
    CxFile::textRead(path(), _separator, &_ini);

    xCHECK_DO(_ini.end() == _ini.find(a_key), return);

    // delete from std::map_tstring_t
    _ini.erase(a_key);

    // write to file
    CxFile::textWrite(path(), _separator, _ini, CxFile::omWrite);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxLocalStorage::_read(
    std::ctstring_t &a_key,
    std::ctstring_t &a_defaultValue,
    std::tstring_t  *a_value
)
{
    xTEST_NA(a_key);
    xTEST_NA(a_defaultValue);
    xTEST_PTR(a_value);

    // read from file
    CxFile::textRead(path(), _separator, &_ini);

    // read to std::map_tstring_t
    std::map_tstring_t::const_iterator it = _ini.find(a_key);
    if (_ini.end() == it) {
        _write(a_key, a_defaultValue);

        *a_value = a_defaultValue;
    } else {
        *a_value = it->second;
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocalStorage::_write(
    std::ctstring_t &a_key,
    std::ctstring_t &a_value
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_NA(a_value);

    // write to std::map_tstring_t
    std::map_tstring_t::iterator it = _ini.find(a_key);
    if (_ini.end() == it) {
        _ini.insert( std::pair<std::tstring_t, std::tstring_t>(a_key, a_value) );
    } else {
        it->second = a_value;
    }

    // write to file
    CxFile::textWrite(path(), _separator, _ini, CxFile::omWrite);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(xlib)
