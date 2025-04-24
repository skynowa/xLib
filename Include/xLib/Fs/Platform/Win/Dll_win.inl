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
Dll::symbol_address_t
Dll::_symbolAddress_impl(
    std::ctstring_t &a_procName
) const
{
    xTEST(_handle.isValid());

    symbol_address_t paRv = ::GetProcAddress(_handle.get(), xT2A(a_procName).c_str());
    xTEST_PTR(paRv);

    return paRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
