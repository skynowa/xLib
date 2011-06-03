/****************************************************************************
* Class name:  CxFunction
* Description: Pkcs11 function
* File name:   CxFunction.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:14:45
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxFunctionH
#define xLib_Pkcs11_CxFunctionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
#include <xLib/Pkcs11/CxSession.h>
//---------------------------------------------------------------------------
class CxFunction :
    public CxNonCopyable
{
    public:
                             CxFunction(const CxPkcs11 &cPkcs11, const CxSession &cSession);
        virtual             ~CxFunction();

        BOOL                 bGetList  (CK_FUNCTION_LIST_PTR_PTR ppFunctionList);
        BOOL                 bGetStatus();
        BOOL                 bCancel   ();
        BOOL                 bGetListEx();

    private:
        BOOL                 _m_bRes;
        CK_RV                _m_ulRes;

        CK_FUNCTION_LIST_PTR _m_pFunc;
        CK_SESSION_HANDLE    _m_hSession;
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxFunctionH
