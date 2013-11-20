/**
 * \file  CxHttpClient.cpp
 * \brief protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTracer.h>
#include <xLib/Core/CxConst.h>


xNAMESPACE_BEGIN(NxLib)

//-------------------------------------------------------------------------------------------------
inline
CxHttpClient::CxHttpClient()
{
}
//-------------------------------------------------------------------------------------------------
//TODO: bHead ()
inline void_t
CxHttpClient::head(
    std::ctstring_t &a_url,
    std::tstring_t  *a_response
)
{
    //url = http://dn1.berloga.net/83841/zombie_baseball_2.swf

    std::tstring_t startLine;
    std::tstring_t header;
    std::tstring_t body;

    startLine = xT("HEAD /83841/zombie_baseball_2.swf HTTP/1.1")         + CxConst::crNl();

    header    = xT("Host: dn1.berloga.net")                              + CxConst::crNl() +
                xT("Accept: text/html, */*")                             + CxConst::crNl() +
                xT("Accept-Encoding: identity")                          + CxConst::crNl() +
                xT("User-Agent: Mozilla/3.0 (compatible; Indy Library)") + CxConst::crNl() + CxConst::crNl();

    body      = xT("");
}
//-------------------------------------------------------------------------------------------------
//TODO: bGet ()
inline void_t
CxHttpClient::get(
    std::ctstring_t &a_url,
    std::tstring_t  *a_response
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
//TODO: bPost ()
inline void_t
CxHttpClient::post(
    std::ctstring_t &a_url,
    std::ctstring_t &a_params,
    std::tstring_t  *a_response
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
//TODO: bOptions ()
inline void_t
CxHttpClient::options(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
//TODO: bTrace ()
inline void_t
CxHttpClient::trace(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
//TODO: bPut ()
inline void_t
CxHttpClient::put(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
//TODO: del ()
inline void_t
CxHttpClient::del(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
//TODO: bConnect ()
inline void_t
CxHttpClient::connect(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
//TODO: bPatch ()
inline void_t
CxHttpClient::patch(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
//TODO: bLink ()
inline void_t
CxHttpClient::link(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
//TODO: bUnlink ()
inline void_t
CxHttpClient::unlink(
    std::ctstring_t &a_url
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
