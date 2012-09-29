/**
 * \file  CxPin.h
 * \brief Pkcs11 pin
 */


#ifndef xLib_Pkcs11_CxPinH
#define xLib_Pkcs11_CxPinH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Common.h>
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;
class CxSession;

class CxPin :
    private CxNonCopyable
    /// Pkcs11 pin
{
    public:
                             CxPin         (const CxPkcs11 &cPkcs11, const CxSession &cSession);
             ///< constructor
        virtual             ~CxPin         ();
             ///< destructor

        bool                 bInitToken    (CK_SLOT_ID slotID, CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen, CK_UTF8CHAR_PTR pLabel);
            ///< initializes a token
        bool                 bInitPIN      (CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen);
            ///< initializes the normal user's PIN
        bool                 bSetPIN       (CK_UTF8CHAR_PTR pOldPin, CK_ULONG ulOldLen, CK_UTF8CHAR_PTR pNewPin, CK_ULONG ulNewLen);
            ///< modifies the PIN of the user who is logged in

        //Utils
    #if xTODO
        std::tstring_t       sChangeUserPin(const AnsiString &casOldUserPin, const AnsiString &casNewUserPin);
        std::tstring_t       sChangeSOPin  (const AnsiString &casOldSOPin,   const AnsiString &casNewSOPin);
    #endif

    private:
        CK_FUNCTION_LIST_PTR _m_pFunc;         ///< pointer to dll's functions list
        CK_SESSION_HANDLE    _m_hSession;    ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxPinH
