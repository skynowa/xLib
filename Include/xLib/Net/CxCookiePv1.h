/**
 * \file  CxCookiePv1.h
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#ifndef xLib_Net_CxCookiePv1H
#define xLib_Net_CxCookiePv1H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
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

        BOOL                 bInit       (const std::tstring &csRawCookie);
        	///< parsing raw cookie string pv0

        const std::tstring & sGetName    () const;
    		///< get name
        BOOL                 bSetName    (const std::tstring &csName);
    		///< set name

        const std::tstring & sGetValue   () const;
    		///< get value
        BOOL                 bSetValue   (const std::tstring &csValue);
    		///< set value

        const std::tstring & sGetComment () const;
    		///< get comment
        BOOL                 bSetComment (const std::tstring &csComment);
    		///< set comment

        const std::tstring & sGetDomain  () const;
    		///< get domain
        BOOL                 bSetDomain  (const std::tstring &csDomain);
    		///< set domain

        const std::tstring & sGetPath    () const;
    		///< get path
        BOOL                 bSetPath    (const std::tstring &csPath);
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

        std::tstring         sToString   () const;
    		///< convert to string
        std::tstring         sGetDump    () const;
    		///< get dump
        BOOL                 bClear      ();
    		///< clear

    private:
        std::tstring         _m_sName;		///< name
        std::tstring         _m_sValue;		///< value
        std::tstring         _m_sComment;	///< comment
        std::tstring         _m_sDomain;	///< domain
        std::tstring         _m_sPath;		///< path
        LONGLONG             _m_liMaxAge;   ///< max age (in seconds)
        BOOL                 _m_bSecure;	///< secure
        BOOL                 _m_bHttpOnly;	///< http only
};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCookiePv1H
