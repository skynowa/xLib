/**
 * \file  CxLocalStorage.cpp
 * \brief ini
 */


#include <xLib/Filesystem/CxLocalStorage.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFile.h>


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

    BOOL bRes = bSetPath(CxPath::sSetExt( CxPath::sGetExe(), _m_csFileExt ));
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
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

    BOOL bRes = bSetPath(CxPath::sSetExt( csFilePath, _m_csFileExt ));
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//-------------------------------------------------------------------------
/*virtual*/
CxLocalStorage::~CxLocalStorage() {

}
//-------------------------------------------------------------------------
BOOL
CxLocalStorage::bCreateDefault(
    const std::tstring &csContent
) const
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/// csContent - n/a;

    BOOL bRes = CxFile::bTextWrite(_m_sFilePath, csContent);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
std::tstring
CxLocalStorage::sGetPath() const {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::tstring());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
BOOL
CxLocalStorage::bSetPath(
    const std::tstring &csFilePath
)
{
    /*DEBUG*///_m_sFilePath - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    BOOL bRes = CxDir::bCreateForce(CxPath::sGetDir(csFilePath));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    _m_sFilePath.assign(csFilePath);

    return TRUE;
}
//---------------------------------------------------------------------------
NxLib::TLocalStorage &
CxLocalStorage::cmsGet() {
    /*DEBUG*/

    return _m_msIni;
}
//---------------------------------------------------------------------------
BOOL
CxLocalStorage::bFlush() const {
    /*DEBUG*/

    BOOL bRes = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxLocalStorage::bClear() {
    /*DEBUG*/

    BOOL bRes = CxFile::bClear(_m_sFilePath);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxLocalStorage::bDelete() {
    /*DEBUG*/

    //file
    BOOL bRes = CxFile::bDelete(_m_sFilePath);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //TLocalStorage
    _m_msIni.clear();

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: key
*
*****************************************************************************/

//-------------------------------------------------------------------------
BOOL
CxLocalStorage::bKeyIsExists(
    const std::tstring &csKey
) const
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);

    NxLib::TLocalStorage mmsIni;

    BOOL bRes = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &mmsIni);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    xCHECK_RET(mmsIni.end() == mmsIni.find(csKey), FALSE);

    return TRUE;
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

    BOOL bRes = _bRead(csKey, csDefaultValue, &sRes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, std::tstring());

    return sRes;
}
//-------------------------------------------------------------------------
BOOL
CxLocalStorage::bKeyWriteString(
    const std::tstring &csKey,
    const std::tstring &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);
    /*DEBUG*///csValue   - n/a

    BOOL bRes = _bWrite(csKey, csValue);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
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
BOOL
CxLocalStorage::bKeyWriteInt(
    const std::tstring &csKey,
    const LONG          cliValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///iValue    - n/a

    return bKeyWriteString(csKey, CxString::lexical_cast(cliValue));
}
//-------------------------------------------------------------------------
DOUBLE
CxLocalStorage::dKeyReadFloat(
    const std::tstring &csKey,
    const DOUBLE        cdDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0.0);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///dDefaultValue - n/a

    return CxString::lexical_cast<DOUBLE>( sKeyReadString(csKey, CxString::lexical_cast(cdDefaultValue)) );
}
//-------------------------------------------------------------------------
BOOL
CxLocalStorage::bKeyWriteFloat(
    const std::tstring &csKey,
    const double        cdValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///dValue    - n/a

    return bKeyWriteString(csKey, CxString::lexical_cast(cdValue));
}
//-------------------------------------------------------------------------
BOOL
CxLocalStorage::bKeyReadBool(
    const std::tstring &csKey,
    const BOOL          cbDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///bDefaultValue - n/a

    std::tstring sStr;

    sStr = sKeyReadString(csKey, CxString::sBoolToStr(cbDefaultValue));

    BOOL bRes = CxString::bStrToBool(sStr);
    /*DEBUG*/

    return bRes;
}
//-------------------------------------------------------------------------
BOOL
CxLocalStorage::bKeyWriteBool(
    const std::tstring &csKey,
    const BOOL          cbValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
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
BOOL
CxLocalStorage::bKeyWriteBin(
    const std::tstring &csKey,
    const std::ustring &cusValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///cusValue  - n/a

    //cusValue (std::ustring) -> sHexStr (std::tstring)
    std::tstring sHexStr;

    sHexStr = CxString::lexical_cast( std::tstring(cusValue.begin(), cusValue.end()), 16);

    return bKeyWriteString(csKey, sHexStr);
}
//-------------------------------------------------------------------------
BOOL
CxLocalStorage::bKeyClear(
    const std::tstring &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);

    return bKeyWriteString(csKey, std::tstring());
}
//---------------------------------------------------------------------------
BOOL
CxLocalStorage::bKeyDelete(
   const std::tstring &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);

    //read from file
    BOOL bRes = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    xCHECK_RET(_m_msIni.end() == _m_msIni.find(csKey), TRUE);

    //delete from TLocalStorage
    _m_msIni.erase(csKey);

    //write to file
    bRes = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxLocalStorage::_bRead(
    const std::tstring &csKey,
    const std::tstring &csDefaultValue,
    std::tstring       *psValue
)
{
    /*DEBUG*/// csKey          - n/a
    /*DEBUG*/// csDefaultValue - n/a
    /*DEBUG*/xASSERT_RET(NULL != psValue, FALSE);

    //read from file
    BOOL bRes = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //read to TLocalStorage
    NxLib::TLocalStorage::iterator it = _m_msIni.find(csKey);
    if (_m_msIni.end() == it) {
        bRes = _bWrite(csKey, csDefaultValue);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        (*psValue) = csDefaultValue;
    } else {
        (*psValue) = (*it).second;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxLocalStorage::_bWrite(
    const std::tstring &csKey,
    const std::tstring &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);
    /*DEBUG*/// csValue - n/a

    //write to TLocalStorage
    NxLib::TLocalStorage::iterator it = _m_msIni.find(csKey);
    if (_m_msIni.end() == it) {
        _m_msIni.insert( std::pair<std::tstring, std::tstring>(csKey, csValue) );
    } else {
        (*it).second = csValue;
    }

    //write to file
    BOOL bRes = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
