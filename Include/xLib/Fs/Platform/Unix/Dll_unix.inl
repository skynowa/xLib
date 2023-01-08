/**
 * \file  Dll.inl
 * \brief dynamic linking loader (lib: -ldl, -lc (FreeBSD)
 */


namespace xl::fs
{

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
    xTEST_MSG(_handle.isValid(), NativeError::format());
}
//-------------------------------------------------------------------------------------------------
bool_t
Dll::_isProcExists_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST(_handle.isValid());

    const char *error {};

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    (void_t)::dlsym(_handle.get(), xT2A(a_procName).c_str());

    error = ::dlerror();
    xCHECK_RET(error != nullptr, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
Dll::proc_address_t
Dll::_procAddress_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_EQ(_handle.isValid(), true);

    const char *error {};

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    proc_address_t paRv = ::dlsym(_handle.get(), xT2A(a_procName).c_str());
    xTEST_NA(paRv);

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    return paRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
