/**
 * \file  CxHttpClient.cpp
 * \brief protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
 */


#include <xLib/Net/CxHttpClient.h>  //65536

#include <xLib/Common/CxConst.h>


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
CxHttpClient::CxHttpClient() {

}
//---------------------------------------------------------------------------
CxHttpClient::~CxHttpClient() {

}
//---------------------------------------------------------------------------
//TODO: bHead ()
void
CxHttpClient::vHead(
    const std::string &a_csUrl, 
    std::string       *a_psResponse
)
{
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
}
//---------------------------------------------------------------------------
//TODO: bGet ()
void
CxHttpClient::vGet(
    const std::string &a_csUrl,  
    std::string       *a_psResponse
)
{
    xNOT_IMPLEMENTED;
}
//---------------------------------------------------------------------------
//TODO: bPost ()
void
CxHttpClient::vPost(
    const std::string &a_csUrl,  
    const std::string &a_csParams, 
    std::string       *a_psResponse
) 
{
    xNOT_IMPLEMENTED;
}
//---------------------------------------------------------------------------
//TODO: bOptions ()
void
CxHttpClient::vOptions(
    const std::string &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//---------------------------------------------------------------------------
//TODO: bTrace ()
void
CxHttpClient::vTrace(
    const std::string &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//---------------------------------------------------------------------------
//TODO: bPut ()
void
CxHttpClient::vPut(
    const std::string &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//---------------------------------------------------------------------------
//TODO: bDelete ()
void
CxHttpClient::vDelete(
    const std::string &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//---------------------------------------------------------------------------
//TODO: bConnect ()
void
CxHttpClient::vConnect(
    const std::string &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//---------------------------------------------------------------------------
//TODO: bPatch ()
void
CxHttpClient::vPatch(
    const std::string &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//---------------------------------------------------------------------------
//TODO: bLink ()
void
CxHttpClient::vLink(
    const std::string &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//---------------------------------------------------------------------------
//TODO: bUnlink ()
void
CxHttpClient::vUnlink(
    const std::string &a_csUrl
)
{
    xNOT_IMPLEMENTED;
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
