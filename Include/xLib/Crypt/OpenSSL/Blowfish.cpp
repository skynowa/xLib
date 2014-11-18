/**
 * \file  Blowfish.inl
 * \brief blowfish (openssl)
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Blowfish.h"
#endif

#if xHAVE_OPENSSL_CRYPTO

#include <xLib/Core/Utils.h>
#include <xLib/IO/File.h>
#include <xLib/IO/Path.h>
#include <xLib/Crypt/Crc32.h>

#if xENV_WIN
    #if xCOMPILER_MS
        #pragma comment(lib, "libeay32.lib")
    #else
        // -lssl
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
xINLINE
Blowfish::Blowfish()
{
    clearKey();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Blowfish::~Blowfish()
{
    // for security
    clearKey();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Blowfish::setKey(
    uchar_t *a_key,
    cint_t  &a_keySize
)
{
    xTEST_PTR(a_key);
    xTEST_GR_EQ(static_cast<int_t>( keySizeMax() ), a_keySize);
    xTEST_LESS(0, a_keySize);

    (void_t)::BF_set_key(&_key, a_keySize, a_key);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Blowfish::setKey(
    std::custring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_GR_EQ(keySizeMax(), a_key.size());

    setKey(const_cast<uchar_t *>( a_key.data() ), static_cast<int_t>( a_key.size() ));
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Blowfish::setKey(
    std::ctstring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_GR_EQ(keySizeMax(), a_key.size() * sizeof(std::tstring_t::value_type));

    setKey(std::ustring_t(a_key.begin(), a_key.end()));
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Blowfish::setFileKey(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(), false);

    std::ustring_t fileKey;

    File file;
    file.create(a_filePath, File::omBinRead);
    xTEST_EQ(file.isEmpty(), false);
    xTEST_LESS_EQ(file.size(), static_cast<longlong_t>( keySizeMax() ));

    file.read(&fileKey);
    setKey(fileKey);

    // for security
    std::fill(fileKey.begin(), fileKey.end(), 0);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Blowfish::clearKey()
{
    xSTRUCT_ZERO(_key);
    xARRAY_ZERO(_ivec);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE size_t
Blowfish::keySizeMax()
{
    xTEST_STATIC(CHAR_BIT == 8);

    // max key size 448 bit = 56 byte
    return 448 / CHAR_BIT;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: cfb64
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Blowfish::encryptCfb64(
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
xINLINE void_t
Blowfish::encryptCfb64(
    std::custring_t   &a_in,
    std::ustring_t    *a_out,
    const ExCryptMode &a_mode
)
{
    xTEST_EQ(a_in.empty(), false);
    xTEST_PTR(a_out);

    a_out->resize( a_in.size() );

    int_t num = 0;  // this integer must be initialized to zero when ivec is initialized

    encryptCfb64(const_cast<uchar_t *>( &a_in.at(0) ), &a_out->at(0),
        static_cast<long_t>( a_in.size() ), &num, a_mode);
    xTEST_LESS(- 1, num);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Blowfish::encryptFileCfb64(
    std::ctstring_t   &a_filePathIn,
    std::ctstring_t   &a_filePathOut,
    const ExCryptMode &a_mode
)
{
    xTEST_EQ(a_filePathIn.empty(), false);
    xTEST_EQ(a_filePathOut.empty(), false);

    std::ustring_t in;
    {
        File fileIn;
        fileIn.create(a_filePathIn, File::omBinRead);
        fileIn.read(&in);
    }

    std::ustring_t out;
    encryptCfb64(in, &out, a_mode);

    {
        File fileOut;
        fileOut.create(a_filePathOut, File::omBinCreateReadWrite);
        fileOut.write(out);
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, crypt)

#endif // xHAVE_OPENSSL_CRYPTO
