/****************************************************************************
* Class name:  CxBlowfish
* Description: blowfish (openssl-1.0.0a)
* File name:   CxBlowfish.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.08.2009 10:41:45
*
*****************************************************************************/


#ifndef xLib_Crypt_OpenSSL_CxBlowfishH
#define xLib_Crypt_OpenSSL_CxBlowfishH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include "openssl/blowfish.h"
//---------------------------------------------------------------------------
class CxBlowfish : public CxNonCopyable {
    private:   
        enum { 
            MAX_KEY_SIZE = 56, //max key size 448 bit (56 byte)
            IVEC_SIZE    = 8
        };

        BOOL          _m_bRes;
        BF_KEY        _m_bfKey;
        UCHAR         _m_ucIvec[IVEC_SIZE];

    public:
        //crypt mode
        enum ECryptMode {
            cmUnknown = - 1,
            cmEncrypt = BF_ENCRYPT,
            cmDecrypt = BF_DECRYPT,
        };

                      CxBlowfish          ();
        virtual      ~CxBlowfish          ();
                     
        BOOL          bSetKey             (UCHAR *pucKey, INT iKeySize);
        BOOL          bSetKey             (const uString &cusKey); 
        BOOL          bSetKey             (const tString &csKey);
        BOOL          bSetFileKey         (const tString &csFilePath);
        static size_t uiGetMaxKeySize     ();

        //cfb64
        BOOL          bEncryptCfb64          (UCHAR *pucIn, UCHAR *pucOut, LONG liInSize, INT *piNum, ECryptMode cmMode);
        BOOL          bEncryptCfb64          (const uString &cusIn, uString *pusOut, ECryptMode cmMode);
        BOOL          bEncryptFileCfb64   (const tString &csFilePathIn, const tString &csFilePathOut, ECryptMode cmMode); 

        //
        BOOL          bEncryptFileCfb64   (const tString &csFilePathIn, const tString &csFilePathOut, const uString &cusStamp, ECryptMode cmCryptMode);
        ECryptMode    cmGetFileCryptStatus(const tString &csFilePath, const uString &cusStamp);

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


