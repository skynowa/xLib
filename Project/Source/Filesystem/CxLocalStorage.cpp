/**
 * \file  CxLocalStorage.cpp
 * \brief ini
 */


#include <xLib/Filesystem/CxLocalStorage.h>

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
    /*DEBUG*/xASSERT_DO(false == _m_csSeparator.empty(), return);
    /*DEBUG*/xASSERT_DO(false == _m_csFileExt.empty(),   return);
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(),   return);

    bool bRv = bSetPath(CxPath::sSetExt( CxPath::sGetExe(), _m_csFileExt ));
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//-------------------------------------------------------------------------
CxLocalStorage::CxLocalStorage(
    const std::tstring_t &csFilePath
) :
    _m_csSeparator(CxConst::xEQUAL),
    _m_csFileExt  (xT("ini")),
    _m_sFilePath  (),
    _m_msIni      ()
{
    /*DEBUG*/xASSERT_DO(false == _m_csSeparator.empty(), return);
    /*DEBUG*/xASSERT_DO(false == _m_csFileExt.empty(),   return);
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(),   return);
    /*DEBUG*/xASSERT_DO(false == csFilePath.empty(),     return);

    bool bRv = bSetPath(CxPath::sSetExt( csFilePath, _m_csFileExt ));
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//-------------------------------------------------------------------------
/* virtual */
CxLocalStorage::~CxLocalStorage() {

}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bCreateDefault(
    const std::tstring_t &csContent
) const
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/// csContent - n/a;

    bool bRv = CxFile::bTextWrite(_m_sFilePath, csContent);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//-------------------------------------------------------------------------
std::tstring_t
CxLocalStorage::sGetPath() const {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::tstring_t());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::bSetPath(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*///_m_sFilePath - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

    bool bRv = CxDir::bCreateForce(CxPath::sGetDir(csFilePath));
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    _m_sFilePath = csFilePath;

    return true;
}
//---------------------------------------------------------------------------
TLocalStorage &
CxLocalStorage::cmsGet() {
    /*DEBUG*/

    return _m_msIni;
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::bFlush() const {
    /*DEBUG*/

    bool bRv = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::bClear() {
    /*DEBUG*/

    bool bRv = CxFile::bClear(_m_sFilePath);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::bDelete() {
    /*DEBUG*/

    //file
    bool bRv = CxFile::bDelete(_m_sFilePath);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //TLocalStorage
    _m_msIni.clear();

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: key
*
*****************************************************************************/

//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyIsExists(
    const std::tstring_t &csKey
) const
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);

    TLocalStorage mmsIni;

    bool bRv = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &mmsIni);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    xCHECK_RET(mmsIni.end() == mmsIni.find(csKey), false);

    return true;
}
//-------------------------------------------------------------------------
std::tstring_t
CxLocalStorage::sKeyReadString(
    const std::tstring_t &csKey,
    const std::tstring_t &csDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::tstring_t());
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        std::tstring_t());
    /*DEBUG*///csDefaultValue - n/a

    std::tstring_t sRv;

    bool bRv = _bRead(csKey, csDefaultValue, &sRv);
    /*DEBUG*/xASSERT_RET(true == bRv, std::tstring_t());

    return sRv;
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyWriteString(
    const std::tstring_t &csKey,
    const std::tstring_t &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        false);
    /*DEBUG*///csValue   - n/a

    bool bRv = _bWrite(csKey, csValue);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
long_t
CxLocalStorage::iKeyReadInt(
    const std::tstring_t &csKey,
    const long_t          cliDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///iDefaultValue - n/a

    return CxString::string_cast<long_t>( sKeyReadString(csKey, CxString::string_cast(cliDefaultValue)) );
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyWriteInt(
    const std::tstring_t &csKey,
    const long_t          cliValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///iValue    - n/a

    return bKeyWriteString(csKey, CxString::string_cast(cliValue));
}
//-------------------------------------------------------------------------
double
CxLocalStorage::dKeyReadFloat(
    const std::tstring_t &csKey,
    const double          cdDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0.0);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///dDefaultValue - n/a

    return CxString::string_cast<double>( sKeyReadString(csKey, CxString::string_cast(cdDefaultValue)) );
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyWriteFloat(
    const std::tstring_t &csKey,
    const double          cdValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///dValue    - n/a

    return bKeyWriteString(csKey, CxString::string_cast(cdValue));
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyReadBool(
    const std::tstring_t &csKey,
    const bool            cbDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///bDefaultValue - n/a

    std::tstring_t sStr;

    sStr = sKeyReadString(csKey, CxString::sBoolToStr(cbDefaultValue));

    bool bRv = CxString::bStrToBool(sStr);
    /*DEBUG*/

    return bRv;
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyWriteBool(
    const std::tstring_t &csKey,
    const bool            cbValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///bValue    - n/a

    std::tstring_t sValue;

    sValue = CxString::sBoolToStr(cbValue);

    return bKeyWriteString(csKey, sValue);
}
//---------------------------------------------------------------------------
std::ustring_t
CxLocalStorage::usKeyReadBin(
    const std::tstring_t &csKey,
    const std::ustring_t &cusDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::ustring_t());
    /*DEBUG*///csKey          - n/a
    /*DEBUG*///cusDefaultValue - n/a

    std::tstring_t sRv;

    std::tstring_t sHexStr = sKeyReadString(csKey, std::tstring_t(cusDefaultValue.begin(), cusDefaultValue.end()));

    //sHexStr -> usRv
    sRv = CxString::string_cast(sHexStr, 16);

    return std::ustring_t(sRv.begin(), sRv.end());
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyWriteBin(
    const std::tstring_t &csKey,
    const std::ustring_t &cusValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///cusValue  - n/a

    //cusValue (std::ustring_t) -> sHexStr (std::tstring_t)
    std::tstring_t sHexStr;

    sHexStr = CxString::string_cast( std::tstring_t(cusValue.begin(), cusValue.end()), 16);

    return bKeyWriteString(csKey, sHexStr);
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyClear(
    const std::tstring_t &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        false);

    return bKeyWriteString(csKey, std::tstring_t());
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::bKeyDelete(
   const std::tstring_t &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        false);

    //read from file
    bool bRv = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    xCHECK_RET(_m_msIni.end() == _m_msIni.find(csKey), true);

    //delete from TLocalStorage
    _m_msIni.erase(csKey);

    //write to file
    bRv = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxLocalStorage::_bRead(
    const std::tstring_t &csKey,
    const std::tstring_t &csDefaultValue,
    std::tstring_t       *psValue
)
{
    /*DEBUG*/// csKey          - n/a
    /*DEBUG*/// csDefaultValue - n/a
    /*DEBUG*/xASSERT_RET(NULL != psValue, false);

    //read from file
    bool bRv = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //read to TLocalStorage
    TLocalStorage::iterator it = _m_msIni.find(csKey);
    if (_m_msIni.end() == it) {
        bRv = _bWrite(csKey, csDefaultValue);
        /*DEBUG*/xASSERT_RET(true == bRv, false);

        (*psValue) = csDefaultValue;
    } else {
        (*psValue) = (*it).second;
    }

    return true;
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::_bWrite(
    const std::tstring_t &csKey,
    const std::tstring_t &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        false);
    /*DEBUG*/// csValue - n/a

    //write to TLocalStorage
    TLocalStorage::iterator it = _m_msIni.find(csKey);
    if (_m_msIni.end() == it) {
        _m_msIni.insert( std::pair<std::tstring_t, std::tstring_t>(csKey, csValue) );
    } else {
        (*it).second = csValue;
    }

    //write to file
    bool bRv = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
