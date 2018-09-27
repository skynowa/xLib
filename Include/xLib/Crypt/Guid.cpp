/**
 * \file   Guid.cpp
 * \brief  GUID (globally unique identifier)
 */


#include "Guid.h"

#include <xLib/Test/Test.h>
#include <xLib/Core/Format.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/Guid_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Guid_unix.inl"

    #if   xENV_LINUX

    #elif xENV_BSD

    #elif xENV_APPLE

    #endif
#endif


xNAMESPACE_BEGIN2(xl, crypt)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Guid::create(
    cType a_type
) const
{
    std::tstring_t sRv;

    switch (a_type) {
    case Type::tpRandomBased:
        sRv = _randomBased_impl();
        break;
    case Type::tpUnknown:
    default:
        xTEST_FAIL;
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, crypt)
