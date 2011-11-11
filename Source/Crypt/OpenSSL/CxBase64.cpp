/**
 * \file  CxBase64.cpp
 * \brief Base64
 */


#include <xLib/Crypt/OpenSSL/CxBase64.h>

#include <xLib/Common/CxChar.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#if defined(xOS_ENV_WIN)
    #if defined(xCOMPILER_MS)
        #pragma comment(lib, "libeay32.lib")
    #endif
#elif defined(xOS_ENV_UNIX)
    // -lcrypt -lssl -lcrypto
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//----------------------------------------------------------------------------------------------------
/*static*/
std::string
CxBase64::sEncode(
    const std::string &csStr
)
{
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

    int iWritten = BIO_write(pbioContainer, &csStr.at(0), csStr.size());    BIO_flush(pbioContainer);
    /*DEBUG*/xASSERT_RET(0                                <  iWritten, std::string());
    /*DEBUG*/xASSERT_RET(static_cast<int>( csStr.size() ) == iWritten, std::string());

    LONG liRes = BIO_get_mem_ptr(pbioContainer, &pbmBuffMemory);
    /*DEBUG*/xASSERT_RET(0 < liRes, std::string());

    sRes.assign(pbmBuffMemory->data, pbmBuffMemory->length);

    BIO_free_all(pbioContainer);
    /*DEBUG*/// n/a

    return sRes;
}
//----------------------------------------------------------------------------------------------------
/*static*/
std::string
CxBase64::sDecode(
    const std::string &csStr
)
{
    std::string  sRes;
    BIO         *pbioMemory    = NULL;
    BIO         *pbioBase64    = NULL;
    BIO         *pbioContainer = NULL;


    //create a memory buffer containing base64 encoded data
    pbioMemory = BIO_new_mem_buf((void *)&csStr.at(0), csStr.size());
    /*DEBUG*/xASSERT_RET(NULL != pbioMemory, std::string());

    //create a base64 filter
    pbioBase64 = BIO_new(BIO_f_base64());
    /*DEBUG*/xASSERT_RET(NULL != pbioBase64, std::string());

    BIO_set_flags(pbioBase64, BIO_FLAGS_BASE64_NO_NL);
    /*DEBUG*/// n/a

    //push a Base64 filter so that reading from buffer decodes it
    pbioContainer = BIO_push(pbioBase64, pbioMemory);

    sRes.resize(csStr.size());

    int iReaded = BIO_read(pbioContainer, &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 < iReaded, std::string());

    sRes.resize(iReaded);

    BIO_free_all(pbioContainer);
    /*DEBUG*/// n/a

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxBase64::bIsCharValid(
    const char cchChar
)
{
    /*DEBUG*/// n/a

    BOOL bRes = static_cast<BOOL>( (FALSE != CxChar::bIsAlphaNum(cchChar)) || ('+' == cchChar) || ('/' == cchChar) );

    return bRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxBase64::CxBase64() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------
/*virtual*/
CxBase64::~CxBase64() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
