/**
 * \file  CxBase64.cpp
 * \brief Base64
 */


#include <xLib/Crypt/OpenSSL/CxBase64.h>

#include <xLib/Common/CxChar.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#if   xOS_ENV_WIN
    #if xCOMPILER_MS
        #pragma comment(lib, "libeay32.lib")
    #endif
#elif xOS_ENV_UNIX
    // -lcrypt -lssl -lcrypto
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------------
/* static */
std::string
CxBase64::encode(
    const std::string &a_csStr
)
{
    std::string  sRv;
    BIO         *pbioMemory    = NULL;
    BIO         *pbioBase64    = NULL;
    BIO         *pbioContainer = NULL;
    BUF_MEM     *pbmBuffMemory = NULL;


    pbioBase64 = ::BIO_new(BIO_f_base64());
    xTEST_PTR(pbioBase64);

    (void)BIO_set_flags(pbioBase64, BIO_FLAGS_BASE64_NO_NL);

    pbioMemory = ::BIO_new(::BIO_s_mem());
    xTEST_PTR(pbioMemory);

    pbioContainer = ::BIO_push(pbioBase64, pbioMemory);
    // n/a

    int_t iWritten = ::BIO_write(pbioContainer, &a_csStr.at(0), static_cast<int_t>( a_csStr.size() ));    (void)BIO_flush(pbioContainer);
    xTEST_LESS(0, iWritten);
    xTEST_EQ(static_cast<int_t>( a_csStr.size() ), iWritten);

    long_t liRv = BIO_get_mem_ptr(pbioContainer, &pbmBuffMemory);
    xTEST_LESS(0L, liRv);

    sRv.assign(pbmBuffMemory->data, pbmBuffMemory->length);

    (void)::BIO_free_all(pbioContainer);

    return sRv;
}
//-------------------------------------------------------------------------------------------------------
/* static */
std::string
CxBase64::decode(
    const std::string &a_csStr
)
{
    std::string  sRv;
    BIO         *pbioMemory    = NULL;
    BIO         *pbioBase64    = NULL;
    BIO         *pbioContainer = NULL;


    //create a memory buffer containing base64 encoded data
    pbioMemory = ::BIO_new_mem_buf((void *)&a_csStr.at(0), static_cast<int_t>( a_csStr.size() ));
    xTEST_PTR(pbioMemory);

    //create a base64 filter
    pbioBase64 = ::BIO_new(BIO_f_base64());
    xTEST_PTR(pbioBase64);

    (void)BIO_set_flags(pbioBase64, BIO_FLAGS_BASE64_NO_NL);

    //push a Base64 filter so that reading from buffer decodes it
    pbioContainer = ::BIO_push(pbioBase64, pbioMemory);

    sRv.resize(a_csStr.size());

    int_t iReaded = ::BIO_read(pbioContainer, &sRv.at(0), static_cast<int_t>( sRv.size() ));
    xTEST_LESS(0, iReaded);

    sRv.resize(iReaded);

    (void)::BIO_free_all(pbioContainer);

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxBase64::isCharValid(
	const char &a_cchChar
)
{
    // n/a

    bool_t bRv = ((false != CxChar::isAlphaNum(a_cchChar)) || 
                ('+' == a_cchChar) || ('/' == a_cchChar));

    return bRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxBase64::CxBase64() {
    
}
//------------------------------------------------------------------------------
/* virtual */
CxBase64::~CxBase64() {
    
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
