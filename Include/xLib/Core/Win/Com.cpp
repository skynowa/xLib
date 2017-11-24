/**
 * \file  Com.inl
 * \brief Component Object Model (COM)
 */


#if xENV_WIN

#include "Com.h"

#if xCOMPILER_MINGW
    // lib: -lole32
#endif


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Com::Com(
    const COINIT &a_concurrencyModel
)
{
    xTEST_NA(a_concurrencyModel);

    HRESULT hrRv = ::CoInitializeEx(xPTR_NULL, a_concurrencyModel);
    xTEST_EQ(SUCCEEDED(hrRv), true);
}
//-------------------------------------------------------------------------------------------------
Com::~Com()
{
    (void_t)::CoUninitialize();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)

#endif
