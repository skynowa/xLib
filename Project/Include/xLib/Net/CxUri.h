/**
 * \file  CxUri.h
 * \brief URI (RFC 3986)
 */


#ifndef xLib_Net_CxUriH
#define xLib_Net_CxUriH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxUri :
    private CxNonCopyable
    /// URI (RFC 3986)
{
public:
                          CxUri          ();
    explicit              CxUri          (const std::tstring_t &csUri);
                         ~CxUri          ();

    std::tstring_t        uri            () const xWARN_UNUSED_RV;
    void                  setUri         (const std::tstring_t &csScheme, const std::tstring_t &csAuthority,
                                          const std::tstring_t &csPath, const std::tstring_t &csQuery,
                                          const std::tstring_t &csFragment);

    std::tstring_t        scheme         () const xWARN_UNUSED_RV;
    void                  setScheme      (const std::tstring_t &csScheme);

    std::tstring_t        authority      () const xWARN_UNUSED_RV;
    void                  setAuthority   (const std::tstring_t &csAuthority);

    std::tstring_t        userInfo       () const xWARN_UNUSED_RV;
    void                  setUserInfo    (const std::tstring_t &csUserInfo);

    std::tstring_t        host           () const xWARN_UNUSED_RV;
    void                  setHost        (const std::tstring_t &csHost);

    ushort_t              port           () xWARN_UNUSED_RV;
    void                  setPort        (const ushort_t &cusPort);

    std::tstring_t        path           () const xWARN_UNUSED_RV;
    void                  setPath        (const std::tstring_t &csPath);

    std::tstring_t        query          () const xWARN_UNUSED_RV;
    void                  setQuery       (const std::tstring_t &csQuery);

    std::tstring_t        fragment       () const xWARN_UNUSED_RV;
    void                  setFragment    (const std::tstring_t &csFragment);

    static std::tstring_t escape         (const std::tstring_t &csUri) xWARN_UNUSED_RV;
    static std::tstring_t unescape       (const std::tstring_t &csUri) xWARN_UNUSED_RV;

    static std::tstring_t encodeComponent(const std::tstring_t &csUri) xWARN_UNUSED_RV;
    static std::tstring_t decodeComponent(const std::tstring_t &csUri) xWARN_UNUSED_RV;

    void                  clear          ();

private:
    static const std::tstring_t RESERVED_PATH;
    static const std::tstring_t RESERVED_QUERY;
    static const std::tstring_t RESERVED_FRAGMENT;
    static const std::tstring_t ILLEGAL;

    std::tstring_t        _m_sScheme;
    std::tstring_t        _m_sAuthority;
    std::tstring_t        _m_sUserInfo;
    std::tstring_t        _m_sHost;
    ushort_t              _m_usPort;
    std::tstring_t        _m_sPath;
    std::tstring_t        _m_sQuery;
    std::tstring_t        _m_sFragment;

    void                  _parse         (const std::tstring_t &csUri);
    void                  _normilize     (const std::tstring_t &csUri);
    ushort_t              _defaultPort   () const xWARN_UNUSED_RV;
    bool                  _isDefaultPort () const xWARN_UNUSED_RV;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Net_CxUriH
