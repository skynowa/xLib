/**
 * \file  Host.inl
 * \brief system information
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
std::tstring_t
Host::_name_impl() const
{
    std::tstring_t sRv;

    ulong_t buffSize                 = xHOST_NAME_MAX;
    tchar_t buff[xHOST_NAME_MAX + 1] {};

    BOOL blRv = ::GetComputerName(buff, &buffSize);
    xTEST_DIFF(blRv, FALSE);

    sRv.assign(buff, buffSize);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
