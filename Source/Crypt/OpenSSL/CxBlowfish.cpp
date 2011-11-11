/**
 * \file  CxBlowfish.cpp
 * \brief blowfish (openssl-1.0.0a)
 */


#include <xLib/Crypt/OpenSSL/CxBlowfish.h>

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Debug/CxProfiler.h>
#include <xLib/Crypt/CxCrc32.h>

#if defined(xOS_ENV_WIN)
    #if defined(xCOMPILER_MS)
        #pragma comment(lib, "libeay32.lib")
    #endif
#elif defined(xOS_ENV_UNIX)
    // -lssl
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxBlowfish::CxBlowfish() {
    xSTRUCT_ZERO(_m_bfKey);
    xBUFF_ZERO(_m_ucIvec);
}
//---------------------------------------------------------------------------
/*virtual*/
CxBlowfish::~CxBlowfish() {
    /*SECURE*/xSTRUCT_ZERO(_m_bfKey);
    /*SECURE*/xBUFF_ZERO(_m_ucIvec);
}
//---------------------------------------------------------------------------
BOOL
CxBlowfish::bSetKey(
    UCHAR     *pucKey,
    const int  ciKeySize
)
{
    /*DEBUG*/xASSERT_RET(NULL         != pucKey,    FALSE);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= ciKeySize, FALSE);
    /*DEBUG*/xASSERT_RET(0            <  ciKeySize, FALSE);

    (void)BF_set_key(&_m_bfKey, ciKeySize, pucKey);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxBlowfish::bSetKey(
    const std::ustring &cusKey
)
{
    /*DEBUG*/xASSERT_RET(false        == cusKey.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= cusKey.size(),  FALSE);

    BOOL bRes = bSetKey(const_cast<UCHAR *>( cusKey.data() ), cusKey.size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxBlowfish::bSetKey(
    const std::string_t &csKey
)
{
    /*DEBUG*/xASSERT_RET(false        == csKey.empty(),                                   FALSE);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= csKey.size() * sizeof(std::string_t::value_type), FALSE);

    BOOL bRes = bSetKey(std::ustring(csKey.begin(), csKey.end()));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxBlowfish::bSetFileKey(
    const std::string_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    size_t       uiRes = 0;
    std::ustring usFile;
    CxFile       sfFile;

    BOOL bRes = sfFile.bCreate(csFilePath, CxFile::omBinRead, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    LONG liFileSize = sfFile.liGetSize();
    /*DEBUG*/xASSERT_RET(0L           <  liFileSize, FALSE);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= liFileSize, FALSE);

    usFile.resize(liFileSize);

    uiRes = sfFile.uiRead(&usFile.at(0), usFile.size());
    /*DEBUG*/xASSERT_RET(usFile.size() == uiRes, FALSE);

    bRes = bSetKey(usFile);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    /*SECURE*/usFile.clear();

    return TRUE;
}
//---------------------------------------------------------------------------
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
BOOL
CxBlowfish::bEncryptCfb64(
    UCHAR            *pucIn,
    UCHAR            *pucOut,
    const LONG        cliInSize,
    int              *piNum,
    const ECryptMode  cmMode
)
{
    /*DEBUG*/xASSERT_RET(NULL != pucIn,     FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pucIn,     FALSE);
    /*DEBUG*/xASSERT_RET(- 1L <  cliInSize, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != piNum,     FALSE);

    xBUFF_ZERO(_m_ucIvec);

    (void)BF_cfb64_encrypt(pucIn, pucOut, cliInSize, &_m_bfKey, _m_ucIvec, piNum, cmMode);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxBlowfish::bEncryptCfb64(
    const std::ustring &cusIn,
    std::ustring       *pusOut,
    const ECryptMode    cmMode
)
{
    /*DEBUG*/xASSERT_RET(false == cusIn.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pusOut,        FALSE);

    int iNum = 0;    //This integer must be initialized to zero when ivec is initialized

    (*pusOut).resize( cusIn.size() );

    BOOL bRes = bEncryptCfb64(const_cast<UCHAR *>( &cusIn.at(0) ), &(*pusOut).at(0), cusIn.size(), &iNum, cmMode);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    /*DEBUG*/xASSERT_RET(- 1   <  iNum, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxBlowfish::bEncryptFileCfb64(
    const std::string_t &csFilePathIn,
    const std::string_t &csFilePathOut,
    const ECryptMode    cmMode
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePathIn.empty(),  FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePathOut.empty(), FALSE);

    BOOL         bRes = FALSE;
    std::ustring usIn;
    std::ustring usOut;

    {
        CxFile sfFileIn;

        bRes = sfFileIn.bCreate(csFilePathIn, CxFile::omBinRead, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        bRes = sfFileIn.bRead(&usIn);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    bRes = bEncryptCfb64(usIn, &usOut, cmMode);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    {
        CxFile sfFileOut;

        bRes = sfFileOut.bCreate(csFilePathOut, CxFile::omBinCreateReadWrite, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        bRes = sfFileOut.bWrite(usOut);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxBlowfish::bEncryptFileCfb64(
    const std::string_t &csFilePathIn,
    const std::string_t &csFilePathOut,
    const std::ustring &cusStamp,
    const ECryptMode    cmCryptMode
)
{
    /*DEBUG*/

    const size_t cuiCrc32StrSize = 8;
    const size_t cuiBuffSize     = 1024;

    //-------------------------------------
    //
    ECryptMode cmFileCryptStatus = cmGetFileCryptStatus(csFilePathIn, cusStamp);
    xCHECK_RET(cmEncrypt == cmCryptMode && cmEncrypt == cmFileCryptStatus, TRUE);
    xCHECK_RET(cmDecrypt == cmCryptMode && cmDecrypt == cmFileCryptStatus, TRUE);

    const std::string_t csCryptFileExt = xT("enc");
    const std::string_t csTempFileExt  = xT("tmp");
    std::ustring       usCrc32FromStamp;

    //-------------------------------------
    //
    CxFile sfFileIn;
    CxFile sfFileOut;

    BOOL bRes = sfFileIn.bCreate(csFilePathIn,   CxFile::omBinRead, TRUE);
    /*DEBUF*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = sfFileOut.bCreate(csFilePathOut, CxFile::omBinWrite, TRUE);
    /*DEBUF*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //
    switch (cmCryptMode) {
        case cmEncrypt: {
                std::ustring usStampCrc32;

                ULONG   ulCrc32 = CxCrc32::ulCalcFileFast(csFilePathIn);
                std::string_t sCrc32 = CxCrc32::sFormatHex(ulCrc32);

                usStampCrc32 = cusStamp + xS2US(sCrc32);
                /*DEBUG*/xASSERT_RET(cusStamp.size() + cuiCrc32StrSize == usStampCrc32.size(), FALSE);

                size_t uiWrited = sfFileOut.uiWrite((void *)&usStampCrc32.at(0), usStampCrc32.size());
                /*DEBUF*/xASSERT_RET(uiWrited == usStampCrc32.size(), FALSE);
            }
            break;

        case cmDecrypt: {
                std::ustring usCrc32;

                usCrc32.resize(cuiCrc32StrSize);

                bRes = sfFileIn.bSetPosition(cusStamp.size(), CxFile::ppBegin);
                /*DEBUF*/xASSERT_RET(FALSE != bRes, FALSE);

                size_t uiReadedSize = sfFileIn.uiRead(&usCrc32.at(0), usCrc32.size());
                /*DEBUF*/xASSERT_RET(usCrc32.size() == uiReadedSize, FALSE);

                usCrc32FromStamp = usCrc32;

                bRes = sfFileIn.bSetPosition(cusStamp.size() + cuiCrc32StrSize, CxFile::ppBegin);
                /*DEBUF*/xASSERT_RET(FALSE != bRes, FALSE);
            }
            break;

        default: {
                /*DEBUF*/xASSERT_RET(FALSE, FALSE);
            }
            break;
    }

    //-------------------------------------
    //
    std::ustring usIn;
    usIn.resize(cuiBuffSize);

    std::ustring usOut;
    usOut.resize(cuiBuffSize);

    for ( ; ; ) {
        int iNum = 0;

        size_t uiInSize = sfFileIn.uiRead(&usIn.at(0), usIn.size());
        xCHECK_DO(uiInSize <= 0, break);

        bRes = bEncryptCfb64(&usIn.at(0), &usOut.at(0), usIn.size(), &iNum, cmCryptMode);
        /*DEBUF*/xASSERT_RET(FALSE != bRes, FALSE);

        size_t uiOutSize = sfFileOut.uiWrite(&usOut.at(0), uiInSize);
        /*DEBUF*/xASSERT_RET(uiInSize == uiOutSize, FALSE);
    }

    bRes = sfFileIn.bClose();
    /*DEBUF*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = sfFileOut.bClose();
    /*DEBUF*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //
    if (cmDecrypt == cmCryptMode) {
        std::string_t sCrc32FileOut = CxCrc32::sFormatHex( CxCrc32::ulCalcFileFast(csFilePathOut) );

        xCHECK_RET(usCrc32FromStamp != xS2US(sCrc32FileOut), FALSE);
    }

    //-------------------------------------
    //File.txt.tmp -> File.txt
    bRes = CxFile::bWipe(csFilePathIn, 1);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //
    switch (cmCryptMode) {
        case CxBlowfish::cmEncrypt: {
                bRes = CxFile::bRename(csFilePathOut, csFilePathIn + CxConst::xDOT + csCryptFileExt);
                /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
            }
            break;

        case CxBlowfish::cmDecrypt: {
                bRes = CxFile::bRename(csFilePathOut, CxPath::sRemoveExtIf(csFilePathIn, csCryptFileExt));
                /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
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
CxBlowfish::ECryptMode
CxBlowfish::cmGetFileCryptStatus(
    const std::string_t &csFilePath,
    const std::ustring &cusStamp
)
{
    /*DEBUG*/

    ECryptMode   cmRes        = cmUnknown;
    std::ustring usStamp;
    size_t       uiReadedSize = 0;
    LONG         liFileSize   = (ULONG)- 1;

    //-------------------------------------
    //CHECK
    xCHECK_RET(FALSE == CxFile::bIsExists(csFilePath), CxBlowfish::cmUnknown);

    liFileSize = CxFile::liGetSize(csFilePath);

    xCHECK_RET(0L == liFileSize,                                     CxBlowfish::cmDecrypt);
    xCHECK_RET(cusStamp.size() >= static_cast<size_t>( liFileSize ), CxBlowfish::cmDecrypt);

    //-------------------------------------
    //
    CxFile sfFile;

    BOOL bRes = sfFile.bCreate(csFilePath, CxFile::omBinRead, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, CxBlowfish::cmUnknown);

    usStamp.resize(cusStamp.size());
    /*DEBUG*/xASSERT_RET(usStamp.size() == cusStamp.size(), CxBlowfish::cmUnknown);

    uiReadedSize = sfFile.uiRead(&usStamp.at(0), usStamp.size());
    /*DEBUG*/xASSERT_RET(usStamp.size() == uiReadedSize, CxBlowfish::cmUnknown);

    if (cusStamp == usStamp) {
        cmRes = CxBlowfish::cmEncrypt;
    } else {
        cmRes = CxBlowfish::cmDecrypt;
    }

    return cmRes;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
