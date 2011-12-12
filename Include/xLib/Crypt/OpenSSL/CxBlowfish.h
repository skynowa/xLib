/**
 * \file  CxBlowfish.h
 * \brief blowfish (openssl-1.0.0a)
 */


#ifndef xLib_Crypt_OpenSSL_CxBlowfishH
#define xLib_Crypt_OpenSSL_CxBlowfishH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <openssl/blowfish.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxBlowfish :
    public CxNonCopyable
    /// blowfish (openssl-1.0.0a)
{
    public:
        enum ECryptMode
            /// crypt mode
        {
            cmUnknown = - 1,
            cmEncrypt = BF_ENCRYPT,
            cmDecrypt = BF_DECRYPT
        };

                      CxBlowfish          ();
            ///< constructor
        virtual      ~CxBlowfish          ();
            ///< destructor

        bool          bSetKey             (uchar_t *pucKey, const int ciKeySize);
            ///< set key
        bool          bSetKey             (const std::ustring_t &cusKey);
            ///< set key
        bool          bSetKey             (const std::tstring_t &csKey);
            ///< set key
        bool          bSetFileKey         (const std::tstring_t &csFilePath);
            ///< set key as file
        static size_t uiGetMaxKeySize     ();
            ///< get maximum key size

        //cfb64
        bool          bEncryptCfb64       (uchar_t *pucIn, uchar_t *pucOut, const long_t cliInSize, int *piNum, const ECryptMode cmMode);
            ///< encrypt buffer
        bool          bEncryptCfb64       (const std::ustring_t &cusIn, std::ustring_t *pusOut, const ECryptMode cmMode);
            ///< encrypt std::ustring_t
        bool          bEncryptFileCfb64   (const std::tstring_t &csFilePathIn, const std::tstring_t &csFilePathOut, const ECryptMode cmMode);
            ///< encrypt file

        //
        bool          bEncryptFileCfb64   (const std::tstring_t &csFilePathIn, const std::tstring_t &csFilePathOut, const std::ustring_t &cusStamp, const ECryptMode cmCryptMode);
            ///< encrypt file
        ECryptMode    cmGetFileCryptStatus(const std::tstring_t &csFilePath, const std::ustring_t &cusStamp);
            ///< get file crypt status

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
//---------------------------------------------------------------------------
#endif //xLib_Crypt_OpenSSL_CxBlowfishH


/*
void  BF_set_key      (BF_KEY *key, int len, unsigned char *data);
void  BF_ecb_encrypt  (unsigned char *in, unsigned char *out, BF_KEY *key, int enc);
void  BF_encrypt      (BF_LONG *data, BF_KEY *key);
void  BF_decrypt      (BF_LONG *data, BF_KEY *key);
void  BF_cbc_encrypt  (unsigned char *in, unsigned char *out, long_t length, BF_KEY *ks,       unsigned char *iv,             int enc);
void  BF_cfb64_encrypt(unsigned char *in, unsigned char *out, long_t length, BF_KEY *schedule, unsigned char *ivec, int *num, int enc);
void  BF_ofb64_encrypt(unsigned char *in, unsigned char *out, long_t length, BF_KEY *schedule, unsigned char *ivec, int *num);
char *BF_options      (void);
*/


