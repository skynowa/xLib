/**
 * \file   Client.inl
 * \brief  CURL client
 */


namespace xl::package::curl
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
Client::setOption(
	cCURLoption  a_option,
	const T     &a_value
)
{
	_lastError = ::curl_easy_setopt(_handle.get(), a_option, a_value);
	xTEST_MSG(_isLastErrorOk(), Format::str(xT("Option: {} - {}"), a_option, strError()));
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
Client::info(
    cCURLINFO  a_info,
    const T   &a_value
)
{
	_lastError = ::curl_easy_getinfo(_handle.get(), a_info, a_value);
    xTEST_MSG(_isLastErrorOk(), Format::str(xT("Info: {} - {}"), a_info, strError()));
}
//-------------------------------------------------------------------------------------------------

} // namespace
