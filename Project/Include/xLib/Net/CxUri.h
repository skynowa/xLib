/**
 * \file  CxUri.h
 * \brief URI (RFC 3986)
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxUri :
    private CxNonCopyable
    /// URI (RFC 3986)
{
public:
                          CxUri();
    explicit              CxUri(std::ctstring_t &csUri);
                         ~CxUri();

    std::tstring_t        uri() const xWARN_UNUSED_RV;
    void_t                setUri(std::ctstring_t &csScheme, std::ctstring_t &csAuthority,
                              std::ctstring_t &csPath, std::ctstring_t &csQuery,
                              std::ctstring_t &csFragment);

    std::tstring_t        scheme() const xWARN_UNUSED_RV;
    void_t                setScheme(std::ctstring_t &csScheme);

    std::tstring_t        authority() const xWARN_UNUSED_RV;
    void_t                setAuthority(std::ctstring_t &csAuthority);

    std::tstring_t        userInfo() const xWARN_UNUSED_RV;
    void_t                setUserInfo(std::ctstring_t &csUserInfo);

    std::tstring_t        host() const xWARN_UNUSED_RV;
    void_t                setHost(std::ctstring_t &csHost);

    ushort_t              port() xWARN_UNUSED_RV;
    void_t                setPort(cushort_t &cusPort);

    std::tstring_t        path() const xWARN_UNUSED_RV;
    void_t                setPath(std::ctstring_t &csPath);

    std::tstring_t        query() const xWARN_UNUSED_RV;
    void_t                setQuery(std::ctstring_t &csQuery);

    std::tstring_t        fragment() const xWARN_UNUSED_RV;
    void_t                setFragment(std::ctstring_t &csFragment);

    static std::tstring_t escape(std::ctstring_t &csUri) xWARN_UNUSED_RV;
    static std::tstring_t unescape(std::ctstring_t &csUri) xWARN_UNUSED_RV;

    static std::tstring_t encodeComponent(std::ctstring_t &csUri) xWARN_UNUSED_RV;
    static std::tstring_t decodeComponent(std::ctstring_t &csUri) xWARN_UNUSED_RV;

    void_t                clear();

private:
    static std::ctstring_t RESERVED_PATH;
    static std::ctstring_t RESERVED_QUERY;
    static std::ctstring_t RESERVED_FRAGMENT;
    static std::ctstring_t ILLEGAL;

    std::tstring_t        _m_sScheme;
    std::tstring_t        _m_sAuthority;
    std::tstring_t        _m_sUserInfo;
    std::tstring_t        _m_sHost;
    ushort_t              _m_usPort;
    std::tstring_t        _m_sPath;
    std::tstring_t        _m_sQuery;
    std::tstring_t        _m_sFragment;

    void_t                _parse(std::ctstring_t &csUri);
    void_t                _normilize(std::ctstring_t &csUri);
    ushort_t              _defaultPort() const xWARN_UNUSED_RV;
    bool_t                _isDefaultPort() const xWARN_UNUSED_RV;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
