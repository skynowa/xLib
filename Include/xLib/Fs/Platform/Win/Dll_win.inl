/**
 * \file  Dll.inl
 * \brief dynamic linking loader
 */


namespace xl::fs
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Dll::_load_impl()
{
    _handle = ::LoadLibrary(_dllPath.c_str());
    xTEST(_handle.isValid());
}
//-------------------------------------------------------------------------------------------------
bool_t
Dll::_isProcExists_impl(
    std::ctstring_t &a_procName
) const
{
	xTEST(_handle.isValid());

    proc_address_t paRv = ::GetProcAddress(_handle.get(), xT2A(a_procName).c_str());
    xCHECK_RET(paRv == nullptr, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
Dll::proc_address_t
Dll::_procAddress_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST(_handle.isValid());

    proc_address_t paRv = ::GetProcAddress(_handle.get(), xT2A(a_procName).c_str());
    xTEST_PTR(paRv);

    return paRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
