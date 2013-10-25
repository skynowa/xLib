/**
 * \file  CxHttpClient.h
 * \brief protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxHttpClient :
    private CxNonCopyable
    /// protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
{
public:
    //status line
    class CxStatusLine;

    //header
    class CxHeader;

    //body
    class CxBody;

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
};
//------------------------------------------------------------------------------
class CxHttpClient::CxStatusLine
    /// HTTP status line
{
public:
             CxStatusLine();
    virtual ~CxStatusLine() {}

private:

};
//------------------------------------------------------------------------------
class CxHttpClient::CxHeader
    /// HTTP header
{
public:
             CxHeader();
    virtual ~CxHeader() {}

private:

};
//------------------------------------------------------------------------------
class CxHttpClient::CxBody
    /// HTTP nody
{
public:
             CxBody();
    virtual ~CxBody() {}

private:

};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Net/CxHttpClient.cpp>
#endif
