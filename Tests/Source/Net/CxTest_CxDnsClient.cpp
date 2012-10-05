/**
 * \file   CxTest_CxDnsClient.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxDnsClient.h>

#include <xLib/Net/CxSocketInit.h>


//---------------------------------------------------------------------------
CxTest_CxDnsClient::CxTest_CxDnsClient() {

}
//---------------------------------------------------------------------------
CxTest_CxDnsClient::~CxTest_CxDnsClient() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxDnsClient::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    //-------------------------------------
    //CxSocketInit
    CxSocketInit siInit(2, 2);

    //-------------------------------------
    //bGetHostAddrByName
    {
        std::tstring_t sHostName = xT("msdn.microsoft.com");
        std::tstring_t sHostAddr = xT("");

        CxDnsClient::vGetHostAddrByName(sHostName, &sHostAddr);

        //std::tcout << xT("[bGetHostAddrByName]: ") << sHostAddr << std::endl;
    }

    //-------------------------------------
    //bGetHostNameByAddr
    {
        std::tstring_t sHostName = xT("");
        std::tstring_t sHostAddr = xT("127.0.0.1");

        CxDnsClient::vGetHostNameByAddr(sHostAddr, CxSocket::afInet, &sHostName);

        //std::tcout << xT("[bGetHostNameByAddr]: ") << sHostName << std::endl;
    }

    //-------------------------------------
    //bGetLocalHostName
    {
        std::tstring_t sLocalHostName = xT("");

        CxDnsClient::vGetLocalHostName(&sLocalHostName);

        //std::tcout << xT("[bGetLocalHostName]: ") << sLocalHostName << std::endl;
    }

    //-------------------------------------
    //bGetNameInfo
    {
        ////CxDnsClient::ExAddressFamily afFamily  = CxDnsClient::afInet;
        ////std::tstring_t                     sHostAddr = /*xT("207.46.172.252");*/    xT("forum.vingrad.ru");
        ////ushort_t                      usPort    = 27015;

        ////m_bRv = CxDnsClient::bGetNameInfo(afFamily, sHostAddr, usPort);
        ////xTEST_EQ(true, m_bRv);

        //xSTD_COUT(xT("[bGetNameInfo]: ") << sLocalHostName);
    }

    //-------------------------------------
    //bGetHostAddrInfo
    {
        std::tstring_t sHostName = xT("www.google.ru");
        std::tstring_t sPort     = xT("http");

        ////addrinfo_t aiHints  = {0};
        addrinfo_t *paiList = NULL;

        CxDnsClient::vGetHostAddrInfo(sHostName, sPort, NULL, &paiList);

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

        #if   xOS_ENV_WIN
            #if xCOMPILER_MS
                ::FreeAddrInfo(paiList);
            #else
                freeaddrinfo(paiList);
            #endif
        #elif xOS_ENV_UNIX
               freeaddrinfo(paiList);
        #endif
        /*DEBUG*/// n/a
    }

    //-------------------------------------
    //bGetProtocolByName
    {
        const tchar_t cszProtocolNames[][10] =
        {
            xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"),
            xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp")
        };

        for (size_t i = 0; i < xARRAY_SIZE(cszProtocolNames); ++ i) {
            std::tstring_t     sName;
            std::vec_tstring_t vsAliases;
            short_t            siNumber = - 1;

            CxDnsClient::vGetProtocolByName(cszProtocolNames[i], &sName, &vsAliases, &siNumber);

            //std::tcout << xT("[bGetProtocolByName]: ")             << std::endl;
            //std::tcout << xT("    sName:    ") << sName             << std::endl;
            for (size_t j = 0; j < vsAliases.size(); ++ j) {
            //std::tcout << xT("    sAlias:   ") << vsAliases.at(j) << std::endl;
            }
            //std::tcout << xT("    siNumber: ") << siNumber          << std::endl;
            //std::tcout << xT("    --------------------")            << std::endl;
        }
        //std::tcout << std::endl;
    }

    //-------------------------------------
    //cszProtocolNumbers
    {
        const int ciProtocolNumbers[] = {
            0, 1, 3, 6, 8, 12, 17, 20, 22, 27
        };

        for (size_t i = 0; i < xARRAY_SIZE(ciProtocolNumbers); ++ i) {
            std::tstring_t     sName;
            std::vec_tstring_t vsAliases;
            short_t            siNumber = - 1;

            CxDnsClient::vGetProtocolByNumber(ciProtocolNumbers[i], &sName, &vsAliases, &siNumber);

            //std::tcout << xT("[bGetProtocolByNumber]: ")           << std::endl;
            //std::tcout << xT("    sName:    ") << sName             << std::endl;;
            for (size_t j = 0; j < vsAliases.size(); ++ j) {
            //std::tcout << xT("    sAlias:   ") << vsAliases.at(j) << std::endl;
            }
            //std::tcout << xT("    siNumber: ") << siNumber          << std::endl;
            //std::tcout << xT("    --------------------")            << std::endl;
        }
        //std::tcout << std::endl;
    }

    //-------------------------------------
    //bGetServiceByName
    {
        std::tstring_t     csServiceName  = xT("http");
        const tchar_t      cszProtocolNames[][10] = {xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"), xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp") };
        std::tstring_t     sName;
        std::vec_tstring_t vsAliases;
        short_t            siPort;
        std::tstring_t     sProtocolName;

        CxDnsClient::vGetServiceByName(csServiceName, cszProtocolNames[3], &sName, &vsAliases, &siPort, &sProtocolName);

        //std::tcout << xT("[bGetServiceByName]: ")                   << std::endl;
        //std::tcout << xT("    sName:         ") << sName             << std::endl;
        for (size_t i = 0; i < vsAliases.size(); ++ i) {
        //std::tcout << xT("    sAlias:        ") << vsAliases.at(i) << std::endl;
        }
        //std::tcout << xT("    siPort:        ") << siPort            << std::endl;
        //std::tcout << xT("    sProtocolName: ") << sProtocolName     << std::endl;
        //std::tcout << xT("    --------------------")                 << std::endl;
        //std::tcout << std::endl;
    }


    //-------------------------------------
    //bGetServiceByPort
    {
        short_t            csiPort  = 20480;
        const tchar_t      cszProtocolNames[][10] = {xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"), xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp") };
        std::tstring_t     sName;
        std::vec_tstring_t vsAliases;
        short_t            siPort = - 1;
        std::tstring_t     sProtocolName;

        CxDnsClient::vGetServiceByPort(csiPort, cszProtocolNames[3], &sName, &vsAliases, &siPort, &sProtocolName);

        //std::tcout << xT("[bGetServiceByPort]: ") << std::endl;
        //std::tcout << xT("    sName:         ") << sName << std::endl;
        for (size_t i = 0; i < vsAliases.size(); ++ i) {
        //std::tcout << xT("    sAlias:        ") << vsAliases.at(i) << std::endl;
        }
        //std::tcout << xT("    siPort:        ") << siPort          << std::endl;
        //std::tcout << xT("    sProtocolName: ") << sProtocolName   << std::endl;
        //std::tcout << xT("  --------------------")                 << std::endl;
        //std::tcout << std::endl;
    }


    //--------------------------------------------------
    //bIsOnLan
    xTEST_CASE(cullCaseLoops)
    {
        //TODO: m_bRv = CxDnsClient::bIsOnLan(const ulong_t culIp);
    }

    //--------------------------------------------------
    //bIsBroadcast
    xTEST_CASE(cullCaseLoops)
    {
        //TODO: m_bRv = CxDnsClient::bIsBroadcast(const ulong_t culIp);
    }
}
//---------------------------------------------------------------------------
