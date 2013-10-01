/**
 * \file  CxLocalStorage.cpp
 * \brief ini
 */


#include <xLib/Filesystem/CxLocalStorage.h>

#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFile.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public: creation
*
*******************************************************************************/

//-------------------------------------------------------------------------
CxLocalStorage::CxLocalStorage() :
    _m_csSeparator(CxConst::xEQUAL),
    _m_csFileExt  (xT("ini")),
    _m_sFilePath  (),
    _m_msIni      ()
{
    xTEST_EQ(false, _m_csSeparator.empty());
    xTEST_EQ(false, _m_csFileExt.empty());
    xTEST_EQ(true,  _m_sFilePath.empty());

    setPath( CxPath( CxPath::exe() ).setExt(_m_csFileExt) );
}
//-------------------------------------------------------------------------
CxLocalStorage::CxLocalStorage(
    std::ctstring_t &a_csFilePath
) :
    _m_csSeparator(CxConst::xEQUAL),
    _m_csFileExt  (xT("ini")),
    _m_sFilePath  (),
    _m_msIni      ()
{
    xTEST_EQ(false, _m_csSeparator.empty());
    xTEST_EQ(false, _m_csFileExt.empty());
    xTEST_EQ(true,  _m_sFilePath.empty());
    xTEST_EQ(false, a_csFilePath.empty());

    setPath( CxPath(a_csFilePath).setExt(_m_csFileExt) );
}
//-------------------------------------------------------------------------
/* virtual */
CxLocalStorage::~CxLocalStorage() {
    flush();
}
//-------------------------------------------------------------------------
void_t
CxLocalStorage::createDefault(
    std::ctstring_t &a_csContent
) const
{
    xTEST_NA(a_csContent);

    CxFile::textWrite(path(), a_csContent);
}
//-------------------------------------------------------------------------
std::ctstring_t &
CxLocalStorage::path() const {
    xTEST_EQ(false, _m_sFilePath.empty());

    return _m_sFilePath;
}
//------------------------------------------------------------------------------
void_t
CxLocalStorage::setPath(
    std::ctstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());

    CxDir( CxPath(a_csFilePath).dir() ).pathCreate();

    _m_sFilePath = a_csFilePath;
}
//------------------------------------------------------------------------------
local_storage_t &
CxLocalStorage::get() {
    return _m_msIni;
}
//------------------------------------------------------------------------------
void_t
CxLocalStorage::flush() const {
    CxFile::textWrite(path(), _m_csSeparator, _m_msIni);
}
//------------------------------------------------------------------------------
void_t
CxLocalStorage::clear() {
    CxFile::clear(path());
}
//------------------------------------------------------------------------------
void_t
CxLocalStorage::remove() {
    // file
    CxFile::remove(path());

    // local_storage_t
    _m_msIni.clear();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: key
*
*******************************************************************************/

//-------------------------------------------------------------------------
bool_t
CxLocalStorage::keyIsExists(
    std::ctstring_t &a_csKey
) const
{
    local_storage_t mmsIni;

    CxFile::textRead(path(), _m_csSeparator, &mmsIni);

    xCHECK_RET(mmsIni.end() == mmsIni.find(a_csKey), false);

    return true;
}
//-------------------------------------------------------------------------
std::tstring_t
CxLocalStorage::keyReadString(
    std::ctstring_t &a_csKey,
    std::ctstring_t &a_csDefaultValue
)
{
    xTEST_EQ(false, a_csKey.empty());
    xTEST_NA(a_csDefaultValue);

    std::tstring_t sRv;

    _read(a_csKey, a_csDefaultValue, &sRv);

    return sRv;
}
//-------------------------------------------------------------------------
void_t
CxLocalStorage::keyWriteString(
    std::ctstring_t &a_csKey,
    std::ctstring_t &a_csValue
)
{
    xTEST_EQ(false, a_csKey.empty());
    xTEST_NA(a_csValue);

    _write(a_csKey, a_csValue);
}
//------------------------------------------------------------------------------
long_t
CxLocalStorage::keyReadInt(
    std::ctstring_t &a_csKey,
    clong_t         &a_cliDefaultValue
)
{
    xTEST_NA(a_csKey);
    xTEST_NA(a_cliDefaultValue);

    return CxString::cast<long_t>( keyReadString(a_csKey, CxString::cast(a_cliDefaultValue)) );
}
//-------------------------------------------------------------------------
void_t
CxLocalStorage::keyWriteInt(
    std::ctstring_t &a_csKey,
    clong_t         &a_cliValue
)
{
    xTEST_NA(a_csKey);
    xTEST_NA(a_cliValue);

    keyWriteString(a_csKey, CxString::cast(a_cliValue));
}
//-------------------------------------------------------------------------
double
CxLocalStorage::keyReadFloat(
    std::ctstring_t &a_csKey,
    cdouble_t       &a_cdDefaultValue
)
{
    xTEST_NA(a_csKey);
    xTEST_NA(a_cdDefaultValue);

    return CxString::cast<double>( keyReadString(a_csKey, CxString::cast(a_cdDefaultValue)) );
}
//-------------------------------------------------------------------------
void_t
CxLocalStorage::keyWriteFloat(
    std::ctstring_t &a_csKey,
    cdouble_t       &a_cdValue
)
{
    xTEST_NA(a_csKey);
    xTEST_NA(a_cdValue);

    keyWriteString(a_csKey, CxString::cast(a_cdValue));
}
//-------------------------------------------------------------------------
bool_t
CxLocalStorage::keyReadBool(
    std::ctstring_t &a_csKey,
    cbool_t         &a_cbDefaultValue
)
{
    xTEST_NA(a_csKey);
    xTEST_NA(a_cbDefaultValue);

    std::tstring_t sStr;

    sStr = keyReadString(a_csKey, CxString::boolToStr(a_cbDefaultValue));

    bool_t bRv = CxString::strToBool(sStr);

    return bRv;
}
//-------------------------------------------------------------------------
void_t
CxLocalStorage::keyWriteBool(
    std::ctstring_t &a_csKey,
    cbool_t         &a_cbValue
)
{
    xTEST_NA(a_csKey);
    xTEST_NA(a_cbValue);

    std::tstring_t sValue;

    sValue = CxString::boolToStr(a_cbValue);

    keyWriteString(a_csKey, sValue);
}
//------------------------------------------------------------------------------
std::ustring_t
CxLocalStorage::keyReadBin(
    std::ctstring_t &a_csKey,
    std::custring_t &a_cusDefaultValue
)
{
    xTEST_NA(a_csKey);
    xTEST_NA(a_cusDefaultValue);

    std::tstring_t sRv;

    std::tstring_t sHexStr = keyReadString(a_csKey, std::tstring_t(a_cusDefaultValue.begin(), a_cusDefaultValue.end()));

    // sHexStr -> usRv
    sRv = CxString::cast(sHexStr, 16);

    return std::ustring_t(sRv.begin(), sRv.end());
}
//-------------------------------------------------------------------------
void_t
CxLocalStorage::keyWriteBin(
    std::ctstring_t &a_csKey,
    std::custring_t &a_cusValue
)
{
    xTEST_NA(a_csKey);
    xTEST_NA(a_cusValue);

    // cusValue (std::ustring_t) -> sHexStr (std::tstring_t)
    std::tstring_t sHexStr;

    sHexStr = CxString::cast( std::tstring_t(a_cusValue.begin(), a_cusValue.end()), 16);

    keyWriteString(a_csKey, sHexStr);
}
//-------------------------------------------------------------------------
void_t
CxLocalStorage::keyClear(
    std::ctstring_t &a_csKey
)
{
    xTEST_EQ(false, a_csKey.empty());

    keyWriteString(a_csKey, std::tstring_t());
}
//------------------------------------------------------------------------------
void_t
CxLocalStorage::keyDelete(
   std::ctstring_t &a_csKey
)
{
    xTEST_EQ(false, a_csKey.empty());

    // read from file
    CxFile::textRead(path(), _m_csSeparator, &_m_msIni);

    xCHECK_DO(_m_msIni.end() == _m_msIni.find(a_csKey), return);

    // delete from local_storage_t
    _m_msIni.erase(a_csKey);

    // write to file
    CxFile::textWrite(path(), _m_csSeparator, _m_msIni);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxLocalStorage::_read(
    std::ctstring_t &a_csKey,
    std::ctstring_t &a_csDefaultValue,
    std::tstring_t  *a_psValue
)
{
    xTEST_NA(a_csKey);
    xTEST_NA(a_csDefaultValue);
    xTEST_PTR(a_psValue);

    // read from file
    CxFile::textRead(path(), _m_csSeparator, &_m_msIni);

    // read to local_storage_t
    local_storage_t::iterator it = _m_msIni.find(a_csKey);
    if (_m_msIni.end() == it) {
        _write(a_csKey, a_csDefaultValue);

        (*a_psValue) = a_csDefaultValue;
    } else {
        (*a_psValue) = (*it).second;
    }
}
//------------------------------------------------------------------------------
void_t
CxLocalStorage::_write(
    std::ctstring_t &a_csKey,
    std::ctstring_t &a_csValue
)
{
    xTEST_EQ(false, a_csKey.empty());
    xTEST_NA(a_csValue);

    // write to local_storage_t
    local_storage_t::iterator it = _m_msIni.find(a_csKey);
    if (_m_msIni.end() == it) {
        _m_msIni.insert( std::pair<std::tstring_t, std::tstring_t>(a_csKey, a_csValue) );
    } else {
        (*it).second = a_csValue;
    }

    // write to file
    CxFile::textWrite(path(), _m_csSeparator, _m_msIni);
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
