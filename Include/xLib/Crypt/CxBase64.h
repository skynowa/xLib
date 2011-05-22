/****************************************************************************
* Class name:  CxBase64
* Description: Base64
* File name:   CxBase64.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     07.07.2009 12:22:00
*
*****************************************************************************/


#ifndef xLib_Crypt_CxBase64H
#define xLib_Crypt_CxBase64H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_WIN)
	#if defined(xCOMPILER_MS)
		#pragma comment(lib, "libeay32.lib")
	#endif
#elif defined(xOS_LINUX)
    // n/a
#endif
//---------------------------------------------------------------------------
class CxBase64 : public CxNonCopyable {
    public:
        static std::string sEncode     (const std::string &csStr);
        static std::string sDecode     (const std::string &csStr);
        static BOOL        bIsCharValid(INT iChar);

    private:
};
//---------------------------------------------------------------------------
#endif    //xLib_Crypt_CxBase64H
