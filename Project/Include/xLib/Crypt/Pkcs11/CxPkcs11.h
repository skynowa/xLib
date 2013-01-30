/**
 * \file  CxPkcs11.h
 * \brief Aladdin eToken, PKCS#11
 */


#ifndef xLib_Pkcs11_CxPkcs11H
#define xLib_Pkcs11_CxPkcs11H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Common.h>
#include <xLib/Filesystem/CxDll.h>
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11 :
    private CxNonCopyable
    /// Aladdin eToken, PKCS#11
{
public:
                          CxPkcs11    ();
        ///< constructor
    virtual              ~CxPkcs11    ();
        ///< destructor

    CK_FUNCTION_LIST_PTR  funcList    () const;
        ///< get pointer to dll functions list
    static std::tstring_t errorStr    (const CK_RV culCode);
        ///< get error string by code, SDK 4.53

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;            ///< pointer to function
    CxDll                _m_dllETPkcs11;    ///< Pkcs11 CxDll object

    void                 _loadETPkcs11();
        ///< load eTPkcs11.dll
    void                 _initialize  ();
        ///< initiate PKCS#11
    void                 _finalize    ();
        ///< finalize PKCS#11
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif // xLib_Pkcs11_CxPkcs11H
