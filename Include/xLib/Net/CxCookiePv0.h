/**
 * \file  CxCookiePv0.h
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#ifndef xLib_Net_CxCookiePv0H
#define xLib_Net_CxCookiePv0H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCookiePv0 :
    public CxNonCopyable
    /// cookie version 0
{
    public:
        explicit             CxCookiePv0 ();
            ///< constructor
                             CxCookiePv0 (const std::tstring &csRawCookie);
            ///< constructor
        virtual             ~CxCookiePv0 ();
            ///< constructor

        bool                 bInit     (const std::tstring &csRawCookie);
            ///< parsing raw cookie string

        const std::tstring & sGetName    () const;
            ///< get name
        bool                 bSetName    (const std::tstring &csName);
            ///< set name

        const std::tstring & sGetValue   () const;
            ///< get value
        bool                 bSetValue   (const std::tstring &csValue);
            ///< set value

        const std::tstring & sGetDomain  () const;
            ///< get domain
        bool                 bSetDomain  (const std::tstring &csDomain);
            ///< set domain

        const std::tstring & sGetPath    () const;
            ///< get path
        bool                 bSetPath    (const std::tstring &csPath);
            ///< set path

        const std::tstring & sGetExpires () const;
            ///< get expire
        bool                 bSetExpires (const std::tstring &csExpires);
            ///< set expire

        bool                 bGetSecure  () const;
            ///< get secure
        bool                 bSetSecure  (bool bFlag);
            ///< set secure

        bool                 bGetHttpOnly() const;
            ///< get http only
        bool                 bSetHttpOnly(bool bFlag);
            ///< set http only

        std::tstring         sToString   () const;
            ///< convert to string
        std::tstring         sGetDump    () const;
            ///< get dump
        bool                 bClear      ();
            ///< clear

    private:
        std::tstring         _m_sName;        ///< name
        std::tstring         _m_sValue;        ///< value
        std::tstring         _m_sDomain;    ///< domain
        std::tstring         _m_sPath;        ///< path
        std::tstring         _m_sExpires;    ///< expire
        bool                 _m_bSecure;    ///< secure
        bool                 _m_bHttpOnly;    ///< http only
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCookiePv0H
