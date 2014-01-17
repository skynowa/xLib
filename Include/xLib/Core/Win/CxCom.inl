/**
 * \file  CxCom.cpp
 * \brief COM
 */


#if xCOMPILER_MINGW
    // lib: -lole32
#endif


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(xlib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxCom::CxCom(
    const COINIT &a_concurrencyModel
)
{
    xTEST_NA(a_concurrencyModel);

    HRESULT hrRv = ::CoInitializeEx(NULL, a_concurrencyModel);
    xTEST_EQ(true, SUCCEEDED(hrRv));
}
//-------------------------------------------------------------------------------------------------
inline
CxCom::~CxCom()
{
    (void_t)::CoUninitialize();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(xlib)

#endif
