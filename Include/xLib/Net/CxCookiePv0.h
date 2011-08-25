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
{
    public:
        explicit         CxCookiePv0 ();
                         CxCookiePv0 (const std::tstring &csRawCookie);
        virtual         ~CxCookiePv0 ();

        BOOL             bInit     (const std::tstring &csRawCookie);

        const std::tstring &  sGetName    () const;
        BOOL             bSetName    (const std::tstring &csName);

        const std::tstring &  sGetValue   () const;
        BOOL             bSetValue   (const std::tstring &csValue);

        const std::tstring &  sGetDomain  () const;
        BOOL             bSetDomain  (const std::tstring &csDomain);

        const std::tstring &  sGetPath    () const;
        BOOL             bSetPath    (const std::tstring &csPath);

        const std::tstring &  sGetExpires () const;
        BOOL             bSetExpires (const std::tstring &csExpires);

        BOOL             bGetSecure  () const;
        BOOL             bSetSecure  (BOOL bFlag);

        BOOL             bGetHttpOnly() const;
        BOOL             bSetHttpOnly(BOOL bFlag);

        std::tstring          sToString   () const;
        std::tstring          sGetDump    () const;
        BOOL             bClear      ();

    private:
        std::tstring          _m_sName;
        std::tstring          _m_sValue;
        std::tstring          _m_sDomain;
        std::tstring          _m_sPath;
        std::tstring          _m_sExpires;
        BOOL             _m_bSecure;
        BOOL             _m_bHttpOnly;
};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCookiePv0H




/*
HttpRequest
HttpResponse
Cookie

*/


