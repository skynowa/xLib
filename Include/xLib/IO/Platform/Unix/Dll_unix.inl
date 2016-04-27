/**
 * \file  Dll.inl
 * \brief dynamic linking loader (lib: -ldl, -lc (FreeBSD)
 */


xNAMESPACE_BEGIN2(xlib, io)

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
    _handle = ::dlopen(xTS2S(a_dllPath).c_str(), RTLD_LAZY | RTLD_GLOBAL);
    xTEST_PTR(_handle);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Dll::_isProcExists_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_handle);

    const char *error = xPTR_NULL;

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    (void_t)::dlsym(_handle, xTS2S(a_procName).c_str());

    error = ::dlerror();
    xCHECK_RET(error != xPTR_NULL, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE Dll::proc_address_t
Dll::_procAddress_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_handle);

    const char *error = xPTR_NULL;

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    proc_address_t paRv = ::dlsym(_handle, xTS2S(a_procName).c_str());
    xTEST_NA(paRv)

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

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
    int_t iRv = ::dlclose(_handle);    _handle = xPTR_NULL;
    xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
