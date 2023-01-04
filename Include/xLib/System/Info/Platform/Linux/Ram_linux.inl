/**
 * \file  Ram.inl
 * \brief system information
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
ulonglong_t
Ram::_ramTotal_impl() const
{
    struct sysinfo info {};

    int_t iRv = ::sysinfo(&info);
    xTEST_DIFF(iRv, - 1);

    ulonglong_t ullRv = info.totalram * info.mem_unit;

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulonglong_t
Ram::_ramAvailable_impl() const
{
    struct sysinfo info {};

    int_t iRv = ::sysinfo(&info);
    xTEST_DIFF(iRv, - 1);

    ulonglong_t ullRv = info.freeram * info.mem_unit;

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Ram::_ramUsage_impl() const
{
    struct sysinfo info {};

    int_t iRv = ::sysinfo(&info);
    xTEST_DIFF(iRv, - 1);

    ulong_t usage = info.totalram - info.freeram;

    ulong_t ulRv = static_cast<ulong_t>( Utils::intSafeDiv(usage * 100, info.totalram) );
    xTEST_EQ(info.totalram, usage + info.freeram);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
