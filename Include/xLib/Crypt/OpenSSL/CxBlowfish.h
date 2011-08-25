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
{
    private:
        enum {
            MAX_KEY_SIZE = 56, //max key size 448 bit (56 byte)
            IVEC_SIZE    = 8
        };

        BOOL          _m_bRes;
        BF_KEY        _m_bfKey;
        UCHAR         _m_ucIvec[IVEC_SIZE];

    public:
        enum ECryptMode {
            cmUnknown = - 1,
            cmEncrypt = BF_ENCRYPT,
            cmDecrypt = BF_DECRYPT
        };

                      CxBlowfish          ();
        virtual      ~CxBlowfish          ();

        BOOL          bSetKey             (UCHAR *pucKey, INT iKeySize);
        BOOL          bSetKey             (const std::ustring &cusKey);
        BOOL          bSetKey             (const std::tstring &csKey);
        BOOL          bSetFileKey         (const std::tstring &csFilePath);
        static size_t uiGetMaxKeySize     ();

        //cfb64
        BOOL          bEncryptCfb64       (UCHAR *pucIn, UCHAR *pucOut, LONG liInSize, INT *piNum, ECryptMode cmMode);
        BOOL          bEncryptCfb64       (const std::ustring &cusIn, std::ustring *pusOut, ECryptMode cmMode);
        BOOL          bEncryptFileCfb64   (const std::tstring &csFilePathIn, const std::tstring &csFilePathOut, ECryptMode cmMode);

        //
        BOOL          bEncryptFileCfb64   (const std::tstring &csFilePathIn, const std::tstring &csFilePathOut, const std::ustring &cusStamp, ECryptMode cmCryptMode);
        ECryptMode    cmGetFileCryptStatus(const std::tstring &csFilePath, const std::ustring &cusStamp);

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


