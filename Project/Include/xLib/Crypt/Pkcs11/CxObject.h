/**
 * \file  CxObject.h
 * \brief Pkcs11 object
 */


#ifndef xLib_Pkcs11_CxObjectH
#define xLib_Pkcs11_CxObjectH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Common.h>
//------------------------------------------------------------------------------
#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;
class CxSession;

class CxObject :
    private CxNonCopyable
    /// Pkcs11 object
{
public:
                         CxObject         (const CxPkcs11 &cPkcs11, const CxSession &cSession);
        ///< constructor
    virtual             ~CxObject         ();
        ///< destructor

    CK_OBJECT_HANDLE     handle           () const xWARN_UNUSED_RESULT;
        ///< get handle
    void                 setHandle        (CK_OBJECT_HANDLE hHandle);
        ///< assign object handle
    void                 create           (CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount);
        ///< creates a new object
    void                 size             (CK_ULONG_PTR pulSize);
        ///< gets the size of an object in bytes
    void                 copy             (CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount, CK_OBJECT_HANDLE_PTR phNewObject);
        ///< copies an object, creating a new object for the copy
    void                 find             (CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount, std::vector<CK_OBJECT_HANDLE> *pvecObjectHandles);
        ///< search for token and session objects that match a template, obtaining additional object handles

    void                 attributeValue   (CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount);
        ///< obtains the value of one or more object attributes
    void                 setAttributeValue(CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount);
        ///< modifies the value of one or more object attributes

    void                 destroy          ();
        ///< destroys an object

    // Utils
    static void          data             (CK_SLOT_ID ulSlotId, const std::ustring_t &cusUserPin, const std::ustring_t &cusDataLabel, std::ustring_t *pusData);
        ///< get data
    static void          setData          (CK_SLOT_ID ulSlotId, const std::ustring_t &cusUserPin, const std::ustring_t &cusDataLabel, const std::ustring_t &cusData);
        ///< set data
    static void          data             (CK_SLOT_ID ulSlotId, const std::ustring_t &cusUserPin, std::vec_ustring_t *pusDataLabel, std::vec_ustring_t *pusDataValue);
        ///< get data

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;      ///< pointer to dll functions list
    CK_SESSION_HANDLE    _m_hSession;   ///< session handle
    CK_OBJECT_HANDLE     _m_hObject;    ///< object handle

    // TODO: bFindInit, bFind, bFindFinal
#if xTODO
    bool                 bFindInit         (CK_ATTRIBUTE_PTR  pTemplate, CK_ULONG ulCount);
        ///< initializes a search for token and session objects that match a template
    bool                 bFind             (CK_OBJECT_HANDLE_PTR phObject, CK_ULONG ulMaxObjectCount, CK_ULONG_PTR pulObjectCount);
        ///< continues a search for token and session objects that match a template, obtaining additional object handles
    bool                 bFindFinal        ();
        ///< finishes a search for token and session objects
#endif
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#endif // xLib_Pkcs11_CxObjectH
