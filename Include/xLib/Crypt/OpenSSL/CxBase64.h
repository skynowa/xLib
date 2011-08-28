/**
 * \file  CxBase64.h
 * \brief base64
 */


#ifndef xLib_Crypt_CxBase64H
#define xLib_Crypt_CxBase64H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxBase64 :
    public CxNonCopyable
    /// Base64
{
    public:
        static std::string sEncode     (const std::string &csStr);
        static std::string sDecode     (const std::string &csStr);
        static BOOL        bIsCharValid(const char cchChar);

    private:
};
//---------------------------------------------------------------------------
#endif    //xLib_Crypt_CxBase64H
