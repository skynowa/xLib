/**
 * \file  CxPin.h
 * \brief Pkcs11 pin
 */


#ifndef xLib_Pkcs11_CxPinH
#define xLib_Pkcs11_CxPinH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Pkcs11/Win/CxSession.h>
//---------------------------------------------------------------------------
class CxPin :
    public CxNonCopyable
    /// Pkcs11 pin
{
    public:
                             CxPin         (const CxPkcs11 &cPkcs11, const CxSession &cSession);
             ///< constructor
        virtual             ~CxPin         ();
             ///< destructor

        BOOL                 bInitToken    (CK_SLOT_ID slotID, CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen, CK_UTF8CHAR_PTR pLabel);
            ///< initializes a token
        BOOL                 bInitPIN      (CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen);
        	///< initializes the normal user's PIN
        BOOL                 bSetPIN       (CK_UTF8CHAR_PTR pOldPin, CK_ULONG ulOldLen, CK_UTF8CHAR_PTR pNewPin, CK_ULONG ulNewLen);
        	///< modifies the PIN of the user who is logged in

        //Utils
	#if xTODO
		std::tstring              sChangeUserPin(const AnsiString &casOldUserPin, const AnsiString &casNewUserPin);
		std::tstring              sChangeSOPin  (const AnsiString &casOldSOPin,   const AnsiString &casNewSOPin);
	#endif

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
#endif    //xLib_Pkcs11_CxPinH
