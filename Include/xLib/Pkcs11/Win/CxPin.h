/****************************************************************************
* Class name:  CxPin
* Description: Pkcs11 pin
* File name:   CxPin.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:09:04
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxPinH
#define xLib_Pkcs11_CxPinH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
#include <xLib/Pkcs11/CxSession.h>
//---------------------------------------------------------------------------
class CxPin :
    public CxNonCopyable
{
    public:
                             CxPin         (const CxPkcs11 &cPkcs11, const CxSession &cSession);
        virtual             ~CxPin         ();

        BOOL                 bInitToken    (CK_SLOT_ID slotID, CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen, CK_UTF8CHAR_PTR pLabel);
        BOOL                 bInitPIN      (CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen);
        BOOL                 bSetPIN       (CK_UTF8CHAR_PTR pOldPin, CK_ULONG ulOldLen, CK_UTF8CHAR_PTR pNewPin, CK_ULONG ulNewLen);

        //Utils
        #if xTODO
        tString              sChangeUserPin(const AnsiString &casOldUserPin, const AnsiString &casNewUserPin);
        tString              sChangeSOPin  (const AnsiString &casOldSOPin,   const AnsiString &casNewSOPin);
        #endif

    private:
        BOOL                 _m_bRes;
        CK_RV                _m_ulRes;

        CK_FUNCTION_LIST_PTR _m_pFunc;
        CK_SESSION_HANDLE    _m_hSession;
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxPinH
