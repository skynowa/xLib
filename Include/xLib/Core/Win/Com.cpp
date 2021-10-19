/**
 * \file  Com.inl
 * \brief Component Object Model (COM)
 */


#include "Com.h"

#if xENV_WIN

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Log/Trace.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Test/Test.h>

#if xCOMPILER_MINGW
    // lib: -lole32
#endif


namespace xl::core
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Com::Com(
    const COINIT a_concurrencyModel
)
{
    xTEST_NA(a_concurrencyModel);

    HRESULT hrRv = ::CoInitializeEx(nullptr, a_concurrencyModel);
    xTEST(SUCCEEDED(hrRv));
}
//-------------------------------------------------------------------------------------------------
Com::~Com()
{
    (void_t)::CoUninitialize();
}
//-------------------------------------------------------------------------------------------------

} // namespace

#endif
