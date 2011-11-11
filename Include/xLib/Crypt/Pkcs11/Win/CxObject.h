/**
 * \file  CxObject.h
 * \brief Pkcs11 object
 */


#ifndef xLib_Pkcs11_CxObjectH
#define xLib_Pkcs11_CxObjectH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Win/Common.h>
#include <xLib/Crypt/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/Win/CxSession.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

xNAMESPACE_BEGIN(NxLib)

class CxObject :
    public CxNonCopyable
    /// Pkcs11 object
{
    public:
                             CxObject          (const CxPkcs11 &cPkcs11, const CxSession &cSession);
            ///< constructor
        virtual             ~CxObject          ();
            ///< destructor

        CK_OBJECT_HANDLE     hGetHandle        () const;
            ///< get handle
        BOOL                 bSetHandle        (CK_OBJECT_HANDLE hHandle);
            ///< assign object handle
        BOOL                 bCreate           (CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount);
            ///< creates a new object
        BOOL                 bGetSize          (CK_ULONG_PTR pulSize);
            ///< gets the size of an object in bytes
        BOOL                 bCopy             (CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount, CK_OBJECT_HANDLE_PTR phNewObject);
            ///< copies an object, creating a new object for the copy
        BOOL                 bFind             (CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount, std::vector<CK_OBJECT_HANDLE> *pvecObjectHandles);
            ///< search for token and session objects that match a template, obtaining additional object handles

        BOOL                 bGetAttributeValue(CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount);
            ///< obtains the value of one or more object attributes
        BOOL                 bSetAttributeValue(CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount);
            ///< modifies the value of one or more object attributes

        BOOL                 bDestroy          ();
            ///< destroys an object

        //Utils
        static BOOL          bGetData          (CK_SLOT_ID ulSlotId, const std::ustring &cusUserPin, const std::ustring &cusDataLabel, std::ustring *pusData);
            ///< get data
        static BOOL          bSetData          (CK_SLOT_ID ulSlotId, const std::ustring &cusUserPin, const std::ustring &cusDataLabel, const std::ustring &cusData);
            ///< set data
        static BOOL          bGetData          (CK_SLOT_ID ulSlotId, const std::ustring &cusUserPin, std::vector<std::ustring> *pusDataLabel, std::vector<std::ustring> *pusDataValue);
            ///< get data

    private:
        CK_FUNCTION_LIST_PTR _m_pFunc;        ///< pointer to dll's functions list
        CK_SESSION_HANDLE    _m_hSession;    ///< session handle
        CK_OBJECT_HANDLE     _m_hObject;    ///< bject handle

    #if xTODO
        BOOL                 bFindInit         (CK_ATTRIBUTE_PTR  pTemplate, CK_ULONG ulCount);
            ///< initializes a search for token and session objects that match a template
        BOOL                 bFind             (CK_OBJECT_HANDLE_PTR phObject, CK_ULONG ulMaxObjectCount, CK_ULONG_PTR pulObjectCount);
            ///< continues a search for token and session objects that match a template, obtaining additional object handles
        BOOL                 bFindFinal        ();
            ///< finishes a search for token and session objects
    #endif
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxObjectH
