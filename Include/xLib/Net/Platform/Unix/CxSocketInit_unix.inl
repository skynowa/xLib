/**
 * \file  CxSocketInit.inl
 * \brief initiates use of the Winsock DLL by a process
 */


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxSocketInit::_construct_impl(
    cushort_t &a_versionMajor,
    cushort_t &a_versionMinor
) const
{
    xUNUSED(a_versionMajor);
    xUNUSED(a_versionMinor);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxSocketInit::_destruct_impl() const
{
    xNA;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
