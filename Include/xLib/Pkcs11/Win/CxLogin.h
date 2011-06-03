/****************************************************************************
* Class name:  CxLogin
* Description: Pkcs11 login
* File name:   CxLogin.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:03:30
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxLoginH
#define xLib_Pkcs11_CxLoginH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
#include <xLib/Pkcs11/CxSession.h>
//---------------------------------------------------------------------------
class CxLogin :
    public CxNonCopyable
{
    public:
                             CxLogin(const CxPkcs11 &cPkcs11, const CxSession &cSession);
        virtual             ~CxLogin();

        BOOL                 bLogin (CK_USER_TYPE userType, CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen);
        BOOL                 bLogout();

    private:
        BOOL                 _m_bRes;
        CK_RV                _m_ulRes;

        CK_FUNCTION_LIST_PTR _m_pFunc;
        CK_SESSION_HANDLE    _m_hSession;
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxLoginH
