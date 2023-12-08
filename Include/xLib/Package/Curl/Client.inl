/**
 * \file   Client.inl
 * \brief  CURL client
 */


#include <xLib/Package/Curl/Error.h>

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
	Error err = ::curl_easy_setopt(_handle.get(), a_option, a_value);
	xTEST_MSG(err.isOk(), Format::str(xT("Option: {} - {}"), a_option, err.str()));
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
Client::info(
    cCURLINFO  a_info,
    const T   &a_value
)
{
	Error err = ::curl_easy_getinfo(_handle.get(), a_info, a_value);
    xTEST_MSG(err.isOk(), Format::str(xT("Info: {} - {}"), a_info, err.str()));
}
//-------------------------------------------------------------------------------------------------

} // namespace
