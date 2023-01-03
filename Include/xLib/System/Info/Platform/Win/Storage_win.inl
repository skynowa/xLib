/**
 * \file  Storage.inl
 * \brief system information
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
ulong_t
Storage::_pageSize_impl() const
{
    SYSTEM_INFO sysInfo {};

    (void_t)::GetNativeStorage(&sysInfo);

    ulong_t ulRv = sysInfo.dwPageSize;
    xTEST_LESS(0UL, ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
