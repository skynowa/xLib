/**
 * \file  CxLogin.h
 * \brief Pkcs11 login
 */


#ifndef xLib_Pkcs11_CxLoginH
#define xLib_Pkcs11_CxLoginH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Pkcs11/Win/CxSession.h>
//---------------------------------------------------------------------------
class CxLogin :
    public CxNonCopyable
    /// Pkcs11 login
{
    public:
                             CxLogin(const CxPkcs11 &cPkcs11, const CxSession &cSession);
            ///< constructor
        virtual             ~CxLogin();
        	///< constructor

        BOOL                 bLogin (CK_USER_TYPE userType, CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen);
        	///< login user into a token
        BOOL                 bLogout();
        	///< logout user from a token

    private:
        BOOL                 _m_bRes;
        	///< for private use
        CK_RV                _m_ulRes;
        	///< for private use

        CK_FUNCTION_LIST_PTR _m_pFunc;
        	///< pointer to dll's functions list
        CK_SESSION_HANDLE    _m_hSession;
        	///< session handle
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxLoginH
