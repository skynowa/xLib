/**
 * \file  CxBlowfish.h
 * \brief blowfish (openssl)
 */


#pragma once

#ifndef xLib_CxBlowfishH
#define xLib_CxBlowfishH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>

#if xHAVE_OPENSSL_CRYPTO

#include <openssl/blowfish.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, crypt)

class CxBlowfish
    /// blowfish
{
public:
    enum ExCryptMode
        /// crypt mode
    {
        cmUnknown = - 1,
        cmEncrypt = BF_ENCRYPT,
        cmDecrypt = BF_DECRYPT
    };

                  CxBlowfish();
        ///< constructor
    virtual      ~CxBlowfish();
        ///< destructor

    void_t        setKey(uchar_t *key, cint_t &keySize);
        ///< set key
    void_t        setKey(std::custring_t &key);
        ///< set key
    void_t        setKey(std::ctstring_t &key);
        ///< set key
    void_t        setFileKey(std::ctstring_t &filePath);
        ///< set key as file
    static
    size_t        maxKeySize() xWARN_UNUSED_RV;
        ///< get maximum key size

    // cfb64
    void_t        encryptCfb64(uchar_t *in, uchar_t *out, clong_t &inSize, int_t *num,
                      const ExCryptMode &mode);
        ///< encrypt buffer
    void_t        encryptCfb64(std::custring_t &in, std::ustring_t *out,
                      const ExCryptMode &mode);
        ///< encrypt std::ustring_t
    void_t        encryptFileCfb64(std::ctstring_t &filePathIn, std::ctstring_t &filePathOut,
                      const ExCryptMode &mode);
        ///< encrypt file

private:
    enum
        /// constants
    {
        MAX_KEY_SIZE = 56,  ///< max key size 448 bit (56 byte)
        IVEC_SIZE    = 8    ///< ivec size
    };

    BF_KEY        _key;             ///< crypt key
    uchar_t       _ivec[IVEC_SIZE]; ///< ivec

    xNO_COPY_ASSIGN(CxBlowfish)
};

xNAMESPACE2_END(xlib, crypt)

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
#include "CxBlowfish.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxBlowfishH


/*
void  BF_set_key      (BF_KEY *key, int_t len, unsigned char *data);
void  BF_ecb_encrypt  (unsigned char *in, unsigned char *out, BF_KEY *key, int_t enc);
void  BF_encrypt      (BF_LONG *data, BF_KEY *key);
void  BF_decrypt      (BF_LONG *data, BF_KEY *key);
void  BF_cbc_encrypt  (unsigned char *in, unsigned char *out, long_t length, BF_KEY *ks,       unsigned char *iv,             int_t enc);
void  BF_cfb64_encrypt(unsigned char *in, unsigned char *out, long_t length, BF_KEY *schedule, unsigned char *ivec, int_t *num, int_t enc);
void  BF_ofb64_encrypt(unsigned char *in, unsigned char *out, long_t length, BF_KEY *schedule, unsigned char *ivec, int_t *num);
char *BF_options      (void_t);
*/
