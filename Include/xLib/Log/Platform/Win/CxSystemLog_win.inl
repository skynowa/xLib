/**
 * \file   CxSystemLog.inl
 * \brief  logging to system log
 */


xNAMESPACE_BEGIN2(xlib, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxSystemLog::_construct_impl(
    std::ctstring_t &a_logName
)
{
    _handle = ::RegisterEventSource(xPTR_NULL, a_logName.c_str());
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxSystemLog::_destruct_impl()
{
    xTEST_PTR(_handle);

    BOOL blRv = ::DeregisterEventSource(_handle);
    xTEST_DIFF(blRv, FALSE);

    _handle = xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxSystemLog::_write_impl(
    cExLevel        &a_level,
    std::ctstring_t &a_msg
) const
{
    WORD    level_impl = internal::enums::toCross(a_level);
    LPCTSTR strings    = a_msg.c_str();

    BOOL bRv = ::ReportEvent(_handle, level, 0, 0UL, xPTR_NULL, 1, 0UL, &strings, xPTR_NULL);
    xTEST_DIFF(bRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, log)
