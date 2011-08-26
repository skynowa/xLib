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
        explicit         CxCookiePv1 ();
                         CxCookiePv1 (const std::tstring &csRawCookie);
        virtual         ~CxCookiePv1 ();

        BOOL             bInit       (const std::tstring &csRawCookie);

        const std::tstring  & sGetName    () const;
        BOOL             bSetName    (const std::tstring &csName);

        const std::tstring  & sGetValue   () const;
        BOOL             bSetValue   (const std::tstring &csValue);

        const std::tstring  & sGetComment () const;
        BOOL             bSetComment (const std::tstring &csComment);

        const std::tstring  & sGetDomain  () const;
        BOOL             bSetDomain  (const std::tstring &csDomain);

        const std::tstring  & sGetPath    () const;
        BOOL             bSetPath    (const std::tstring &csPath);

        LONGLONG         liGetMaxAge () const;
        BOOL             bSetMaxAge  (LONGLONG liMaxAge);

        BOOL             bGetSecure  () const;
        BOOL             bSetSecure  (BOOL bFlag);

        BOOL             bGetHttpOnly() const;
        BOOL             bSetHttpOnly(BOOL bFlag);

        std::tstring          sToString   () const;
        std::tstring          sGetDump    () const;  //TODO: impl
        BOOL             bClear      ();

    private:
        std::tstring          _m_sName;
        std::tstring          _m_sValue;
        std::tstring          _m_sComment;
        std::tstring          _m_sDomain;
        std::tstring          _m_sPath;
        LONGLONG         _m_liMaxAge;    //in seconds
        BOOL             _m_bSecure;
        BOOL             _m_bHttpOnly;
};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCookiePv1H




/*
HttpRequest
HttpResponse
Cookie

*/


