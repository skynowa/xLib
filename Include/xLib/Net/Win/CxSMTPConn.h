/**********************************************************************
*    CxSMTPConn.h
*
*    7021 - on
*    7020 - off
*   7022 - info
***********************************************************************/


#ifndef xLib_CxSMTPConnH
#define xLib_CxSMTPConnH
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
//#include <atlsmtpconnection.h>
//#include <Windns.h>
//
//#pragma comment(lib,"Dnsapi.lib")
////---------------------------------------------------------------------
//class CxSMTPConn : public CxSMTPConnection {
//    public:
//        BOOL Connect(LPCTSTR lpszHostDomain, DWORD dwTimeout /*= 10000*/) throw();
//
//    private:
//        void _GetSMTPList(LPCTSTR lpszHostDomain, CSimpleArray<CString>& arrSMTP);
//};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------
#endif    //xLib_CxSMTPConnH
