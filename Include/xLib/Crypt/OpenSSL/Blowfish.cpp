/**
 * \file  Blowfish.inl
 * \brief blowfish (openssl)
 */


#include "Blowfish.h"

#if cmOPENSSL_CRYPTO_FOUND

#include <xLib/Core/Utils.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/Path.h>
#include <xLib/Crypt/Crc32.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>


xNAMESPACE_BEGIN2(xl, crypt)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Blowfish::Blowfish()
{
    clearKey();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Blowfish::~Blowfish()
{
    // for security
    clearKey();
}
//-------------------------------------------------------------------------------------------------
void_t
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
void_t
Blowfish::setKey(
    std::custring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_GR_EQ(keySizeMax(), a_key.size());

    setKey(const_cast<uchar_t *>( a_key.data() ), static_cast<int_t>( a_key.size() ));
}
//-------------------------------------------------------------------------------------------------
void_t
Blowfish::setKey(
    std::ctstring_t &a_key
)
{
    xTEST_EQ(a_key.empty(), false);
    xTEST_GR_EQ(keySizeMax(), a_key.size() * sizeof(std::tstring_t::value_type));

    setKey(std::ustring_t(a_key.begin(), a_key.end()));
}
//-------------------------------------------------------------------------------------------------
void_t
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
void_t
Blowfish::clearKey()
{
    Utils::structZeroT(_key);
    Utils::arraySizeT(_ivec);
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
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
void_t
Blowfish::encryptCfb64(
    cuchar_t  *a_in,
    uchar_t   *a_out,
    clong_t   &a_inSize,
    int_t     *a_num,
    cCryptMode a_mode
)
{
    xTEST_PTR(a_in);
    xTEST_PTR(a_out);
    xTEST_LESS(- 1L, a_inSize);
    xTEST_PTR(a_num);

    Utils::arraySizeT(_ivec);

    (void_t)::BF_cfb64_encrypt(a_in, a_out, a_inSize, &_key, _ivec, a_num, a_mode);
}
//-------------------------------------------------------------------------------------------------
void_t
Blowfish::encryptCfb64(
    std::custring_t &a_in,
    std::ustring_t  *a_out,
    cCryptMode       a_mode
)
{
    xTEST_EQ(a_in.empty(), false);
    xTEST_PTR(a_out);

    a_out->resize( a_in.size() );

    int_t num = 0;  // this integer must be initialized to zero when ivec is initialized

    encryptCfb64(&a_in.at(0), &a_out->at(0),
        static_cast<long_t>( a_in.size() ), &num, a_mode);
    xTEST_LESS(- 1, num);
}
//-------------------------------------------------------------------------------------------------
void_t
Blowfish::encryptFileCfb64(
    std::ctstring_t &a_filePathIn,
    std::ctstring_t &a_filePathOut,
    cCryptMode       a_mode
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

xNAMESPACE_END2(xl, crypt)

#endif // cmOPENSSL_CRYPTO_FOUND
