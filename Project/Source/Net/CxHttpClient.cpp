/**
 * \file  CxHttpClient.cpp
 * \brief protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
 */


#include <xLib/Net/CxHttpClient.h>  //65536

#include <xLib/Core/CxConst.h>


xNAMESPACE_BEGIN(NxLib)

//------------------------------------------------------------------------------
xINLINE_HO
CxHttpClient::CxHttpClient()
{
}
//------------------------------------------------------------------------------
//TODO: bHead ()
xINLINE_HO void_t
CxHttpClient::head(
    std::ctstring_t &a_url,
    std::tstring_t  *a_response
)
{
    //url = http://dn1.berloga.net/83841/zombie_baseball_2.swf

    std::tstring_t sStartLine;
    std::tstring_t sHeader;
    std::tstring_t sBody;

    sStartLine = xT("HEAD /83841/zombie_baseball_2.swf HTTP/1.1")         + CxConst::xCRNL();

    sHeader    = xT("Host: dn1.berloga.net")                              + CxConst::xCRNL() +
                 xT("Accept: text/html, */*")                             + CxConst::xCRNL() +
                 xT("Accept-Encoding: identity")                          + CxConst::xCRNL() +
                 xT("User-Agent: Mozilla/3.0 (compatible; Indy Library)") + CxConst::xCRNL() + CxConst::xCRNL();

    sBody      = xT("");
}
//------------------------------------------------------------------------------
//TODO: bGet ()
xINLINE_HO void_t
CxHttpClient::get(
    std::ctstring_t &a_url,
    std::tstring_t  *a_response
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bPost ()
xINLINE_HO void_t
CxHttpClient::post(
    std::ctstring_t &a_url,
    std::ctstring_t &a_params,
    std::tstring_t  *a_response
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bOptions ()
xINLINE_HO void_t
CxHttpClient::options(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bTrace ()
xINLINE_HO void_t
CxHttpClient::trace(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bPut ()
xINLINE_HO void_t
CxHttpClient::put(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: del ()
xINLINE_HO void_t
CxHttpClient::del(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bConnect ()
xINLINE_HO void_t
CxHttpClient::connect(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bPatch ()
xINLINE_HO void_t
CxHttpClient::patch(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bLink ()
xINLINE_HO void_t
CxHttpClient::link(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bUnlink ()
xINLINE_HO void_t
CxHttpClient::unlink(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
