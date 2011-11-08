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

        BOOL          bSetKey             (UCHAR *pucKey, const int ciKeySize);
            ///< set key
        BOOL          bSetKey             (const std::ustring &cusKey);
            ///< set key
        BOOL          bSetKey             (const std::string_t &csKey);
            ///< set key
        BOOL          bSetFileKey         (const std::string_t &csFilePath);
            ///< set key as file
        static size_t uiGetMaxKeySize     ();
            ///< get maximum key size

        //cfb64
        BOOL          bEncryptCfb64       (UCHAR *pucIn, UCHAR *pucOut, const LONG cliInSize, int *piNum, const ECryptMode cmMode);
            ///< encrypt buffer
        BOOL          bEncryptCfb64       (const std::ustring &cusIn, std::ustring *pusOut, const ECryptMode cmMode);
            ///< encrypt std::ustring
        BOOL          bEncryptFileCfb64   (const std::string_t &csFilePathIn, const std::string_t &csFilePathOut, const ECryptMode cmMode);
            ///< encrypt file

        //
        BOOL          bEncryptFileCfb64   (const std::string_t &csFilePathIn, const std::string_t &csFilePathOut, const std::ustring &cusStamp, const ECryptMode cmCryptMode);
            ///< encrypt file
        ECryptMode    cmGetFileCryptStatus(const std::string_t &csFilePath, const std::ustring &cusStamp);
            ///< get file crypt status

    private:
        enum
            /// constants
        {
            MAX_KEY_SIZE = 56,  ///< max key size 448 bit (56 byte)
            IVEC_SIZE    = 8    ///< ivec size
        };

        BF_KEY        _m_bfKey;             ///< crypt key
        UCHAR         _m_ucIvec[IVEC_SIZE]; ///< ivec
};
//---------------------------------------------------------------------------
#endif //xLib_Crypt_OpenSSL_CxBlowfishH


/*
void  BF_set_key      (BF_KEY *key, int len, unsigned char *data);
void  BF_ecb_encrypt  (unsigned char *in, unsigned char *out, BF_KEY *key, int enc);
void  BF_encrypt      (BF_LONG *data, BF_KEY *key);
void  BF_decrypt      (BF_LONG *data, BF_KEY *key);
void  BF_cbc_encrypt  (unsigned char *in, unsigned char *out, long length, BF_KEY *ks,       unsigned char *iv,             int enc);
void  BF_cfb64_encrypt(unsigned char *in, unsigned char *out, long length, BF_KEY *schedule, unsigned char *ivec, int *num, int enc);
void  BF_ofb64_encrypt(unsigned char *in, unsigned char *out, long length, BF_KEY *schedule, unsigned char *ivec, int *num);
char *BF_options      (void);
*/


