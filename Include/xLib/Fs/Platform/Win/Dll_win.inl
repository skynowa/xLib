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
void_t
Dll::_load_impl(
    std::ctstring_t &a_dllPath
)
{
    _handle = ::LoadLibrary(a_dllPath.c_str());
    xTEST_EQ(_handle.isValid(), true);
}
//-------------------------------------------------------------------------------------------------
bool_t
Dll::_isProcExists_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_EQ(_handle.isValid(), true);

    proc_address_t paRv = ::GetProcAddress(_handle.get(), xT2A(a_procName).c_str());
    xCHECK_RET(paRv == xPTR_NULL, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
Dll::proc_address_t
Dll::_procAddress_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST_EQ(_handle.isValid(), true);

    proc_address_t paRv = ::GetProcAddress(_handle.get(), xT2A(a_procName).c_str());
    xTEST_PTR(paRv);

    return paRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
