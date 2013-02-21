/**
 * \file  CxBlowfish.cpp
 * \brief blowfish (openssl-1.0.0a)
 */


#include <xLib/Crypt/OpenSSL/CxBlowfish.h>

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Debug/CxProfiler.h>
#include <xLib/Crypt/CxCrc32.h>

#if   xOS_ENV_WIN
    #if xCOMPILER_MS
        #pragma comment(lib, "libeay32.lib")
    #endif
#elif xOS_ENV_UNIX
    // -lssl
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxBlowfish::CxBlowfish() {
    xSTRUCT_ZERO(_m_bfKey);
    xARRAY_ZERO(_m_ucIvec);
}
//------------------------------------------------------------------------------
/* virtual */
CxBlowfish::~CxBlowfish() {
    /*SECURE*/xSTRUCT_ZERO(_m_bfKey);
    /*SECURE*/xARRAY_ZERO(_m_ucIvec);
}
//------------------------------------------------------------------------------
void
CxBlowfish::setKey(
    uchar_t   *a_pucKey,
    const int &a_ciKeySize
)
{
    xTEST_PTR(a_pucKey);
    xTEST_GR_EQ(static_cast<int>( MAX_KEY_SIZE ), a_ciKeySize);
    xTEST_LESS(0, a_ciKeySize);

    (void)::BF_set_key(&_m_bfKey, a_ciKeySize, a_pucKey);
}
//------------------------------------------------------------------------------
void
CxBlowfish::setKey(
    const std::ustring_t &a_cusKey
)
{
    xTEST_EQ(false, a_cusKey.empty());
    xTEST_GR_EQ(static_cast<size_t>( MAX_KEY_SIZE ), a_cusKey.size());

    setKey(const_cast<uchar_t *>( a_cusKey.data() ), static_cast<int>( a_cusKey.size() ));
}
//------------------------------------------------------------------------------
void
CxBlowfish::setKey(
    const std::tstring_t &a_csKey
)
{
    xTEST_EQ(false, a_csKey.empty());
    xTEST_GR_EQ(static_cast<size_t>( MAX_KEY_SIZE ), a_csKey.size() * sizeof(std::tstring_t::value_type));

    setKey(std::ustring_t(a_csKey.begin(), a_csKey.end()));
}
//------------------------------------------------------------------------------
void
CxBlowfish::setFileKey(
    const std::tstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());

    size_t         uiRes = 0;
    std::ustring_t usFile;
    CxFile         sfFile;

    sfFile.create(a_csFilePath, CxFile::omBinRead, true);

    longlong_t llFileSize = sfFile.size();
    xTEST_LESS(0LL, llFileSize);
    xTEST_GR_EQ(static_cast<longlong_t>( MAX_KEY_SIZE ) >= llFileSize, false);

    usFile.resize( static_cast<size_t>( llFileSize ) );

    uiRes = sfFile.read(&usFile.at(0), usFile.size());
    xTEST_EQ(usFile.size(), uiRes);

    setKey(usFile);

    // for security
    usFile.clear();
}
//------------------------------------------------------------------------------
/* static */
size_t
CxBlowfish::maxKeySize() {
    return MAX_KEY_SIZE;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: cfb64
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CxBlowfish::encryptCfb64(
    uchar_t           *a_pucIn,
    uchar_t           *a_pucOut,
    const long_t      &a_cliInSize,
    int               *a_piNum,
    const ExCryptMode &a_cmMode
)
{
    xTEST_PTR(a_pucIn);
    xTEST_PTR(a_pucOut);
    xTEST_LESS(- 1L, a_cliInSize);
    xTEST_PTR(a_piNum);

    xARRAY_ZERO(_m_ucIvec);

    (void)::BF_cfb64_encrypt(a_pucIn, a_pucOut, a_cliInSize, &_m_bfKey, _m_ucIvec, a_piNum, a_cmMode);
}
//------------------------------------------------------------------------------
void
CxBlowfish::encryptCfb64(
    const std::ustring_t &a_cusIn,
    std::ustring_t       *a_pusOut,
    const ExCryptMode    &a_cmMode
)
{
    xTEST_EQ(false, a_cusIn.empty());
    xTEST_PTR(a_pusOut);

    int iNum = 0;    //This integer must be initialized to zero when ivec is initialized

    (*a_pusOut).resize( a_cusIn.size() );

    encryptCfb64(
        const_cast<uchar_t *>( &a_cusIn.at(0) ), &(*a_pusOut).at(0),
        static_cast<long_t>( a_cusIn.size() ), &iNum, a_cmMode);
    xTEST_LESS(- 1, iNum);
}
//------------------------------------------------------------------------------
void
CxBlowfish::encryptFileCfb64(
    const std::tstring_t &a_csFilePathIn,
    const std::tstring_t &a_csFilePathOut,
    const ExCryptMode    &a_cmMode
)
{
    xTEST_EQ(false, a_csFilePathIn.empty());
    xTEST_EQ(false, a_csFilePathOut.empty());

    std::ustring_t usIn;
    std::ustring_t usOut;

    {
        CxFile sfFileIn;

        sfFileIn.create(a_csFilePathIn, CxFile::omBinRead, true);
        sfFileIn.read(&usIn);
    }

    encryptCfb64(usIn, &usOut, a_cmMode);

    {
        CxFile sfFileOut;

        sfFileOut.create(a_csFilePathOut, CxFile::omBinCreateReadWrite, true);
        sfFileOut.write(usOut);
    }
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
