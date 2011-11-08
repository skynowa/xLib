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
CxTest_CxDnsClient::CxTest_CxDnsClient() {

}
//---------------------------------------------------------------------------
CxTest_CxDnsClient::~CxTest_CxDnsClient() {

}
//---------------------------------------------------------------------------
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
		std::tstring sHostName = xT("msdn.microsoft.com");
		std::tstring sHostAddr = xT("");

		m_bRes = CxDnsClient::bGetHostAddrByName(sHostName, &sHostAddr);
		xTEST_DIFF(FALSE, m_bRes);

		//std::tcout << xT("[bGetHostAddrByName]: ") << sHostAddr << std::endl;
	}

	//-------------------------------------
	//bGetHostNameByAddr
	{
		std::tstring sHostName = xT("");
		std::tstring sHostAddr = xT("127.0.0.1");

		m_bRes = CxDnsClient::bGetHostNameByAddr(sHostAddr, CxSocket::afInet, &sHostName);
		xTEST_DIFF(FALSE, m_bRes);

		//std::tcout << xT("[bGetHostNameByAddr]: ") << sHostName << std::endl;
	}

	//-------------------------------------
	//bGetLocalHostName
	{
		std::tstring sLocalHostName = xT("");

		m_bRes = CxDnsClient::bGetLocalHostName(&sLocalHostName);
		xTEST_DIFF(FALSE, m_bRes);

		//std::tcout << xT("[bGetLocalHostName]: ") << sLocalHostName << std::endl;
	}

	//-------------------------------------
	//bGetNameInfo
	{
		////CxDnsClient::EAddressFamily afFamily  = CxDnsClient::afInet;
		////std::tstring                     sHostAddr = /*xT("207.46.172.252");*/    xT("forum.vingrad.ru");
		////USHORT                      usPort    = 27015;

		////m_bRes = CxDnsClient::bGetNameInfo(afFamily, sHostAddr, usPort);
		////xTEST_DIFF(FALSE, m_bRes);

		//xSTD_COUT(xT("[bGetNameInfo]: ") << sLocalHostName);
	}

	//-------------------------------------
	//bGetHostAddrInfo
	{
		std::tstring sHostName = xT("www.google.ru");
		std::tstring sPort     = xT("http");

		////ADDRINFOT aiHints  = {0};
		ADDRINFOT *paiList = NULL;

		m_bRes = CxDnsClient::bGetHostAddrInfo(sHostName, sPort, NULL, &paiList);
		xTEST_DIFF(FALSE, m_bRes);

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

        #if defined(xOS_ENV_WIN)
			#if defined(xCOMPILER_MS)
				::FreeAddrInfo(paiList);
			#else
				freeaddrinfo(paiList);
			#endif
        #elif defined(xOS_ENV_UNIX)
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
			std::tstring              sName;
			std::vector<std::tstring> vsAliases;
			SHORT                siNumber = - 1;

			m_bRes = CxDnsClient::bGetProtocolByName(cszProtocolNames[i], &sName, &vsAliases, &siNumber);
			xTEST_DIFF(FALSE, m_bRes);

			//std::tcout << xT("[bGetProtocolByName]: ")             << std::endl;
			//std::tcout << xT("	sName:    ") << sName             << std::endl;
			for (size_t j = 0; j < vsAliases.size(); ++ j) {
			//std::tcout << xT("	sAlias:   ") << vsAliases.at(j) << std::endl;
			}
			//std::tcout << xT("	siNumber: ") << siNumber          << std::endl;
			//std::tcout << xT("	--------------------")            << std::endl;
		}
        //std::tcout << std::endl;
	}

	//-------------------------------------
	//cszProtocolNumbers
	{
		const INT ciProtocolNumbers[] = {
		    0, 1, 3, 6, 8, 12, 17, 20, 22, 27
		};

		for (size_t i = 0; i < xARRAY_SIZE(ciProtocolNumbers); ++ i) {
			std::tstring              sName;
			std::vector<std::tstring> vsAliases;
			SHORT                siNumber = - 1;

			m_bRes = CxDnsClient::bGetProtocolByNumber(ciProtocolNumbers[i], &sName, &vsAliases, &siNumber);
			xTEST_DIFF(FALSE, m_bRes);

			//std::tcout << xT("[bGetProtocolByNumber]: ")           << std::endl;
			//std::tcout << xT("	sName:    ") << sName             << std::endl;;
			for (size_t j = 0; j < vsAliases.size(); ++ j) {
			//std::tcout << xT("	sAlias:   ") << vsAliases.at(j) << std::endl;
			}
			//std::tcout << xT("	siNumber: ") << siNumber          << std::endl;
			//std::tcout << xT("	--------------------")            << std::endl;
		}
        //std::tcout << std::endl;
	}

	//-------------------------------------
	//bGetServiceByName
	{
		std::tstring              csServiceName  = xT("http");
		const TCHAR          cszProtocolNames[][10] = {xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"), xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp") };
		std::tstring              sName;
		std::vector<std::tstring> vsAliases;
		SHORT                siPort;
		std::tstring              sProtocolName;

		m_bRes = CxDnsClient::bGetServiceByName(csServiceName, cszProtocolNames[3], &sName, &vsAliases, &siPort, &sProtocolName);
		xTEST_DIFF(FALSE, m_bRes);

		//std::tcout << xT("[bGetServiceByName]: ")                   << std::endl;
		//std::tcout << xT("	sName:         ") << sName             << std::endl;
		for (size_t i = 0; i < vsAliases.size(); ++ i) {
		//std::tcout << xT("	sAlias:        ") << vsAliases.at(i) << std::endl;
		}
		//std::tcout << xT("	siPort:        ") << siPort            << std::endl;
		//std::tcout << xT("	sProtocolName: ") << sProtocolName     << std::endl;
		//std::tcout << xT("	--------------------")                 << std::endl;
        //std::tcout << std::endl;
	}


	//-------------------------------------
	//bGetServiceByPort
	{
		SHORT                     csiPort  = 20480;
		const TCHAR               cszProtocolNames[][10] = {xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"), xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp") };
		std::tstring              sName;
		std::vector<std::tstring> vsAliases;
		SHORT                     siPort = - 1;
		std::tstring              sProtocolName;

		m_bRes = CxDnsClient::bGetServiceByPort(csiPort, cszProtocolNames[3], &sName, &vsAliases, &siPort, &sProtocolName);
		xTEST_DIFF(FALSE, m_bRes);

		//std::tcout << xT("[bGetServiceByPort]: ") << std::endl;
		//std::tcout << xT("	sName:         ") << sName << std::endl;
		for (size_t i = 0; i < vsAliases.size(); ++ i) {
		//std::tcout << xT("	sAlias:        ") << vsAliases.at(i) << std::endl;
		}
		//std::tcout << xT("	siPort:        ") << siPort          << std::endl;
		//std::tcout << xT("	sProtocolName: ") << sProtocolName   << std::endl;
        //std::tcout << xT("  --------------------")                 << std::endl;
        //std::tcout << std::endl;
	}

	return TRUE;
}
//---------------------------------------------------------------------------
