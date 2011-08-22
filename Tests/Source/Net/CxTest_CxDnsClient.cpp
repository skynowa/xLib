/****************************************************************************
* Class name:  CxTest_CxDnsClient
* Description: test CxDnsClient
* File name:   CxTest_CxDnsClient.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Net/CxTest_CxDnsClient.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxDnsClient
CxTest_CxDnsClient::CxTest_CxDnsClient() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxDnsClient
CxTest_CxDnsClient::~CxTest_CxDnsClient() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxDnsClient::bUnit(
    const ULONGLONG cullBlockLoops
)
{
	//-------------------------------------
	//CxSocketInit
	CxSocketInit siInit(2, 2);

	//-------------------------------------
	//bGetHostAddrByName
	{
		tString sHostName = xT("msdn.microsoft.com");
		tString sHostAddr = xT("");

		m_bRes = CxDnsClient::bGetHostAddrByName(sHostName, &sHostAddr);
		xASSERT_NOT_EQ(FALSE, m_bRes);

		//tcout << xT("[bGetHostAddrByName]: ") << sHostAddr << tendl;
	}

	//-------------------------------------
	//bGetHostNameByAddr
	{
		tString sHostName = xT("");
		tString sHostAddr = xT("127.0.0.1");

		m_bRes = CxDnsClient::bGetHostNameByAddr(sHostAddr, CxSocket::afInet, &sHostName);
		xASSERT_NOT_EQ(FALSE, m_bRes);

		//tcout << xT("[bGetHostNameByAddr]: ") << sHostName << tendl;
	}

	//-------------------------------------
	//bGetLocalHostName
	{
		tString sLocalHostName = xT("");

		m_bRes = CxDnsClient::bGetLocalHostName(&sLocalHostName);
		xASSERT_NOT_EQ(FALSE, m_bRes);

		//tcout << xT("[bGetLocalHostName]: ") << sLocalHostName << tendl;
	}

	//-------------------------------------
	//bGetNameInfo
	{
		////CxDnsClient::EAddressFamily afFamily  = CxDnsClient::afInet;
		////tString                     sHostAddr = /*xT("207.46.172.252");*/    xT("forum.vingrad.ru");
		////USHORT                      usPort    = 27015;

		////m_bRes = CxDnsClient::bGetNameInfo(afFamily, sHostAddr, usPort);
		////xASSERT_NOT_EQ(FALSE, m_bRes);

		//xSTD_COUT(xT("[bGetNameInfo]: ") << sLocalHostName);
	}

	//-------------------------------------
	//bGetHostAddrInfo
	{
		tString sHostName = xT("www.google.ru");
		tString sPort     = xT("http");

		////ADDRINFOT aiHints  = {0};
		ADDRINFOT *paiList = NULL;

		m_bRes = CxDnsClient::bGetHostAddrInfo(sHostName, sPort, NULL, &paiList);
		xASSERT_NOT_EQ(FALSE, m_bRes);

		//xSTD_COUT(xT("[bGetLocalHostName]: ") << sLocalHostName);


		{
			///*int*/                 paiList->ai_flags;       // AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST
			///*int*/                 paiList->ai_family;      // PF_xxx
			///*int*/                 paiList->ai_socktype;    // SOCK_xxx
			///*int*/                 paiList->ai_protocol;    // 0 or IPPROTO_xxx for IPv4 and IPv6
			///*size_t*/              paiList->ai_addrlen;     // Length of ai_addr
			///*char **/              paiList->ai_canonname;   // Canonical name for nodename
			///*__field_bcount(ai_addrlen) struct sockaddr **/   paiList->ai_addr;        // Binary address
			///*struct addrinfo **/   paiList->ai_next;        // Next structure in linked list
		}

        #if defined(xOS_WIN)
		    ////freeaddrinfo(paiList);
       		::FreeAddrInfo(paiList);
        #elif defined(xOS_LINUX)
       		freeaddrinfo(paiList);
        #endif
		/*DEBUG*/// n/a
	}

	//-------------------------------------
	//bGetProtocolByName
	{
		const TCHAR cszProtocolNames[][10] =
		{
            xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"),
            xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp")
		};

		for (size_t i = 0; i < xARRAY_SIZE(cszProtocolNames); ++ i) {
			tString              sName;
			std::vector<tString> vsAliases;
			SHORT                siNumber = - 1;

			m_bRes = CxDnsClient::bGetProtocolByName(cszProtocolNames[i], &sName, &vsAliases, &siNumber);
			xASSERT_NOT_EQ(FALSE, m_bRes);

			//tcout << xT("[bGetProtocolByName]: ")             << tendl;
			//tcout << xT("	sName:    ") << sName             << tendl;
			for (size_t j = 0; j < vsAliases.size(); ++ j) {
			//tcout << xT("	sAlias:   ") << vsAliases.at(j) << tendl;
			}
			//tcout << xT("	siNumber: ") << siNumber          << tendl;
			//tcout << xT("	--------------------")            << tendl;
		}
        //tcout << tendl;
	}

	//-------------------------------------
	//cszProtocolNumbers
	{
		const INT ciProtocolNumbers[] = {
		    0, 1, 3, 6, 8, 12, 17, 20, 22, 27
		};

		for (size_t i = 0; i < xARRAY_SIZE(ciProtocolNumbers); ++ i) {
			tString              sName;
			std::vector<tString> vsAliases;
			SHORT                siNumber = - 1;

			m_bRes = CxDnsClient::bGetProtocolByNumber(ciProtocolNumbers[i], &sName, &vsAliases, &siNumber);
			xASSERT_NOT_EQ(FALSE, m_bRes);

			//tcout << xT("[bGetProtocolByNumber]: ")           << tendl;
			//tcout << xT("	sName:    ") << sName             << tendl;;
			for (size_t j = 0; j < vsAliases.size(); ++ j) {
			//tcout << xT("	sAlias:   ") << vsAliases.at(j) << tendl;
			}
			//tcout << xT("	siNumber: ") << siNumber          << tendl;
			//tcout << xT("	--------------------")            << tendl;
		}
        //tcout << tendl;
	}

	//-------------------------------------
	//bGetServiceByName
	{
		tString              csServiceName  = xT("http");
		const TCHAR          cszProtocolNames[][10] = {xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"), xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp") };
		tString              sName;
		std::vector<tString> vsAliases;
		SHORT                siPort;
		tString              sProtocolName;

		m_bRes = CxDnsClient::bGetServiceByName(csServiceName, cszProtocolNames[3], &sName, &vsAliases, &siPort, &sProtocolName);
		xASSERT_NOT_EQ(FALSE, m_bRes);

		//tcout << xT("[bGetServiceByName]: ")                   << tendl;
		//tcout << xT("	sName:         ") << sName             << tendl;
		for (size_t i = 0; i < vsAliases.size(); ++ i) {
		//tcout << xT("	sAlias:        ") << vsAliases.at(i) << tendl;
		}
		//tcout << xT("	siPort:        ") << siPort            << tendl;
		//tcout << xT("	sProtocolName: ") << sProtocolName     << tendl;
		//tcout << xT("	--------------------")                 << tendl;
        //tcout << tendl;
	}


	//-------------------------------------
	//bGetServiceByPort
	{
		SHORT                csiPort  = 20480;
		const TCHAR          cszProtocolNames[][10] = {xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"), xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp") };
		tString              sName;
		std::vector<tString> vsAliases;
		SHORT                siPort = - 1;
		tString              sProtocolName;

		m_bRes = CxDnsClient::bGetServiceByPort(csiPort, cszProtocolNames[3], &sName, &vsAliases, &siPort, &sProtocolName);
		xASSERT_NOT_EQ(FALSE, m_bRes);

		//tcout << xT("[bGetServiceByPort]: ") << tendl;
		//tcout << xT("	sName:         ") << sName << tendl;
		for (size_t i = 0; i < vsAliases.size(); ++ i) {
		//tcout << xT("	sAlias:        ") << vsAliases.at(i) << tendl;
		}
		//tcout << xT("	siPort:        ") << siPort            << tendl;
		//tcout << xT("	sProtocolName: ") << sProtocolName     << tendl;
        //tcout << xT("  --------------------")                << tendl;
        //tcout << tendl;
	}

	return TRUE;
}
//---------------------------------------------------------------------------
