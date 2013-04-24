/**
 * \file  CxBase64.h
 * \brief base64
 */


#ifndef xLib_Crypt_CxBase64H
#define xLib_Crypt_CxBase64H
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
#if xOPENSSL_IS_USE

xNAMESPACE_BEGIN(NxLib)

class CxBase64 :
    private CxNonCopyable
    /// Base64
{
public:
    static std::string encode     (std::cstring_t &csStr) xWARN_UNUSED_RV;
        ///< encoding
    static std::string decode     (std::cstring_t &csStr) xWARN_UNUSED_RV;
        ///< decoding
    static bool_t      isCharValid(const char &cchChar) xWARN_UNUSED_RV;
        ///< is a valid Base64 char

private:
                       CxBase64   ();
        ///< constructor
    virtual           ~CxBase64   ();
        ///< destructor
};

xNAMESPACE_END(NxLib)

#endif // xOPENSSL_IS_USE
//------------------------------------------------------------------------------
#endif // xLib_Crypt_CxBase64H
