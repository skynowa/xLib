/**
 * \file  CxSession.h
 * \brief Pkcs11 session
 */


#ifndef xLib_Pkcs11_CxSessionH
#define xLib_Pkcs11_CxSessionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
//---------------------------------------------------------------------------
class CxSession :
    public CxNonCopyable
{
    public:
                             CxSession         (const CxPkcs11 &cPkcs11);
            ///< constructor
        virtual             ~CxSession         ();
        	///< destructor

        CK_SESSION_HANDLE    hGetHandle        () const;
    		///< get handle
        BOOL                 bOpen             (CK_SLOT_ID slotID, CK_FLAGS flags, CK_VOID_PTR pApplication, CK_NOTIFY Notify);
    		///< opens a session between an application and a token
        BOOL                 bGetInfo          (CK_SESSION_INFO_PTR pInfo);
    		///< obtains information about the session
        BOOL                 bSetOperationState(CK_BYTE_PTR pOperationState, CK_ULONG ulOperationStateLen, CK_OBJECT_HANDLE hEncryptionKey, CK_OBJECT_HANDLE hAuthenticationKey);
    		///< restores the state of the cryptographic operation in a session
        BOOL                 bGetOperationState(CK_BYTE_PTR pOperationState, CK_ULONG_PTR pulOperationStateLen);
        	///< obtains the state of the cryptographic operation in a session
        BOOL                 bClose            ();
    		///< closes a session between an application and a token
        BOOL                 bCloseAll         (CK_SLOT_ID slotID);
    		///< closes all sessions with a token

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
#endif    //xLib_Pkcs11_CxSessionH
