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
    private CxNonCopyable
    /// cookie version 0
{
    public:
        explicit               CxCookiePv0 ();
            ///< constructor
                               CxCookiePv0 (const std::tstring_t &csRawCookie);
            ///< constructor
        virtual               ~CxCookiePv0 ();
            ///< constructor

        bool                   bInit       (const std::tstring_t &csRawCookie);
            ///< parsing raw cookie string

        const std::tstring_t & sGetName    () const;
            ///< get name
        bool                   bSetName    (const std::tstring_t &csName);
            ///< set name

        const std::tstring_t & sGetValue   () const;
            ///< get value
        bool                   bSetValue   (const std::tstring_t &csValue);
            ///< set value

        const std::tstring_t & sGetDomain  () const;
            ///< get domain
        bool                   bSetDomain  (const std::tstring_t &csDomain);
            ///< set domain

        const std::tstring_t & sGetPath    () const;
            ///< get path
        bool                   bSetPath    (const std::tstring_t &csPath);
            ///< set path

        const std::tstring_t & sGetExpires () const;
            ///< get expire
        bool                   bSetExpires (const std::tstring_t &csExpires);
            ///< set expire

        bool                   bGetSecure  () const;
            ///< get secure
        bool                   bSetSecure  (bool bFlag);
            ///< set secure

        bool                   bGetHttpOnly() const;
            ///< get http only
        bool                   bSetHttpOnly(bool bFlag);
            ///< set http only

        std::tstring_t         sToString   () const;
            ///< convert to string
        std::tstring_t         sGetDump    () const;
            ///< get dump
        bool                   bClear      ();
            ///< clear

    private:
        std::tstring_t         _m_sName;        ///< name
        std::tstring_t         _m_sValue;        ///< value
        std::tstring_t         _m_sDomain;    ///< domain
        std::tstring_t         _m_sPath;        ///< path
        std::tstring_t         _m_sExpires;    ///< expire
        bool                   _m_bSecure;    ///< secure
        bool                   _m_bHttpOnly;    ///< http only
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCookiePv0H
