/**
 * \file   HttpClient.cpp
 * \brief  HTTP client
 */


#include "HttpClient.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>


xNAMESPACE_BEGIN3(xl, package, curl)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::request(
	cRequestType  a_type,		///<
	DataIn       &a_dataIn,		///< [in,out]
	DataOut      *out_dataOut	///< [out]
)
{
	xTEST_DIFF((int)a_type, (int)RequestType::Unknown);
	xTEST_PTR(out_dataOut);

	out_dataOut->headers.clear();
	out_dataOut->body.clear();

	setProtocols(CURLPROTO_HTTP | CURLPROTO_HTTPS);

	switch (a_type) {
	case RequestType::Get:
		{
		   /**
			* Retrieve information from the given server using a given URI.
			* Requests using GET should only retrieve data and should have no other effect
			* on the data
			*/

			setOption(CURLOPT_POST, 0L);
			setOption(CURLOPT_NOBODY, 0L);
		}
		break;
	case RequestType::Head:
		{
		   /**
			* Same as GET, but transfers the status line and header section only
			*/

			setOption(CURLOPT_NOBODY, 1L);
		}
		break;
	case RequestType::Post:
		{
		   /**
			* Send data to the server, for example, customer information, file upload, etc.
			* using HTML forms
			*/

			setOption(CURLOPT_POST,          1L);
			setOption(CURLOPT_POSTFIELDS,    a_dataIn.request.c_str());
			setOption(CURLOPT_POSTFIELDSIZE, a_dataIn.request.size());
		}
		break;
	case RequestType::Put:
		{
		   /**
			* Replaces all current representations of the target resource with uploaded content
			*/

			// TODO: RequestType::Put
			setOption(CURLOPT_UPLOAD, 1L);
		}
		break;
	case RequestType::Delete:
		{
		   /**
			* Removes all current representations of the target resource given by a URI
			*/

			setOption(CURLOPT_CUSTOMREQUEST, xT("DELETE"));
		}
		break;
	case RequestType::Connect:
		{
		   /**
			* Establishes a tunnel to the server identified by a given URI
			*/

			// TODO: RequestType::Connect
		}
		break;
	case RequestType::Options:
		{
		   /**
			* Describes the communication options for the target resource
			*/

			// TODO: RequestType::Options
		}
		break;
	case RequestType::Trace:
		{
		   /**
			* Performs a message loop-back test along the path to the target resource
			*/

			// TODO: RequestType::Trace
		}
		break;
	case RequestType::Unknown:
	default:
		xTEST(false);
		return false;
		break;
	}

	curl_slist *headers {};
	Buffer      buffHeader;
	Buffer      buffData;
	CurlBase::setOptionsDefault(&a_dataIn, headers, &buffHeader, &buffData);

	/*CURLcode st = */ perform();

	CurlBase::getInfos(out_dataOut);

	Utils::freeT(headers, ::curl_slist_free_all, nullptr);

	/// _error = st;

	// [out]
	String::split(buffHeader.buffer(), Const::crNl(), xT(": "), &out_dataOut->headers);
	out_dataOut->body = buffData.buffer();

	/// std::cout << "buffHeader.buffer() : [" << buffHeader.buffer() << "]" << std::endl;

	return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, package, curl)
