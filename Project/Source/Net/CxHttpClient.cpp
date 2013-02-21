/**
 * \file  CxHttpClient.cpp
 * \brief protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
 */


#include <xLib/Net/CxHttpClient.h>  //65536

#include <xLib/Common/CxConst.h>


xNAMESPACE_BEGIN(NxLib)

//------------------------------------------------------------------------------
CxHttpClient::CxHttpClient() {

}
//------------------------------------------------------------------------------
CxHttpClient::~CxHttpClient() {

}
//------------------------------------------------------------------------------
//TODO: bHead ()
void
CxHttpClient::head(
    const std::tstring_t &a_csUrl, 
    std::tstring_t       *a_psResponse
)
{
    //csUrl = http://dn1.berloga.net/83841/zombie_baseball_2.swf

    std::tstring_t sStartLine;
    std::tstring_t sHeader;
    std::tstring_t sBody;

    sStartLine = xT("HEAD /83841/zombie_baseball_2.swf HTTP/1.1")         + CxConst::xCRNL;

    sHeader    = xT("Host: dn1.berloga.net")                              + CxConst::xCRNL +
                 xT("Accept: text/html, */*")                             + CxConst::xCRNL +
                 xT("Accept-Encoding: identity")                          + CxConst::xCRNL +
                 xT("User-Agent: Mozilla/3.0 (compatible; Indy Library)") + CxConst::xCRNL + CxConst::xCRNL;

    sBody      = xT("");
}
//------------------------------------------------------------------------------
//TODO: bGet ()
void
CxHttpClient::get(
    const std::tstring_t &a_csUrl,  
    std::tstring_t       *a_psResponse
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bPost ()
void
CxHttpClient::post(
    const std::tstring_t &a_csUrl,  
    const std::tstring_t &a_csParams, 
    std::tstring_t       *a_psResponse
) 
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bOptions ()
void
CxHttpClient::options(
    const std::tstring_t &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bTrace ()
void
CxHttpClient::trace(
    const std::tstring_t &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bPut ()
void
CxHttpClient::put(
    const std::tstring_t &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: del ()
void
CxHttpClient::del(
    const std::tstring_t &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bConnect ()
void
CxHttpClient::connect(
    const std::tstring_t &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bPatch ()
void
CxHttpClient::patch(
    const std::tstring_t &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bLink ()
void
CxHttpClient::link(
    const std::tstring_t &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bUnlink ()
void
CxHttpClient::unlink(
    const std::tstring_t &a_csUrl
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------


/*******************************************************************************
* Class name:  CxStatusLine
* Description: protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
* File name:   CxHttpClient.cpp



* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.02.2011

*
*******************************************************************************/

//------------------------------------------------------------------------------
//TODO: CxStatusLine ()
CxHttpClient::CxStatusLine::CxStatusLine() {
    

}
//------------------------------------------------------------------------------
//TODO: ~CxStatusLine ()
CxHttpClient::CxStatusLine::~CxStatusLine() {
    

}
//------------------------------------------------------------------------------


/*******************************************************************************
* Class name:  CxHeader
* Description: protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
* File name:   CxHttpClient.cpp



* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.02.2011

*
*******************************************************************************/

//------------------------------------------------------------------------------
//TODO: CxHeader ()
CxHttpClient::CxHeader::CxHeader() {
    

}
//------------------------------------------------------------------------------
//TODO: ~CxHeader ()
CxHttpClient::CxHeader::~CxHeader() {
    

}
//------------------------------------------------------------------------------


/*******************************************************************************
* Class name:  CxBody
* Description: protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
* File name:   CxHttpClient.cpp



* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.02.2011

*
*******************************************************************************/

//------------------------------------------------------------------------------
//TODO: CxBody ()
CxHttpClient::CxBody::CxBody() {
    

}
//------------------------------------------------------------------------------
//TODO: ~CxBody ()
CxHttpClient::CxBody::~CxBody() {
    

}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
