/**
 * \file  Blowfish.cpp
 * \brief OpenSSL - blowfish
 */


#include "Blowfish.h"

#include <xLib/Core/Utils.h>
#include <xLib/Fs/FileIO.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Fs/FileBin.h>
#include <xLib/Fs/Path.h>
#include <xLib/Crypt/Crc32.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>


namespace xl::crypt
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Blowfish::Blowfish()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Blowfish::~Blowfish()
{
	_clearKey();
}
//-------------------------------------------------------------------------------------------------
void_t
Blowfish::setKey(
    uchar_t *a_key,
    cint_t  &a_keySize
)
{
    xTEST_PTR(a_key);
    xTEST_GR_EQ(static_cast<int_t>( _keySizeMax() ), a_keySize);
    xTEST_LESS(0, a_keySize);

    (void_t)::BF_set_key(&_key, a_keySize, a_key);
}
//-------------------------------------------------------------------------------------------------
void_t
Blowfish::setKey(
    std::custring_t &a_key
)
{
    xTEST(!a_key.empty());
    xTEST_GR_EQ(_keySizeMax(), a_key.size());

    setKey(const_cast<uchar_t *>( a_key.data() ), static_cast<int_t>( a_key.size() ));
}
//-------------------------------------------------------------------------------------------------
void_t
Blowfish::setKey(
    std::ctstring_t &a_key
)
{
    xTEST(!a_key.empty());
    xTEST_GR_EQ(_keySizeMax(), a_key.size() * sizeof(std::tstring_t::value_type));

    setKey(std::ustring_t(a_key.cbegin(), a_key.cend()));
}
//-------------------------------------------------------------------------------------------------
void_t
Blowfish::setFileKey(
    std::ctstring_t &a_filePath
)
{
    xTEST(!a_filePath.empty());

    std::ustring_t fileKey;
	{
		FileBin file(a_filePath);
		file.read(&fileKey);

		FileInfo fileInfo(a_filePath);
		xTEST(!fileInfo.isEmpty());
		xTEST_LESS_EQ(fileInfo.size(), static_cast<longlong_t>( _keySizeMax() ));
	}

    setKey(fileKey);

    // for security
    std::fill(fileKey.begin(), fileKey.end(), uchar_t{});
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: cfb64
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Blowfish::encryptCfb64(
    cMode     a_mode,
    cuchar_t *a_in,
    uchar_t  *a_out,
    clong_t  &a_inSize,
    int_t    *a_num
)
{
    xTEST(a_mode == Blowfish::Mode::Encrypt || a_mode == Blowfish::Mode::Decrypt);
    xTEST_PTR(a_in);
    xTEST_PTR(a_out);
    xTEST_GR_EQ(a_inSize, 0L);
    xTEST_PTR(a_num);

    Utils::arrayZeroT(_ivec);

    (void_t)::BF_cfb64_encrypt(a_in, a_out, a_inSize, &_key, _ivec, a_num,
        static_cast<int_t>(a_mode));
}
//-------------------------------------------------------------------------------------------------
void_t
Blowfish::encryptCfb64(
    cMode            a_mode,
    std::custring_t &a_in,
    std::ustring_t  *a_out
)
{
    xTEST(!a_in.empty());
    xTEST_PTR(a_out);

    a_out->resize( a_in.size() );

    // this integer must be initialized to zero when ivec is initialized
    int_t num {};
    encryptCfb64(a_mode, &a_in.at(0), &a_out->at(0), static_cast<long_t>( a_in.size() ), &num);
    xTEST_LESS(- 1, num);
}
//-------------------------------------------------------------------------------------------------
void_t
Blowfish::encryptFileCfb64(
    cMode            a_mode,
    std::ctstring_t &a_filePathIn,
    std::ctstring_t &a_filePathOut
)
{
    xTEST(!a_filePathIn.empty());
    xTEST(!a_filePathOut.empty());

    std::ustring_t in;
    FileBin(a_filePathIn).read(&in);

    std::ustring_t out;
    encryptCfb64(a_mode, in, &out);

    FileBin(a_filePathOut).write(out, FileIO::OpenMode::BinReadWrite);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/**
 * Blowfish max key size
 *
 * https://www.oreilly.com/library/view/secure-programming-cookbook/0596003943/ch05s18.html
 *
 * OpenSSL     - 256 bits (32 bytes)
 * Algorithm's - 448 bits (56 bytes)
 */
constexpr size_t
Blowfish::_keySizeMax() const
{
    static_assert(CHAR_BIT == 8);

    return 32 * CHAR_BIT / CHAR_BIT;
}
//-------------------------------------------------------------------------------------------------
void_t
Blowfish::_clearKey()
{
    _key = {};
    Utils::arrayZeroT(_ivec);
}
//-------------------------------------------------------------------------------------------------

} // namespace
