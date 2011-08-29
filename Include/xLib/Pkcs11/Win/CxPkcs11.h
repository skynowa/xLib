/**
 * \file  CxPkcs11.h
 * \brief Aladdin eToken, PKCS#11
 */


#ifndef xLib_Pkcs11_CxPkcs11H
#define xLib_Pkcs11_CxPkcs11H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Filesystem/CxDll.h>
//---------------------------------------------------------------------------
class CxPkcs11 :
    public CxNonCopyable
    /// Aladdin eToken, PKCS#11
{
    public:
                             CxPkcs11      ();
            ///< constructor
        virtual             ~CxPkcs11      ();
        	///< destructor

        CK_FUNCTION_LIST_PTR pGetFuncList  () const;
        	///< get pointer to dll's functions list
   private:
        BOOL                 _m_bRes;        	///< for private use
        CK_RV                _m_ulRes;        	///< for private use
        CK_FUNCTION_LIST_PTR _m_pFunc;        	///< pointer to fumction
        CxDll                _m_dllETPkcs11;	///< Pkcs11 CxDll object

        BOOL                 _bLoadETPkcs11();
        	///< load eTPkcs11.dll
        BOOL                 bInitialize   ();
        	///< initiate PKCS#11
        BOOL                 bFinalize     ();
        	///< finalize PKCS#11
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxPkcs11H
