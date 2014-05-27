/**
 * \file   CxGuid.inl
 * \brief  GUID (globally unique identifier)
 */


#include <xLib/Crypt/CxGuid.h>

#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>

#if   xENV_WIN
    #include "Platform/Win/CxGuid_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxGuid_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxGuid_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxGuid_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, crypt)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxGuid::create(
    cExType &a_type
) const
{
    std::tstring_t sRv;

    switch (a_type) {
    case tpRandomBased:
        sRv = _randomBased();
        break;
    case tpUnknown:
    default:
        xTEST_FAIL;
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxGuid::_randomBased() const
{
    return _randomBased_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, crypt)
