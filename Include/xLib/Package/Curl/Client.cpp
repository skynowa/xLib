/**
 * \file   Client.cpp
 * \brief  CURL client
 */


#include "Client.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Log/Trace.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Test/Test.h>


namespace xl::package::curl
{

/**************************************************************************************************
*   DebugData public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
DebugData::print(
	core::OStream &a_os
) const
{
	a_os
		<< xTRACE_VAR(text)      << xT("\n")
		<< xTRACE_VAR(headerIn)  << xT("\n")
		<< xTRACE_VAR(headerOut) << xT("\n")
		<< xTRACE_VAR(dataOut)   << xT("\n")
		<< xTRACE_VAR(sslDataIn) << xT("\n")
		<< xTRACE_VAR(sslDataOut);
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Client::Client(
	cbool_t a_isDebug
) :
	_isDebug{a_isDebug}
{
	_lastError = ::curl_global_init(CURL_GLOBAL_ALL);
	xTEST_EQ(_lastError, CURLE_OK);

    _handle = ::curl_easy_init();
    xTEST_EQ(_handle.isValid(), true);

	setOption(CURLOPT_ERRORBUFFER, _errorStr);

	if (_isDebug) {
		setOption(CURLOPT_VERBOSE,        1L);
		setOption(CURLOPT_DEBUGFUNCTION,  _onDebug);
		setOption(CURLOPT_DEBUGDATA,     &_debugData);
	}
}
//-------------------------------------------------------------------------------------------------
Client::~Client()
{
	(void_t)::curl_global_cleanup();
}
//-------------------------------------------------------------------------------------------------
HandleCurl &
Client::get()
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
void_t
Client::reset()
{
    (void_t)::curl_easy_reset( _handle.get() );
}
//-------------------------------------------------------------------------------------------------
void_t
Client::perform()
{
    _lastError = ::curl_easy_perform( _handle.get() );
    xTEST_EQ_MSG(_lastError, CURLE_OK, Format::str(xT("perform: {}"), strError()));
}
//-------------------------------------------------------------------------------------------------
void_t
Client::pause(
    cint_t a_bitMask
)
{
    _lastError = ::curl_easy_pause(_handle.get(), a_bitMask);
    xTEST_EQ(_lastError, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void_t
Client::receive(
    void_t       *a_buff,
    std::csize_t  a_buffSize,
    std::size_t  *a_items
)
{
    _lastError = ::curl_easy_recv(_handle.get(), a_buff, a_buffSize, a_items);
    xTEST_EQ(_lastError, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void_t
Client::send(
    cvoid_t      *a_buff,
    std::csize_t  a_buffSize,
    std::size_t  *a_items
)
{
    _lastError = ::curl_easy_send(_handle.get(), a_buff, a_buffSize, a_items);
    xTEST_EQ(_lastError, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Client::escape(
    std::ctstring_t &a_str
) const
{
    std::tstring_t sRv;

    char *pszRv = ::curl_easy_escape(_handle.get(), a_str.c_str(), static_cast<int>( a_str.size() ));
    xTEST_PTR(pszRv);

    sRv.assign(pszRv);

    Utils::freeT(pszRv, ::curl_free, nullptr);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Client::unescape(
    std::ctstring_t &a_str
) const
{
    std::tstring_t sRv;

    int size_out = 0;
    char *pszRv = ::curl_easy_unescape(_handle.get(), a_str.c_str(),
        static_cast<int>( a_str.size() ), &size_out);
    xTEST_PTR(pszRv);

    sRv.assign(pszRv, static_cast<std::size_t>(size_out));

    Utils::freeT(pszRv, ::curl_free, nullptr);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Client::strError() const
{
    const char *pszRv = ::curl_easy_strerror(_lastError);
    if (pszRv == nullptr) {
        return Const::strUnknown();
    }

    return pszRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Client::escapeUrl(
    std::ctstring_t &a_str
)
{
    std::tstring_t sRv;

    char *pszRv = ::curl_escape(a_str.c_str(), static_cast<int>( a_str.size() ));
    xTEST_PTR(pszRv);

    sRv.assign(pszRv);

    Utils::freeT(pszRv, ::curl_free, nullptr);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Client::unescapeUrl(
    std::ctstring_t &a_str
)
{
    std::tstring_t sRv;

    char *pszRv = ::curl_unescape(a_str.c_str(), static_cast<int>( a_str.size() ));
    xTEST_PTR(pszRv);

    sRv.assign(pszRv);

    Utils::freeT(pszRv, ::curl_free, nullptr);

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public, callbacks
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::size_t
Client::onWriteHeader(
	void_t       *a_buff,		///<
	std::csize_t  a_size,		///<
	std::csize_t  a_items,		///<
	void_t       *out_userData	///< [in,out]
)
{
	xTEST_PTR(a_buff);
	xTEST_DIFF(a_size,  std::size_t{0});
	xTEST_DIFF(a_items, std::size_t{0});
	xTEST_PTR(out_userData);

	auto *data = static_cast<std::tstring_t *>(out_userData);
	xTEST_PTR(data);

	std::csize_t buffSize = a_items * a_size;
	data->append(static_cast<char *>(a_buff), buffSize);

    return buffSize;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::size_t
Client::onWriteData(
	void_t       *a_buff,		///<
	std::csize_t  a_size,		///<
	std::csize_t  a_items,		///<
	void_t       *out_userData	///< [in,out]
)
{
	xTEST_PTR(a_buff);
	xTEST_DIFF(a_size,  std::size_t{0});
	xTEST_DIFF(a_items, std::size_t{0});
	xTEST_PTR(out_userData);

	auto *data = static_cast<std::tstring_t *>(out_userData);
	xTEST_PTR(data);

	std::csize_t buffSize = a_items * a_size;
	data->append(static_cast<char *>(a_buff), buffSize);

	return buffSize;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::size_t
Client::onReadData(
	void_t       *out_buff,		///< [out]
	std::csize_t  a_size,		///<
	std::csize_t  a_items,		///<
	void_t       *out_userData	///< [in,out]
)
{
	xTEST_PTR(out_buff);
	xTEST_DIFF(a_size,  std::size_t{0});
	xTEST_DIFF(a_items, std::size_t{0});
	xTEST_PTR(out_userData);

	auto *data = static_cast<struct ReadData *>(out_userData);
	xTEST_PTR(data);

	std::ctstring_t buff = data->buff.substr(data->bytes);
	if ( buff.empty() ) {
		return 0;
	}

	std::csize_t buffSizeMax = a_size * a_items;
	std::size_t  buffSize    = buff.size();
	if (buffSizeMax < buffSize) {
		buffSize = buffSizeMax;
	}

	std::memcpy(out_buff, buff.data(), buffSize);

	data->bytes += buffSize;

	return buffSize;
}
//-------------------------------------------------------------------------------------------------
/* static */
int
Client::_onDebug(
	CURL                *a_curl,		///<
	const curl_infotype  a_type,		///<
	char                *a_buff,		///<
	std::csize_t         a_size,		///<
	void_t              *out_useData	///< [out] as DataIn::DebugData
)
{
	xUNUSED(a_curl);

	xCHECK_RET(a_buff == nullptr,      CURLE_OK);
	xCHECK_RET(a_size == 0,            CURLE_OK);
	xCHECK_RET(out_useData == nullptr, CURLE_OK);

	auto *data = static_cast<DebugData *>(out_useData);
	if (data == nullptr) {
		return CURLE_OK;
	}

	std::ctstring_t buff(a_buff, a_size);

	switch (a_type) {
	case CURLINFO_TEXT:
		data->text = buff;
		break;
	case CURLINFO_HEADER_IN:
		data->headerIn = buff;
		break;
	case CURLINFO_HEADER_OUT:
		data->headerOut = buff;
		break;
	case CURLINFO_DATA_IN:
		data->dataIn = buff;
		break;
	case CURLINFO_DATA_OUT:
		data->dataOut = buff;
		break;
	case CURLINFO_SSL_DATA_IN:
		data->sslDataIn = buff;
		break;
	case CURLINFO_SSL_DATA_OUT:
		data->sslDataOut = buff;
		break;
	case CURLINFO_END:
		xTEST(false);
		break;
	}

	return CURLE_OK;
}
//-------------------------------------------------------------------------------------------------

} // namespace
