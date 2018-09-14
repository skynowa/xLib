/**
 * \file   CurlClient.inl
 * \brief  CURL client
 */


xNAMESPACE_BEGIN3(xl, package, curl)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
CurlClient::setOption(
	cCURLoption a_option,
	const T     a_value
)
{
	CURLcode iRv = ::curl_easy_setopt(_handle.get(), a_option, a_value);

	xTEST_EQ_MSG(iRv, CURLE_OK, Format::str(xT("Option: {} - {}"), a_option, strError(iRv)));
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
CurlClient::info(
    cCURLINFO a_info,
    const T   a_value
)
{
    CURLcode iRv = ::curl_easy_getinfo(_handle.get(), a_info, a_value);

    xTEST_EQ_MSG(iRv, CURLE_OK, Format::str(xT("Info: {} - {}"), a_info, strError(iRv)));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, package, curl)
