/**
 * \file  CxEncrypt.h
 * \brief Pkcs11 encrypt
 */


#ifndef xLib_Pkcs11_CxEncryptH
#define xLib_Pkcs11_CxEncryptH
//------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Crypt/Pkcs11/Core.h>
//------------------------------------------------------------------------------
#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;
class CxSession;

class CxEncrypt :
    private CxNonCopyable
    /// Pkcs11 encrypt
{
public:
                         CxEncrypt(const CxPkcs11 &cPkcs11, const CxSession &cSession);
        ///< constructor
    virtual             ~CxEncrypt();
        ///< destructor

    void_t               init     (CK_MECHANISM_PTR  pMechanism, CK_OBJECT_HANDLE hKey);
        ///< initializes an encryption operation
    void_t               make     (CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pEncryptedData, CK_ULONG_PTR pulEncryptedDataLen);
        ///< encrypts single-part data
    void_t               update   (CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR  pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);
        ///< continues a multiple-part encryption operation
    void_t               final    (CK_BYTE_PTR pLastEncryptedPart, CK_ULONG_PTR pulLastEncryptedPartLen );
        ///< finishes a multiple-part encryption operation

    // Utils
    void_t               makeFile (std::ctstring_t &csInFilePath, std::ctstring_t &csOutFilePath, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
        ///< make file

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;      ///< pointer to dll functions list
    CK_SESSION_HANDLE    _m_hSession;   ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#endif // xLib_Pkcs11_CxEncryptH
