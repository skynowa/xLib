/**
 * \file  CxIni.cpp
 * \brief ini
 */


#include <xLib/Filesystem/Win/CxIni.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFile.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public: creation
*
*****************************************************************************/

//-------------------------------------------------------------------------
CxIni::CxIni() :
    _m_sFilePath()
{
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(), return);

    bool bRes = bSetPath(CxPath::sSetExt( CxPath::sGetExe(), xT("ini") ));
    /*DEBUG*/xASSERT_DO(false != bRes, return);
}
//-------------------------------------------------------------------------
CxIni::CxIni(
    const std::tstring &csFilePath
) :
    _m_sFilePath()
{
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(), return);
    /*DEBUG*/xASSERT_DO(false == csFilePath.empty(),   return);

    bool bRes = bSetPath(csFilePath);
    /*DEBUG*/xASSERT_DO(false != bRes, return);
}
//-------------------------------------------------------------------------
/*virtual*/
CxIni::~CxIni() {
    (void)bFlush();
}
//-------------------------------------------------------------------------
//DONE: bCreateDefault
bool
CxIni::bCreateDefault(
    const std::tstring &csContent
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/// csContent - n/a;

    //�������� �����
    bool bRes = CxDir::bCreateForce(CxPath::sGetDir(_m_sFilePath));
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    //�������� �����
    CxFile sfFile;

    bRes = sfFile.bCreate(_m_sFilePath, CxFile::omCreateReadWrite, true);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    int iRes = sfFile.iWrite(csContent.c_str());
    /*DEBUG*/xASSERT_RET(CxFile::etError != iRes, false);

    return true;
}
//-------------------------------------------------------------------------
//DONE: sGetPath
std::tstring
CxIni::sGetPath() {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::tstring());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
//DONE: bSetPath
bool
CxIni::bSetPath(
    const std::tstring &csFilePath
)
{
    /*DEBUG*///_m_sFilePath - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

    _m_sFilePath.assign(csFilePath);

    bool bRes = CxDir::bCreateForce(CxPath::sGetDir(_m_sFilePath));
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bFlush
bool
CxIni::bFlush() {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);

    BOOL blRes = ::WritePrivateProfileString(NULL, NULL, NULL, _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE == blRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bClear
bool
CxIni::bClear() {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);

    std::vector<std::tstring> vsNames;

    bool bRes = bSectionsReadNames(&vsNames);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    for (std::size_t i = 0; i < vsNames.size(); ++ i) {
        bRes = bSectionDelete(vsNames.at(i));
        /*DEBUG*/xASSERT_RET(false != bRes, false);
    }

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: key
*
*****************************************************************************/

//-------------------------------------------------------------------------
//DONE: bKeyIsExists
bool
CxIni::bKeyIsExists(
    const std::tstring &csSection,
    const std::tstring &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);

    std::map<std::tstring, std::tstring> msContent;

    bool bRes = bSectionRead(csSection, &msContent);
    xASSERT(false != bRes);

    if (msContent.end() == msContent.find(csKey)) {
        return false;
    } else {
        return true;
    }
}
//---------------------------------------------------------------------------
//DONE: iKeyReadInt
int
CxIni::iKeyReadInt(
    const std::tstring &csSection,
    const std::tstring &csKey,
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
bool
CxIni::bKeyWriteInt(
    const std::tstring &csSection,
    const std::tstring &csKey,
    LONG                iValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///iValue    - n/a

    return bKeyWriteString(csSection, csKey, CxString::lexical_cast(iValue));
}
//-------------------------------------------------------------------------
//DONE: dKeyReadFloat
double
CxIni::dKeyReadFloat(
    const std::tstring &csSection,
    const std::tstring &csKey,
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
bool
CxIni::bKeyWriteFloat(
    const std::tstring &csSection,
    const std::tstring &csKey,
    double              dValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///dValue    - n/a

    return bKeyWriteString(csSection, csKey, CxString::lexical_cast(dValue));
}
//-------------------------------------------------------------------------
//DONE: bKeyReadBool
bool
CxIni::bKeyReadBool(
    const std::tstring &csSection,
    const std::tstring &csKey,
    bool                bDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);
    /*DEBUG*///csKey         - n/a
    /*DEBUG*///bDefaultValue - n/a

    std::tstring sStr;
    std::tstring sDefaultValue;

    sStr = sKeyReadString(csSection, csKey, CxString::sBoolToStr(bDefaultValue));

    bool bRes = CxString::bStrToBool(sStr);
    /*DEBUG*/

    return bRes;
}
//-------------------------------------------------------------------------
//DONE: bKeyWriteBool
bool
CxIni::bKeyWriteBool(
    const std::tstring &csSection,
    const std::tstring &csKey,
    bool                bValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///bValue    - n/a

    std::tstring sValue;

    sValue = bValue ? xT("true") : xT("false");

    return bKeyWriteString(csSection, csKey, sValue);
}
//-------------------------------------------------------------------------
//DONE: sKeyReadString
std::tstring
CxIni::sKeyReadString(
    const std::tstring &csSection,
    const std::tstring &csKey,
    const std::tstring &csDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::tstring());
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    std::tstring());
    /*DEBUG*///csKey          - n/a
    /*DEBUG*///csDefaultValue - n/a

    std::tstring      sRes;
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
bool
CxIni::bKeyWriteString(
    const std::tstring &csSection,
    const std::tstring &csKey,
    const std::tstring &csValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///csValue   - n/a

    BOOL blRes = ::WritePrivateProfileString(csSection.c_str(), csKey.c_str(), csValue.c_str(), _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//-------------------------------------------------------------------------
//DONE: usKeyReadBin
std::ustring
CxIni::usKeyReadBin(
    const std::tstring &csSection,
    const std::tstring &csKey,
    const std::ustring &cusDefaultValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), std::ustring());
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    std::ustring());
    /*DEBUG*///csKey          - n/a
    /*DEBUG*///cusDefaultValue - n/a

    std::tstring sRes;

    std::tstring sHexStr = sKeyReadString(csSection, csKey, std::tstring(cusDefaultValue.begin(), cusDefaultValue.end()));

    //sHexStr -> usRes
    sRes = CxString::lexical_cast(sHexStr, 16);

    return std::ustring(sRes.begin(), sRes.end());
}
//-------------------------------------------------------------------------
//DONE: bKeyWriteBin
bool
CxIni::bKeyWriteBin(
    const std::tstring &csSection,
    const std::tstring &csKey,
    const std::ustring &cusValue
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);
    /*DEBUG*///csKey     - n/a
    /*DEBUG*///cusValue  - n/a

    //cusValue (std::ustring) -> sHexStr (std::tstring)
    std::tstring sHexStr = CxString::lexical_cast(std::tstring(cusValue.begin(), cusValue.end()), 16);

    return bKeyWriteString(csSection, csKey, sHexStr);
}
//-------------------------------------------------------------------------
//DONE: bKeyClear
bool
CxIni::bKeyClear(
    const std::tstring &csSection,
    const std::tstring &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        false);

    return bKeyWriteString(csSection, csKey, std::tstring());
}
//---------------------------------------------------------------------------
//DONE: bKeyDelete
bool
CxIni::bKeyDelete(
    const std::tstring &csSection,
    const std::tstring &csKey
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);
    /*DEBUG*/xASSERT_RET(false == csKey.empty(),        false);

    BOOL blRes = ::WritePrivateProfileString(csSection.c_str(), csKey.c_str(), NULL, _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: section
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bSectionIsExists
bool
CxIni::bSectionIsExists(
    const std::tstring &csSection
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);

    ULONG             ulRes       = 0;
    std::tstring           sRes;
    const std::size_t cuiLineSize = 32;

    sRes.resize(cuiLineSize);

    ulRes = ::GetPrivateProfileString(csSection.c_str(), NULL, xT(""), &sRes.at(0), sRes.size(), _m_sFilePath.c_str());

    return (ulRes > 0UL);
}
//---------------------------------------------------------------------------
//DONE: bSectionRead
bool
CxIni::bSectionRead(
    const std::tstring                   &csSection,
    std::map<std::tstring, std::tstring> *pmsContent
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);
    /*DEBUG*/xASSERT_RET(NULL  != pmsContent,         false);

    std::tstring      sBuff;
    const std::size_t cuiSectionSize = 32 * 4;
    ULONG             ulRes          = 0;

    sBuff.resize(cuiSectionSize);

    for ( ; ; ) {
        ulRes = ::GetPrivateProfileSection(csSection.c_str(), &sBuff.at(0), /*DWORD*/sBuff.size(), _m_sFilePath.c_str());
        /*DEBUG*/// n/a
        xCHECK_RET(0 == ulRes, true);    //������ ����� ��� �� ����������

        if (ulRes < sBuff.size() - 2) {
            sBuff.resize(ulRes);

            break;
        } else {
            sBuff.resize(sBuff.size() * 2);
        }
    }

    //-------------------------------------
    //���������� std::vector
    std::vector<std::tstring> vsContent;

    vsContent.clear();

    sBuff = CxString::sReplaceAll(sBuff, xT('\0'), CxConst::xNL.at(0));
    /*DEBUG*/

    sBuff = CxString::sTrimRightChars(sBuff, CxConst::xNL);
    /*DEBUG*/

    if (std::tstring::npos != sBuff.find(CxConst::xNL)) {
        bool bRes = CxString::bSplit(sBuff, CxConst::xNL, &vsContent);
        /*DEBUG*/xASSERT_RET(false != bRes, false);
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

    std::vector<std::tstring> vsKeyValue;
    std::pair<std::map<std::tstring, std::tstring>::iterator, bool> itRet;

    for (std::vector<std::tstring>::const_iterator it = vsContent.begin(); it != vsContent.end(); ++ it) {
        bool bRes = CxString::bSplit(*it, xT("="), &vsKeyValue);
        /*DEBUG*/xASSERT_RET(false != bRes, false);

        itRet = (*pmsContent).insert( std::pair<std::tstring, std::tstring>(vsKeyValue.at(0), vsKeyValue.at(1)) );
        /*DEBUG*/xASSERT_RET(false != itRet.second, false);        //element 'z' already existed
    }

    return true;
}
//---------------------------------------------------------------------------
//DONE: bSectionWrite
bool
CxIni::bSectionWrite(
    const std::tstring                         &csSection,
    const std::map<std::tstring, std::tstring> &msContent
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);
    /*DEBUG*/// vsContent - n/a

    std::tstring sContent;

    //-------------------------------------
    //������ std::map
    for (std::map<std::tstring, std::tstring>::const_iterator it = msContent.begin();
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
    BOOL blRes = ::WritePrivateProfileSection(csSection.c_str(), sContent.c_str(), _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//-------------------------------------------------------------------------
//DONE: bSectionsReadNames
bool
CxIni::bSectionsReadNames(
    std::vector<std::tstring> *pvsNames
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pvsNames,           false);

    std::tstring           sBuff;
    const std::size_t cuiSectionsNamesSize = 32 * 8;
    ULONG             ulRes                = 0;

    sBuff.resize(cuiSectionsNamesSize);

    for ( ; ; ) {
        ulRes = ::GetPrivateProfileSectionNames(&sBuff.at(0), /*DWORD*/sBuff.size(), _m_sFilePath.c_str());
        /*DEBUG*/// n/a
        xCHECK_RET(0 == ulRes, true);    //���� ����

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

    bool bRes = CxString::bSplit(sBuff, CxConst::xNL, pvsNames);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//-------------------------------------------------------------------------
//DONE: bSectionClear
bool
CxIni::bSectionClear(
    const std::tstring &csSection
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);

    BOOL blRes = ::WritePrivateProfileSection(csSection.c_str(), xT(""), _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//-------------------------------------------------------------------------
//DONE: bSectionDelete
bool
CxIni::bSectionDelete(
    const std::tstring &csSection
)
{
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csSection.empty(),    false);

    BOOL blRes = ::WritePrivateProfileSection(csSection.c_str(), NULL, _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//-------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
