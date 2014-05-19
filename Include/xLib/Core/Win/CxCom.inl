/**
 * \file  CxCom.inl
 * \brief Component Object Model (COM)
 */


#if xCOMPILER_MINGW
    // lib: -lole32
#endif


#if xENV_WIN

xNAMESPACE_BEGIN2(xlib, core)

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

    HRESULT hrRv = ::CoInitializeEx(xPTR_NULL, a_concurrencyModel);
    xTEST_EQ(SUCCEEDED(hrRv), true);
}
//-------------------------------------------------------------------------------------------------
inline
CxCom::~CxCom()
{
    (void_t)::CoUninitialize();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)

#endif
