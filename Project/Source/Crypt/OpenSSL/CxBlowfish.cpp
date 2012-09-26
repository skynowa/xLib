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
/* virtual */
CxBlowfish::~CxBlowfish() {
    /*SECURE*/xSTRUCT_ZERO(_m_bfKey);
    /*SECURE*/xBUFF_ZERO(_m_ucIvec);
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bSetKey(
    uchar_t   *a_pucKey,
    const int  a_ciKeySize
)
{
    /*DEBUG*/xASSERT_RET(NULL         != a_pucKey,    false);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= a_ciKeySize, false);
    /*DEBUG*/xASSERT_RET(0            <  a_ciKeySize, false);

    (void)::BF_set_key(&_m_bfKey, a_ciKeySize, a_pucKey);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bSetKey(
    const std::ustring_t &a_cusKey
)
{
    /*DEBUG*/xASSERT_RET(false        == a_cusKey.empty(), false);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= a_cusKey.size(),  false);

    bool bRv = bSetKey(const_cast<uchar_t *>( a_cusKey.data() ), a_cusKey.size());
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bSetKey(
    const std::tstring_t &a_csKey
)
{
    /*DEBUG*/xASSERT_RET(false        == a_csKey.empty(),                                     false);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= a_csKey.size() * sizeof(std::tstring_t::value_type), false);

    bool bRv = bSetKey(std::ustring_t(a_csKey.begin(), a_csKey.end()));
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bSetFileKey(
    const std::tstring_t &a_csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == a_csFilePath.empty(), false);

    size_t         uiRes = 0;
    std::ustring_t usFile;
    CxFile         sfFile;

    bool bRv = sfFile.bCreate(a_csFilePath, CxFile::omBinRead, true);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    longlong_t llFileSize = sfFile.llGetSize();
    /*DEBUG*/xASSERT_RET(0LL          <  llFileSize, false);
    /*DEBUG*/xASSERT_RET(MAX_KEY_SIZE >= llFileSize, false);

    usFile.resize( static_cast<size_t>( llFileSize ) );

    uiRes = sfFile.uiRead(&usFile.at(0), usFile.size());
    /*DEBUG*/xASSERT_RET(usFile.size() == uiRes, false);

    bRv = bSetKey(usFile);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    /*SECURE*/usFile.clear();

    return true;
}
//---------------------------------------------------------------------------
/* static */
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
    uchar_t          *a_pucIn,
    uchar_t          *a_pucOut,
    const long_t      a_cliInSize,
    int              *a_piNum,
    const ExCryptMode a_cmMode
)
{
    /*DEBUG*/xASSERT_RET(NULL != a_pucIn,     false);
    /*DEBUG*/xASSERT_RET(NULL != a_pucOut,    false);
    /*DEBUG*/xASSERT_RET(- 1L <  a_cliInSize, false);
    /*DEBUG*/xASSERT_RET(NULL != a_piNum,     false);

    xBUFF_ZERO(_m_ucIvec);

    (void)::BF_cfb64_encrypt(a_pucIn, a_pucOut, a_cliInSize, &_m_bfKey, _m_ucIvec, a_piNum, a_cmMode);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bEncryptCfb64(
    const std::ustring_t &a_cusIn,
    std::ustring_t       *a_pusOut,
    const ExCryptMode     a_cmMode
)
{
    /*DEBUG*/xASSERT_RET(false == a_cusIn.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != a_pusOut,        false);

    int iNum = 0;    //This integer must be initialized to zero when ivec is initialized

    (*a_pusOut).resize( a_cusIn.size() );

    bool bRv = bEncryptCfb64(const_cast<uchar_t *>( &a_cusIn.at(0) ), &(*a_pusOut).at(0), a_cusIn.size(), &iNum, a_cmMode);
    /*DEBUG*/xASSERT_RET(true == bRv, false);
    /*DEBUG*/xASSERT_RET(- 1  <  iNum, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxBlowfish::bEncryptFileCfb64(
    const std::tstring_t &a_csFilePathIn,
    const std::tstring_t &a_csFilePathOut,
    const ExCryptMode     a_cmMode
)
{
    /*DEBUG*/xASSERT_RET(false == a_csFilePathIn.empty(),  false);
    /*DEBUG*/xASSERT_RET(false == a_csFilePathOut.empty(), false);

    bool           bRv = false;
    std::ustring_t usIn;
    std::ustring_t usOut;

    {
        CxFile sfFileIn;

        bRv = sfFileIn.bCreate(a_csFilePathIn, CxFile::omBinRead, true);
        /*DEBUG*/xASSERT_RET(true == bRv, false);

        bRv = sfFileIn.bRead(&usIn);
        /*DEBUG*/xASSERT_RET(true == bRv, false);
    }

    bRv = bEncryptCfb64(usIn, &usOut, a_cmMode);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    {
        CxFile sfFileOut;

        bRv = sfFileOut.bCreate(a_csFilePathOut, CxFile::omBinCreateReadWrite, true);
        /*DEBUG*/xASSERT_RET(true == bRv, false);

        bRv = sfFileOut.bWrite(usOut);
        /*DEBUG*/xASSERT_RET(true == bRv, false);
    }

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
