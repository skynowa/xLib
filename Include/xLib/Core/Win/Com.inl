/**
 * \file  Com.inl
 * \brief Component Object Model (COM)
 */


#if !xOPTION_HEADER_ONLY
    #include "Com.inl"
#endif

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
Com::Com(
    const COINIT &a_concurrencyModel
)
{
    xTEST_NA(a_concurrencyModel);

    HRESULT hrRv = ::CoInitializeEx(xPTR_NULL, a_concurrencyModel);
    xTEST_EQ(SUCCEEDED(hrRv), true);
}
//-------------------------------------------------------------------------------------------------
inline
Com::~Com()
{
    (void_t)::CoUninitialize();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)

#endif
