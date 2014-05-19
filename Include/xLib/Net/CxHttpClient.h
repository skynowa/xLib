/**
 * \file  CxHttpClient.h
 * \brief protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
 */


#pragma once

#ifndef xLib_CxHttpClientH
#define xLib_CxHttpClientH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, net)

class CxHttpClient
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

             CxHttpClient();
    virtual ~CxHttpClient() {}

    xNO_COPY_ASSIGN(CxHttpClient)
};
//-------------------------------------------------------------------------------------------------
class CxStatusLine
    /// HTTP status line
{
public:
             CxStatusLine();
    virtual ~CxStatusLine() {}

private:
    xNO_COPY_ASSIGN(CxStatusLine)
};
//-------------------------------------------------------------------------------------------------
class CxHeader
    /// HTTP header
{
public:
             CxHeader();
    virtual ~CxHeader() {}

private:
    xNO_COPY_ASSIGN(CxHeader)
};
//-------------------------------------------------------------------------------------------------
class CxBody
    /// HTTP nody
{
public:
             CxBody();
    virtual ~CxBody() {}

private:
    xNO_COPY_ASSIGN(CxBody)
};

xNAMESPACE_END2(xlib, net)
//-------------------------------------------------------------------------------------------------
#include "CxHttpClient.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxHttpClientH
