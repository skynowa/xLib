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

    bool bRes = bSetPath(CxPath::sSetExt( CxPath::sGetExe(), _m_csFileExt ));
    /*DEBUG*/xASSERT_DO(false != bRes, return);
}
//-------------------------------------------------------------------------
CxLocalStorage::CxLocalStorage(
    const std::tstring &csFilePath
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

    bool bRes = bSetPath(CxPath::sSetExt( csFilePath, _m_csFileExt ));
    /*DEBUG*/xASSERT_DO(false != bRes, return);
}
//-------------------------------------------------------------------------
/*virtual*/
CxLocalStorage::~CxLocalStorage() {

}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bCreateDefault(
    const std::tstring &csContent
) const
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/// csContent - n/a;

    bool bRes = CxFile::bTextWrite(_m_sFilePath, csContent);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//-------------------------------------------------------------------------
std::tstring
CxLocalStorage::sGetPath() const {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::tstring());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::bSetPath(
    const std::tstring &csFilePath
)
{
    /*DEBUG*///_m_sFilePath - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

    bool bRes = CxDir::bCreateForce(CxPath::sGetDir(csFilePath));
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    _m_sFilePath.assign(csFilePath);

    return true;
}
//---------------------------------------------------------------------------
NxLib::TLocalStorage &
CxLocalStorage::cmsGet() {
    /*DEBUG*/

    return _m_msIni;
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::bFlush() const {
    /*DEBUG*/

    bool bRes = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::bClear() {
    /*DEBUG*/

    bool bRes = CxFile::bClear(_m_sFilePath);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::bDelete() {
    /*DEBUG*/

    //file
    bool bRes = CxFile::bDelete(_m_sFilePath);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

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
    const std::tstring &csKey
) const
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);

    NxLib::TLocalStorage mmsIni;

    bool bRes = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &mmsIni);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    xCHECK_RET(mmsIni.end() == mmsIni.find(csKey), false);

    return true;
}
//-------------------------------------------------------------------------
std::tstring
CxLocalStorage::sKeyReadString(
    const std::tstring &csKey,
    const std::tstring &csDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::tstring());
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        std::tstring());
    /*DEBUG*///csDefaultValue - n/a

    std::tstring sRes;

    bool bRes = _bRead(csKey, csDefaultValue, &sRes);
    /*DEBUG*/xASSERT_RET(false != bRes, std::tstring());

    return sRes;
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyWriteString(
    const std::tstring &csKey,
    const std::tstring &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        false);
    /*DEBUG*///csValue   - n/a

    bool bRes = _bWrite(csKey, csValue);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
LONG
CxLocalStorage::iKeyReadInt(
    const std::tstring &csKey,
    const LONG          cliDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///iDefaultValue - n/a

    return CxString::lexical_cast<LONG>( sKeyReadString(csKey, CxString::lexical_cast(cliDefaultValue)) );
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyWriteInt(
    const std::tstring &csKey,
    const LONG          cliValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///iValue    - n/a

    return bKeyWriteString(csKey, CxString::lexical_cast(cliValue));
}
//-------------------------------------------------------------------------
double
CxLocalStorage::dKeyReadFloat(
    const std::tstring &csKey,
    const double        cdDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0.0);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///dDefaultValue - n/a

    return CxString::lexical_cast<double>( sKeyReadString(csKey, CxString::lexical_cast(cdDefaultValue)) );
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyWriteFloat(
    const std::tstring &csKey,
    const double        cdValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///dValue    - n/a

    return bKeyWriteString(csKey, CxString::lexical_cast(cdValue));
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyReadBool(
    const std::tstring &csKey,
    const bool          cbDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///bDefaultValue - n/a

    std::tstring sStr;

    sStr = sKeyReadString(csKey, CxString::sBoolToStr(cbDefaultValue));

    bool bRes = CxString::bStrToBool(sStr);
    /*DEBUG*/

    return bRes;
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyWriteBool(
    const std::tstring &csKey,
    const bool          cbValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///bValue    - n/a

    std::tstring sValue;

    sValue = CxString::sBoolToStr(cbValue);

    return bKeyWriteString(csKey, sValue);
}
//---------------------------------------------------------------------------
std::ustring
CxLocalStorage::usKeyReadBin(
    const std::tstring &csKey,
    const std::ustring &cusDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::ustring());
    /*DEBUG*///csKey          - n/a
    /*DEBUG*///cusDefaultValue - n/a

    std::tstring sRes;

    std::tstring sHexStr = sKeyReadString(csKey, std::tstring(cusDefaultValue.begin(), cusDefaultValue.end()));

    //sHexStr -> usRes
    sRes = CxString::lexical_cast(sHexStr, 16);

    return std::ustring(sRes.begin(), sRes.end());
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyWriteBin(
    const std::tstring &csKey,
    const std::ustring &cusValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///cusValue  - n/a

    //cusValue (std::ustring) -> sHexStr (std::tstring)
    std::tstring sHexStr;

    sHexStr = CxString::lexical_cast( std::tstring(cusValue.begin(), cusValue.end()), 16);

    return bKeyWriteString(csKey, sHexStr);
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyClear(
    const std::tstring &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        false);

    return bKeyWriteString(csKey, std::tstring());
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::bKeyDelete(
   const std::tstring &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        false);

    //read from file
    bool bRes = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    xCHECK_RET(_m_msIni.end() == _m_msIni.find(csKey), true);

    //delete from TLocalStorage
    _m_msIni.erase(csKey);

    //write to file
    bRes = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

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
    const std::tstring &csKey,
    const std::tstring &csDefaultValue,
    std::tstring       *psValue
)
{
    /*DEBUG*/// csKey          - n/a
    /*DEBUG*/// csDefaultValue - n/a
    /*DEBUG*/xASSERT_RET(NULL != psValue, false);

    //read from file
    bool bRes = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    //read to TLocalStorage
    NxLib::TLocalStorage::iterator it = _m_msIni.find(csKey);
    if (_m_msIni.end() == it) {
        bRes = _bWrite(csKey, csDefaultValue);
        /*DEBUG*/xASSERT_RET(false != bRes, false);

        (*psValue) = csDefaultValue;
    } else {
        (*psValue) = (*it).second;
    }

    return true;
}
//---------------------------------------------------------------------------
bool
CxLocalStorage::_bWrite(
    const std::tstring &csKey,
    const std::tstring &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        false);
    /*DEBUG*/// csValue - n/a

    //write to TLocalStorage
    NxLib::TLocalStorage::iterator it = _m_msIni.find(csKey);
    if (_m_msIni.end() == it) {
        _m_msIni.insert( std::pair<std::tstring, std::tstring>(csKey, csValue) );
    } else {
        (*it).second = csValue;
    }

    //write to file
    bool bRes = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
