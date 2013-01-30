/**
 * \file  CxUri.h
 * \brief URI (RFC 3986)
 */


#ifndef xLib_Net_CxUriH
#define xLib_Net_CxUriH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxUri :
    private CxNonCopyable
    /// URI (RFC 3986)
{
public:
                       CxUri            ();
    explicit           CxUri            (const std::tstring_t &csUri);
                      ~CxUri            ();

    std::tstring_t        sUri          () const;
    void               vSetUri          (const std::tstring_t &csScheme, const std::tstring_t &csAuthority, const std::tstring_t &csPath, const std::tstring_t &csQuery, const std::tstring_t &csFragment);

    std::tstring_t        sScheme       () const;
    void               vSetScheme       (const std::tstring_t &csScheme);

    std::tstring_t        sAuthority    () const;
    void               vSetAuthority    (const std::tstring_t &csAuthority);

    std::tstring_t        sUserInfo     () const;
    void               vSetUserInfo     (const std::tstring_t &csUserInfo);

    std::tstring_t        sHost         () const;
    void               vSetHost         (const std::tstring_t &csHost);

    ushort_t           usPort        ();
    void               vSetPort         (const ushort_t &cusPort);

    std::tstring_t        sPath         () const;
    void               vSetPath         (const std::tstring_t &csPath);

    std::tstring_t        sQuery        () const;
    void               vSetQuery        (const std::tstring_t &csQuery);

    std::tstring_t        sFragment     () const;
    void               vSetFragment     (const std::tstring_t &csFragment);

    static std::tstring_t sEscape          (const std::tstring_t &csUri);
    static std::tstring_t sUnescape        (const std::tstring_t &csUri);

    static std::tstring_t sEncodeComponent (const std::tstring_t &csUri);
    static std::tstring_t sDecodeComponent (const std::tstring_t &csUri);

    void               vClear           ();

private:
    static const std::tstring_t RESERVED_PATH;
    static const std::tstring_t RESERVED_QUERY;
    static const std::tstring_t RESERVED_FRAGMENT;
    static const std::tstring_t ILLEGAL;

    std::tstring_t        _m_sScheme;
    std::tstring_t        _m_sAuthority;
    std::tstring_t        _m_sUserInfo;
    std::tstring_t        _m_sHost;
    ushort_t           _m_usPort;
    std::tstring_t        _m_sPath;
    std::tstring_t        _m_sQuery;
    std::tstring_t        _m_sFragment;

    void               _vParse          (const std::tstring_t &csUri);
    void               _vNormilize      (const std::tstring_t &csUri);
    ushort_t           _usDefaultPort() const;
    bool               _bIsDefaultPort  () const;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Net_CxUriH
