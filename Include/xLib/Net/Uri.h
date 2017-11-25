/**
 * \file  Uri.h
 * \brief URI (RFC 3986)
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, net)

class Uri
    /// URI (RFC 3986)
{
public:
                      Uri();
    explicit          Uri(std::ctstring_t &uri);
    virtual          ~Uri() {}

    std::tstring_t    uri() const xWARN_UNUSED_RV;
    void_t            setUri(std::ctstring_t &scheme, std::ctstring_t &authority,
                          std::ctstring_t &path, std::ctstring_t &query, std::ctstring_t &fragment);

    std::tstring_t    scheme() const xWARN_UNUSED_RV;
    void_t            setScheme(std::ctstring_t &scheme);

    std::tstring_t    authority() const xWARN_UNUSED_RV;
    void_t            setAuthority(std::ctstring_t &authority);

    std::tstring_t    userInfo() const xWARN_UNUSED_RV;
    void_t            setUserInfo(std::ctstring_t &userInfo);

    std::tstring_t    host() const xWARN_UNUSED_RV;
    void_t            setHost(std::ctstring_t &host);

    ushort_t          port() xWARN_UNUSED_RV;
    void_t            setPort(cushort_t &port);

    std::tstring_t    path() const xWARN_UNUSED_RV;
    void_t            setPath(std::ctstring_t &path);

    std::tstring_t    query() const xWARN_UNUSED_RV;
    void_t            setQuery(std::ctstring_t &query);

    std::tstring_t    fragment() const xWARN_UNUSED_RV;
    void_t            setFragment(std::ctstring_t &fragment);

    static
    std::tstring_t    escape(std::ctstring_t &uri) xWARN_UNUSED_RV;
    static
    std::tstring_t    unescape(std::ctstring_t &uri) xWARN_UNUSED_RV;

    static
    std::tstring_t    encodeComponent(std::ctstring_t &uri) xWARN_UNUSED_RV;
    static
    std::tstring_t    decodeComponent(std::ctstring_t &uri) xWARN_UNUSED_RV;

    void_t            clear();

private:
    static
    std::ctstring_t & _reservedPath();
    static
    std::ctstring_t & _reservedQuery();
    static
    std::ctstring_t & _reservedFragment();
    static
    std::ctstring_t & _illegal();

    std::tstring_t    _scheme;
    std::tstring_t    _authority;
    std::tstring_t    _userInfo;
    std::tstring_t    _host;
    ushort_t          _port;
    std::tstring_t    _path;
    std::tstring_t    _query;
    std::tstring_t    _fragment;

    void_t            _parse(std::ctstring_t &uri);
    void_t            _normilize(std::ctstring_t &uri);
    ushort_t          _defaultPort() const xWARN_UNUSED_RV;
    bool_t            _isDefaultPort() const xWARN_UNUSED_RV;

    xNO_COPY_ASSIGN(Uri)
};

xNAMESPACE_END2(xl, net)
//-------------------------------------------------------------------------------------------------
