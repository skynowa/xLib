/****************************************************************************
* Class name:  CxIni
* Description: ini
* File name:   CxIni.cpp
* Libraries:   WinAPI, Stl
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     10.05.2011
*
*****************************************************************************/


#include <xLib/Filesystem/CxIni.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxStdioFile.h>


/****************************************************************************
*    public: creation
*
*****************************************************************************/

//-------------------------------------------------------------------------
//DONE: CxIni (exe-file path)
CxIni::CxIni() :
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
//DONE: CxIni (file path)
CxIni::CxIni(
    const tString &csFilePath
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
//DONE: ~CxIni
/*virtual*/
CxIni::~CxIni() {

}
//-------------------------------------------------------------------------
//DONE: bCreateDefault (create default file)
BOOL
CxIni::bCreateDefault(
    const tString &csContent
) const
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/// csContent - n/a;

    _m_bRes = CxStdioFile::bTextWrite(_m_sFilePath, csContent);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
//DONE: sGetPath (get file path)
tString
CxIni::sGetPath() const {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), tString());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
//DONE: bSetPath (set file path)
BOOL
CxIni::bSetPath(
    const tString &csFilePath
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
//DONE: cmapsGet (get innner TIni, may be used with bFlush)
NxLib::TIni &
CxIni::cmapsGet() {
    /*DEBUG*/

    return _m_msIni;
}
//---------------------------------------------------------------------------
//DONE: bFlush (flush)
BOOL
CxIni::bFlush() const {
    /*DEBUG*/

    _m_bRes = CxStdioFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear (clear content)
BOOL
CxIni::bClear() {
    /*DEBUG*/

    _m_bRes = CxStdioFile::bClear(_m_sFilePath);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bDelete (delete)
BOOL
CxIni::bDelete() {
    /*DEBUG*/

    //file
    _m_bRes = CxStdioFile::bDelete(_m_sFilePath);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //TIni
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
CxIni::bKeyIsExists(
    const tString &csKey
) const
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);

    NxLib::TIni mmsIni;

    _m_bRes = CxStdioFile::bTextRead(_m_sFilePath, _m_csSeparator, &mmsIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    xCHECK_RET(mmsIni.end() == mmsIni.find(csKey), FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
//DONE: sKeyReadString (read tString)
tString
CxIni::sKeyReadString(
    const tString &csKey,
    const tString &csDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), tString());
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        tString());
    /*DEBUG*///csDefaultValue - n/a

    tString sRes;

    _m_bRes = _bRead(csKey, csDefaultValue, &sRes);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, tString());

    return sRes;
}
//-------------------------------------------------------------------------
//DONE: bKeyWriteString (write tString)
BOOL
CxIni::bKeyWriteString(
    const tString &csKey,
    const tString &csValue
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
CxIni::iKeyReadInt(
    const tString &csKey,
    const LONG     cliDefaultValue
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
CxIni::bKeyWriteInt(
    const tString &csKey,
    const LONG     cliValue
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
CxIni::dKeyReadFloat(
    const tString &csKey,
    const DOUBLE   cdDefaultValue
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
CxIni::bKeyWriteFloat(
    const tString &csKey,
    const double   cdValue
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
CxIni::bKeyReadBool(
    const tString &csKey,
    const BOOL     cbDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///bDefaultValue - n/a

    BOOL    bRes = FALSE;
    tString sStr;
    tString sDefaultValue;

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
CxIni::bKeyWriteBool(
    const tString &csKey,
    const BOOL     cbValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///bValue    - n/a

    tString sValue;

    sValue = CxString::sBoolToStr(cbValue);

    return bKeyWriteString(csKey, sValue);
}
//---------------------------------------------------------------------------
//DONE: usKeyReadBin (write uString)
uString
CxIni::usKeyReadBin(
    const tString &csKey,
    const uString &cusDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), uString());
    /*DEBUG*///csKey          - n/a
    /*DEBUG*///cusDefaultValue - n/a

    tString sRes;

    tString sHexStr = sKeyReadString(csKey, tString(cusDefaultValue.begin(), cusDefaultValue.end()));

    //sHexStr -> usRes
    sRes = CxString::lexical_cast(sHexStr, 16);

    return uString(sRes.begin(), sRes.end());
}
//-------------------------------------------------------------------------
//DONE: bKeyWriteBin (read uString)
BOOL
CxIni::bKeyWriteBin(
    const tString &csKey,
    const uString &cusValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///cusValue  - n/a

    //cusValue (uString) -> sHexStr (tString)
    tString sHexStr;

    sHexStr = CxString::lexical_cast( tString(cusValue.begin(), cusValue.end()), 16);

    return bKeyWriteString(csKey, sHexStr);
}
//-------------------------------------------------------------------------
//DONE: bKeyClear (clear value)
BOOL
CxIni::bKeyClear(
    const tString &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);

    return bKeyWriteString(csKey, tString());
}
//---------------------------------------------------------------------------
//DONE: bKeyDelete (delete key and value)
BOOL
CxIni::bKeyDelete(
   const tString &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);

    //read from file
    _m_bRes = CxStdioFile::bTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    xCHECK_RET(_m_msIni.end() == _m_msIni.find(csKey), TRUE);

    //delete from TIni
    _m_msIni.erase(csKey);

    //write to file
    _m_bRes = CxStdioFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
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
CxIni::_bRead(
    const tString &csKey,
    const tString &csDefaultValue,
    tString       *psValue
)
{
    /*DEBUG*/// csKey          - n/a
    /*DEBUG*/// csDefaultValue - n/a
    /*DEBUG*/xASSERT_RET(NULL != psValue, FALSE);

    //read from file
    _m_bRes = CxStdioFile::bTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //read to TIni
    NxLib::TIni::iterator it = _m_msIni.find(csKey);
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
//DONE: _bWrite (flush to TIni, file)
BOOL
CxIni::_bWrite(
    const tString &csKey,
    const tString &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);
    /*DEBUG*/// csValue - n/a

    //write to TIni
    NxLib::TIni::iterator it = _m_msIni.find(csKey);
    if (_m_msIni.end() == it) {
        _m_msIni.insert( std::pair<tString, tString>(csKey, csValue) );
    } else {
        (*it).second = csValue;
    }

    //write to file
    _m_bRes = CxStdioFile::bTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
