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
        explicit           CxUri            (const std::string &csUri);
                          ~CxUri            ();

        std::string        sGetUri          () const;
        void               vSetUri          (const std::string &csScheme, const std::string &csAuthority, const std::string &csPath, const std::string &csQuery, const std::string &csFragment);

        std::string        sGetScheme       () const;
        void               vSetScheme       (const std::string &csScheme);

        std::string        sGetAuthority    () const;
        void               vSetAuthority    (const std::string &csAuthority);

        std::string        sGetUserInfo     () const;
        void               vSetUserInfo     (const std::string &csUserInfo);

        std::string        sGetHost         () const;
        void               vSetHost         (const std::string &csHost);

        ushort_t           usGetPort        ();
        void               vSetPort         (const ushort_t &cusPort);

        std::string        sGetPath         () const;
        void               vSetPath         (const std::string &csPath);

        std::string        sGetQuery        () const;
        void               vSetQuery        (const std::string &csQuery);

        std::string        sGetFragment     () const;
        void               vSetFragment     (const std::string &csFragment);

        static std::string sEscape          (const std::string &csUri);
        static std::string sUnescape        (const std::string &csUri);

        static std::string sEncodeComponent (const std::string &csUri);
        static std::string sDecodeComponent (const std::string &csUri);

        void               vClear           ();

    private:
        static const std::string RESERVED_PATH;
        static const std::string RESERVED_QUERY;
        static const std::string RESERVED_FRAGMENT;
        static const std::string ILLEGAL;

        std::string        _m_sScheme;
        std::string        _m_sAuthority;
        std::string        _m_sUserInfo;
        std::string        _m_sHost;
        ushort_t           _m_usPort;
        std::string        _m_sPath;
        std::string        _m_sQuery;
        std::string        _m_sFragment;

        void               _vParse          (const std::string &csUri);
        void               _vNormilize      (const std::string &csUri);
        ushort_t           _usGetDefaultPort() const;
        bool               _bIsDefaultPort  () const;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxUriH
