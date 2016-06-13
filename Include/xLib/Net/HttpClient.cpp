/**
 * \file  HttpClient.inl
 * \brief protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "HttpClient.h"
#endif

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>
#include <xLib/Core/Const.h>


xNAMESPACE_BEGIN2(xlib, net)

//-------------------------------------------------------------------------------------------------
xINLINE
HttpClient::HttpClient()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
HttpClient::head(
    std::ctstring_t &a_url,
    std::tstring_t  *a_response
)
{
    xUNUSED(a_url);
    xUNUSED(a_response);

    //url = http://dn1.berloga.net/83841/zombie_baseball_2.swf

    std::tstring_t startLine;
    std::tstring_t header;
    std::tstring_t body;

    startLine = xT("HEAD /83841/zombie_baseball_2.swf HTTP/1.1")         + Const::crNl();

    header    = xT("Host: dn1.berloga.net")                              + Const::crNl() +
                xT("Accept: text/html, */*")                             + Const::crNl() +
                xT("Accept-Encoding: identity")                          + Const::crNl() +
                xT("User-Agent: Mozilla/3.0 (compatible; Indy Library)") + Const::crNl() + Const::crNl();

    body      = xT("");
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
HttpClient::get(
    std::ctstring_t &a_url,
    std::tstring_t  *a_response
)
{
    xUNUSED(a_url);
    xUNUSED(a_response);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
HttpClient::post(
    std::ctstring_t &a_url,
    std::ctstring_t &a_params,
    std::tstring_t  *a_response
)
{
    xUNUSED(a_url);
    xUNUSED(a_params);
    xUNUSED(a_response);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
HttpClient::options(
    std::ctstring_t &a_url
)
{
    xUNUSED(a_url);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
HttpClient::trace(
    std::ctstring_t &a_url
)
{
    xUNUSED(a_url);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
HttpClient::put(
    std::ctstring_t &a_url
)
{
    xUNUSED(a_url);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
HttpClient::del(
    std::ctstring_t &a_url
)
{
    xUNUSED(a_url);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
HttpClient::connect(
    std::ctstring_t &a_url
)
{
    xUNUSED(a_url);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
HttpClient::patch(
    std::ctstring_t &a_url
)
{
    xUNUSED(a_url);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
HttpClient::link(
    std::ctstring_t &a_url
)
{
    xUNUSED(a_url);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
HttpClient::unlink(
    std::ctstring_t &a_url
)
{
    xUNUSED(a_url);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
