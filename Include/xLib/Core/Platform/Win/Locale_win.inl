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
std::tstring_t
Locale::_current_impl() const
{
    // n/a

    std::tstring_t sRv;

    int_t iRv  = - 1;
    LCID  id = 0;

    id = ::GetSystemDefaultLCID();
    // n/a

    //Retrieves information about a locale specified by identifier
    iRv = ::GetLocaleInfo(id, LOCALE_SENGLANGUAGE, 0, 0);
    xTEST_DIFF(iRv, 0);

    sRv.resize(iRv);
    iRv = ::GetLocaleInfo(id, LOCALE_SENGLANGUAGE, &sRv.at(0), static_cast<int_t>( sRv.size() ));
    xTEST_DIFF(iRv, 0);

    sRv.resize(iRv - sizeof('\0')); // delete from end '\0'

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
