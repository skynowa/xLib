/**
 * \file   SystemLog.inl
 * \brief  logging to system log
 */


namespace xl::log
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
SystemLog &
SystemLog::operator << (const T &valueT)
{
    _oss << valueT;
    return *this;
}
//-------------------------------------------------------------------------------------------------

} // namespace
