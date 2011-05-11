/****************************************************************************
* Class name:  CxIni
* Description: ini
* File name:   CxIni.cpp
* Libraries:   WinAPI, Stl
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.04.2009 12:10:56
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
//DONE:: CxIni (constructor, exe-file path)
CxIni::CxIni() :
    _m_bRes     (FALSE),
    _m_sFilePath(),
    _m_mmsIni   ()
{
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(), return);

    _m_bRes = bSetPath(CxPath::sSetExt( CxPath::sGetExe(), xT("ini") ));
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//-------------------------------------------------------------------------
//DONE:: CxIni (constructor, file path)
CxIni::CxIni(
    const tString &csFilePath
) :
    _m_bRes     (FALSE),
    _m_sFilePath(),
    _m_mmsIni   ()
{
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(), return);
    /*DEBUG*/xASSERT_DO(false == csFilePath.empty(),   return);

    _m_bRes = bSetPath(csFilePath);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//-------------------------------------------------------------------------
//DONE:: ~CxIni (destructor)
/*virtual*/
CxIni::~CxIni() {

}
//-------------------------------------------------------------------------
//DONE:: bCreateDefault (create default file)
BOOL
CxIni::bCreateDefault(
    const tString &csContent
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/// csContent - n/a;

    CxStdioFile sfFile;

    _m_bRes = sfFile.bOpen(_m_sFilePath, CxStdioFile::omCreateReadWrite);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    size_t uiRes = sfFile.uiWrite((LPVOID)csContent.data(), csContent.size());
    /*DEBUG*/xASSERT_RET(csContent.size() == uiRes, FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
//DONE:: sGetPath (get file path)
tString
CxIni::sGetPath() {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), tString());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
//DONE:: bSetPath (set file path)
BOOL
CxIni::bSetPath(const tString &csFilePath) {
    /*DEBUG*///_m_sFilePath - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    _m_bRes = CxDir::bCreateForce(CxPath::sGetDir(csFilePath));
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_sFilePath.assign(csFilePath);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE:: bClear (clear content)
BOOL
CxIni::bClear() {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);

    CxStdioFile sfFile;

    _m_bRes = sfFile.bOpen(_m_sFilePath, CxStdioFile::omCreateReadWrite);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bRes = sfFile.bClear();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: key
*
*****************************************************************************/

//-------------------------------------------------------------------------
//DONE:: bKeyIsExists (is exists)
BOOL
CxIni::bKeyIsExists(
    const tString &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);

    TIni mmsIni;

    _m_bRes = CxStdioFile::bTextRead(_m_sFilePath, CxConst::xEQUAL, &mmsIni);
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
//TODO: iKeyReadInt (read INT)
INT
CxIni::iKeyReadInt(
    const tString &csKey,
    const LONG     ciDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///iDefaultValue - n/a

    return CxString::lexical_cast<LONG>( sKeyReadString(csKey, CxString::lexical_cast(ciDefaultValue)) );
}
//-------------------------------------------------------------------------
//TODO: bKeyWriteInt (write INT)
BOOL
CxIni::bKeyWriteInt(
    const tString &csKey,
    const LONG     ciValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///iValue    - n/a

    return bKeyWriteString(csKey, CxString::lexical_cast(ciValue));
}
//-------------------------------------------------------------------------
//TODO: dKeyReadFloat (read FLOAT)
double
CxIni::dKeyReadFloat(
    const tString &csKey,
    const double   cdDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0.0);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///dDefaultValue - n/a

    return CxString::lexical_cast<double>( sKeyReadString(csKey, CxString::lexical_cast(cdDefaultValue)) );
}
//-------------------------------------------------------------------------
//TODO: bKeyWriteFloat (write FLOAT)
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
//TODO: bKeyReadBool (read BOOL)
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
//TODO: bKeyWriteBool (write BOOL)
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
//TODO: usKeyReadBin (write uString)
uString
CxIni::usKeyReadBin(
    const tString &csKey,
    const uString &cusDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), uString());
    /*DEBUG*///csKey          - n/a
    /*DEBUG*///cusDefaultValue - n/a

    uString usRes;

    tString sHexStr = sKeyReadString(csKey, tString(cusDefaultValue.begin(), cusDefaultValue.end()));

    //sHexStr -> usRes
    #if xTODO
        usRes = CxString::lexical_cast<uString/*UCHAR*/>(sHexStr, 16);
    #endif

    return usRes;
}
//-------------------------------------------------------------------------
//TODO: bKeyWriteBin (read uString)
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

    #if xTODO
        sHexStr = CxString::lexical_cast(cusValue, 16);
    #endif

    return bKeyWriteString(csKey, sHexStr);
}
//-------------------------------------------------------------------------

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
    _m_bRes = CxStdioFile::bTextRead(_m_sFilePath, CxConst::xEQUAL, &_m_mmsIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //read to TIni
    TIni::iterator it = _m_mmsIni.find(csKey);
    if (_m_mmsIni.end() == it) {
        _m_bRes = _bWrite(csKey, csDefaultValue);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        (*psValue) = csDefaultValue;
    } else {
        (*psValue) = (*it).second;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE:: _bWrite (flush to TIni, file)
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
    TIni::iterator it = _m_mmsIni.find(csKey);
    if (_m_mmsIni.end() == it) {
        _m_mmsIni.insert( std::pair<tString, tString>(csKey, csValue) );
    } else {
        (*it).second = csValue;
    }

    //write to file
    _m_bRes = CxStdioFile::bTextWrite(_m_sFilePath, CxConst::xEQUAL, _m_mmsIni);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------










//-------------------------------------------------------------------------
//TODO: bKeyClear (������� �����)
#if xTODO
    BOOL
    CxIni::bKeyClear(const tString &csKey) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
        /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);

        return bKeyWriteString(csSection, csKey, tString());
    }
#endif
//---------------------------------------------------------------------------
//TODO: bKeyDelete (�������� �����)
#if xTODO
    BOOL
    CxIni::bKeyDelete(const tString &csKey) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
        /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);

    #if defined(xOS_WIN)
        //TODO: xOS_WIN
        _m_bRes = ::WritePrivateProfileString(csSection.c_str(), csKey.c_str(), NULL, _m_sFilePath.c_str());
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX
        xNOT_IMPLEMENTED_RET(FALSE);
    #endif

        return TRUE;
    }
#endif
//---------------------------------------------------------------------------











