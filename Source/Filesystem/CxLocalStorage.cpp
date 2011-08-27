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
//DONE: CxLocalStorage (exe-file path)
CxLocalStorage::CxLocalStorage() :
    _m_csSeparator(CxConst::xEQUAL),
    _m_csFileExt  (xT("ini")),
    _m_bRes       (FALSE),
    _m_sFilePath  (),
    _m_msIni      ()
{
    /*DEBUG*/xASSERT_DO(false == _m_csSeparator.empty(), return);
    /*DEBUG*/xASSERT_DO(false == _m_csFileExt.empty(),   return);
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(),   return);

    _m_bRes = bSetPath(CxPath::sSetExt( CxPath::sGetExe(), _m_csFileExt ));
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//-------------------------------------------------------------------------
//DONE: CxLocalStorage (file path)
CxLocalStorage::CxLocalStorage(
    const std::tstring &csFilePath
) :
    _m_csSeparator(CxConst::xEQUAL),
    _m_csFileExt  (xT("ini")),
    _m_bRes       (FALSE),
    _m_sFilePath  (),
    _m_msIni      ()
{
    /*DEBUG*/xASSERT_DO(false == _m_csSeparator.empty(), return);
    /*DEBUG*/xASSERT_DO(false == _m_csFileExt.empty(),   return);
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(),   return);
    /*DEBUG*/xASSERT_DO(false == csFilePath.empty(),     return);

    _m_bRes = bSetPath(CxPath::sSetExt( csFilePath, _m_csFileExt ));
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//-------------------------------------------------------------------------
//DONE: ~CxLocalStorage
/*virtual*/
CxLocalStorage::~CxLocalStorage() {

}
//-------------------------------------------------------------------------
//DONE: bCreateDefault (create default file)
BOOL
CxLocalStorage::bCreateDefault(
    const std::tstring &csContent
) const
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/// csContent - n/a;

    _m_bRes = CxFile::bTextWrite(_m_sFilePath, csContent);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
//DONE: sGetPath (get file path)
std::tstring
CxLocalStorage::sGetPath() const {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::tstring());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
//DONE: bSetPath (set file path)
BOOL
CxLocalStorage::bSetPath(
    const std::tstring &csFilePath
)
{
    /*DEBUG*///_m_sFilePath - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    _m_bRes = CxDir::bCreateForce(CxPath::sGetDir(csFilePath));
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_sFilePath.assign(csFilePath);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: cmsGet (get innner TLocalStorage, may be used with bFlush)
NxLib::TLocalStorage &
CxLocalStorage::cmsGet() {
    /*DEBUG*/

    return _m_msIni;
}
//---------------------------------------------------------------------------
//DONE: bFlush (flush)
BOOL
CxLocalStorage::bFlush() const {
    /*DEBUG*/

    _m_bRes = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear (clear content)
BOOL
CxLocalStorage::bClear() {
    /*DEBUG*/

    _m_bRes = CxFile::bClear(_m_sFilePath);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bDelete (delete)
BOOL
CxLocalStorage::bDelete() {
    /*DEBUG*/

    //file
    _m_bRes = CxFile::bDelete(_m_sFilePath);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

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
//DONE: bKeyIsExists (is exists)
BOOL
CxLocalStorage::bKeyIsExists(
    const std::tstring &csKey
) const
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);

    NxLib::TLocalStorage mmsIni;

    _m_bRes = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &mmsIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    xCHECK_RET(mmsIni.end() == mmsIni.find(csKey), FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
//DONE: sKeyReadString (read std::tstring)
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

    _m_bRes = _bRead(csKey, csDefaultValue, &sRes);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, std::tstring());

    return sRes;
}
//-------------------------------------------------------------------------
//DONE: bKeyWriteString (write std::tstring)
BOOL
CxLocalStorage::bKeyWriteString(
    const std::tstring &csKey,
    const std::tstring &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);
    /*DEBUG*///csValue   - n/a

    _m_bRes = _bWrite(csKey, csValue);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: iKeyReadInt (read INT)
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
//DONE: bKeyWriteInt (write INT)
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
//DONE: dKeyReadFloat (read FLOAT)
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
//DONE: bKeyWriteFloat (write FLOAT)
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
//DONE: bKeyReadBool (read BOOL)
BOOL
CxLocalStorage::bKeyReadBool(
    const std::tstring &csKey,
    const BOOL          cbDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///bDefaultValue - n/a

    BOOL    bRes = FALSE;
    std::tstring sStr;
    std::tstring sDefaultValue;

    sStr = CxString::sBoolToStr(cbDefaultValue);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    sStr = sKeyReadString(csKey, sStr);

    bRes = CxString::bStrToBool(sStr);
    /*DEBUG*/

    return bRes;
}
//-------------------------------------------------------------------------
//DONE: bKeyWriteBool (write BOOL)
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
//DONE: usKeyReadBin (write std::ustring)
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
//DONE: bKeyWriteBin (read std::ustring)
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
//DONE: bKeyClear (clear value)
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
//DONE: bKeyDelete (delete key and value)
BOOL
CxLocalStorage::bKeyDelete(
   const std::tstring &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);

    //read from file
    _m_bRes = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    xCHECK_RET(_m_msIni.end() == _m_msIni.find(csKey), TRUE);

    //delete from TLocalStorage
    _m_msIni.erase(csKey);

    //write to file
    _m_bRes = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bRead (parse file)
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
    _m_bRes = CxFile::bTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //read to TLocalStorage
    NxLib::TLocalStorage::iterator it = _m_msIni.find(csKey);
    if (_m_msIni.end() == it) {
        _m_bRes = _bWrite(csKey, csDefaultValue);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        (*psValue) = csDefaultValue;
    } else {
        (*psValue) = (*it).second;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: _bWrite (flush to TLocalStorage, file)
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
    _m_bRes = CxFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
