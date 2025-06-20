/**
 * \file  SystemLog.inl
 * \brief logging to system log
 */


namespace xl::log
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
SystemLog::_ctor_impl(
    std::ctstring_t &a_logName
)
{
    _handle = ::RegisterEventSource(nullptr, a_logName.c_str());
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);
}
//-------------------------------------------------------------------------------------------------
void_t
SystemLog::_dtor_impl()
{
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);

    BOOL blRv = ::DeregisterEventSource(_handle);
    xTEST_DIFF(blRv, FALSE);

    _handle = xNATIVE_HANDLE_NULL;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
SystemLog::_write_impl(
    cLevel           a_level,
    std::ctstring_t &a_msg
) const
{
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);

    const auto level_impl = static_cast<WORD>(
        internal::enums::levels.toImpl( static_cast<std::ssize_t>(a_level)) );

    LPCTSTR strings    = a_msg.c_str();

    BOOL bRv = ::ReportEvent(_handle, level_impl, 0, 0UL, nullptr, 1, 0UL, &strings, nullptr);
    xTEST_DIFF(bRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

} // namespace
