/**
 * \file  Storage.inl
 * \brief system information
 *
 * \see   https://www.kernel.org/doc/Documentation/ABI/testing/sysfs-class-net
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
ulong_t
Storage::_pageSize_impl() const
{
    long_t liRv = ::sysconf(xPAGE_SIZE);
    xTEST_DIFF(liRv, - 1L);
    xTEST_GR(liRv, 0L);

    auto ulRv = static_cast<ulong_t>( liRv );
    xTEST_GR(ulRv, 0UL);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
