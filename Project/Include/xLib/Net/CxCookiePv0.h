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
                               CxCookiePv0 ();
            ///< constructor
        explicit               CxCookiePv0 (const std::tstring_t &csRawCookie);
            ///< constructor
        virtual               ~CxCookiePv0 ();
            ///< constructor

        void                   vInit       (const std::tstring_t &csRawCookie);
            ///< parsing raw cookie string

        const std::tstring_t & sGetName    () const;
            ///< get name
        void                   vSetName    (const std::tstring_t &csName);
            ///< set name

        const std::tstring_t & sGetValue   () const;
            ///< get value
        void                   vSetValue   (const std::tstring_t &csValue);
            ///< set value

        const std::tstring_t & sGetDomain  () const;
            ///< get domain
        void                   vSetDomain  (const std::tstring_t &csDomain);
            ///< set domain

        const std::tstring_t & sGetPath    () const;
            ///< get path
        void                   vSetPath    (const std::tstring_t &csPath);
            ///< set path

        const std::tstring_t & sGetExpires () const;
            ///< get expire
        void                   vSetExpires (const std::tstring_t &csExpires);
            ///< set expire

        bool                   bGetSecure  () const;
            ///< get secure
        void                   vSetSecure  (const bool &cbFlag);
            ///< set secure

        bool                   bGetHttpOnly() const;
            ///< get http only
        void                   vSetHttpOnly(const bool &cbFlag);
            ///< set http only

        std::tstring_t         sToString   () const;
            ///< convert to string
        std::tstring_t         sGetDump    () const;
            ///< get dump
        void                   vClear      ();
            ///< clear

    private:
        std::tstring_t         _m_sName;        ///< name
        std::tstring_t         _m_sValue;       ///< value
        std::tstring_t         _m_sDomain;      ///< domain
        std::tstring_t         _m_sPath;        ///< path
        std::tstring_t         _m_sExpires;     ///< expire
        bool                   _m_bSecure;      ///< secure
        bool                   _m_bHttpOnly;    ///< http only
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCookiePv0H
