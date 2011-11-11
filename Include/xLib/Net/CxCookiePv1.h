/**
 * \file  CxCookiePv1.h
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#ifndef xLib_Net_CxCookiePv1H
#define xLib_Net_CxCookiePv1H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCookiePv1 :
    public CxNonCopyable
    /// cookie version 1
{
    public:
        explicit             CxCookiePv1 ();
            ///< constructor
                             CxCookiePv1 (const std::string_t &csRawCookie);
            ///< constructor
        virtual             ~CxCookiePv1 ();
            ///< destructor

        BOOL                 bInit       (const std::string_t &csRawCookie);
            ///< parsing raw cookie string pv0

        const std::string_t & sGetName    () const;
            ///< get name
        BOOL                 bSetName    (const std::string_t &csName);
            ///< set name

        const std::string_t & sGetValue   () const;
            ///< get value
        BOOL                 bSetValue   (const std::string_t &csValue);
            ///< set value

        const std::string_t & sGetComment () const;
            ///< get comment
        BOOL                 bSetComment (const std::string_t &csComment);
            ///< set comment

        const std::string_t & sGetDomain  () const;
            ///< get domain
        BOOL                 bSetDomain  (const std::string_t &csDomain);
            ///< set domain

        const std::string_t & sGetPath    () const;
            ///< get path
        BOOL                 bSetPath    (const std::string_t &csPath);
            ///< set path

        LONGLONG             liGetMaxAge () const;
            ///< get max age
        BOOL                 bSetMaxAge  (LONGLONG liMaxAge);
            ///< set max age

        BOOL                 bGetSecure  () const;
            ///< get secure
        BOOL                 bSetSecure  (BOOL bFlag);
            ///< set decure

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
        std::string_t         _m_sComment;    ///< comment
        std::string_t         _m_sDomain;    ///< domain
        std::string_t         _m_sPath;        ///< path
        LONGLONG             _m_liMaxAge;   ///< max age (in seconds)
        BOOL                 _m_bSecure;    ///< secure
        BOOL                 _m_bHttpOnly;    ///< http only
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCookiePv1H
