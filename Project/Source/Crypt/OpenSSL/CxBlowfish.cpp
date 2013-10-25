/**
 * \file  CxBlowfish.cpp
 * \brief blowfish (openssl-1.0.0a)
 */


#include <xLib/Crypt/OpenSSL/CxBlowfish.h>

#if xOPENSSL_IS_USE

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Debug/CxProfiler.h>
#include <xLib/Crypt/CxCrc32.h>

#if xOS_ENV_WIN
    #if xCOMPILER_MS
        #pragma comment(lib, "libeay32.lib")
    #endif
#else
    // -lssl
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxBlowfish::CxBlowfish()
{
    xSTRUCT_ZERO(_bfKey);
    xARRAY_ZERO(_ivec);
}
//------------------------------------------------------------------------------
xINLINE_HO
/* virtual */
CxBlowfish::~CxBlowfish()
{
    /*SECURE*/xSTRUCT_ZERO(_bfKey);
    /*SECURE*/xARRAY_ZERO(_ivec);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxBlowfish::setKey(
    uchar_t *a_key,
    cint_t  &a_keySize
)
{
    xTEST_PTR(a_key);
    xTEST_GR_EQ(static_cast<int_t>( MAX_KEY_SIZE ), a_keySize);
    xTEST_LESS(0, a_keySize);

    (void_t)::BF_set_key(&_bfKey, a_keySize, a_key);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxBlowfish::setKey(
    std::custring_t &a_key
)
{
    xTEST_EQ(false, a_key.empty());
    xTEST_GR_EQ(static_cast<size_t>( MAX_KEY_SIZE ), a_key.size());

    setKey(const_cast<uchar_t *>( a_key.data() ), static_cast<int_t>( a_key.size() ));
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxBlowfish::setKey(
    std::ctstring_t &a_key
)
{
    xTEST_EQ(false, a_key.empty());
    xTEST_GR_EQ(static_cast<size_t>( MAX_KEY_SIZE ), a_key.size() * sizeof(std::tstring_t::value_type));

    setKey(std::ustring_t(a_key.begin(), a_key.end()));
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxBlowfish::setFileKey(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());

    size_t         uiRes = 0;
    std::ustring_t usFile;
    CxFile         sfFile;

    sfFile.create(a_filePath, CxFile::omBinRead, true);

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
xINLINE_HO size_t
CxBlowfish::maxKeySize()
{
    return MAX_KEY_SIZE;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: cfb64
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxBlowfish::encryptCfb64(
    uchar_t           *a_in,
    uchar_t           *a_out,
    clong_t           &a_inSize,
    int_t             *a_num,
    const ExCryptMode &a_mode
)
{
    xTEST_PTR(a_in);
    xTEST_PTR(a_out);
    xTEST_LESS(- 1L, a_inSize);
    xTEST_PTR(a_num);

    xARRAY_ZERO(_ivec);

    (void_t)::BF_cfb64_encrypt(a_in, a_out, a_inSize, &_bfKey, _ivec, a_num, a_mode);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxBlowfish::encryptCfb64(
    std::custring_t   &a_cusIn,
    std::ustring_t    *a_pusOut,
    const ExCryptMode &a_mode
)
{
    xTEST_EQ(false, a_cusIn.empty());
    xTEST_PTR(a_pusOut);

    int_t iNum = 0;    //This integer must be initialized to zero when ivec is initialized

    (*a_pusOut).resize( a_cusIn.size() );

    encryptCfb64(
        const_cast<uchar_t *>( &a_cusIn.at(0) ), &(*a_pusOut).at(0),
        static_cast<long_t>( a_cusIn.size() ), &iNum, a_mode);
    xTEST_LESS(- 1, iNum);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxBlowfish::encryptFileCfb64(
    std::ctstring_t   &a_filePathIn,
    std::ctstring_t   &a_filePathOut,
    const ExCryptMode &a_mode
)
{
    xTEST_EQ(false, a_filePathIn.empty());
    xTEST_EQ(false, a_filePathOut.empty());

    std::ustring_t usIn;
    std::ustring_t usOut;

    {
        CxFile sfFileIn;

        sfFileIn.create(a_filePathIn, CxFile::omBinRead, true);
        sfFileIn.read(&usIn);
    }

    encryptCfb64(usIn, &usOut, a_mode);

    {
        CxFile sfFileOut;

        sfFileOut.create(a_filePathOut, CxFile::omBinCreateReadWrite, true);
        sfFileOut.write(usOut);
    }
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif // xOPENSSL_IS_USE
