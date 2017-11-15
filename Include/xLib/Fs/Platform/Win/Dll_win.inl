/**
 * \file  Dll.inl
 * \brief dynamic linking loader
 */


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dll::_load_impl(
    std::ctstring_t &a_dllPath
)
{
    _handle = ::LoadLibrary(a_dllPath.c_str());
    xTEST_PTR(_handle);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Dll::_isProcExists_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_handle);

    proc_address_t paRv = ::GetProcAddress(_handle, xT2A(a_procName).c_str());
    xCHECK_RET(paRv == xPTR_NULL, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE Dll::proc_address_t
Dll::_procAddress_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_handle);

    proc_address_t paRv = ::GetProcAddress(_handle, xT2A(a_procName).c_str());
    xTEST_PTR(paRv);

    return paRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dll::_destruct_impl()
{
    BOOL blRv = ::FreeLibrary(_handle);    _handle = xPTR_NULL;
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
