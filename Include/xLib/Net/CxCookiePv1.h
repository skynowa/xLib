/****************************************************************************
* Class name:  CxCookiePv1
* Description: cookie (http://www.ietf.org/rfc/rfc2109.txt)
* File name:   CxCookiePv1.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     26.01.2011 0:04:44
*
*****************************************************************************/


#ifndef xLib_Net_CxCookiePv1H
#define xLib_Net_CxCookiePv1H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxCookiePv1 : public CxNonCopyable {
    public:
		explicit         CxCookiePv1 ();
                         CxCookiePv1 (const tString &csRawCookie);
        virtual         ~CxCookiePv1 ();

        BOOL             bInit       (const tString &csRawCookie);

        const tString  & sGetName    () const;
        BOOL             bSetName    (const tString &csName);

        const tString  & sGetValue   () const;
        BOOL             bSetValue   (const tString &csValue);

        const tString  & sGetComment () const;
        BOOL             bSetComment (const tString &csComment);

        const tString  & sGetDomain  () const;
        BOOL             bSetDomain  (const tString &csDomain);

        const tString  & sGetPath    () const;
        BOOL             bSetPath    (const tString &csPath);

        ULONGLONG        iGetMaxAge  () const;
        BOOL             bSetMaxAge  (ULONGLONG iMaxAge);

        BOOL             bGetSecure  () const;
        BOOL             bSetSecure  (BOOL bFlag);

        BOOL             bGetHttpOnly() const;
        BOOL             bSetHttpOnly(BOOL bFlag);

        tString          sToString   () const;
        tString          sGetDump    () const;  //TODO: impl
        BOOL             bClear      ();

    private:
        tString          _m_sName;
        tString          _m_sValue;
        tString          _m_sComment;
        tString          _m_sDomain;
        tString          _m_sPath;
        ULONGLONG        _m_iMaxAge;    //in seconds
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


