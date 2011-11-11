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
                             CxCookiePv0 (const std::string_t &csRawCookie);
            ///< constructor
        virtual             ~CxCookiePv0 ();
            ///< constructor

        BOOL                 bInit     (const std::string_t &csRawCookie);
            ///< parsing raw cookie string

        const std::string_t & sGetName    () const;
            ///< get name
        BOOL                 bSetName    (const std::string_t &csName);
            ///< set name

        const std::string_t & sGetValue   () const;
            ///< get value
        BOOL                 bSetValue   (const std::string_t &csValue);
            ///< set value

        const std::string_t & sGetDomain  () const;
            ///< get domain
        BOOL                 bSetDomain  (const std::string_t &csDomain);
            ///< set domain

        const std::string_t & sGetPath    () const;
            ///< get path
        BOOL                 bSetPath    (const std::string_t &csPath);
            ///< set path

        const std::string_t & sGetExpires () const;
            ///< get expire
        BOOL                 bSetExpires (const std::string_t &csExpires);
            ///< set expire

        BOOL                 bGetSecure  () const;
            ///< get secure
        BOOL                 bSetSecure  (BOOL bFlag);
            ///< set secure

        BOOL                 bGetHttpOnly() const;
            ///< get http only
        BOOL                 bSetHttpOnly(BOOL bFlag);
            ///< set http only

        std::string_t         sToString   () const;
            ///< convert to string
        std::string_t         sGetDump    () const;
            ///< get dump
        BOOL                 bClear      ();
            ///< clear

    private:
        std::string_t         _m_sName;        ///< name
        std::string_t         _m_sValue;        ///< value
        std::string_t         _m_sDomain;    ///< domain
        std::string_t         _m_sPath;        ///< path
        std::string_t         _m_sExpires;    ///< expire
        BOOL                 _m_bSecure;    ///< secure
        BOOL                 _m_bHttpOnly;    ///< http only
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCookiePv0H
