/**
 * \file  CxDll.inl
 * \brief dynamic linking loader
 */


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxDll::_load_impl(
    std::ctstring_t &a_dllPath
)
{
    _handle = ::LoadLibrary(a_dllPath.c_str());
    xTEST_PTR(_handle);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDll::_isProcExists_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_handle);

    proc_address_t paRv = ::GetProcAddress(_handle, xTS2S(a_procName).c_str());
    xCHECK_RET(paRv == xPTR_NULL, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline CxDll::proc_address_t
CxDll::_procAddress_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_handle);

    proc_address_t paRv = ::GetProcAddress(_handle, xTS2S(a_procName).c_str());
    xTEST_PTR(paRv);

    return paRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxDll::_destruct_impl()
{
    BOOL blRv = ::FreeLibrary(_handle);    _handle = xPTR_NULL;
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
