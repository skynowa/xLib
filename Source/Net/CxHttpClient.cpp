/****************************************************************************
* Class name:  CxHttpClient
* Description: protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
* File name:   CxHttpClient.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     16.11.2009 14:43:15
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Net/CxHttpClient.h>  //65536


//---------------------------------------------------------------------------
CxHttpClient::CxHttpClient() {
	//code
}
//---------------------------------------------------------------------------
CxHttpClient::~CxHttpClient() {
	//code
}
//---------------------------------------------------------------------------
//TODO: bHead ()
BOOL
CxHttpClient::bHead(const std::string &csUrl, std::string *psResponse) {
	BOOL bRes = FALSE;
	xUNUSED(bRes);

	//csUrl = http://dn1.berloga.net/83841/zombie_baseball_2.swf

	std::string sStartLine;
	std::string sHeader;
	std::string sBody;
	
	sStartLine = "HEAD /83841/zombie_baseball_2.swf HTTP/1.1"         + CxConst::xCRNL;
		
	sHeader    = "Host: dn1.berloga.net"                              + CxConst::xCRNL +
			     "Accept: text/html, */*"                             + CxConst::xCRNL +
				 "Accept-Encoding: identity"                          + CxConst::xCRNL +
				 "User-Agent: Mozilla/3.0 (compatible; Indy Library)" + CxConst::xCRNL + CxConst::xCRNL;	

	sBody      = "";

	return TRUE;



}
//---------------------------------------------------------------------------
//TODO: bGet ()
BOOL
CxHttpClient::bGet(const std::string &csUrl,  std::string *psResponse) {
	return FALSE;
}
//---------------------------------------------------------------------------
//TODO: bPost ()
BOOL
CxHttpClient::bPost(const std::string &csUrl,  const std::string &csParams, std::string *psResponse) {
	return FALSE;
}
//---------------------------------------------------------------------------
//TODO: bOptions ()
BOOL
CxHttpClient::bOptions(const std::string &csUrl) {
	return FALSE;
}
//---------------------------------------------------------------------------
//TODO: bTrace ()
BOOL
CxHttpClient::bTrace(const std::string &csUrl) {
	return FALSE;
}
//---------------------------------------------------------------------------
//TODO: bPut ()
BOOL
CxHttpClient::bPut(const std::string &csUrl) {
	return FALSE;
}
//---------------------------------------------------------------------------
//TODO: bDelete ()
BOOL
CxHttpClient::bDelete(const std::string &csUrl) {
	return FALSE;
}
//---------------------------------------------------------------------------
//TODO: bConnect ()
BOOL
CxHttpClient::bConnect(const std::string &csUrl) {
	return FALSE;
}
//---------------------------------------------------------------------------
//TODO: bPatch ()
BOOL
CxHttpClient::bPatch(const std::string &csUrl) {
	return FALSE;
}
//---------------------------------------------------------------------------
//TODO: bLink ()
BOOL
CxHttpClient::bLink(const std::string &csUrl) {
	return FALSE;
}
//---------------------------------------------------------------------------
//TODO: bUnlink ()
BOOL
CxHttpClient::bUnlink(const std::string &csUrl) {
	return FALSE;
}
//---------------------------------------------------------------------------


/****************************************************************************
* Class name:  CxStatusLine
* Description: protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
* File name:   CxHttpClient.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.02.2011
* Version:     1.0.0.0 Debug
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxStatusLine ()
CxHttpClient::CxStatusLine::CxStatusLine() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
//TODO: ~CxStatusLine ()
CxHttpClient::CxStatusLine::~CxStatusLine() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------


/****************************************************************************
* Class name:  CxHeader
* Description: protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
* File name:   CxHttpClient.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.02.2011
* Version:     1.0.0.0 Debug
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxHeader ()
CxHttpClient::CxHeader::CxHeader() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
//TODO: ~CxHeader ()
CxHttpClient::CxHeader::~CxHeader() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------


/****************************************************************************
* Class name:  CxBody
* Description: protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
* File name:   CxHttpClient.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.02.2011
* Version:     1.0.0.0 Debug
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxBody ()
CxHttpClient::CxBody::CxBody() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
//TODO: ~CxBody ()
CxHttpClient::CxBody::~CxBody() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
