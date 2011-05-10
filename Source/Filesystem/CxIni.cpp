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
//DONE: CxIni (����������� - ���� � ���������� Exe)
CxIni::CxIni() :
    _m_bRes     (FALSE),
    _m_sFilePath()
{
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(), return);

    _m_bRes = bSetPath(CxPath::sSetExt( CxPath::sGetExe(), xT("ini") ));
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//-------------------------------------------------------------------------
//DONE: CxIni (����������� - ���� � �������� ����������)
CxIni::CxIni(const tString &csFilePath) :
    _m_bRes     (FALSE),
    _m_sFilePath()
{
    /*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(), return);
    /*DEBUG*/xASSERT_DO(false == csFilePath.empty(),   return);

    _m_bRes = bSetPath(csFilePath);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//-------------------------------------------------------------------------
//DONE: ~CxIni (����������)
/*virtual*/
CxIni::~CxIni() {
    _m_bRes = bFlush();
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//-------------------------------------------------------------------------
//DONE: bCreateDefault (�������� ����� ��-���������)
#if xTEMP_DISABLED
    BOOL
    CxIni::bCreateDefault(const tString &csContent) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
        /*DEBUG*/// csContent - n/a;

    #if defined(xOS_WIN)
        //TODO: xOS_WIN
        //�������� �����
        _m_bRes = CxDir::bCreateForce(CxPath::sGetDir(_m_sFilePath));
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        //�������� �����
        CxStdioFile sfFile;

        _m_bRes = sfFile.bOpen(_m_sFilePath, CxStdioFile::omCreateReadWrite);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        INT iRes = sfFile.iWrite(csContent.c_str());
        /*DEBUG*/xASSERT_RET(CxStdioFile::etError != iRes, FALSE);
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX
        xNOT_IMPLEMENTED_RET(FALSE);
    #endif

        return TRUE;
    }
#endif
//-------------------------------------------------------------------------
//DONE: sGetPath (��������� ���� � �����)
tString
CxIni::sGetPath() {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), tString());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
//DONE: bSetPath (��������� ���� � ����)
BOOL
CxIni::bSetPath(const tString &csFilePath) {
    /*DEBUG*///_m_sFilePath - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    _m_sFilePath.assign(csFilePath);

    _m_bRes = CxDir::bCreateForce(CxPath::sGetDir(_m_sFilePath));
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bFlush (����� ����������� � ����)
BOOL
CxIni::bFlush() {
    /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);

#if defined(xOS_WIN)
    //TODO: xOS_WIN
    _m_bRes = ::WritePrivateProfileString(NULL, NULL, NULL, _m_sFilePath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE == _m_bRes, FALSE);
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear (������� �����)
#if xTEMP_DISABLED
    BOOL
    CxIni::bClear() {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);

        #if defined(xOS_WIN)
            //TODO: xOS_WIN
            std::vector<tString> vecsNames;

            _m_bRes = bSectionsReadNames(&vecsNames);
            /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

            for (std::size_t i = 0; i < vecsNames.size(); ++ i) {
                _m_bRes = bSectionDelete(vecsNames.at(i));
                /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
            }
        #elif defined(xOS_LINUX)
            //TODO: xOS_LINUX
            xNOT_IMPLEMENTED_RET(FALSE);
        #endif

        return TRUE;
    }
#endif
//---------------------------------------------------------------------------


/****************************************************************************
*    public: key
*
*****************************************************************************/

//-------------------------------------------------------------------------
//DONE: bKeyIsExists (������������� ������)
#if xTEMP_DISABLED
    BOOL
    CxIni::bKeyIsExists(const tString &csSection, const tString &csKey) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);

    #if defined(xOS_WIN)
        //TODO: xOS_WIN
        std::map<tString, tString> mapsContent;

        _m_bRes = bSectionRead(csSection, &mapsContent);
        xASSERT(FALSE != _m_bRes);

        if (mapsContent.end() == mapsContent.find(csKey)) {
            return FALSE;
        } else {
            return TRUE;
        }
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX
        xNOT_IMPLEMENTED_RET(FALSE);
    #endif
    }
#endif
//---------------------------------------------------------------------------
//DONE: iKeyReadInt (������ INT)
#if xTEMP_DISABLED
    INT
    CxIni::iKeyReadInt(const tString &csSection, const tString &csKey, LONG iDefaultValue) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    0);
        /*DEBUG*///csKey         - n/a
        /*DEBUG*///iDefaultValue - n/a

        return CxString::lexical_cast<LONG>( sKeyReadString(csSection, csKey, CxString::lexical_cast(iDefaultValue)) );
    }
#endif
//-------------------------------------------------------------------------
//DONE: bKeyWriteInt (������ INT)
#if xTEMP_DISABLED
    BOOL
    CxIni::bKeyWriteInt(const tString &csSection, const tString &csKey, LONG iValue) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
        /*DEBUG*///csKey     - n/a
        /*DEBUG*///iValue    - n/a

        return bKeyWriteString(csSection, csKey, CxString::lexical_cast(iValue));
    }
#endif
//-------------------------------------------------------------------------
//DONE: dKeyReadFloat (������ FLOAT)
#if xTEMP_DISABLED
    double
    CxIni::dKeyReadFloat(const tString &csSection, const tString &csKey, double dDefaultValue) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0.0);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    0.0);
        /*DEBUG*///csKey         - n/a
        /*DEBUG*///dDefaultValue - n/a

        return CxString::lexical_cast<double>( sKeyReadString(csSection, csKey, CxString::lexical_cast(dDefaultValue)) );
    }
#endif
//-------------------------------------------------------------------------
//DONE: bKeyWriteFloat (������ FLOAT)
#if xTEMP_DISABLED
    BOOL
    CxIni::bKeyWriteFloat(const tString &csSection, const tString &csKey, double dValue) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
        /*DEBUG*///csKey     - n/a
        /*DEBUG*///dValue    - n/a

        return bKeyWriteString(csSection, csKey, CxString::lexical_cast(dValue));
    }
#endif
//-------------------------------------------------------------------------
//DONE: bKeyReadBool (������ BOOL)
#if xTEMP_DISABLED
    BOOL
    CxIni::bKeyReadBool(const tString &csSection, const tString &csKey, BOOL bDefaultValue) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
        /*DEBUG*///csKey         - n/a
        /*DEBUG*///bDefaultValue - n/a

        BOOL    bRes = FALSE;
        tString sStr;
        tString sDefaultValue;

        sStr = CxString::sBoolToStr(bDefaultValue);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        sStr = sKeyReadString(csSection, csKey, sStr);

        bRes = CxString::bStrToBool(sStr);
        /*DEBUG*/

        return bRes;
    }
#endif
//-------------------------------------------------------------------------
//DONE: bKeyWriteBool (������ BOOL)
#if xTEMP_DISABLED
    BOOL
    CxIni::bKeyWriteBool(const tString &csSection, const tString &csKey, BOOL bValue) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
        /*DEBUG*///csKey     - n/a
        /*DEBUG*///bValue    - n/a

        tString sValue;

        sValue = bValue ? xT("true") : xT("false");

        return bKeyWriteString(csSection, csKey, sValue);
    }
#endif
//-------------------------------------------------------------------------
//DONE: sKeyReadString (������ tString)
#if xTEMP_DISABLED
    tString
    CxIni::sKeyReadString(const tString &csSection, const tString &csKey, const tString &csDefaultValue) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), tString());
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    tString());
        /*DEBUG*///csKey          - n/a
        /*DEBUG*///csDefaultValue - n/a

        tString           sRes;

    #if defined(xOS_WIN)
        //TODO: xOS_WIN
        const std::size_t cuiLineSize = 32;
        ULONG             ulRes       = 0;

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
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX
        xNOT_IMPLEMENTED_RET(tString());
    #endif

        return sRes;
    }
#endif
//-------------------------------------------------------------------------
//DONE: bKeyWriteString (������ tString)
#if xTEMP_DISABLED
    BOOL
    CxIni::bKeyWriteString(const tString &csSection, const tString &csKey, const tString &csValue) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
        /*DEBUG*///csKey     - n/a
        /*DEBUG*///csValue   - n/a

    #if defined(xOS_WIN)
        //TODO: xOS_WIN
        _m_bRes = ::WritePrivateProfileString(csSection.c_str(), csKey.c_str(), csValue.c_str(), _m_sFilePath.c_str());
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX
        xNOT_IMPLEMENTED_RET(FALSE);
    #endif

        return TRUE;
    }
#endif
//-------------------------------------------------------------------------
//DONE: usKeyReadBin (������ uString)
#if xTEMP_DISABLED
    uString
    CxIni::usKeyReadBin(const tString &csSection, const tString &csKey, const uString &cusDefaultValue) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), uString());
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    uString());
        /*DEBUG*///csKey          - n/a
        /*DEBUG*///cusDefaultValue - n/a

        uString usRes;

    #if defined(xOS_WIN)
        //TODO: xOS_WIN
        tString sHexStr = sKeyReadString(csSection, csKey, tString(cusDefaultValue.begin(), cusDefaultValue.end()));

        //sHexStr -> usRes
        usRes = CxString::sFromBase<uString/*UCHAR*/>(sHexStr, 16);
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX
        xNOT_IMPLEMENTED_RET(uString());
    #endif

        return usRes;
    }
#endif
//-------------------------------------------------------------------------
//DONE: bKeyWriteBin (������ uString)
#if xTEMP_DISABLED
    BOOL
    CxIni::bKeyWriteBin(const tString &csSection, const tString &csKey, const uString &cusValue) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
        /*DEBUG*///csKey     - n/a
        /*DEBUG*///cusValue  - n/a

    #if defined(xOS_WIN)
        //TODO: xOS_WIN
        //cusValue (uString) -> sHexStr (tString)
        tString sHexStr = CxString::sToBase(cusValue, 16);

        return bKeyWriteString(csSection, csKey, sHexStr);
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX
        xNOT_IMPLEMENTED_RET(FALSE);
    #endif
    }
#endif
//-------------------------------------------------------------------------
//DONE: bKeyClear (������� �����)
#if xTEMP_DISABLED
    BOOL
    CxIni::bKeyClear(const tString &csSection, const tString &csKey) {
        /*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
        /*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
        /*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);

        return bKeyWriteString(csSection, csKey, tString());
    }
#endif
//---------------------------------------------------------------------------
//DONE: bKeyDelete (�������� �����)
#if xTEMP_DISABLED
    BOOL
    CxIni::bKeyDelete(const tString &csSection, const tString &csKey) {
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












