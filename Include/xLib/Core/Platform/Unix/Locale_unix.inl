/**
 * \file  Locale.inl
 * \brief locale
 */


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Locale::_current_impl() const
{
    // n/a

    std::tstring_t sRv;

    cptr_ctchar_t locale = xTSETLOCALE(LC_ALL, xPTR_NULL);
    xTEST_PTR(locale);

    sRv.assign(locale);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
