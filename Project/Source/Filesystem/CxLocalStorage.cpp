/**
 * \file  CxLocalStorage.cpp
 * \brief ini
 */


#include <xLib/Filesystem/CxLocalStorage.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFile.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public: creation
*
*****************************************************************************/

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

    vSetPath(CxPath::sSetExt( CxPath::sExe(), _m_csFileExt ));
}
//-------------------------------------------------------------------------
CxLocalStorage::CxLocalStorage(
    const std::tstring_t &a_csFilePath
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

    vSetPath(CxPath::sSetExt( a_csFilePath, _m_csFileExt ));
}
//-------------------------------------------------------------------------
/* virtual */
CxLocalStorage::~CxLocalStorage() {

}
//-------------------------------------------------------------------------
void
CxLocalStorage::vCreateDefault(
    const std::tstring_t &a_csContent
) const
{
    xTEST_EQ(false, _m_sFilePath.empty());
    // csContent - n/a;

    CxFile::vTextWrite(_m_sFilePath, a_csContent);
}
//-------------------------------------------------------------------------
std::tstring_t
CxLocalStorage::sPath() const {
    xTEST_EQ(false, _m_sFilePath.empty());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
void
CxLocalStorage::vSetPath(
    const std::tstring_t &a_csFilePath
)
{
    //_m_sFilePath - n/a
    xTEST_EQ(false, a_csFilePath.empty());

    CxDir( CxPath::sDir(a_csFilePath) ).vCreatePath();

    _m_sFilePath = a_csFilePath;
}
//---------------------------------------------------------------------------
TLocalStorage &
CxLocalStorage::cmsGet() {


    return _m_msIni;
}
//---------------------------------------------------------------------------
void
CxLocalStorage::vFlush() const {


    CxFile::vTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
}
//---------------------------------------------------------------------------
void
CxLocalStorage::vClear() {


    CxFile::vClear(_m_sFilePath);
}
//---------------------------------------------------------------------------
void
CxLocalStorage::vDelete() {


    //file
    CxFile::vDelete(_m_sFilePath);

    //TLocalStorage
    _m_msIni.clear();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: key
*
*****************************************************************************/

//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyIsExists(
    const std::tstring_t &a_csKey
) const
{
    xTEST_EQ(false, _m_sFilePath.empty());

    TLocalStorage mmsIni;

    CxFile::vTextRead(_m_sFilePath, _m_csSeparator, &mmsIni);

    xCHECK_RET(mmsIni.end() == mmsIni.find(a_csKey), false);

    return true;
}
//-------------------------------------------------------------------------
std::tstring_t
CxLocalStorage::sKeyReadString(
    const std::tstring_t &a_csKey,
    const std::tstring_t &a_csDefaultValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(false, a_csKey.empty());
    // a_csDefaultValue - n/a

    std::tstring_t sRv;

    _vRead(a_csKey, a_csDefaultValue, &sRv);

    return sRv;
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyWriteString(
    const std::tstring_t &a_csKey,
    const std::tstring_t &a_csValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(false, a_csKey.empty());
    //csValue   - n/a

    _vWrite(a_csKey, a_csValue);
}
//---------------------------------------------------------------------------
long_t
CxLocalStorage::iKeyReadInt(
    const std::tstring_t &a_csKey,
    const long_t         &a_cliDefaultValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey         - n/a
    //iDefaultValue - n/a

    return CxString::cast<long_t>( sKeyReadString(a_csKey, CxString::cast(a_cliDefaultValue)) );
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyWriteInt(
    const std::tstring_t &a_csKey,
    const long_t         &a_cliValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey     - n/a
    //iValue    - n/a

    vKeyWriteString(a_csKey, CxString::cast(a_cliValue));
}
//-------------------------------------------------------------------------
double
CxLocalStorage::dKeyReadFloat(
    const std::tstring_t &a_csKey,
    const double         &a_cdDefaultValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey         - n/a
    //dDefaultValue - n/a

    return CxString::cast<double>( sKeyReadString(a_csKey, CxString::cast(a_cdDefaultValue)) );
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyWriteFloat(
    const std::tstring_t &a_csKey,
    const double         &a_cdValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey     - n/a
    //dValue    - n/a

    vKeyWriteString(a_csKey, CxString::cast(a_cdValue));
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyReadBool(
    const std::tstring_t &a_csKey,
    const bool           &a_cbDefaultValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey         - n/a
    //bDefaultValue - n/a

    std::tstring_t sStr;

    sStr = sKeyReadString(a_csKey, CxString::sBoolToStr(a_cbDefaultValue));

    bool bRv = CxString::bStrToBool(sStr);


    return bRv;
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyWriteBool(
    const std::tstring_t &a_csKey,
    const bool           &a_cbValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey     - n/a
    //bValue    - n/a

    std::tstring_t sValue;

    sValue = CxString::sBoolToStr(a_cbValue);

    vKeyWriteString(a_csKey, sValue);
}
//---------------------------------------------------------------------------
std::ustring_t
CxLocalStorage::usKeyReadBin(
    const std::tstring_t &a_csKey,
    const std::ustring_t &a_cusDefaultValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey          - n/a
    //cusDefaultValue - n/a

    std::tstring_t sRv;

    std::tstring_t sHexStr = sKeyReadString(a_csKey, std::tstring_t(a_cusDefaultValue.begin(), a_cusDefaultValue.end()));

    //sHexStr -> usRv
    sRv = CxString::cast(sHexStr, 16);

    return std::ustring_t(sRv.begin(), sRv.end());
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyWriteBin(
    const std::tstring_t &a_csKey,
    const std::ustring_t &a_cusValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey     - n/a
    //cusValue  - n/a

    //cusValue (std::ustring_t) -> sHexStr (std::tstring_t)
    std::tstring_t sHexStr;

    sHexStr = CxString::cast( std::tstring_t(a_cusValue.begin(), a_cusValue.end()), 16);

    vKeyWriteString(a_csKey, sHexStr);
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyClear(
    const std::tstring_t &a_csKey
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(false, a_csKey.empty());

    vKeyWriteString(a_csKey, std::tstring_t());
}
//---------------------------------------------------------------------------
void
CxLocalStorage::vKeyDelete(
   const std::tstring_t &a_csKey
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(false, a_csKey.empty());

    //read from file
    CxFile::vTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);

    xCHECK_DO(_m_msIni.end() == _m_msIni.find(a_csKey), return);

    //delete from TLocalStorage
    _m_msIni.erase(a_csKey);

    //write to file
    CxFile::vTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxLocalStorage::_vRead(
    const std::tstring_t &a_csKey,
    const std::tstring_t &a_csDefaultValue,
    std::tstring_t       *a_psValue
)
{
    // csKey          - n/a
    // csDefaultValue - n/a
    xTEST_PTR(a_psValue);

    //read from file
    CxFile::vTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);

    //read to TLocalStorage
    TLocalStorage::iterator it = _m_msIni.find(a_csKey);
    if (_m_msIni.end() == it) {
        _vWrite(a_csKey, a_csDefaultValue);

        (*a_psValue) = a_csDefaultValue;
    } else {
        (*a_psValue) = (*it).second;
    }
}
//---------------------------------------------------------------------------
void
CxLocalStorage::_vWrite(
    const std::tstring_t &a_csKey,
    const std::tstring_t &a_csValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(false, a_csKey.empty());
    // csValue - n/a

    //write to TLocalStorage
    TLocalStorage::iterator it = _m_msIni.find(a_csKey);
    if (_m_msIni.end() == it) {
        _m_msIni.insert( std::pair<std::tstring_t, std::tstring_t>(a_csKey, a_csValue) );
    } else {
        (*it).second = a_csValue;
    }

    //write to file
    CxFile::vTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
