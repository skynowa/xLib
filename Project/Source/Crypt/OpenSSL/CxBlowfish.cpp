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
    uchar_t   *pucKey,
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
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bSetKey(
    const std::tstring_t &csKey
)
{
    /*DEBUG*/xASSERT_RET(false        == csKey.empty(),                                     false);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= csKey.size() * sizeof(std::tstring_t::value_type), false);

    bool bRes = bSetKey(std::ustring_t(csKey.begin(), csKey.end()));
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bSetFileKey(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

    size_t         uiRes = 0;
    std::ustring_t usFile;
    CxFile         sfFile;

    bool bRes = sfFile.bCreate(csFilePath, CxFile::omBinRead, true);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    longlong_t llFileSize = sfFile.llGetSize();
    /*DEBUG*/xASSERT_RET(0LL          <  llFileSize, false);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= llFileSize, false);

    usFile.resize( static_cast<size_t>( llFileSize ) );

    uiRes = sfFile.uiRead(&usFile.at(0), usFile.size());
    /*DEBUG*/xASSERT_RET(usFile.size() == uiRes, false);

    bRes = bSetKey(usFile);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

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
    uchar_t          *pucIn,
    uchar_t          *pucOut,
    const long_t      cliInSize,
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
    const ECryptMode      cmMode
)
{
    /*DEBUG*/xASSERT_RET(false == cusIn.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pusOut,        false);

    int iNum = 0;    //This integer must be initialized to zero when ivec is initialized

    (*pusOut).resize( cusIn.size() );

    bool bRes = bEncryptCfb64(const_cast<uchar_t *>( &cusIn.at(0) ), &(*pusOut).at(0), cusIn.size(), &iNum, cmMode);
    /*DEBUG*/xASSERT_RET(true == bRes, false);
    /*DEBUG*/xASSERT_RET(- 1  <  iNum, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bEncryptFileCfb64(
    const std::tstring_t &csFilePathIn,
    const std::tstring_t &csFilePathOut,
    const ECryptMode      cmMode
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePathIn.empty(),  false);
    /*DEBUG*/xASSERT_RET(false == csFilePathOut.empty(), false);

    bool           bRes = false;
    std::ustring_t usIn;
    std::ustring_t usOut;

    {
        CxFile sfFileIn;

        bRes = sfFileIn.bCreate(csFilePathIn, CxFile::omBinRead, true);
        /*DEBUG*/xASSERT_RET(true == bRes, false);

        bRes = sfFileIn.bRead(&usIn);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }

    bRes = bEncryptCfb64(usIn, &usOut, cmMode);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    {
        CxFile sfFileOut;

        bRes = sfFileOut.bCreate(csFilePathOut, CxFile::omBinCreateReadWrite, true);
        /*DEBUG*/xASSERT_RET(true == bRes, false);

        bRes = sfFileOut.bWrite(usOut);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
