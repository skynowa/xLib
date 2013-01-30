/**
 * \file  CxPkcs11.cpp
 * \brief Aladdin eToken, PKCS #11
 */


#include <xLib/Crypt/Pkcs11/CxPkcs11.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxPkcs11::CxPkcs11() :
    _m_pFunc      (NULL),
    _m_dllETPkcs11()
{
    xTEST_PTR(_m_pFunc);
    // _m_dllETPkcs11 - n/a

    _loadETPkcs11();
    _initialize();
}
//---------------------------------------------------------------------------
/* virtual */
CxPkcs11::~CxPkcs11() {
    _finalize();
}
//---------------------------------------------------------------------------
CK_FUNCTION_LIST_PTR
CxPkcs11::funcList() const {
    xTEST_PTR(_m_pFunc);

    return _m_pFunc;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxPkcs11::errorStr(
    const CK_RV a_culCode
)
{
    // culCode - n/a

    std::tstring_t sRv;

    switch (a_culCode) {
        case CKR_OK:                               sRv = xT("CKR_OK"); break;
        case CKR_CANCEL:                           sRv = xT("CKR_CANCEL"); break;
        case CKR_HOST_MEMORY:                      sRv = xT("CKR_HOST_MEMORY"); break;
        case CKR_SLOT_ID_INVALID:                  sRv = xT("CKR_SLOT_ID_INVALID"); break;
        case CKR_GENERAL_ERROR:                    sRv = xT("CKR_GENERAL_ERROR"); break;
        case CKR_FUNCTION_FAILED:                  sRv = xT("CKR_FUNCTION_FAILED"); break;
        case CKR_ARGUMENTS_BAD:                    sRv = xT("CKR_ARGUMENTS_BAD"); break;
        case CKR_NO_EVENT:                         sRv = xT("CKR_NO_EVENT"); break;
        case CKR_NEED_TO_CREATE_THREADS:           sRv = xT("CKR_NEED_TO_CREATE_THREADS"); break;
        case CKR_CANT_LOCK:                        sRv = xT("CKR_CANT_LOCK"); break;
        case CKR_ATTRIBUTE_READ_ONLY:              sRv = xT("CKR_ATTRIBUTE_READ_ONLY"); break;
        case CKR_ATTRIBUTE_SENSITIVE:              sRv = xT("CKR_ATTRIBUTE_SENSITIVE"); break;
        case CKR_ATTRIBUTE_TYPE_INVALID:           sRv = xT("CKR_ATTRIBUTE_TYPE_INVALID"); break;
        case CKR_ATTRIBUTE_VALUE_INVALID:          sRv = xT("CKR_ATTRIBUTE_VALUE_INVALID"); break;
        case CKR_DATA_INVALID:                     sRv = xT("CKR_DATA_INVALID"); break;
        case CKR_DATA_LEN_RANGE:                   sRv = xT("CKR_DATA_LEN_RANGE"); break;
        case CKR_DEVICE_ERROR:                     sRv = xT("CKR_DEVICE_ERROR"); break;
        case CKR_DEVICE_MEMORY:                    sRv = xT("CKR_DEVICE_MEMORY"); break;
        case CKR_DEVICE_REMOVED:                   sRv = xT("CKR_DEVICE_REMOVED"); break;
        case CKR_ENCRYPTED_DATA_INVALID:           sRv = xT("CKR_ENCRYPTED_DATA_INVALID"); break;
        case CKR_ENCRYPTED_DATA_LEN_RANGE:         sRv = xT("CKR_ENCRYPTED_DATA_LEN_RANGE"); break;
        case CKR_FUNCTION_CANCELED:                sRv = xT("CKR_FUNCTION_CANCELED"); break;
        case CKR_FUNCTION_NOT_PARALLEL:            sRv = xT("CKR_FUNCTION_NOT_PARALLEL"); break;
        case CKR_FUNCTION_NOT_SUPPORTED:           sRv = xT("CKR_FUNCTION_NOT_SUPPORTED"); break;
        case CKR_KEY_HANDLE_INVALID:               sRv = xT("CKR_KEY_HANDLE_INVALID"); break;
        case CKR_KEY_SIZE_RANGE:                   sRv = xT("CKR_KEY_SIZE_RANGE"); break;
        case CKR_KEY_TYPE_INCONSISTENT:            sRv = xT("CKR_KEY_TYPE_INCONSISTENT"); break;
        case CKR_KEY_NOT_NEEDED:                   sRv = xT("CKR_KEY_NOT_NEEDED"); break;
        case CKR_KEY_CHANGED:                      sRv = xT("CKR_KEY_CHANGED"); break;
        case CKR_KEY_NEEDED:                       sRv = xT("CKR_KEY_NEEDED"); break;
        case CKR_KEY_INDIGESTIBLE:                 sRv = xT("CKR_KEY_INDIGESTIBLE"); break;
        case CKR_KEY_FUNCTION_NOT_PERMITTED:       sRv = xT("CKR_KEY_FUNCTION_NOT_PERMITTED"); break;
        case CKR_KEY_NOT_WRAPPABLE:                sRv = xT("CKR_KEY_NOT_WRAPPABLE"); break;
        case CKR_KEY_UNEXTRACTABLE:                sRv = xT("CKR_KEY_UNEXTRACTABLE"); break;
        case CKR_MECHANISM_INVALID:                sRv = xT("CKR_MECHANISM_INVALID"); break;
        case CKR_MECHANISM_PARAM_INVALID:          sRv = xT("CKR_MECHANISM_PARAM_INVALID"); break;
        case CKR_OBJECT_HANDLE_INVALID:            sRv = xT("CKR_OBJECT_HANDLE_INVALID"); break;
        case CKR_OPERATION_ACTIVE:                 sRv = xT("CKR_OPERATION_ACTIVE"); break;
        case CKR_OPERATION_NOT_INITIALIZED:        sRv = xT("CKR_OPERATION_NOT_INITIALIZED"); break;
        case CKR_PIN_INCORRECT:                    sRv = xT("CKR_PIN_INCORRECT"); break;
        case CKR_PIN_INVALID:                      sRv = xT("CKR_PIN_INVALID"); break;
        case CKR_PIN_LEN_RANGE:                    sRv = xT("CKR_PIN_LEN_RANGE"); break;
        case CKR_PIN_EXPIRED:                      sRv = xT("CKR_PIN_EXPIRED"); break;
        case CKR_PIN_LOCKED:                       sRv = xT("CKR_PIN_LOCKED"); break;
        case CKR_SESSION_CLOSED:                   sRv = xT("CKR_SESSION_CLOSED"); break;
        case CKR_SESSION_COUNT:                    sRv = xT("CKR_SESSION_COUNT"); break;
        case CKR_SESSION_HANDLE_INVALID:           sRv = xT("CKR_SESSION_HANDLE_INVALID"); break;
        case CKR_SESSION_PARALLEL_NOT_SUPPORTED:   sRv = xT("CKR_SESSION_PARALLEL_NOT_SUPPORTED"); break;
        case CKR_SESSION_READ_ONLY:                sRv = xT("CKR_SESSION_READ_ONLY"); break;
        case CKR_SESSION_EXISTS:                   sRv = xT("CKR_SESSION_EXISTS"); break;
        case CKR_SESSION_READ_ONLY_EXISTS:         sRv = xT("CKR_SESSION_READ_ONLY_EXISTS"); break;
        case CKR_SESSION_READ_WRITE_SO_EXISTS:     sRv = xT("CKR_SESSION_READ_WRITE_SO_EXISTS"); break;
        case CKR_SIGNATURE_INVALID:                sRv = xT("CKR_SIGNATURE_INVALID"); break;
        case CKR_SIGNATURE_LEN_RANGE:              sRv = xT("CKR_SIGNATURE_LEN_RANGE"); break;
        case CKR_TEMPLATE_INCOMPLETE:              sRv = xT("CKR_TEMPLATE_INCOMPLETE"); break;
        case CKR_TEMPLATE_INCONSISTENT:            sRv = xT("CKR_TEMPLATE_INCONSISTENT"); break;
        case CKR_TOKEN_NOT_PRESENT:                sRv = xT("CKR_TOKEN_NOT_PRESENT"); break;
        case CKR_TOKEN_NOT_RECOGNIZED:             sRv = xT("CKR_TOKEN_NOT_RECOGNIZED"); break;
        case CKR_TOKEN_WRITE_PROTECTED:            sRv = xT("CKR_TOKEN_WRITE_PROTECTED"); break;
        case CKR_UNWRAPPING_KEY_HANDLE_INVALID:    sRv = xT("CKR_UNWRAPPING_KEY_HANDLE_INVALID"); break;
        case CKR_UNWRAPPING_KEY_SIZE_RANGE:        sRv = xT("CKR_UNWRAPPING_KEY_SIZE_RANGE"); break;
        case CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT: sRv = xT("CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT"); break;
        case CKR_USER_ALREADY_LOGGED_IN:           sRv = xT("CKR_USER_ALREADY_LOGGED_IN"); break;
        case CKR_USER_NOT_LOGGED_IN:               sRv = xT("CKR_USER_NOT_LOGGED_IN"); break;
        case CKR_USER_PIN_NOT_INITIALIZED:         sRv = xT("CKR_USER_PIN_NOT_INITIALIZED"); break;
        case CKR_USER_TYPE_INVALID:                sRv = xT("CKR_USER_TYPE_INVALID"); break;
        case CKR_USER_ANOTHER_ALREADY_LOGGED_IN:   sRv = xT("CKR_USER_ANOTHER_ALREADY_LOGGED_IN"); break;
        case CKR_USER_TOO_MANY_TYPES:              sRv = xT("CKR_USER_TOO_MANY_TYPES"); break;
        case CKR_WRAPPED_KEY_INVALID:              sRv = xT("CKR_WRAPPED_KEY_INVALID"); break;
        case CKR_WRAPPED_KEY_LEN_RANGE:            sRv = xT("CKR_WRAPPED_KEY_LEN_RANGE"); break;
        case CKR_WRAPPING_KEY_HANDLE_INVALID:      sRv = xT("CKR_WRAPPING_KEY_HANDLE_INVALID"); break;
        case CKR_WRAPPING_KEY_SIZE_RANGE:          sRv = xT("CKR_WRAPPING_KEY_SIZE_RANGE"); break;
        case CKR_WRAPPING_KEY_TYPE_INCONSISTENT:   sRv = xT("CKR_WRAPPING_KEY_TYPE_INCONSISTENT"); break;
        case CKR_RANDOM_SEED_NOT_SUPPORTED:        sRv = xT("CKR_RANDOM_SEED_NOT_SUPPORTED"); break;
        case CKR_RANDOM_NO_RNG:                    sRv = xT("CKR_RANDOM_NO_RNG"); break;
        case CKR_DOMAIN_PARAMS_INVALID:            sRv = xT("CKR_DOMAIN_PARAMS_INVALID");  break;        /*new SDK 4.53*/
        case CKR_BUFFER_TOO_SMALL:                 sRv = xT("CKR_BUFFER_TOO_SMALL"); break;
        case CKR_SAVED_STATE_INVALID:              sRv = xT("CKR_SAVED_STATE_INVALID"); break;
        case CKR_INFORMATION_SENSITIVE:            sRv = xT("CKR_INFORMATION_SENSITIVE"); break;
        case CKR_STATE_UNSAVEABLE:                 sRv = xT("CKR_STATE_UNSAVEABLE"); break;
        case CKR_CRYPTOKI_NOT_INITIALIZED:         sRv = xT("CKR_CRYPTOKI_NOT_INITIALIZED"); break;
        case CKR_CRYPTOKI_ALREADY_INITIALIZED:     sRv = xT("CKR_CRYPTOKI_ALREADY_INITIALIZED"); break;
        case CKR_MUTEX_BAD:                        sRv = xT("CKR_MUTEX_BAD"); break;
        case CKR_MUTEX_NOT_LOCKED:                 sRv = xT("CKR_MUTEX_NOT_LOCKED"); break;
        case CKR_FUNCTION_REJECTED:                sRv = xT("CKR_FUNCTION_REJECTED"); break;           /*new SDK 4.53*/
        case CKR_VENDOR_DEFINED:                   sRv = xT("CKR_VENDOR_DEFINED"); break;
        case CKR_SAPI_OBJECT_DOES_NOT_EXIST:       sRv = xT("CKR_SAPI_OBJECT_DOES_NOT_EXIST"); break;   /*new SDK 4.53*/
        case CKR_SAPI_OBJECT_ALREADY_EXISTS:       sRv = xT("CKR_SAPI_OBJECT_ALREADY_EXISTS"); break;   /*new SDK 4.53*/
        case CKR_SAPI_NOT_SUPPORTED_BY_TOKEN:      sRv = xT("CKR_SAPI_NOT_SUPPORTED_BY_TOKEN"); break;  /*new SDK 4.53*/
        case CKR_SAPI_PIN_QUALITY:                 sRv = xT("CKR_SAPI_PIN_QUALITY"); break;             /*new SDK 4.53*/
        case CKR_SAPI_PIN_DEFAULT:                 sRv = xT("CKR_SAPI_PIN_DEFAULT"); break;             /*new SDK 4.53*/
        case CKR_SAPI_PIN_EXPIRATION:              sRv = xT("CKR_SAPI_PIN_EXPIRATION"); break;          /*new SDK 4.53*/
        case CKR_SAPI_PIN_CHANGE_NOT_ALLOWED:      sRv = xT("CKR_SAPI_PIN_CHANGE_NOT_ALLOWED"); break;  /*new SDK 4.53*/
        case CKR_SAPI_CANCELLED:                   sRv = xT("CKR_SAPI_CANCELLED"); break;               /*new SDK 4.53*/
        case CKR_NEW_PIN_MODE:                     sRv = xT("CKR_NEW_PIN_MODE"); break;                 /*new SDK 4.53*/
        case CKR_NEXT_OTP:                         sRv = xT("CKR_NEXT_OTP"); break;                     /*new SDK 4.53*/

        default:                                   sRv = xT("CKR_UNKNOWN_ERROR"); break;
    }

    return sRv;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxPkcs11::_loadETPkcs11() {
    _m_dllETPkcs11.load(xT("eTPkcs11.dll"));

    CK_C_GetFunctionList pFunctionList = NULL;

    (FARPROC &)pFunctionList = (FARPROC)_m_dllETPkcs11.procAddress(xT("C_GetFunctionList"));
    xTEST_PTR(pFunctionList);

    CK_RV ulRv = pFunctionList(&_m_pFunc);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
    xTEST_PTR(_m_pFunc);
}
//---------------------------------------------------------------------------
void
CxPkcs11::_initialize() {
    xTEST_PTR(_m_pFunc);

    CK_RV ulRv = _m_pFunc->C_Initialize(NULL_PTR);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxPkcs11::_finalize() {
    xTEST_PTR(_m_pFunc);

    CK_RV ulRv = _m_pFunc->C_Finalize(NULL_PTR);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
