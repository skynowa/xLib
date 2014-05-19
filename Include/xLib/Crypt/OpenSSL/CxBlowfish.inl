/**
 * \file  CxBlowfish.inl
 * \brief blowfish (openssl)
 */


#if xHAVE_OPENSSL_CRYPTO

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Crypt/CxCrc32.h>

#if xENV_WIN
    #if xCOMPILER_MS
        #pragma comment(lib, "libeay32.lib")
    #endif
#else
    // -lssl
#endif


xNAMESPACE_BEGIN2(xlib, crypt)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxBlowfish::CxBlowfish()
{
    xSTRUCT_ZERO(_key);
    xARRAY_ZERO(_ivec);
}
//-------------------------------------------------------------------------------------------------
inline
/* virtual */
CxBlowfish::~CxBlowfish()
{
    // for security
    xSTRUCT_ZERO(_key);
    xARRAY_ZERO(_ivec);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxBlowfish::setKey(
    uchar_t *a_key,
    cint_t  &a_keySize
)
{
    xTEST_PTR(a_key);
    xTEST_GR_EQ(static_cast<int_t>( maxKeySize() ), a_keySize);
    xTEST_LESS(0, a_keySize);

    (void_t)::BF_set_key(&_key, a_keySize, a_key);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxBlowfish::setKey(
    std::custring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_GR_EQ(maxKeySize(), a_key.size());

    setKey(const_cast<uchar_t *>( a_key.data() ), static_cast<int_t>( a_key.size() ));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxBlowfish::setKey(
    std::ctstring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_GR_EQ(maxKeySize(), a_key.size() * sizeof(std::tstring_t::value_type));

    setKey(std::ustring_t(a_key.begin(), a_key.end()));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxBlowfish::setFileKey(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(), false);

    size_t         uiRv = 0;
    std::ustring_t fileKey;
    CxFile         file;

    file.create(a_filePath, CxFile::omBinRead, true);

    longlong_t fileSize = file.size();
    xTEST_LESS(0LL, fileSize);
    xTEST_GR_EQ(static_cast<longlong_t>( maxKeySize() ) >= fileSize, false);

    fileKey.resize( static_cast<size_t>( fileSize ) );

    uiRv = file.read(&fileKey.at(0), fileKey.size());
    xTEST_EQ(fileKey.size(), uiRv);

    setKey(fileKey);

    // for security
    fileKey.clear();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline size_t
CxBlowfish::maxKeySize()
{
    return MAX_KEY_SIZE;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: cfb64
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
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

    (void_t)::BF_cfb64_encrypt(a_in, a_out, a_inSize, &_key, _ivec, a_num, a_mode);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxBlowfish::encryptCfb64(
    std::custring_t   &a_in,
    std::ustring_t    *a_out,
    const ExCryptMode &a_mode
)
{
    xTEST_EQ(a_in.empty(), false);
    xTEST_PTR(a_out);

    int_t num = 0;    //This integer must be initialized to zero when ivec is initialized

    a_out->resize( a_in.size() );

    encryptCfb64(const_cast<uchar_t *>( &a_in.at(0) ), &a_out->at(0),
        static_cast<long_t>( a_in.size() ), &num, a_mode);
    xTEST_LESS(- 1, num);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxBlowfish::encryptFileCfb64(
    std::ctstring_t   &a_filePathIn,
    std::ctstring_t   &a_filePathOut,
    const ExCryptMode &a_mode
)
{
    xTEST_EQ(a_filePathIn.empty(), false);
    xTEST_EQ(a_filePathOut.empty(), false);

    std::ustring_t in;
    std::ustring_t out;

    {
        CxFile fileIn;

        fileIn.create(a_filePathIn, CxFile::omBinRead, true);
        fileIn.read(&in);
    }

    encryptCfb64(in, &out, a_mode);

    {
        CxFile fileOut;

        fileOut.create(a_filePathOut, CxFile::omBinCreateReadWrite, true);
        fileOut.write(out);
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, crypt)

#endif // xHAVE_OPENSSL_CRYPTO
