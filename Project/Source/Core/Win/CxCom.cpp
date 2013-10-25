/**
 * \file  CxCom.cpp
 * \brief COM
 */


#include <xLib/Core/Win/CxCom.h>

#if xCOMPILER_MINGW
    // lib: -lole32
#endif


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxCom::CxCom(
    const COINIT &a_concurrencyModel
)
{
    xTEST_NA(a_concurrencyModel);

    HRESULT hrRv = ::CoInitializeEx(NULL, a_concurrencyModel);
    xTEST_EQ(true, SUCCEEDED(hrRv));
}
//------------------------------------------------------------------------------
xINLINE_HO
CxCom::~CxCom()
{
    (void_t)::CoUninitialize();
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
