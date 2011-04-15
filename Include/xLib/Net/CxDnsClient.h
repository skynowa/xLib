/****************************************************************************
* Class name:  CxDnsClient
* Description: DNS
* File name:   CxDnsClient.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     17.06.2010 12:59:14
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Net_CxDnsClientH
#define xLib_Net_CxDnsClientH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxSocket.h>
//---------------------------------------------------------------------------
class CxDnsClient : public CxNonCopyable {
	public:
		static BOOL bGetHostAddrByName  (const tString &csHostName, tString *psHostAddr);
		static BOOL bGetHostNameByAddr  (const tString &csHostAddr, CxSocket::EAddressFamily afFamily, tString *psHostName);
		static BOOL bGetLocalHostName   (tString *psHostName);
		////static BOOL bGetNameInfo    (EAddressFamily afFamily, const tString &csHostAddr, USHORT usPort);
		static BOOL bGetHostAddrInfo    (const tString &csHostName, const tString &csPort, const ADDRINFOT *pHints, ADDRINFOT **ppResult);


		//TODO: ������� ����� �������
		static BOOL bGetProtocolByName  (const tString &csProtocolName, tString *psName, std::vector<tString> *pvecsAliases, SHORT *psiNumber);
		static BOOL bGetProtocolByNumber(SHORT siNumber, tString *psName, std::vector<tString> *pvecsAliases, SHORT *psiNum);

		//TODO: ������� ����� �������
		static BOOL bGetServiceByName   (const tString &csServiceName, const tString &csProtocolName, tString *psName, std::vector<tString> *pvecsAliases, SHORT *psiPort,  tString *psProtocolName);
		static BOOL bGetServiceByPort   (SHORT siPort, const tString &csProtocolName, tString *psName, std::vector<tString> *pvecsAliases, SHORT *psiPort,  tString *psProtocolName);

	private:
		static BOOL _ms_bRes; 
		static INT  _ms_iRes; 

 					CxDnsClient         ();
		virtual    ~CxDnsClient         ();
};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxDnsClientH




////- GetAddressByName

////+ getaddrinfo
////+ GetAddrInfoW
////+ freeaddrinfo
////+ FreeAddrInfoW

////- GetAddrInfoEx
////- SetAddrInfoEx
////- FreeAddrInfoEx

////+ gethostbyname
////+ gethostbyaddr
////+ gethostname

////GetNameByType
////GetTypeByName

////getnameinfo
////GetNameInfoW


////+ getprotobyname
////+ getprotobynumber
////+ getservbyname
////+ getservbyport

