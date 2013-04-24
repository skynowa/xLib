/**
 * \file  CxBlowfish.h
 * \brief blowfish (openssl-1.0.0a)
 */


#ifndef xLib_Crypt_OpenSSL_CxBlowfishH
#define xLib_Crypt_OpenSSL_CxBlowfishH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if xOPENSSL_IS_USE

#include <openssl/blowfish.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxBlowfish :
    private CxNonCopyable
    /// blowfish (openssl-1.0.0a)
{
public:
    enum ExCryptMode
        /// crypt mode
    {
        cmUnknown = - 1,
        cmEncrypt = BF_ENCRYPT,
        cmDecrypt = BF_DECRYPT
    };

                  CxBlowfish      ();
        ///< constructor
    virtual      ~CxBlowfish      ();
        ///< destructor

    void_t        setKey          (uchar_t *pucKey, cint_t &ciKeySize);
        ///< set key
    void_t        setKey          (std::custring_t &cusKey);
        ///< set key
    void_t        setKey          (std::ctstring_t &csKey);
        ///< set key
    void_t        setFileKey      (std::ctstring_t &csFilePath);
        ///< set key as file
    static size_t maxKeySize      () xWARN_UNUSED_RV;
        ///< get maximum key size

    //cfb64
    void_t        encryptCfb64    (uchar_t *pucIn, uchar_t *pucOut, clong_t &cliInSize, int_t *piNum, const ExCryptMode &cmMode);
        ///< encrypt buffer
    void_t        encryptCfb64    (std::custring_t &cusIn, std::ustring_t *pusOut, const ExCryptMode &cmMode);
        ///< encrypt std::ustring_t
    void_t        encryptFileCfb64(std::ctstring_t &csFilePathIn, std::ctstring_t &csFilePathOut, const ExCryptMode &cmMode);
        ///< encrypt file

private:
    enum
        /// constants
    {
        MAX_KEY_SIZE = 56,  ///< max key size 448 bit (56 byte)
        IVEC_SIZE    = 8    ///< ivec size
    };

    BF_KEY        _m_bfKey;             ///< crypt key
    uchar_t       _m_ucIvec[IVEC_SIZE]; ///< ivec
};

xNAMESPACE_END(NxLib)

#endif // xOPENSSL_IS_USE
//------------------------------------------------------------------------------
#endif // xLib_Crypt_OpenSSL_CxBlowfishH


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


