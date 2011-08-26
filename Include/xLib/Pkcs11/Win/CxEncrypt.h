/**
 * \file  CxEncrypt.h
 * \brief Pkcs11 encrypt
 */


#ifndef xLib_Pkcs11_CxEncryptH
#define xLib_Pkcs11_CxEncryptH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Pkcs11/Win/CxSession.h>
//---------------------------------------------------------------------------
class CxEncrypt :
    public CxNonCopyable
    /// Pkcs11 encrypt
{
    public:
                             CxEncrypt(const CxPkcs11 &cPkcs11, const CxSession &cSession);
            ///< constructor
        virtual             ~CxEncrypt();
        	///< destructor

        BOOL                 bInit    (CK_MECHANISM_PTR  pMechanism, CK_OBJECT_HANDLE hKey);
        	///< initializes an encryption operation
        BOOL                 bMake    (CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pEncryptedData, CK_ULONG_PTR pulEncryptedDataLen);
        	///< encrypts single-part data
        BOOL                 bUpdate  (CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR  pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);
        	///< continues a multiple-part encryption operation
        BOOL                 bFinal   (CK_BYTE_PTR pLastEncryptedPart, CK_ULONG_PTR pulLastEncryptedPartLen );
        	///< finishes a multiple-part encryption operation

        //Utils
        BOOL                 bMakeFile(const std::tstring &csInFilePath, const std::tstring &csOutFilePath, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
        	///< make file

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
#endif    //xLib_Pkcs11_CxEncryptH
