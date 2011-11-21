/**
 * \file  CxBlowfish.cpp
 * \brief blowfish (openssl-1.0.0a)
 */


#include <xLib/Crypt/OpenSSL/CxBlowfish.h>

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Debug/CxProfiler.h>
#include <xLib/Crypt/CxCrc32.h>

#if xOS_ENV_WIN
    #if xCOMPILER_MS
        #pragma comment(lib, "libeay32.lib")
    #endif
#elif xOS_ENV_UNIX
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
bool
CxBlowfish::bSetKey(
    uchar_t     *pucKey,
    const int  ciKeySize
)
{
    /*DEBUG*/xASSERT_RET(NULL         != pucKey,    false);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= ciKeySize, false);
    /*DEBUG*/xASSERT_RET(0            <  ciKeySize, false);

    (void)::BF_set_key(&_m_bfKey, ciKeySize, pucKey);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bSetKey(
    const std::ustring_t &cusKey
)
{
    /*DEBUG*/xASSERT_RET(false        == cusKey.empty(), false);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= cusKey.size(),  false);

    bool bRes = bSetKey(const_cast<uchar_t *>( cusKey.data() ), cusKey.size());
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bSetKey(
    const std::tstring_t &csKey
)
{
    /*DEBUG*/xASSERT_RET(false        == csKey.empty(),                                   false);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= csKey.size() * sizeof(std::tstring_t::value_type), false);

    bool bRes = bSetKey(std::ustring_t(csKey.begin(), csKey.end()));
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bSetFileKey(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

    size_t       uiRes = 0;
    std::ustring_t usFile;
    CxFile       sfFile;

    bool bRes = sfFile.bCreate(csFilePath, CxFile::omBinRead, true);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    long_t liFileSize = sfFile.liGetSize();
    /*DEBUG*/xASSERT_RET(0L           <  liFileSize, false);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= liFileSize, false);

    usFile.resize(liFileSize);

    uiRes = sfFile.uiRead(&usFile.at(0), usFile.size());
    /*DEBUG*/xASSERT_RET(usFile.size() == uiRes, false);

    bRes = bSetKey(usFile);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    /*SECURE*/usFile.clear();

    return true;
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
bool
CxBlowfish::bEncryptCfb64(
    uchar_t            *pucIn,
    uchar_t            *pucOut,
    const long_t        cliInSize,
    int              *piNum,
    const ECryptMode  cmMode
)
{
    /*DEBUG*/xASSERT_RET(NULL != pucIn,     false);
    /*DEBUG*/xASSERT_RET(NULL != pucIn,     false);
    /*DEBUG*/xASSERT_RET(- 1L <  cliInSize, false);
    /*DEBUG*/xASSERT_RET(NULL != piNum,     false);

    xBUFF_ZERO(_m_ucIvec);

    (void)::BF_cfb64_encrypt(pucIn, pucOut, cliInSize, &_m_bfKey, _m_ucIvec, piNum, cmMode);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bEncryptCfb64(
    const std::ustring_t &cusIn,
    std::ustring_t       *pusOut,
    const ECryptMode    cmMode
)
{
    /*DEBUG*/xASSERT_RET(false == cusIn.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pusOut,        false);

    int iNum = 0;    //This integer must be initialized to zero when ivec is initialized

    (*pusOut).resize( cusIn.size() );

    bool bRes = bEncryptCfb64(const_cast<uchar_t *>( &cusIn.at(0) ), &(*pusOut).at(0), cusIn.size(), &iNum, cmMode);
    /*DEBUG*/xASSERT_RET(false != bRes, false);
    /*DEBUG*/xASSERT_RET(- 1   <  iNum, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bEncryptFileCfb64(
    const std::tstring_t &csFilePathIn,
    const std::tstring_t &csFilePathOut,
    const ECryptMode    cmMode
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePathIn.empty(),  false);
    /*DEBUG*/xASSERT_RET(false == csFilePathOut.empty(), false);

    bool         bRes = false;
    std::ustring_t usIn;
    std::ustring_t usOut;

    {
        CxFile sfFileIn;

        bRes = sfFileIn.bCreate(csFilePathIn, CxFile::omBinRead, true);
        /*DEBUG*/xASSERT_RET(false != bRes, false);

        bRes = sfFileIn.bRead(&usIn);
        /*DEBUG*/xASSERT_RET(false != bRes, false);
    }

    bRes = bEncryptCfb64(usIn, &usOut, cmMode);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    {
        CxFile sfFileOut;

        bRes = sfFileOut.bCreate(csFilePathOut, CxFile::omBinCreateReadWrite, true);
        /*DEBUG*/xASSERT_RET(false != bRes, false);

        bRes = sfFileOut.bWrite(usOut);
        /*DEBUG*/xASSERT_RET(false != bRes, false);
    }

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxBlowfish::bEncryptFileCfb64(
    const std::tstring_t &csFilePathIn,
    const std::tstring_t &csFilePathOut,
    const std::ustring_t &cusStamp,
    const ECryptMode    cmCryptMode
)
{
    /*DEBUG*/

    const size_t cuiCrc32StrSize = 8;
    const size_t cuiBuffSize     = 1024;

    //-------------------------------------
    //
    ECryptMode cmFileCryptStatus = cmGetFileCryptStatus(csFilePathIn, cusStamp);
    xCHECK_RET(cmEncrypt == cmCryptMode && cmEncrypt == cmFileCryptStatus, true);
    xCHECK_RET(cmDecrypt == cmCryptMode && cmDecrypt == cmFileCryptStatus, true);

    const std::tstring_t csCryptFileExt = xT("enc");
    const std::tstring_t csTempFileExt  = xT("tmp");
    std::ustring_t       usCrc32FromStamp;

    //-------------------------------------
    //
    CxFile sfFileIn;
    CxFile sfFileOut;

    bool bRes = sfFileIn.bCreate(csFilePathIn,   CxFile::omBinRead, true);
    /*DEBUF*/xASSERT_RET(false != bRes, false);

    bRes = sfFileOut.bCreate(csFilePathOut, CxFile::omBinWrite, true);
    /*DEBUF*/xASSERT_RET(false != bRes, false);

    //-------------------------------------
    //
    switch (cmCryptMode) {
        case cmEncrypt: {
                std::ustring_t usStampCrc32;

                ulong_t   ulCrc32 = CxCrc32::ulCalcFileFast(csFilePathIn);
                std::tstring_t sCrc32 = CxCrc32::sFormatHex(ulCrc32);

                usStampCrc32 = cusStamp + xS2US(sCrc32);
                /*DEBUG*/xASSERT_RET(cusStamp.size() + cuiCrc32StrSize == usStampCrc32.size(), false);

                size_t uiWrited = sfFileOut.uiWrite((void *)&usStampCrc32.at(0), usStampCrc32.size());
                /*DEBUF*/xASSERT_RET(uiWrited == usStampCrc32.size(), false);
            }
            break;

        case cmDecrypt: {
                std::ustring_t usCrc32;

                usCrc32.resize(cuiCrc32StrSize);

                bRes = sfFileIn.bSetPosition(cusStamp.size(), CxFile::ppBegin);
                /*DEBUF*/xASSERT_RET(false != bRes, false);

                size_t uiReadedSize = sfFileIn.uiRead(&usCrc32.at(0), usCrc32.size());
                /*DEBUF*/xASSERT_RET(usCrc32.size() == uiReadedSize, false);

                usCrc32FromStamp = usCrc32;

                bRes = sfFileIn.bSetPosition(cusStamp.size() + cuiCrc32StrSize, CxFile::ppBegin);
                /*DEBUF*/xASSERT_RET(false != bRes, false);
            }
            break;

        default: {
                /*DEBUF*/xASSERT_RET(false, false);
            }
            break;
    }

    //-------------------------------------
    //
    std::ustring_t usIn;
    usIn.resize(cuiBuffSize);

    std::ustring_t usOut;
    usOut.resize(cuiBuffSize);

    for ( ; ; ) {
        int iNum = 0;

        size_t uiInSize = sfFileIn.uiRead(&usIn.at(0), usIn.size());
        xCHECK_DO(uiInSize <= 0, break);

        bRes = bEncryptCfb64(&usIn.at(0), &usOut.at(0), usIn.size(), &iNum, cmCryptMode);
        /*DEBUF*/xASSERT_RET(false != bRes, false);

        size_t uiOutSize = sfFileOut.uiWrite(&usOut.at(0), uiInSize);
        /*DEBUF*/xASSERT_RET(uiInSize == uiOutSize, false);
    }

    bRes = sfFileIn.bClose();
    /*DEBUF*/xASSERT_RET(false != bRes, false);

    bRes = sfFileOut.bClose();
    /*DEBUF*/xASSERT_RET(false != bRes, false);

    //-------------------------------------
    //
    if (cmDecrypt == cmCryptMode) {
        std::tstring_t sCrc32FileOut = CxCrc32::sFormatHex( CxCrc32::ulCalcFileFast(csFilePathOut) );

        xCHECK_RET(usCrc32FromStamp != xS2US(sCrc32FileOut), false);
    }

    //-------------------------------------
    //File.txt.tmp -> File.txt
    bRes = CxFile::bWipe(csFilePathIn, 1);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    //-------------------------------------
    //
    switch (cmCryptMode) {
        case CxBlowfish::cmEncrypt: {
                bRes = CxFile::bRename(csFilePathOut, csFilePathIn + CxConst::xDOT + csCryptFileExt);
                /*DEBUG*/xASSERT_RET(false != bRes, false);
            }
            break;

        case CxBlowfish::cmDecrypt: {
                bRes = CxFile::bRename(csFilePathOut, CxPath::sRemoveExtIf(csFilePathIn, csCryptFileExt));
                /*DEBUG*/xASSERT_RET(false != bRes, false);
            }
            break;

        default: {
                /*DEBUG*/xASSERT_RET(false, false);
            }
            break;
    }

    return true;
}
//---------------------------------------------------------------------------
CxBlowfish::ECryptMode
CxBlowfish::cmGetFileCryptStatus(
    const std::tstring_t &csFilePath,
    const std::ustring_t &cusStamp
)
{
    /*DEBUG*/

    ECryptMode   cmRes        = cmUnknown;
    std::ustring_t usStamp;
    size_t       uiReadedSize = 0;
    long_t         liFileSize   = (ulong_t)- 1;

    //-------------------------------------
    //CHECK
    xCHECK_RET(false == CxFile::bIsExists(csFilePath), CxBlowfish::cmUnknown);

    liFileSize = CxFile::liGetSize(csFilePath);

    xCHECK_RET(0L == liFileSize,                                     CxBlowfish::cmDecrypt);
    xCHECK_RET(cusStamp.size() >= static_cast<size_t>( liFileSize ), CxBlowfish::cmDecrypt);

    //-------------------------------------
    //
    CxFile sfFile;

    bool bRes = sfFile.bCreate(csFilePath, CxFile::omBinRead, true);
    /*DEBUG*/xASSERT_RET(false != bRes, CxBlowfish::cmUnknown);

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
