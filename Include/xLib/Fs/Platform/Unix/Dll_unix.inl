/**
 * \file  Dll.inl
 * \brief dynamic linking loader (lib: -ldl, -lc (FreeBSD)
 */


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Dll::_load_impl(
    std::ctstring_t &a_dllPath
)
{
    _handle = ::dlopen(xT2A(a_dllPath).c_str(), RTLD_LAZY | RTLD_GLOBAL);
    xTEST_EQ_MSG(_handle.isValid(), true, StdError::format());
}
//-------------------------------------------------------------------------------------------------
bool_t
Dll::_isProcExists_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_EQ(_handle.isValid(), true);

    const char *error = xPTR_NULL;

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    (void_t)::dlsym(_handle.get(), xT2A(a_procName).c_str());

    error = ::dlerror();
    xCHECK_RET(error != xPTR_NULL, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
Dll::proc_address_t
Dll::_procAddress_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_EQ(_handle.isValid(), true);

    const char *error = xPTR_NULL;

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    proc_address_t paRv = ::dlsym(_handle.get(), xT2A(a_procName).c_str());
    xTEST_NA(paRv)

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    return paRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
