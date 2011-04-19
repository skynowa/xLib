/****************************************************************************
* Class name:  CxBase64
* Description: Base64
* File name:   CxBase64.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     07.07.2009 12:22:00
*
*****************************************************************************/


#include <xLib/Crypt/CxBase64.h>

#include <xLib/Common/CxChar.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//----------------------------------------------------------------------------------------------------
//DONE: sEncode (encoding)
/*static*/
std::string
CxBase64::sEncode(const std::string &csStr) {
    std::string  sRes;
    BIO         *pbioMemory    = NULL;
    BIO         *pbioBase64    = NULL;
    BIO         *pbioContainer = NULL;
    BUF_MEM     *pbmBuffMemory = NULL;


    pbioBase64 = BIO_new(BIO_f_base64());
    /*DEBUG*/xASSERT_RET(NULL != pbioBase64, std::string());

    BIO_set_flags(pbioBase64, BIO_FLAGS_BASE64_NO_NL);
    /*DEBUG*/// n/a

    pbioMemory = BIO_new(BIO_s_mem());
    /*DEBUG*/xASSERT_RET(NULL != pbioMemory, std::string());

    pbioContainer = BIO_push(pbioBase64, pbioMemory);
    /*DEBUG*/// n/a

    INT iWrited = BIO_write(pbioContainer, &csStr.at(0), csStr.size());    BIO_flush(pbioContainer);
    /*DEBUG*/xASSERT_RET(0 < iWrited, std::string());

    LONG liRes = BIO_get_mem_ptr(pbioContainer, &pbmBuffMemory);
    /*DEBUG*/xASSERT_RET(0 < liRes, std::string());

    sRes.assign(pbmBuffMemory->data, pbmBuffMemory->length);

    BIO_free_all(pbioContainer);
    /*DEBUG*/// n/a

    return sRes;
}
//----------------------------------------------------------------------------------------------------
//DONE: sDecode (decoding)
/*static*/
std::string
CxBase64::sDecode(const std::string &csStr) {
    std::string  sRes;
    BIO         *pbioMemory    = NULL;
    BIO         *pbioBase64    = NULL;
    BIO         *pbioContainer = NULL;
 

    //create a memory buffer containing base64 encoded data
    pbioMemory = BIO_new_mem_buf((VOID *)&csStr.at(0), csStr.size());
    /*DEBUG*/xASSERT_RET(NULL != pbioMemory, std::string());

    //create a base64 filter
    pbioBase64 = BIO_new(BIO_f_base64());
    /*DEBUG*/xASSERT_RET(NULL != pbioBase64, std::string());

    BIO_set_flags(pbioBase64, BIO_FLAGS_BASE64_NO_NL);
    /*DEBUG*/// n/a

    //push a Base64 filter so that reading from buffer decodes it
    pbioContainer = BIO_push(pbioBase64, pbioMemory);

    sRes.resize(csStr.size());

    INT iReaded = BIO_read(pbioContainer, &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 < iReaded, std::string());

    sRes.resize(iReaded);

    BIO_free_all(pbioContainer);
    /*DEBUG*/// n/a

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bIsCharValid (is a valid base64 char)
/*static*/
BOOL
CxBase64::bIsCharValid(INT iChar) {
    /*DEBUG*/// n/a

    BOOL bRes = FALSE;

    bRes = static_cast<BOOL>( TRUE == CxChar::bIsAlphaNum(iChar) || ('+' == iChar) || ('/' == iChar) );

    return bRes;
}
//---------------------------------------------------------------------------
