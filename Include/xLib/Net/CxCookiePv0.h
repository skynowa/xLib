/****************************************************************************
* Class name:  CxCookiePv0
* Description: cookie (http://www.ietf.org/rfc/rfc2109.txt)
* File name:   CxCookiePv0.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     26.01.2011 0:04:44
*
*****************************************************************************/


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
                         CxCookiePv0 (const tString &csRawCookie);
        virtual         ~CxCookiePv0 ();

        BOOL             bInit     (const tString &csRawCookie);

        const tString &  sGetName    () const;
        BOOL             bSetName    (const tString &csName);

        const tString &  sGetValue   () const;
        BOOL             bSetValue   (const tString &csValue);

        const tString &  sGetDomain  () const;
        BOOL             bSetDomain  (const tString &csDomain);

        const tString &  sGetPath    () const;
        BOOL             bSetPath    (const tString &csPath);

        const tString &  sGetExpires () const;
        BOOL             bSetExpires (const tString &csExpires);

        BOOL             bGetSecure  () const;
        BOOL             bSetSecure  (BOOL bFlag);

        BOOL             bGetHttpOnly() const;
        BOOL             bSetHttpOnly(BOOL bFlag);

        tString          sToString   () const;
        tString          sGetDump    () const;
        BOOL             bClear      ();

    private:
        tString          _m_sName;
        tString          _m_sValue;
        tString          _m_sDomain;
        tString          _m_sPath;
        tString          _m_sExpires;
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


