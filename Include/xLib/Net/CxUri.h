/****************************************************************************
* Class name:  CxUri
* Description: URI (RFC 3986)
* File name:   CxUri.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     17.11.2009 12:41:10
*
*****************************************************************************/


#ifndef xLib_Net_CxUriH
#define xLib_Net_CxUriH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxUri : CxNonCopyable {
    public:
                           CxUri            ();
        explicit           CxUri            (const std::string &csUri);
                          ~CxUri            ();

        std::string        sGetUri          () const;
        BOOL               bSetUri          (const std::string &csScheme, const std::string &csAuthority, const std::string &csPath, const std::string &csQuery, const std::string &csFragment);

        std::string        sGetScheme       () const;
        BOOL               bSetScheme       (const std::string &csScheme);

        std::string        sGetAuthority    () const;
        BOOL               bSetAuthority    (const std::string &csAuthority);

        std::string        sGetUserInfo     () const;
        BOOL               bSetUserInfo     (const std::string &csUserInfo);

        std::string        sGetHost         () const;
        BOOL               bSetHost         (const std::string &csHost);

        USHORT             usGetPort        ();
        BOOL               bSetPort         (const USHORT &cusPort);

        std::string        sGetPath         () const;
        BOOL               bSetPath         (const std::string &csPath);

        std::string        sGetQuery        () const;
        BOOL               bSetQuery        (const std::string &csQuery);

        std::string        sGetFragment     () const;
        BOOL               bSetFragment     (const std::string &csFragment);

        static std::string sEscape          (const std::string &csUri);
        static std::string sUnescape        (const std::string &csUri);

        static std::string sEncodeComponent (const std::string &csUri);
        static std::string sDecodeComponent (const std::string &csUri);

        BOOL               bClear           ();

    private:
        static const std::string RESERVED_PATH;
        static const std::string RESERVED_QUERY;
        static const std::string RESERVED_FRAGMENT;
        static const std::string ILLEGAL;

        std::string        _m_sScheme;
        std::string        _m_sAuthority;
        std::string        _m_sUserInfo;
        std::string        _m_sHost;
        USHORT             _m_usPort;
        std::string        _m_sPath;
        std::string        _m_sQuery;
        std::string        _m_sFragment;

        BOOL               _bParse          (const std::string &csUri);
        BOOL               _bNormilize      (const std::string &csUri);
        USHORT             _usGetDefaultPort() const;
        BOOL               _bIsDefaultPort  () const;
};
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxUriH
