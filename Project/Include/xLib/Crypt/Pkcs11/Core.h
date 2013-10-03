/**
 * \file  Core.h
 * \brief all SDK headers
 */


#define pragma once

#include <xLib/Core/xCore.h>

#if xOS_ENV_WIN
    #include "SDK/4.53/pkcs11.h"
    #include "SDK/4.53/eTSAPI.h"
    #include "SDK/4.53/otp-pkcs11.h"
#endif
