/**
 * \file  Host.inl
 * \brief system information
 *
 * \see   https://www.kernel.org/doc/Documentation/ABI/testing/sysfs-class-net
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
std::tstring_t
Host::_name_impl() const
{
    std::tstring_t sRv;

    utsname info {};

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    sRv = xA2T(info.nodename);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
