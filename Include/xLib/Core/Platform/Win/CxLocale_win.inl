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

xNAMESPACE_END2(xlib, core)
