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
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Pkcs11/Win/CxSession.h>
//---------------------------------------------------------------------------
class CxObject :
    public CxNonCopyable
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
        static BOOL          bGetData          (CK_SLOT_ID ulSlotId, const uString &cusUserPin, const uString &cusDataLabel, uString *pusData);
    		///< get data
        static BOOL          bSetData          (CK_SLOT_ID ulSlotId, const uString &cusUserPin, const uString &cusDataLabel, const uString &cusData);
    		///< set data
        static BOOL          bGetData          (CK_SLOT_ID ulSlotId, const uString &cusUserPin, std::vector<uString> *pusDataLabel, std::vector<uString> *pusDataValue);
    		///< get data

    private:
        BOOL                 _m_bRes;
        	///< for private use
        CK_RV                _m_ulRes;
        	///< for private use
        CK_FUNCTION_LIST_PTR _m_pFunc;
        	///< pointer to dll's functions list
        CK_SESSION_HANDLE    _m_hSession;
        	///< session handle
        CK_OBJECT_HANDLE     _m_hObject;
        	///< bject handle

	#if xTODO
		BOOL                 bFindInit         (CK_ATTRIBUTE_PTR  pTemplate, CK_ULONG ulCount);
			///< initializes a search for token and session objects that match a template
		BOOL                 bFind             (CK_OBJECT_HANDLE_PTR phObject, CK_ULONG ulMaxObjectCount, CK_ULONG_PTR pulObjectCount);
			///< continues a search for token and session objects that match a template, obtaining additional object handles
		BOOL                 bFindFinal        ();
			///< finishes a search for token and session objects
	#endif
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxObjectH
