/**
 * \file  CxBlowfish.cpp
 * \brief blowfish (openssl-1.0.0a)
 */


#include <xLib/Crypt/OpenSSL/CxBlowfish.h>

#include <xLib/Filesystem/CxStdioFile.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Debug/CxProfiler.h>
#include <xLib/Crypt/CxCrc32.h>

#if defined(xOS_WIN)
    #if defined(xCOMPILER_MS)
        #pragma comment(lib, "libeay32.lib")
    #endif
#elif defined(xOS_LINUX)
    // -lssl
#endif


/****************************************************************************
*    public
*
*****************************************************************************/

#define CRC32_STR_SIZE 8
#define BUFF_SIZE      1024

//---------------------------------------------------------------------------
//DONE: CxBlowfish
CxBlowfish::CxBlowfish() :
    _m_bRes(FALSE)
{
    xSTRUCT_ZERO(_m_bfKey);
    xBUFF_ZERO(_m_ucIvec);
}
//---------------------------------------------------------------------------
//DONE: ~CxBlowfish
CxBlowfish::~CxBlowfish() {
    /*SECURE*/xSTRUCT_ZERO(_m_bfKey);
    /*SECURE*/xBUFF_ZERO(_m_ucIvec);
}
//---------------------------------------------------------------------------
//DONE: bSetKey
BOOL
CxBlowfish::bSetKey(
    UCHAR *pucKey, 
    INT    iKeySize
)
{
    /*DEBUG*/xASSERT_RET(NULL         != pucKey,   FALSE);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= iKeySize, FALSE);
    /*DEBUG*/xASSERT_RET(0            <  iKeySize, FALSE);

    BF_set_key(&_m_bfKey, iKeySize, pucKey);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetKey (???? - UCHAR)
BOOL
CxBlowfish::bSetKey(
    const std::ustring &cusKey
)
{
    /*DEBUG*/xASSERT_RET(false        == cusKey.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= cusKey.size(),  FALSE);

    _m_bRes = bSetKey(const_cast<UCHAR *>( cusKey.data() ), cusKey.size());
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetKey (???? - std::tstring)
BOOL
CxBlowfish::bSetKey(
    const std::tstring &csKey
)
{
    /*DEBUG*/xASSERT_RET(false        == csKey.empty(),                              FALSE);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= csKey.size() * sizeof(std::tstring::value_type), FALSE);

    _m_bRes = bSetKey(std::ustring(csKey.begin(), csKey.end()));
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetFileKey (???? - ????)
BOOL
CxBlowfish::bSetFileKey(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    size_t      uiRes = 0;
    std::ustring     usFile;
    CxStdioFile sfFile;

    _m_bRes = sfFile.bOpen(csFilePath, CxStdioFile::omBinRead, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    LONG liFileSize = sfFile.liGetSize();
    /*DEBUG*/xASSERT_RET(0            <  liFileSize, FALSE);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= liFileSize, FALSE);

    usFile.resize(liFileSize);

    uiRes = sfFile.uiRead(&usFile.at(0), usFile.size());
    /*DEBUG*/xASSERT_RET(usFile.size() == uiRes, FALSE);

    _m_bRes = bSetKey(usFile);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    /*SECURE*/usFile.clear();

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: uiGetMaxKeySize
/*static*/
size_t
CxBlowfish::uiGetMaxKeySize() {
    return MAX_KEY_SIZE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: cfb64
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bEncryptCfb64
BOOL
CxBlowfish::bEncryptCfb64(
    UCHAR      *pucIn, 
    UCHAR      *pucOut, 
    LONG        liInSize, 
    INT        *piNum, 
    ECryptMode  cmMode
)
{
    /*DEBUG*/xASSERT_RET(NULL != pucIn,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pucIn,    FALSE);
    /*DEBUG*/xASSERT_RET(0    <  liInSize, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != piNum,    FALSE);

    xBUFF_ZERO(_m_ucIvec);

    BF_cfb64_encrypt(pucIn, pucOut, liInSize, &_m_bfKey, _m_ucIvec, piNum, cmMode);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bEncryptCfb64
BOOL
CxBlowfish::bEncryptCfb64(
    const std::ustring &cusIn, 
    std::ustring       *pusOut, 
    ECryptMode          cmMode
)
{
    /*DEBUG*/xASSERT_RET(false == cusIn.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pusOut,        FALSE);

    INT iNum = 0;    //This integer must be initialized to zero when ivec is initialized

    (*pusOut).resize( cusIn.size() );

    _m_bRes = bEncryptCfb64(const_cast<UCHAR *>(&cusIn.at(0)), &(*pusOut).at(0), cusIn.size(), &iNum, cmMode);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    /*DEBUG*/xASSERT_RET(- 1   <  iNum,    FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bEncryptFileCfb64
BOOL
CxBlowfish::bEncryptFileCfb64(
    const std::tstring &csFilePathIn, 
    const std::tstring &csFilePathOut, 
    ECryptMode          cmMode
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePathIn.empty(),  FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePathOut.empty(), FALSE);

    std::ustring usIn;
    std::ustring usOut;

    {
        CxStdioFile sfFileIn;

        _m_bRes = sfFileIn.bOpen(csFilePathIn, CxStdioFile::omBinRead, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        _m_bRes = sfFileIn.bRead(&usIn);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    }

    _m_bRes = bEncryptCfb64(usIn, &usOut, cmMode);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    {
        CxStdioFile sfFileOut;

        _m_bRes = sfFileOut.bOpen(csFilePathOut, CxStdioFile::omBinCreateReadWrite, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        _m_bRes = sfFileOut.bWrite(usOut);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bEncryptFileCfb64 (COMMENTS)
BOOL
CxBlowfish::bEncryptFileCfb64(
    const std::tstring &csFilePathIn, 
    const std::tstring &csFilePathOut, 
    const std::ustring &cusStamp, 
    ECryptMode          cmCryptMode
)
{
    /*DEBUG*/

    //-------------------------------------
    //??????????? ??????? ????? (???? / ??????)
    ECryptMode cmFileCryptStatus = cmGetFileCryptStatus(csFilePathIn, cusStamp);
    xCHECK_RET(cmEncrypt == cmCryptMode && cmEncrypt == cmFileCryptStatus, TRUE);
    xCHECK_RET(cmDecrypt == cmCryptMode && cmDecrypt == cmFileCryptStatus, TRUE);

    const std::tstring g_csCryptFileExt = xT("enc");
    const std::tstring g_csTempFileExt  = xT("tmp");
    std::ustring       usCrc32FromStamp;

    //-------------------------------------
    //???????? ??????
    CxStdioFile sfFileIn;
    CxStdioFile sfFileOut;

    _m_bRes = sfFileIn.bOpen(csFilePathIn,   CxStdioFile::omBinRead, TRUE);
    /*DEBUF*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bRes = sfFileOut.bOpen(csFilePathOut, CxStdioFile::omBinWrite, TRUE);
    /*DEBUF*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //Crc32 + ?????
    switch (cmCryptMode) {
        //??????????
        case cmEncrypt: {
                //-------------------------------------
                //????? + Crc32
                std::ustring usStampCrc32;

                ULONG   ulCrc32 = CxCrc32::ulCalcFileFast(csFilePathIn);
                std::tstring sCrc32 = CxCrc32::sFormatHex(ulCrc32);

                usStampCrc32 = cusStamp + xS2US(sCrc32);
                /*DEBUG*/xASSERT_RET(cusStamp.size() + CRC32_STR_SIZE == usStampCrc32.size(), FALSE);

                //-------------------------------------
                //?????? ?????? ? Crc32 ? ???. ????
                size_t uiWrited = sfFileOut.uiWrite((LPVOID)&usStampCrc32.at(0), usStampCrc32.size());
                /*DEBUF*/xASSERT_RET(uiWrited == usStampCrc32.size(), FALSE);
            }
            break;

        //????????????
        case cmDecrypt: {
                //-------------------------------------
                //?????
                std::ustring usCrc32;

                usCrc32.resize(CRC32_STR_SIZE);

                //?????? Crc32 ?? ??????
                _m_bRes = sfFileIn.bSetPosition(cusStamp.size(), CxStdioFile::ppBegin);
                /*DEBUF*/xASSERT_RET(FALSE != _m_bRes, FALSE);

                size_t uiReadedSize = sfFileIn.uiRead(&usCrc32.at(0), usCrc32.size());
                /*DEBUF*/xASSERT_RET(usCrc32.size() == uiReadedSize, FALSE);

                usCrc32FromStamp = usCrc32;

                //?????? ?????, ??????? ? ????? ??????
                _m_bRes = sfFileIn.bSetPosition(cusStamp.size() + CRC32_STR_SIZE, CxStdioFile::ppBegin);
                /*DEBUF*/xASSERT_RET(FALSE != _m_bRes, FALSE);
            }
            break;

        default: {
                /*DEBUF*/xASSERT_RET(FALSE, FALSE);
            }
            break;
    }

    //-------------------------------------
    //?????????? / ???????????? ???????? ?????
    std::ustring usIn;
    usIn.resize(BUFF_SIZE);

    std::ustring usOut;
    usOut.resize(BUFF_SIZE);

    for ( ; ; ) {
        INT iNum = 0;

        size_t uiInSize = sfFileIn.uiRead(&usIn.at(0), usIn.size());
        xCHECK_DO(uiInSize <= 0, break);

        _m_bRes = bEncryptCfb64(&usIn.at(0), &usOut.at(0), usIn.size(), &iNum, cmCryptMode);
        /*DEBUF*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        size_t uiOutSize = sfFileOut.uiWrite(&usOut.at(0), uiInSize);
        /*DEBUF*/xASSERT_RET(uiInSize == uiOutSize, FALSE);
    }

    _m_bRes = sfFileIn.bClose();
    /*DEBUF*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bRes = sfFileOut.bClose();
    /*DEBUF*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //???? ?????????? - ???????? Crc32 ??????????????? ?????
    if (cmDecrypt == cmCryptMode) {
        std::tstring sCrc32FileOut = CxCrc32::sFormatHex( CxCrc32::ulCalcFileFast(csFilePathOut) );

        xCHECK_RET(usCrc32FromStamp != xS2US(sCrc32FileOut), FALSE);
    }

    //-------------------------------------
    //??????????? File.txt.tmp -> File.txt
    _m_bRes = CxStdioFile::bWipe(csFilePathIn, 1);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //????????? ?????????? ??? ???. ?????
    switch (cmCryptMode) {
        case CxBlowfish::cmEncrypt: {
                _m_bRes = CxStdioFile::bRename(csFilePathOut, csFilePathIn + CxConst::xDOT + g_csCryptFileExt);
                /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
            }
            break;

        case CxBlowfish::cmDecrypt: {
                _m_bRes = CxStdioFile::bRename(csFilePathOut, CxPath::sRemoveExtIf(csFilePathIn, g_csCryptFileExt));
                /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
            }
            break;

        default: {
                /*DEBUG*/xASSERT_RET(FALSE, FALSE);
            }
            break;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: cmGetFileCryptStatus (????? ?????????)
CxBlowfish::ECryptMode
CxBlowfish::cmGetFileCryptStatus(
    const std::tstring &csFilePath, 
    const std::ustring &cusStamp
)
{
    /*DEBUG*/

    ECryptMode cmRes = cmUnknown;
    std::ustring    usStamp;
    size_t     uiReadedSize = 0;
    LONG       liFileSize   = - 1;

    //-------------------------------------
    //CHECK

    //???? ?? ??????????
    xCHECK_RET(FALSE == CxStdioFile::bIsExists(csFilePath), CxBlowfish::cmUnknown);

    liFileSize = CxStdioFile::liGetSize(csFilePath);

    //???? ????
    ////--xCHECK_RET(0 == liFileSize, CxBlowfish::cmNotNeed);
    xCHECK_RET(0 == liFileSize, CxBlowfish::cmDecrypt);

    //?????? ????? ??????, ????? ??????? ??????, ???? ?????? - ???????
    xCHECK_RET(cusStamp.size() >= (size_t)liFileSize, CxBlowfish::cmDecrypt);

    //-------------------------------------
    //?????? ?????? N ??????
    CxStdioFile sfFile;

    _m_bRes = sfFile.bOpen(csFilePath, CxStdioFile::omBinRead, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, CxBlowfish::cmUnknown);

    //???????? ?????? ??? ?????
    usStamp.resize(cusStamp.size());
    /*DEBUG*/xASSERT_RET(usStamp.size() == cusStamp.size(), CxBlowfish::cmUnknown);

    //??????????? ???? ? ?????
    uiReadedSize = sfFile.uiRead(&usStamp.at(0), usStamp.size());
    /*DEBUG*/xASSERT_RET(usStamp.size() == uiReadedSize, CxBlowfish::cmUnknown);

    //?????????? cusStamp ? ??????? ???????
    if (cusStamp == usStamp) {
        cmRes = CxBlowfish::cmEncrypt;
    } else {
        cmRes = CxBlowfish::cmDecrypt;
    }

    return cmRes;
}
//---------------------------------------------------------------------------

