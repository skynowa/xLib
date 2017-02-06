/**
 * \file   SystemLog.inl
 * \brief  logging to system log
 */


xNAMESPACE_BEGIN2(xl, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
SystemLog::_construct_impl(
    std::ctstring_t &a_logName
)
{
    _handle = ::RegisterEventSource(xPTR_NULL, a_logName.c_str());
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
SystemLog::_destruct_impl()
{
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);

    BOOL blRv = ::DeregisterEventSource(_handle);
    xTEST_DIFF(blRv, FALSE);

    _handle = xNATIVE_HANDLE_NULL;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE void_t
SystemLog::_write_impl(
    cExLevel        &a_level,
    std::ctstring_t &a_msg
) const
{
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);

    WORD    level_impl = internal::enums::toCross(a_level);
    LPCTSTR strings    = a_msg.c_str();

    BOOL bRv = ::ReportEvent(_handle, level, 0, 0UL, xPTR_NULL, 1, 0UL, &strings, xPTR_NULL);
    xTEST_DIFF(bRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, log)
