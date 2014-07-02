/**
 * \file  HttpClient.h
 * \brief protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, net)

class HttpClient
    /// protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
{
public:
    enum ExProtocolVersion
        /// protocol version
    {
        pv10 = 0,
        pv11 = 1
    };

    enum ExMethod
        /// method
    {
        hmHead,
        hmGet,
        hmPost,
        hmOptions,
        hmTrace,
        hmPut,
        hmDelete,
        hmConnect,
        hmPatch,
        hmLink,
        hmUnlink
    };

    void_t   head(std::ctstring_t &url, std::tstring_t *response);
    void_t   get(std::ctstring_t &url, std::tstring_t *response);
    void_t   post(std::ctstring_t &url, std::ctstring_t &params, std::tstring_t *response);
    void_t   options(std::ctstring_t &url);
    void_t   trace(std::ctstring_t &url);
    void_t   put(std::ctstring_t &url);
    void_t   del(std::ctstring_t &url);
    void_t   connect(std::ctstring_t &url);
    void_t   patch(std::ctstring_t &url);
    void_t   link(std::ctstring_t &url);
    void_t   unlink(std::ctstring_t &url);

             HttpClient();
    virtual ~HttpClient() {}

    xNO_COPY_ASSIGN(HttpClient)
};
//-------------------------------------------------------------------------------------------------
class StatusLine
    /// HTTP status line
{
public:
             StatusLine();
    virtual ~StatusLine() {}

private:
    xNO_COPY_ASSIGN(StatusLine)
};
//-------------------------------------------------------------------------------------------------
class Header
    /// HTTP header
{
public:
             Header();
    virtual ~Header() {}

private:
    xNO_COPY_ASSIGN(Header)
};
//-------------------------------------------------------------------------------------------------
class Body
    /// HTTP nody
{
public:
             Body();
    virtual ~Body() {}

private:
    xNO_COPY_ASSIGN(Body)
};

xNAMESPACE_END2(xlib, net)
//-------------------------------------------------------------------------------------------------
#include "HttpClient.inl"
