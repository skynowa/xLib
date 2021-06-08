/**
 * \file  Blowfish.h
 * \brief blowfish (openssl)
 */


#pragma once

#include <xLib/Core/Core.h>

#include <openssl/blowfish.h>
//-------------------------------------------------------------------------------------------------
namespace xl::crypt
{

class Blowfish
    /// blowfish
{
public:
    enum class Mode
        /// crypt mode
    {
        Unknown = - 1,
        Encrypt = BF_ENCRYPT,
        Decrypt = BF_DECRYPT
    };
    xUSING_CONST(Mode);

///@name ctors, dtor
///@{
			 Blowfish();
	virtual ~Blowfish();

	xNO_COPY_ASSIGN(Blowfish)
///@}

    void_t   setKey(uchar_t *key, cint_t &keySize);
        ///< set key
    void_t   setKey(std::custring_t &key);
        ///< set key
    void_t   setKey(std::ctstring_t &key);
        ///< set key
    void_t   setFileKey(std::ctstring_t &filePath);
        ///< set key as file

    // cfb64
    void_t   encryptCfb64(cMode mode, cuchar_t *in, uchar_t *out, clong_t &inSize, int_t *num);
        ///< encrypt buffer
    void_t   encryptCfb64(cMode mode, std::custring_t &in, std::ustring_t *out);
        ///< encrypt std::ustring_t
    void_t   encryptFileCfb64(cMode mode, std::ctstring_t &filePathIn, std::ctstring_t &filePathOut);
        ///< encrypt file

private:
    BF_KEY  _key {};            ///< crypt key
    uchar_t _ivec[BF_BLOCK] {}; ///< ivec

    constexpr size_t _keySizeMax() const;
        ///< get maximum key size
    void_t           _clearKey();
        ///< clear key (for security)
};

} // namespace
//-------------------------------------------------------------------------------------------------

/**
 * TODO:
 *
 * void_t  BF_set_key      (BF_KEY *key, int_t len, unsigned char *data);
 * void_t  BF_ecb_encrypt  (unsigned char *in, unsigned char *out, BF_KEY *key, int_t enc);
 * void_t  BF_encrypt      (BF_LONG *data, BF_KEY *key);
 * void_t  BF_decrypt      (BF_LONG *data, BF_KEY *key);
 * void_t  BF_cbc_encrypt  (unsigned char *in, unsigned char *out, long_t length, BF_KEY *ks,       unsigned char *iv,             int_t enc);
 * void_t  BF_cfb64_encrypt(unsigned char *in, unsigned char *out, long_t length, BF_KEY *schedule, unsigned char *ivec, int_t *num, int_t enc);
 * void_t  BF_ofb64_encrypt(unsigned char *in, unsigned char *out, long_t length, BF_KEY *schedule, unsigned char *ivec, int_t *num);
 * char *BF_options      (void_t);
 */
