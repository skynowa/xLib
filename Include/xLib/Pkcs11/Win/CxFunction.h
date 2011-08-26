/**
 * \file  CxFunction.h
 * \brief Pkcs11 function
 */


#ifndef xLib_Pkcs11_CxFunctionH
#define xLib_Pkcs11_CxFunctionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Pkcs11/Win/CxSession.h>
//---------------------------------------------------------------------------
class CxFunction :
    public CxNonCopyable
    /// Pkcs11 function
{
    public:
                             CxFunction(const CxPkcs11 &cPkcs11, const CxSession &cSession);
            ///< constructor
        virtual             ~CxFunction();
        	///< destructor

        BOOL                 bGetList  (CK_FUNCTION_LIST_PTR_PTR ppFunctionList);
        	///< returns the function list
        BOOL                 bGetStatus();
        	///< is a legacy function; it obtains an updated status of a function running in parallel with an application
        BOOL                 bCancel   ();
        	///< is a legacy function; it cancels a function running in parallel
        BOOL                 bGetListEx();
        	///< SDK 4.53

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
#endif    //xLib_Pkcs11_CxFunctionH
