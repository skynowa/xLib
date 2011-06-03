/****************************************************************************
* Class name:  CxObject
* Description: Pkcs11 object
* File name:   CxObject.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:09:54
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxObjectH
#define xLib_Pkcs11_CxObjectH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
#include <xLib/Pkcs11/CxSession.h>
//---------------------------------------------------------------------------
class CxObject :
    public CxNonCopyable
{
    public:
                             CxObject          (const CxPkcs11 &cPkcs11, const CxSession &cSession);
        virtual             ~CxObject          ();

        CK_OBJECT_HANDLE     hGetHandle        () const;
        BOOL                 bSetHandle        (CK_OBJECT_HANDLE hHandle);

        BOOL                 bCreate           (CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount);
        BOOL                 bGetSize          (CK_ULONG_PTR pulSize);
        BOOL                 bCopy             (CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount, CK_OBJECT_HANDLE_PTR phNewObject);
        BOOL                 bFind             (CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount, std::vector<CK_OBJECT_HANDLE> *pvecObjectHandles);

        BOOL                 bGetAttributeValue(CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount);
        BOOL                 bSetAttributeValue(CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount);

        BOOL                 bDestroy          ();

        //Utils
        static BOOL          bGetData          (CK_SLOT_ID ulSlotId, const uString &cusUserPin, const uString &cusDataLabel, uString *pusData);
        static BOOL          bSetData          (CK_SLOT_ID ulSlotId, const uString &cusUserPin, const uString &cusDataLabel, const uString &cusData);
        static BOOL          bGetData          (CK_SLOT_ID ulSlotId, const uString &cusUserPin, std::vector<uString> *pusDataLabel, std::vector<uString> *pusDataValue);

    private:
        BOOL                 _m_bRes;
        CK_RV                _m_ulRes;

        CK_FUNCTION_LIST_PTR _m_pFunc;
        CK_SESSION_HANDLE    _m_hSession;
        CK_OBJECT_HANDLE     _m_hObject;

        #if xTODO
            BOOL                   bFindInit           (CK_ATTRIBUTE_PTR  pTemplate, CK_ULONG ulCount);
            BOOL                   bFind               (CK_OBJECT_HANDLE_PTR phObject, CK_ULONG ulMaxObjectCount, CK_ULONG_PTR pulObjectCount);
            BOOL                   bFindFinal          ();
        #endif
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxObjectH
