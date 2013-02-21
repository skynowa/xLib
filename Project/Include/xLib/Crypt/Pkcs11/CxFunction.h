/**
 * \file  CxFunction.h
 * \brief Pkcs11 function
 */


#ifndef xLib_Pkcs11_CxFunctionH
#define xLib_Pkcs11_CxFunctionH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Common.h>
//------------------------------------------------------------------------------
#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;
class CxSession;

class CxFunction :
    private CxNonCopyable
    /// Pkcs11 function
{
public:
                         CxFunction(const CxPkcs11 &cPkcs11, const CxSession &cSession);
        ///< constructor
    virtual             ~CxFunction();
        ///< destructor

    void                 list      (CK_FUNCTION_LIST_PTR_PTR ppFunctionList);
        ///< returns the function list
    void                 status    ();
        ///< is a legacy function; it obtains an updated status of a function running in parallel with an application
    void                 cancel    ();
        ///< is a legacy function; it cancels a function running in parallel
    void                 listEx    ();
        ///< SDK 4.53

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;      ///< pointer to dll functions list
    CK_SESSION_HANDLE    _m_hSession;   ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#endif // xLib_Pkcs11_CxFunctionH
