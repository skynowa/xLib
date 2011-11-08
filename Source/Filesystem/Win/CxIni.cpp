/**
 * \file  CxIni.cpp
 * \brief ini
 */


#include <xLib/Filesystem/Win/CxIni.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFile.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public: creation
*
*****************************************************************************/

//-------------------------------------------------------------------------
CxIni::CxIni() :
    _m_sFilePath()
{
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(), return);

    BOOL bRes = bSetPath(CxPath::sSetExt( CxPath::sGetExe(), xT("ini") ));
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//-------------------------------------------------------------------------
CxIni::CxIni(
    const std::string_t &csFilePath
) :
    _m_sFilePath()
{
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(), return);
    /*DEBUG*/xASSERT_DO(false == csFilePath.empty(),   return);

    BOOL bRes = bSetPath(csFilePath);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//-------------------------------------------------------------------------
/*virtual*/
CxIni::~CxIni() {
    (void)bFlush();
}
//-------------------------------------------------------------------------
//DONE: bCreateDefault
BOOL
CxIni::bCreateDefault(
    const std::string_t &csContent
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/// csContent - n/a;

    //�������� �����
    BOOL bRes = CxDir::bCreateForce(CxPath::sGetDir(_m_sFilePath));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //�������� �����
    CxFile sfFile;

    bRes = sfFile.bCreate(_m_sFilePath, CxFile::omCreateReadWrite, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    int iRes = sfFile.iWrite(csContent.c_str());
    /*DEBUG*/xASSERT_RET(CxFile::etError != iRes, FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
//DONE: sGetPath
std::string_t
CxIni::sGetPath() {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::string_t());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
//DONE: bSetPath
BOOL
CxIni::bSetPath(
    const std::string_t &csFilePath
)
{
    /*DEBUG*///_m_sFilePath - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    _m_sFilePath.assign(csFilePath);

    BOOL bRes = CxDir::bCreateForce(CxPath::sGetDir(_m_sFilePath));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bFlush
BOOL
CxIni::bFlush() {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);

    BOOL bRes = ::WritePrivateProfileString(NULL, NULL, NULL, _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE == bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear
BOOL
CxIni::bClear() {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);

    std::vector<std::string_t> vsNames;

    BOOL bRes = bSectionsReadNames(&vsNames);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    for (std::size_t i = 0; i < vsNames.size(); ++ i) {
        bRes = bSectionDelete(vsNames.at(i));
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: key
*
*****************************************************************************/

//-------------------------------------------------------------------------
//DONE: bKeyIsExists
BOOL
CxIni::bKeyIsExists(
    const std::string_t &csSection,
    const std::string_t &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);

    std::map<std::string_t, std::string_t> msContent;

    BOOL bRes = bSectionRead(csSection, &msContent);
    xASSERT(FALSE != bRes);

    if (msContent.end() == msContent.find(csKey)) {
        return FALSE;
    } else {
        return TRUE;
    }
}
//---------------------------------------------------------------------------
//DONE: iKeyReadInt
int
CxIni::iKeyReadInt(
    const std::string_t &csSection,
    const std::string_t &csKey,
    LONG                iDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    0);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///iDefaultValue - n/a

    return CxString::lexical_cast<LONG>( sKeyReadString(csSection, csKey, CxString::lexical_cast(iDefaultValue)) );
}
//-------------------------------------------------------------------------
//DONE: bKeyWriteInt
BOOL
CxIni::bKeyWriteInt(
    const std::string_t &csSection,
    const std::string_t &csKey,
    LONG                iValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///iValue    - n/a

    return bKeyWriteString(csSection, csKey, CxString::lexical_cast(iValue));
}
//-------------------------------------------------------------------------
//DONE: dKeyReadFloat
double
CxIni::dKeyReadFloat(
    const std::string_t &csSection,
    const std::string_t &csKey,
    double              dDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0.0);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    0.0);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///dDefaultValue - n/a

    return CxString::lexical_cast<double>( sKeyReadString(csSection, csKey, CxString::lexical_cast(dDefaultValue)) );
}
//-------------------------------------------------------------------------
//DONE: bKeyWriteFloat
BOOL
CxIni::bKeyWriteFloat(
    const std::string_t &csSection,
    const std::string_t &csKey,
    double              dValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///dValue    - n/a

    return bKeyWriteString(csSection, csKey, CxString::lexical_cast(dValue));
}
//-------------------------------------------------------------------------
//DONE: bKeyReadBool
BOOL
CxIni::bKeyReadBool(
    const std::string_t &csSection,
    const std::string_t &csKey,
    BOOL                bDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///bDefaultValue - n/a
      
    std::string_t sStr;
    std::string_t sDefaultValue;

    sStr = sKeyReadString(csSection, csKey, CxString::sBoolToStr(bDefaultValue));

    BOOL bRes = CxString::bStrToBool(sStr);
    /*DEBUG*/

    return bRes;
}
//-------------------------------------------------------------------------
//DONE: bKeyWriteBool
BOOL
CxIni::bKeyWriteBool(
    const std::string_t &csSection,
    const std::string_t &csKey,
    BOOL                bValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///bValue    - n/a

    std::string_t sValue;

    sValue = bValue ? xT("true") : xT("false");

    return bKeyWriteString(csSection, csKey, sValue);
}
//-------------------------------------------------------------------------
//DONE: sKeyReadString
std::string_t
CxIni::sKeyReadString(
    const std::string_t &csSection,
    const std::string_t &csKey,
    const std::string_t &csDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::string_t());
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    std::string_t());
    /*DEBUG*///csKey          - n/a
    /*DEBUG*///csDefaultValue - n/a

    std::string_t      sRes;
    const std::size_t cuiLineSize = 32;
    ULONG             ulRes       = 0UL;

    sRes.resize(cuiLineSize);

    for ( ; ; ) {
        ulRes = ::GetPrivateProfileString(csSection.c_str(), csKey.c_str(), csDefaultValue.c_str(), &sRes.at(0), sRes.size(), _m_sFilePath.c_str());
        /*DEBUG*/// n/a

        if (ulRes < sRes.size() - 2) {
            sRes.resize(ulRes);

            break;
        } else {
            sRes.resize(sRes.size() * 2);
        }
    }

    return sRes;
}
//-------------------------------------------------------------------------
//DONE: bKeyWriteString
BOOL
CxIni::bKeyWriteString(
    const std::string_t &csSection,
    const std::string_t &csKey,
    const std::string_t &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///csValue   - n/a

    BOOL bRes = ::WritePrivateProfileString(csSection.c_str(), csKey.c_str(), csValue.c_str(), _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
//DONE: usKeyReadBin
std::ustring
CxIni::usKeyReadBin(
    const std::string_t &csSection,
    const std::string_t &csKey,
    const std::ustring &cusDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::ustring());
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    std::ustring());
    /*DEBUG*///csKey          - n/a
    /*DEBUG*///cusDefaultValue - n/a

    std::string_t sRes;

    std::string_t sHexStr = sKeyReadString(csSection, csKey, std::string_t(cusDefaultValue.begin(), cusDefaultValue.end()));

    //sHexStr -> usRes
    sRes = CxString::lexical_cast(sHexStr, 16);

    return std::ustring(sRes.begin(), sRes.end());
}
//-------------------------------------------------------------------------
//DONE: bKeyWriteBin
BOOL
CxIni::bKeyWriteBin(
    const std::string_t &csSection,
    const std::string_t &csKey,
    const std::ustring &cusValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///cusValue  - n/a

    //cusValue (std::ustring) -> sHexStr (std::string_t)
    std::string_t sHexStr = CxString::lexical_cast(std::string_t(cusValue.begin(), cusValue.end()), 16);

    return bKeyWriteString(csSection, csKey, sHexStr);
}
//-------------------------------------------------------------------------
//DONE: bKeyClear
BOOL
CxIni::bKeyClear(
    const std::string_t &csSection,
    const std::string_t &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);

    return bKeyWriteString(csSection, csKey, std::string_t());
}
//---------------------------------------------------------------------------
//DONE: bKeyDelete
BOOL
CxIni::bKeyDelete(
    const std::string_t &csSection,
    const std::string_t &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);

    BOOL bRes = ::WritePrivateProfileString(csSection.c_str(), csKey.c_str(), NULL, _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: section
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bSectionIsExists
BOOL
CxIni::bSectionIsExists(
    const std::string_t &csSection
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);

    ULONG             ulRes       = 0;
    std::string_t           sRes;
    const std::size_t cuiLineSize = 32;

    sRes.resize(cuiLineSize);

    ulRes = ::GetPrivateProfileString(csSection.c_str(), NULL, xT(""), &sRes.at(0), sRes.size(), _m_sFilePath.c_str());

    return (ulRes > 0UL);
}
//---------------------------------------------------------------------------
//DONE: bSectionRead
BOOL
CxIni::bSectionRead(
    const std::string_t                   &csSection,
    std::map<std::string_t, std::string_t> *pmsContent
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pmsContent,         FALSE);

    std::string_t      sBuff;
    const std::size_t cuiSectionSize = 32 * 4;
    ULONG             ulRes          = 0;

    sBuff.resize(cuiSectionSize);

    for ( ; ; ) {
        ulRes = ::GetPrivateProfileSection(csSection.c_str(), &sBuff.at(0), /*DWORD*/sBuff.size(), _m_sFilePath.c_str());
        /*DEBUG*/// n/a
        xCHECK_RET(0 == ulRes, TRUE);    //������ ����� ��� �� ����������

        if (ulRes < sBuff.size() - 2) {
            sBuff.resize(ulRes);

            break;
        } else {
            sBuff.resize(sBuff.size() * 2);
        }
    }

    //-------------------------------------
    //���������� std::vector
    std::vector<std::string_t> vsContent;

    vsContent.clear();

    sBuff = CxString::sReplaceAll(sBuff, xT('\0'), CxConst::xNL.at(0));
    /*DEBUG*/

    sBuff = CxString::sTrimRightChars(sBuff, CxConst::xNL);
    /*DEBUG*/

    if (std::string_t::npos != sBuff.find(CxConst::xNL)) {
        BOOL bRes = CxString::bSplit(sBuff, CxConst::xNL, &vsContent);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    } else {
        vsContent.push_back(sBuff);
    }

    //-------------------------------------
    //���������� std::map
    /*
    qqq=111
    www=222
    eee=333
    */
    (*pmsContent).clear();

    std::vector<std::string_t> vsKeyValue;
    std::pair<std::map<std::string_t, std::string_t>::iterator, bool> itRet;

    for (std::vector<std::string_t>::const_iterator it = vsContent.begin(); it != vsContent.end(); ++ it) {
        BOOL bRes = CxString::bSplit(*it, xT("="), &vsKeyValue);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        itRet = (*pmsContent).insert( std::pair<std::string_t, std::string_t>(vsKeyValue.at(0), vsKeyValue.at(1)) );
        /*DEBUG*/xASSERT_RET(false != itRet.second, FALSE);        //element 'z' already existed
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSectionWrite
BOOL
CxIni::bSectionWrite(
    const std::string_t                         &csSection,
    const std::map<std::string_t, std::string_t> &msContent
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
    /*DEBUG*/// vsContent - n/a

    std::string_t sContent;

    //-------------------------------------
    //������ std::map
    for (std::map<std::string_t, std::string_t>::const_iterator it = msContent.begin();
        it != msContent.end();
        ++ it)
    {
        sContent.append((*it).first);
        sContent.append(xT("="));
        sContent.append((*it).second);
        sContent.push_back(xT('\0'));
    }

    //-------------------------------------
    //������
    BOOL bRes = ::WritePrivateProfileSection(csSection.c_str(), sContent.c_str(), _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
//DONE: bSectionsReadNames
BOOL
CxIni::bSectionsReadNames(
    std::vector<std::string_t> *pvsNames
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pvsNames,           FALSE);

    std::string_t           sBuff;
    const std::size_t cuiSectionsNamesSize = 32 * 8;
    ULONG             ulRes                = 0;

    sBuff.resize(cuiSectionsNamesSize);

    for ( ; ; ) {
        ulRes = ::GetPrivateProfileSectionNames(&sBuff.at(0), /*DWORD*/sBuff.size(), _m_sFilePath.c_str());
        /*DEBUG*/// n/a
        xCHECK_RET(0 == ulRes, TRUE);    //���� ����

        if (ulRes < sBuff.size() - 2) {
            sBuff.resize(ulRes);

            break;
        } else {
            sBuff.resize(sBuff.size() * 2);
        }
    }

    //-------------------------------------
    //���������� std::vector
    sBuff.resize(ulRes);
    (*pvsNames).clear();

    sBuff = CxString::sReplaceAll(sBuff, xT('\0'), CxConst::xNL.at(0));
    /*DEBUG*/

    sBuff = CxString::sTrimRightChars(sBuff, CxConst::xNL);
    /*DEBUG*/

    BOOL bRes = CxString::bSplit(sBuff, CxConst::xNL, pvsNames);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
//DONE: bSectionClear
BOOL
CxIni::bSectionClear(
    const std::string_t &csSection
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);

    BOOL bRes = ::WritePrivateProfileSection(csSection.c_str(), xT(""), _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
//DONE: bSectionDelete
BOOL
CxIni::bSectionDelete(
    const std::string_t &csSection
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);

    BOOL bRes = ::WritePrivateProfileSection(csSection.c_str(), NULL, _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//-------------------------------------------------------------------------
#endif
