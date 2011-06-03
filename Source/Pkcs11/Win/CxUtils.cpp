/****************************************************************************
* Class name:  CxUtils
* Description: Pkcs11 utils
* File name:   CxUtils.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:15:59
*
*****************************************************************************/


#include <xLib/Pkcs11/CxUtils.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//--------------------------------------------------------------------------
//TODO: CxUtils::sErrorStr (get error string by code, SDK 4.53)
/*static*/
tString
CxUtils::sErrorStr(
    CK_RV ulCode
)
{
    /*DEBUG*/// ulCode - n/a

    tString sRes;

    switch (ulCode) {
        case CKR_OK:                               sRes.assign(xT("CKR_OK"));
        case CKR_CANCEL:                           sRes.assign(xT("CKR_CANCEL"));
        case CKR_HOST_MEMORY:                      sRes.assign(xT("CKR_HOST_MEMORY"));
        case CKR_SLOT_ID_INVALID:                  sRes.assign(xT("CKR_SLOT_ID_INVALID"));
        case CKR_GENERAL_ERROR:                    sRes.assign(xT("CKR_GENERAL_ERROR"));
        case CKR_FUNCTION_FAILED:                  sRes.assign(xT("CKR_FUNCTION_FAILED"));
        case CKR_ARGUMENTS_BAD:                    sRes.assign(xT("CKR_ARGUMENTS_BAD"));
        case CKR_NO_EVENT:                         sRes.assign(xT("CKR_NO_EVENT"));
        case CKR_NEED_TO_CREATE_THREADS:           sRes.assign(xT("CKR_NEED_TO_CREATE_THREADS"));
        case CKR_CANT_LOCK:                        sRes.assign(xT("CKR_CANT_LOCK"));
        case CKR_ATTRIBUTE_READ_ONLY:              sRes.assign(xT("CKR_ATTRIBUTE_READ_ONLY"));
        case CKR_ATTRIBUTE_SENSITIVE:              sRes.assign(xT("CKR_ATTRIBUTE_SENSITIVE"));
        case CKR_ATTRIBUTE_TYPE_INVALID:           sRes.assign(xT("CKR_ATTRIBUTE_TYPE_INVALID"));
        case CKR_ATTRIBUTE_VALUE_INVALID:          sRes.assign(xT("CKR_ATTRIBUTE_VALUE_INVALID"));
        case CKR_DATA_INVALID:                     sRes.assign(xT("CKR_DATA_INVALID"));
        case CKR_DATA_LEN_RANGE:                   sRes.assign(xT("CKR_DATA_LEN_RANGE"));
        case CKR_DEVICE_ERROR:                     sRes.assign(xT("CKR_DEVICE_ERROR"));
        case CKR_DEVICE_MEMORY:                    sRes.assign(xT("CKR_DEVICE_MEMORY"));
        case CKR_DEVICE_REMOVED:                   sRes.assign(xT("CKR_DEVICE_REMOVED"));
        case CKR_ENCRYPTED_DATA_INVALID:           sRes.assign(xT("CKR_ENCRYPTED_DATA_INVALID"));
        case CKR_ENCRYPTED_DATA_LEN_RANGE:         sRes.assign(xT("CKR_ENCRYPTED_DATA_LEN_RANGE"));
        case CKR_FUNCTION_CANCELED:                sRes.assign(xT("CKR_FUNCTION_CANCELED"));
        case CKR_FUNCTION_NOT_PARALLEL:            sRes.assign(xT("CKR_FUNCTION_NOT_PARALLEL"));
        case CKR_FUNCTION_NOT_SUPPORTED:           sRes.assign(xT("CKR_FUNCTION_NOT_SUPPORTED"));
        case CKR_KEY_HANDLE_INVALID:               sRes.assign(xT("CKR_KEY_HANDLE_INVALID"));
        case CKR_KEY_SIZE_RANGE:                   sRes.assign(xT("CKR_KEY_SIZE_RANGE"));
        case CKR_KEY_TYPE_INCONSISTENT:            sRes.assign(xT("CKR_KEY_TYPE_INCONSISTENT"));
        case CKR_KEY_NOT_NEEDED:                   sRes.assign(xT("CKR_KEY_NOT_NEEDED"));
        case CKR_KEY_CHANGED:                      sRes.assign(xT("CKR_KEY_CHANGED"));
        case CKR_KEY_NEEDED:                       sRes.assign(xT("CKR_KEY_NEEDED"));
        case CKR_KEY_INDIGESTIBLE:                 sRes.assign(xT("CKR_KEY_INDIGESTIBLE"));
        case CKR_KEY_FUNCTION_NOT_PERMITTED:       sRes.assign(xT("CKR_KEY_FUNCTION_NOT_PERMITTED"));
        case CKR_KEY_NOT_WRAPPABLE:                sRes.assign(xT("CKR_KEY_NOT_WRAPPABLE"));
        case CKR_KEY_UNEXTRACTABLE:                sRes.assign(xT("CKR_KEY_UNEXTRACTABLE"));
        case CKR_MECHANISM_INVALID:                sRes.assign(xT("CKR_MECHANISM_INVALID"));
        case CKR_MECHANISM_PARAM_INVALID:          sRes.assign(xT("CKR_MECHANISM_PARAM_INVALID"));
        case CKR_OBJECT_HANDLE_INVALID:            sRes.assign(xT("CKR_OBJECT_HANDLE_INVALID"));
        case CKR_OPERATION_ACTIVE:                 sRes.assign(xT("CKR_OPERATION_ACTIVE"));
        case CKR_OPERATION_NOT_INITIALIZED:        sRes.assign(xT("CKR_OPERATION_NOT_INITIALIZED"));
        case CKR_PIN_INCORRECT:                    sRes.assign(xT("CKR_PIN_INCORRECT"));
        case CKR_PIN_INVALID:                      sRes.assign(xT("CKR_PIN_INVALID"));
        case CKR_PIN_LEN_RANGE:                    sRes.assign(xT("CKR_PIN_LEN_RANGE"));
        case CKR_PIN_EXPIRED:                      sRes.assign(xT("CKR_PIN_EXPIRED"));
        case CKR_PIN_LOCKED:                       sRes.assign(xT("CKR_PIN_LOCKED"));
        case CKR_SESSION_CLOSED:                   sRes.assign(xT("CKR_SESSION_CLOSED"));
        case CKR_SESSION_COUNT:                    sRes.assign(xT("CKR_SESSION_COUNT"));
        case CKR_SESSION_HANDLE_INVALID:           sRes.assign(xT("CKR_SESSION_HANDLE_INVALID"));
        case CKR_SESSION_PARALLEL_NOT_SUPPORTED:   sRes.assign(xT("CKR_SESSION_PARALLEL_NOT_SUPPORTED"));
        case CKR_SESSION_READ_ONLY:                sRes.assign(xT("CKR_SESSION_READ_ONLY"));
        case CKR_SESSION_EXISTS:                   sRes.assign(xT("CKR_SESSION_EXISTS"));
        case CKR_SESSION_READ_ONLY_EXISTS:         sRes.assign(xT("CKR_SESSION_READ_ONLY_EXISTS"));
        case CKR_SESSION_READ_WRITE_SO_EXISTS:     sRes.assign(xT("CKR_SESSION_READ_WRITE_SO_EXISTS"));
        case CKR_SIGNATURE_INVALID:                sRes.assign(xT("CKR_SIGNATURE_INVALID"));
        case CKR_SIGNATURE_LEN_RANGE:              sRes.assign(xT("CKR_SIGNATURE_LEN_RANGE"));
        case CKR_TEMPLATE_INCOMPLETE:              sRes.assign(xT("CKR_TEMPLATE_INCOMPLETE"));
        case CKR_TEMPLATE_INCONSISTENT:            sRes.assign(xT("CKR_TEMPLATE_INCONSISTENT"));
        case CKR_TOKEN_NOT_PRESENT:                sRes.assign(xT("CKR_TOKEN_NOT_PRESENT"));
        case CKR_TOKEN_NOT_RECOGNIZED:             sRes.assign(xT("CKR_TOKEN_NOT_RECOGNIZED"));
        case CKR_TOKEN_WRITE_PROTECTED:            sRes.assign(xT("CKR_TOKEN_WRITE_PROTECTED"));
        case CKR_UNWRAPPING_KEY_HANDLE_INVALID:    sRes.assign(xT("CKR_UNWRAPPING_KEY_HANDLE_INVALID"));
        case CKR_UNWRAPPING_KEY_SIZE_RANGE:        sRes.assign(xT("CKR_UNWRAPPING_KEY_SIZE_RANGE"));
        case CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT: sRes.assign(xT("CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT"));
        case CKR_USER_ALREADY_LOGGED_IN:           sRes.assign(xT("CKR_USER_ALREADY_LOGGED_IN"));
        case CKR_USER_NOT_LOGGED_IN:               sRes.assign(xT("CKR_USER_NOT_LOGGED_IN"));
        case CKR_USER_PIN_NOT_INITIALIZED:         sRes.assign(xT("CKR_USER_PIN_NOT_INITIALIZED"));
        case CKR_USER_TYPE_INVALID:                sRes.assign(xT("CKR_USER_TYPE_INVALID"));
        case CKR_USER_ANOTHER_ALREADY_LOGGED_IN:   sRes.assign(xT("CKR_USER_ANOTHER_ALREADY_LOGGED_IN"));
        case CKR_USER_TOO_MANY_TYPES:              sRes.assign(xT("CKR_USER_TOO_MANY_TYPES"));
        case CKR_WRAPPED_KEY_INVALID:              sRes.assign(xT("CKR_WRAPPED_KEY_INVALID"));
        case CKR_WRAPPED_KEY_LEN_RANGE:            sRes.assign(xT("CKR_WRAPPED_KEY_LEN_RANGE"));
        case CKR_WRAPPING_KEY_HANDLE_INVALID:      sRes.assign(xT("CKR_WRAPPING_KEY_HANDLE_INVALID"));
        case CKR_WRAPPING_KEY_SIZE_RANGE:          sRes.assign(xT("CKR_WRAPPING_KEY_SIZE_RANGE"));
        case CKR_WRAPPING_KEY_TYPE_INCONSISTENT:   sRes.assign(xT("CKR_WRAPPING_KEY_TYPE_INCONSISTENT"));
        case CKR_RANDOM_SEED_NOT_SUPPORTED:        sRes.assign(xT("CKR_RANDOM_SEED_NOT_SUPPORTED"));
        case CKR_RANDOM_NO_RNG:                    sRes.assign(xT("CKR_RANDOM_NO_RNG"));
        case CKR_DOMAIN_PARAMS_INVALID:            sRes.assign(xT("CKR_DOMAIN_PARAMS_INVALID"));        /*new SDK 4.53*/
        case CKR_BUFFER_TOO_SMALL:                 sRes.assign(xT("CKR_BUFFER_TOO_SMALL"));
        case CKR_SAVED_STATE_INVALID:              sRes.assign(xT("CKR_SAVED_STATE_INVALID"));
        case CKR_INFORMATION_SENSITIVE:            sRes.assign(xT("CKR_INFORMATION_SENSITIVE"));
        case CKR_STATE_UNSAVEABLE:                 sRes.assign(xT("CKR_STATE_UNSAVEABLE"));
        case CKR_CRYPTOKI_NOT_INITIALIZED:         sRes.assign(xT("CKR_CRYPTOKI_NOT_INITIALIZED"));
        case CKR_CRYPTOKI_ALREADY_INITIALIZED:     sRes.assign(xT("CKR_CRYPTOKI_ALREADY_INITIALIZED"));
        case CKR_MUTEX_BAD:                        sRes.assign(xT("CKR_MUTEX_BAD"));
        case CKR_MUTEX_NOT_LOCKED:                 sRes.assign(xT("CKR_MUTEX_NOT_LOCKED"));
        case CKR_FUNCTION_REJECTED:                sRes.assign(xT("CKR_FUNCTION_REJECTED"));            /*new SDK 4.53*/
        case CKR_VENDOR_DEFINED:                   sRes.assign(xT("CKR_VENDOR_DEFINED"));
        case CKR_SAPI_OBJECT_DOES_NOT_EXIST:       sRes.assign(xT("CKR_SAPI_OBJECT_DOES_NOT_EXIST"));   /*new SDK 4.53*/
        case CKR_SAPI_OBJECT_ALREADY_EXISTS:       sRes.assign(xT("CKR_SAPI_OBJECT_ALREADY_EXISTS"));   /*new SDK 4.53*/
        case CKR_SAPI_NOT_SUPPORTED_BY_TOKEN:      sRes.assign(xT("CKR_SAPI_NOT_SUPPORTED_BY_TOKEN"));  /*new SDK 4.53*/
        case CKR_SAPI_PIN_QUALITY:                 sRes.assign(xT("CKR_SAPI_PIN_QUALITY"));             /*new SDK 4.53*/
        case CKR_SAPI_PIN_DEFAULT:                 sRes.assign(xT("CKR_SAPI_PIN_DEFAULT"));             /*new SDK 4.53*/
        case CKR_SAPI_PIN_EXPIRATION:              sRes.assign(xT("CKR_SAPI_PIN_EXPIRATION"));          /*new SDK 4.53*/
        case CKR_SAPI_PIN_CHANGE_NOT_ALLOWED:      sRes.assign(xT("CKR_SAPI_PIN_CHANGE_NOT_ALLOWED"));  /*new SDK 4.53*/
        case CKR_SAPI_CANCELLED:                   sRes.assign(xT("CKR_SAPI_CANCELLED"));               /*new SDK 4.53*/
        case CKR_NEW_PIN_MODE:                     sRes.assign(xT("CKR_NEW_PIN_MODE"));                 /*new SDK 4.53*/
        case CKR_NEXT_OTP:                         sRes.assign(xT("CKR_NEXT_OTP"));                     /*new SDK 4.53*/

        default:                                   sRes.assign(xT("CKR_UNKNOWN_ERROR"));
    }

    return sRes;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxUtils ()
CxUtils::CxUtils() {

}
//---------------------------------------------------------------------------
//TODO: ~CxUtils ()
/*virtual*/
CxUtils::~CxUtils() {

}
//---------------------------------------------------------------------------
