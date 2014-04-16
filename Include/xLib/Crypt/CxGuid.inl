/**
 * \file   CxGuid.cpp
 * \brief
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


xNAMESPACE2_BEGIN(xlib, crypt)

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
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    GUID    guid = {0};
    HRESULT hrGuid = S_FALSE;

    hrGuid = ::CoCreateGuid(&guid);
    xTEST_EQ(true, SUCCEEDED(hrGuid));

    sRv = CxString::format(xT("%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"), guid.Data1,
        guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    xTEST_EQ(sRv.empty(), false);
#elif xOS_ENV_UNIX
    uint_t timeNow = static_cast<uint_t>( std::time(xPTR_NULL) );
    std::srand(timeNow);

    sRv = CxString::format("%x%x-%x-%x-%x-%x%x%x",
        ::rand_r(&timeNow), ::rand_r(&timeNow),   // 64-bit Hex number
        ::rand_r(&timeNow),                       // 32-bit Hex number
        ((::rand_r(&timeNow) & 0x0fff) | 0x4000), // 32-bit Hex number of the form 4xxx (4 indicates the UUID version)
        ::rand_r(&timeNow) % 0x3fff + 0x8000,     // 32-bit Hex number in the range [0x8000, 0xbfff]
        ::rand_r(&timeNow), ::rand_r(&timeNow), ::rand_r(&timeNow)); // 96-bit Hex number
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, crypt)
