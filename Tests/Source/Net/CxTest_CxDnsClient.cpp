/**
 * \file   CxTest_CxDnsClient.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxDnsClient.h>

#include <xLib/Net/CxSocketInit.h>


//------------------------------------------------------------------------------
CxTest_CxDnsClient::CxTest_CxDnsClient() {

}
//------------------------------------------------------------------------------
CxTest_CxDnsClient::~CxTest_CxDnsClient() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxDnsClient::unit(
    culonglong_t &cullCaseLoops
)
{
    CxSocketInit siInit(2, 2);

    xTEST_CASE("CxDnsClient::hostAddrByName", cullCaseLoops)
    {
        std::tstring_t sHostName = xT("msdn.microsoft.com");
        std::tstring_t sHostAddr = xT("");

        CxDnsClient::hostAddrByName(sHostName, &sHostAddr);

        //std::tcout << xT("[hostAddrByName]: ") << sHostAddr << std::endl;
    }

    xTEST_CASE("CxDnsClient::hostNameByAddr", cullCaseLoops)
    {
        std::tstring_t sHostName = xT("");
        std::tstring_t sHostAddr = xT("127.0.0.1");

        CxDnsClient::hostNameByAddr(sHostAddr, CxSocket::afInet, &sHostName);

        //std::tcout << xT("[hostNameByAddr]: ") << sHostName << std::endl;
    }

    xTEST_CASE("CxDnsClient::localHostName", cullCaseLoops)
    {
        std::tstring_t sLocalHostName = xT("");

        CxDnsClient::localHostName(&sLocalHostName);

        //std::tcout << xT("[localHostName]: ") << sLocalHostName << std::endl;
    }

    xTEST_CASE("CxDnsClient::nameInfo", cullCaseLoops)
    {
        ////CxDnsClient::ExAddressFamily afFamily  = CxDnsClient::afInet;
        ////std::tstring_t                     sHostAddr = /*xT("207.46.172.252");*/    xT("forum.vingrad.ru");
        ////ushort_t                      usPort    = 27015;

        ////m_bRv = CxDnsClient::nameInfo(afFamily, sHostAddr, usPort);
        ////xTEST_EQ(true, m_bRv);

        //xSTD_COUT(xT("[nameInfo]: ") << sLocalHostName);
    }

    xTEST_CASE("CxDnsClient::hostAddrInfo", cullCaseLoops)
    {
        std::tstring_t sHostName = xT("www.google.ru");
        std::tstring_t sPort     = xT("http");

        ////addrinfo_t aiHints  = {0};
        addrinfo_t *paiList = NULL;

        CxDnsClient::hostAddrInfo(sHostName, sPort, NULL, &paiList);

        //xSTD_COUT(xT("[hostAddrInfo]: ") << sLocalHostName);

        {
            ///*int_t*/                 paiList->ai_flags;       // AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST
            ///*int_t*/                 paiList->ai_family;      // PF_xxx
            ///*int_t*/                 paiList->ai_socktype;    // SOCK_xxx
            ///*int_t*/                 paiList->ai_protocol;    // 0 or IPPROTO_xxx for IPv4 and IPv6
            ///*size_t*/              paiList->ai_addrlen;     // Length of ai_addr
            ///*char **/              paiList->ai_canonname;   // Canonical name for nodename
            ///*__field_bcount(ai_addrlen) struct sockaddr **/   paiList->ai_addr;        // Binary address
            ///*struct addrinfo **/   paiList->ai_next;        // Next structure in linked list
        }

        #if   xOS_ENV_WIN
            #if xCOMPILER_MS
                ::FreeAddrInfo(paiList);
            #else
                freeaddrinfo(paiList);
            #endif
        #elif xOS_ENV_UNIX
               freeaddrinfo(paiList);
        #endif
        // n/a
    }

    xTEST_CASE("CxDnsClient::protocolByName", cullCaseLoops)
    {
        ctchar_t cszProtocolNames[][10] =
        {
            xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"),
            xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp")
        };

        for (size_t i = 0; i < xARRAY_SIZE(cszProtocolNames); ++ i) {
            std::tstring_t     sName;
            std::vec_tstring_t vsAliases;
            short_t            siNumber = - 1;

            CxDnsClient::protocolByName(cszProtocolNames[i], &sName, &vsAliases, &siNumber);

            //std::tcout << xT("[protocolByName]: ")             << std::endl;
            //std::tcout << xT("    sName:    ") << sName             << std::endl;
            for (size_t j = 0; j < vsAliases.size(); ++ j) {
            //std::tcout << xT("    sAlias:   ") << vsAliases.at(j) << std::endl;
            }
            //std::tcout << xT("    siNumber: ") << siNumber          << std::endl;
            //std::tcout << xT("    --------------------")            << std::endl;
        }
        //std::tcout << std::endl;
    }

    xTEST_CASE("CxDnsClient::protocolByNumber", cullCaseLoops)
    {
        cint_t ciProtocolNumbers[] = {
            0, 1, 3, 6, 8, 12, 17, 20, 22, 27
        };

        for (size_t i = 0; i < xARRAY_SIZE(ciProtocolNumbers); ++ i) {
            std::tstring_t     sName;
            std::vec_tstring_t vsAliases;
            short_t            siNumber = - 1;

            CxDnsClient::protocolByNumber(ciProtocolNumbers[i], &sName, &vsAliases, &siNumber);

            //std::tcout << xT("[protocolByNumber]: ")           << std::endl;
            //std::tcout << xT("    sName:    ") << sName             << std::endl;;
            for (size_t j = 0; j < vsAliases.size(); ++ j) {
            //std::tcout << xT("    sAlias:   ") << vsAliases.at(j) << std::endl;
            }
            //std::tcout << xT("    siNumber: ") << siNumber          << std::endl;
            //std::tcout << xT("    --------------------")            << std::endl;
        }
        //std::tcout << std::endl;
    }

    xTEST_CASE("CxDnsClient::serviceByName", cullCaseLoops)
    {
        std::tstring_t     csServiceName  = xT("http");
        ctchar_t      cszProtocolNames[][10] = {xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"), xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp") };
        std::tstring_t     sName;
        std::vec_tstring_t vsAliases;
        short_t            siPort;
        std::tstring_t     sProtocolName;

        CxDnsClient::serviceByName(csServiceName, cszProtocolNames[3], &sName, &vsAliases, &siPort, &sProtocolName);

        //std::tcout << xT("[serviceByName]: ")                   << std::endl;
        //std::tcout << xT("    sName:         ") << sName             << std::endl;
        for (size_t i = 0; i < vsAliases.size(); ++ i) {
        //std::tcout << xT("    sAlias:        ") << vsAliases.at(i) << std::endl;
        }
        //std::tcout << xT("    siPort:        ") << siPort            << std::endl;
        //std::tcout << xT("    sProtocolName: ") << sProtocolName     << std::endl;
        //std::tcout << xT("    --------------------")                 << std::endl;
        //std::tcout << std::endl;
    }

    xTEST_CASE("CxDnsClient::serviceByPort", cullCaseLoops)
    {
        short_t            csiPort  = 20480;
        ctchar_t      cszProtocolNames[][10] = {xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"), xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp") };
        std::tstring_t     sName;
        std::vec_tstring_t vsAliases;
        short_t            siPort = - 1;
        std::tstring_t     sProtocolName;

        CxDnsClient::serviceByPort(csiPort, cszProtocolNames[3], &sName, &vsAliases, &siPort, &sProtocolName);

        //std::tcout << xT("[serviceByPort]: ") << std::endl;
        //std::tcout << xT("    sName:         ") << sName << std::endl;
        for (size_t i = 0; i < vsAliases.size(); ++ i) {
        //std::tcout << xT("    sAlias:        ") << vsAliases.at(i) << std::endl;
        }
        //std::tcout << xT("    siPort:        ") << siPort          << std::endl;
        //std::tcout << xT("    sProtocolName: ") << sProtocolName   << std::endl;
        //std::tcout << xT("  --------------------")                 << std::endl;
        //std::tcout << std::endl;
    }
    
    xTEST_CASE("CxDnsClient::isOnLan", cullCaseLoops)
    {
        //TODO: m_bRv = CxDnsClient::isOnLan(culong_t culIp);
    }

    xTEST_CASE("CxDnsClient::isBroadcast", cullCaseLoops)
    {
        //TODO: m_bRv = CxDnsClient::isBroadcast(culong_t culIp);
    }
}
//------------------------------------------------------------------------------
