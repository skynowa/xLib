/**
 * \file  Locale.inl
 * \brief locale
 */


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>


namespace xl::core
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Locale::_current_impl() const
{
    // n/a

    std::tstring_t sRv;

    cptr_ctchar_t locale = xTSETLOCALE(LC_ALL, nullptr);
    xTEST_PTR(locale);

    sRv.assign(locale);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
