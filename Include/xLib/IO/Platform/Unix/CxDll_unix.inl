/**
 * \file  CxDll.inl
 * \brief dynamic linking loader (lib: -ldl, -lc (FreeBSD)
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
    _handle = ::dlopen(a_dllPath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    xTEST_PTR(_handle);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDll::_isProcExists_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_handle);

    const char *error = xPTR_NULL;

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    (void_t)::dlsym(_handle, a_procName.c_str());

    error = ::dlerror();
    xCHECK_RET(error != xPTR_NULL, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline CxDll::proc_address_t
CxDll::_procAddress_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_handle);

    const char *error = xPTR_NULL;

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    proc_address_t paRv = ::dlsym(_handle, a_procName.c_str());
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
inline void_t
CxDll::_destruct_impl()
{
    int_t iRv = ::dlclose(_handle);    _handle = xPTR_NULL;
    xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
