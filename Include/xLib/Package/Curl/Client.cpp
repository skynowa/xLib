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
#include <xLib/Package/Curl/BaseClient.h>


namespace xl::package::curl
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Client::Client()
{
	cCURLcode iRv = ::curl_global_init(CURL_GLOBAL_ALL);
	xTEST_EQ(iRv, CURLE_OK);

    _handle = ::curl_easy_init();
    xTEST_EQ(_handle.isValid(), true);
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
    cCURLcode iRv = ::curl_easy_perform( _handle.get() );
    xTEST_EQ_MSG(iRv, CURLE_OK, Format::str(xT("perform: {}"), strError(iRv)));
}
//-------------------------------------------------------------------------------------------------
void_t
Client::pause(
    cint_t a_bitMask
)
{
    cCURLcode iRv = ::curl_easy_pause(_handle.get(), a_bitMask);
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void_t
Client::receive(
    void_t       *a_buff,
    std::csize_t  a_buffSize,
    std::size_t  *a_n
)
{
    cCURLcode iRv = ::curl_easy_recv(_handle.get(), a_buff, a_buffSize, a_n);
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void_t
Client::send(
    cvoid_t      *a_buff,
    std::csize_t  a_buffSize,
    std::size_t  *a_n
)
{
    CURLcode iRv = ::curl_easy_send(_handle.get(), a_buff, a_buffSize, a_n);
    xTEST_EQ(iRv, CURLE_OK);
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

    if (pszRv != nullptr) {
        ::curl_free(pszRv);
        pszRv = nullptr;
    }

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

    if (pszRv != nullptr) {
        ::curl_free(pszRv);
        pszRv = nullptr;
    }

    return sRv;
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

    if (pszRv != nullptr) {
        ::curl_free(pszRv);
        pszRv = nullptr;
    }

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

    if (pszRv != nullptr) {
        ::curl_free(pszRv);
        pszRv = nullptr;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Client::strError(
   cCURLcode a_code
)
{
    const char *pszRv = ::curl_easy_strerror(a_code);
    if (pszRv == nullptr) {
        return Const::strUnknown();
    }

    return pszRv;
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
	void_t         *a_buff,
	std::csize_t    a_size,
	std::csize_t    a_items,
	std::tstring_t *out_userData
)
{
	xTEST_PTR(a_buff);
	xTEST_DIFF(a_size, std::size_t{0});
	xTEST_DIFF(a_items, std::size_t{0});
	xTEST_PTR(out_userData);

	std::csize_t buffSize = a_items * a_size;
    out_userData->append(static_cast<char *>(a_buff), buffSize);

    return buffSize;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::size_t
Client::onWriteData(
	void_t         *a_buff,
	std::csize_t    a_size,
	std::csize_t    a_items,
	std::tstring_t *out_userData
)
{
	xTEST_PTR(a_buff);
	xTEST_DIFF(a_size, std::size_t{0});
	xTEST_DIFF(a_items, std::size_t{0});
	xTEST_PTR(out_userData);

	std::csize_t buffSize = a_items * a_size;
    out_userData->append(static_cast<char *>(a_buff), buffSize);

	return buffSize;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::size_t
Client::onReadData(
	void_t          *out_buff,	///< [out]
	std::csize_t     a_size,	///<
	std::csize_t     a_items,	///<
	std::ctstring_t *a_userData	///< [in,out]
)
{
	xTEST_PTR(out_buff);
	xTEST_DIFF(a_size, std::size_t{0});
	xTEST_DIFF(a_items, std::size_t{0});
	xTEST_PTR(a_userData);

	auto *readData = (struct ReadData *)a_userData;
	xTEST_PTR(readData);

	std::ctstring_t buff = readData->buff.substr(readData->bytes);
	if ( buff.empty() ) {
		return 0;
	}

	std::csize_t buffSizeMax = a_size * a_items;
	std::size_t  buffSize    = buff.size();
	if (buffSizeMax < buffSize) {
		buffSize = buffSizeMax;
	}

	std::memcpy(out_buff, buff.data(), buffSize);

	readData->bytes += buffSize;

	return buffSize;
}
//-------------------------------------------------------------------------------------------------
/* static */
int
Client::onDebug(
	CURL          *a_curl,		///<
	curl_infotype  a_type,		///<
	char          *a_buf,		///<
	std::csize_t   a_len,		///<
	void_t        *out_useData	///< as DataIn::DebugData
)
{
	xUNUSED(a_curl);

	if (out_useData == nullptr) {
		return CURLE_OK;
	}

	auto *data = static_cast<DataIn::DebugData *>(out_useData);
	if (data == nullptr) {
		return CURLE_OK;
	}

	switch (a_type) {
	case CURLINFO_TEXT:
		data->text.assign(a_buf, a_len);
		break;
	case CURLINFO_HEADER_IN:
		data->headerIn.assign(a_buf, a_len);
		break;
	case CURLINFO_HEADER_OUT:
		data->headerOut.assign(a_buf, a_len);
		break;
	case CURLINFO_DATA_IN:
		data->dataIn.assign(a_buf, a_len);
		break;
	case CURLINFO_DATA_OUT:
		data->dataOut.assign(a_buf, a_len);
		break;
	case CURLINFO_SSL_DATA_IN:
		data->sslDataIn.assign(a_buf, a_len);
		break;
	case CURLINFO_SSL_DATA_OUT:
		data->sslDataOut.assign(a_buf, a_len);
		break;
	case CURLINFO_END:
	default:
		xTEST(false);
		break;
	}

	return CURLE_OK;
}
//-------------------------------------------------------------------------------------------------

} // namespace
