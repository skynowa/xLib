/**
 * \file  Com.inl
 * \brief Component Object Model (COM)
 */


#if xENV_WIN

#include "Com.h"

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
