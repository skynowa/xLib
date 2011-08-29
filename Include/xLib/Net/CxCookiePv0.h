/**
 * \file  CxCookiePv0.h
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#ifndef xLib_Net_CxCookiePv0H
#define xLib_Net_CxCookiePv0H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
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

        BOOL                 bInit     (const std::tstring &csRawCookie);
    		///< parsing raw cookie string

        const std::tstring & sGetName    () const;
    		///< get name
        BOOL                 bSetName    (const std::tstring &csName);
    		///< set name

        const std::tstring & sGetValue   () const;
    		///< get value
        BOOL                 bSetValue   (const std::tstring &csValue);
    		///< set value

        const std::tstring & sGetDomain  () const;
    		///< get domain
        BOOL                 bSetDomain  (const std::tstring &csDomain);
    		///< set domain

        const std::tstring & sGetPath    () const;
    		///< get path
        BOOL                 bSetPath    (const std::tstring &csPath);
    		///< set path

        const std::tstring & sGetExpires () const;
    		///< get expire
        BOOL                 bSetExpires (const std::tstring &csExpires);
    		///< set expire

        BOOL                 bGetSecure  () const;
    		///< get secure
        BOOL                 bSetSecure  (BOOL bFlag);
    		///< set secure

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
        std::tstring         _m_sDomain;	///< domain
        std::tstring         _m_sPath;		///< path
        std::tstring         _m_sExpires;	///< expire
        BOOL                 _m_bSecure;	///< secure
        BOOL                 _m_bHttpOnly;	///< http only
};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCookiePv0H
