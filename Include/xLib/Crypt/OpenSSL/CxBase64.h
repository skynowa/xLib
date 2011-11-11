/**
 * \file  CxBase64.h
 * \brief base64
 */


#ifndef xLib_Crypt_CxBase64H
#define xLib_Crypt_CxBase64H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxBase64 :
    public CxNonCopyable
    /// Base64
{
    public:
        static std::string sEncode     (const std::string &csStr);
            ///< encoding
        static std::string sDecode     (const std::string &csStr);
            ///< decoding
        static BOOL        bIsCharValid(const char cchChar);
            ///< is a valid Base64 char

    private:
                           CxBase64();
            ///< constructor
        virtual           ~CxBase64();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Crypt_CxBase64H
