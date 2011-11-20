/**
 * \file  CxHttpClient.cpp
 * \brief protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
 */


#include <xLib/Net/CxHttpClient.h>  //65536


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
CxHttpClient::CxHttpClient() {

}
//---------------------------------------------------------------------------
CxHttpClient::~CxHttpClient() {

}
//---------------------------------------------------------------------------
//TODO: bHead ()
bool
CxHttpClient::bHead(const std::string &csUrl, std::string *psResponse) {
    bool bRes = false;
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

    return true;



}
//---------------------------------------------------------------------------
//TODO: bGet ()
bool
CxHttpClient::bGet(const std::string &csUrl,  std::string *psResponse) {
    return false;
}
//---------------------------------------------------------------------------
//TODO: bPost ()
bool
CxHttpClient::bPost(const std::string &csUrl,  const std::string &csParams, std::string *psResponse) {
    return false;
}
//---------------------------------------------------------------------------
//TODO: bOptions ()
bool
CxHttpClient::bOptions(const std::string &csUrl) {
    return false;
}
//---------------------------------------------------------------------------
//TODO: bTrace ()
bool
CxHttpClient::bTrace(const std::string &csUrl) {
    return false;
}
//---------------------------------------------------------------------------
//TODO: bPut ()
bool
CxHttpClient::bPut(const std::string &csUrl) {
    return false;
}
//---------------------------------------------------------------------------
//TODO: bDelete ()
bool
CxHttpClient::bDelete(const std::string &csUrl) {
    return false;
}
//---------------------------------------------------------------------------
//TODO: bConnect ()
bool
CxHttpClient::bConnect(const std::string &csUrl) {
    return false;
}
//---------------------------------------------------------------------------
//TODO: bPatch ()
bool
CxHttpClient::bPatch(const std::string &csUrl) {
    return false;
}
//---------------------------------------------------------------------------
//TODO: bLink ()
bool
CxHttpClient::bLink(const std::string &csUrl) {
    return false;
}
//---------------------------------------------------------------------------
//TODO: bUnlink ()
bool
CxHttpClient::bUnlink(const std::string &csUrl) {
    return false;
}
//---------------------------------------------------------------------------


/****************************************************************************
* Class name:  CxStatusLine
* Description: protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
* File name:   CxHttpClient.cpp



* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.02.2011

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



* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.02.2011

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



* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.02.2011

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

xNAMESPACE_END(NxLib)
