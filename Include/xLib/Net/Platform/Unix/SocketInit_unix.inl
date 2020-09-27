/**
 * \file  SocketInit.inl
 * \brief initiates use of the Winsock DLL by a process
 */


namespace xl::net
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
SocketInit::_construct_impl(
    cushort_t a_versionMajor,
    cushort_t a_versionMinor
) const
{
    xUNUSED(a_versionMajor);
    xUNUSED(a_versionMinor);
}
//-------------------------------------------------------------------------------------------------
void_t
SocketInit::_destruct_impl() const
{
    xNA;
}
//-------------------------------------------------------------------------------------------------

} // namespace
