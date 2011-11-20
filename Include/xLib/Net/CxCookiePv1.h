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
                             CxCookiePv1 (const std::tstring &csRawCookie);
            ///< constructor
        virtual             ~CxCookiePv1 ();
            ///< destructor

        bool                 bInit       (const std::tstring &csRawCookie);
            ///< parsing raw cookie string pv0

        const std::tstring & sGetName    () const;
            ///< get name
        bool                 bSetName    (const std::tstring &csName);
            ///< set name

        const std::tstring & sGetValue   () const;
            ///< get value
        bool                 bSetValue   (const std::tstring &csValue);
            ///< set value

        const std::tstring & sGetComment () const;
            ///< get comment
        bool                 bSetComment (const std::tstring &csComment);
            ///< set comment

        const std::tstring & sGetDomain  () const;
            ///< get domain
        bool                 bSetDomain  (const std::tstring &csDomain);
            ///< set domain

        const std::tstring & sGetPath    () const;
            ///< get path
        bool                 bSetPath    (const std::tstring &csPath);
            ///< set path

        LONGLONG             liGetMaxAge () const;
            ///< get max age
        bool                 bSetMaxAge  (LONGLONG liMaxAge);
            ///< set max age

        bool                 bGetSecure  () const;
            ///< get secure
        bool                 bSetSecure  (bool bFlag);
            ///< set decure

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
        std::tstring         _m_sComment;    ///< comment
        std::tstring         _m_sDomain;    ///< domain
        std::tstring         _m_sPath;        ///< path
        LONGLONG             _m_liMaxAge;   ///< max age (in seconds)
        bool                 _m_bSecure;    ///< secure
        bool                 _m_bHttpOnly;    ///< http only
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCookiePv1H
