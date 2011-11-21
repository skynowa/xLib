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
                             CxCookiePv1 (const std::tstring_t &csRawCookie);
            ///< constructor
        virtual             ~CxCookiePv1 ();
            ///< destructor

        bool                 bInit       (const std::tstring_t &csRawCookie);
            ///< parsing raw cookie string pv0

        const std::tstring_t & sGetName    () const;
            ///< get name
        bool                 bSetName    (const std::tstring_t &csName);
            ///< set name

        const std::tstring_t & sGetValue   () const;
            ///< get value
        bool                 bSetValue   (const std::tstring_t &csValue);
            ///< set value

        const std::tstring_t & sGetComment () const;
            ///< get comment
        bool                 bSetComment (const std::tstring_t &csComment);
            ///< set comment

        const std::tstring_t & sGetDomain  () const;
            ///< get domain
        bool                 bSetDomain  (const std::tstring_t &csDomain);
            ///< set domain

        const std::tstring_t & sGetPath    () const;
            ///< get path
        bool                 bSetPath    (const std::tstring_t &csPath);
            ///< set path

        longlong_t             liGetMaxAge () const;
            ///< get max age
        bool                 bSetMaxAge  (longlong_t liMaxAge);
            ///< set max age

        bool                 bGetSecure  () const;
            ///< get secure
        bool                 bSetSecure  (bool bFlag);
            ///< set decure

        bool                 bGetHttpOnly() const;
            ///< get http only
        bool                 bSetHttpOnly(bool bFlag);
            ///< set http only

        std::tstring_t         sToString   () const;
            ///< convert to string
        std::tstring_t         sGetDump    () const;
            ///< get dump
        bool                 bClear      ();
            ///< clear

    private:
        std::tstring_t         _m_sName;        ///< name
        std::tstring_t         _m_sValue;        ///< value
        std::tstring_t         _m_sComment;    ///< comment
        std::tstring_t         _m_sDomain;    ///< domain
        std::tstring_t         _m_sPath;        ///< path
        longlong_t             _m_liMaxAge;   ///< max age (in seconds)
        bool                 _m_bSecure;    ///< secure
        bool                 _m_bHttpOnly;    ///< http only
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCookiePv1H
