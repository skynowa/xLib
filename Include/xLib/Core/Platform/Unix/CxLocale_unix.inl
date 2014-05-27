/**
 * \file  CxLocale.inl
 * \brief locale
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxLocale::_current_impl() const
{
    // n/a

    std::tstring_t sRv;

    ctchar_t *locale = xTSETLOCALE(LC_ALL, xPTR_NULL);
    xTEST_PTR(locale);

    sRv.assign(locale);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
