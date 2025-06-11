/**
 * \file   Test_DnsClient.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_DnsClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_DnsClient::unit()
{
    SocketInit siInit(2, 2);

    xTEST_CASE("hostAddrByName")
    {
        std::ctstring_t hostName = xT("msdn.microsoft.com");

        std::tstring_t hostAddr;
        DnsClient::hostAddrByName(hostName, &hostAddr);
		xTEST(!hostAddr.empty());
    }

    xTEST_CASE("hostNameByAddr")
    {
        std::ctstring_t hostAddr = xT("127.0.0.1");

        std::tstring_t hostName;
        DnsClient::hostNameByAddr(hostAddr, ISocket::AddressFamily::afInet, &hostName);
        xTEST(!hostAddr.empty());
    }

    xTEST_CASE("localHostName")
    {
        std::tstring_t localHostName;
        DnsClient::localHostName(&localHostName);
        xTEST(!localHostName.empty());
    }

    xTEST_CASE("nameInfo")
    {
        ISocket::cAddressFamily family   = ISocket::AddressFamily::afInet;
        std::ctstring_t         hostAddr = xT("127.0.0.1");
        cushort_t               hostPort = 27015;

		std::tstring_t name;
		std::tstring_t port;
        DnsClient::nameInfo(family, hostAddr, hostPort, &name, &port);
        // LogCout() << xTRACE_VAR_2(name, port) << std::endl;
        xTEST_EQ(name, std::tstring_t(xT("localhost")));
        xTEST_EQ(port, std::to_string(hostPort));
    }

    xTEST_CASE("hostAddrInfo")
    {
        std::ctstring_t hostName = xT("www.google.com");
        std::ctstring_t port     = xT("http");

        addrinfo_t hints {};
		hints.ai_family    = AF_UNSPEC;		// Allow IPv4 or IPv6
		hints.ai_socktype  = SOCK_STREAM;
		hints.ai_flags     = AI_PASSIVE;	// For wildcard IP address
		hints.ai_protocol  = 0;				// Any protocol
		hints.ai_canonname = nullptr;
		hints.ai_addr      = nullptr;
		hints.ai_next      = nullptr;

        addrinfo_t *result {};
        DnsClient::hostAddrInfo(hostName, port, &hints, &result);
        xTEST_PTR(result);

        xADDR_INFO_FREE(result);
        result = nullptr;
    }

    xTEST_CASE("protocolByName")
    {
        ctchar_t cszProtocolNames[][10] =
        {
            xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"),
            xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp")
        };

        for (size_t i = 0; i < xARRAY_SIZE(cszProtocolNames); ++ i) {
            std::tstring_t     sName;
            std::vec_tstring_t vsAliases;
            int_t              siNumber = - 1;

            DnsClient::protocolByName(cszProtocolNames[i], &sName, &vsAliases, &siNumber);

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

    xTEST_CASE("protocolByNumber")
    {
        constexpr cint_t ciProtocolNumbers[] = {
            0, 1, 3, 6, 8, 12, 17, 20, 22, 27
        };

        for (size_t i = 0; i < xARRAY_SIZE(ciProtocolNumbers); ++ i) {
            std::tstring_t     sName;
            std::vec_tstring_t vsAliases;
            int_t              siNumber = - 1;

            DnsClient::protocolByNumber(ciProtocolNumbers[i], &sName, &vsAliases, &siNumber);

            //std::tcout << xT("[protocolByNumber]: ")           << std::endl;
            //std::tcout << xT("    sName:    ") << sName             << std::endl;
            for (size_t j = 0; j < vsAliases.size(); ++ j) {
            //std::tcout << xT("    sAlias:   ") << vsAliases.at(j) << std::endl;
            }
            //std::tcout << xT("    siNumber: ") << siNumber          << std::endl;
            //std::tcout << xT("    --------------------")            << std::endl;
        }
        //std::tcout << std::endl;
    }

    xTEST_CASE("serviceByName")
    {
        std::tstring_t     csServiceName  = xT("http");
        ctchar_t           cszProtocolNames[][10] = {xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"), xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp") };
        std::tstring_t     sName;
        std::vec_tstring_t vsAliases;
        int_t              siPort;
        std::tstring_t     sProtocolName;

        DnsClient::serviceByName(csServiceName, cszProtocolNames[3], &sName, &vsAliases, &siPort, &sProtocolName);

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

    xTEST_CASE("serviceByPort")
    {
        ushort_t           port  = 20480;
        ctchar_t           cszProtocolNames[][10] = {xT("ip"), xT("icmp"), xT("ggp"), xT("tcp"), xT("egp"), xT("pup"), xT("udp"), xT("hmp"), xT("xns-idp"), xT("rdp") };
        std::tstring_t     sName;
        std::vec_tstring_t vsAliases;
        short_t            siPort = - 1;
        std::tstring_t     sProtocolName;

        DnsClient::serviceByPort(port, cszProtocolNames[3], &sName, &vsAliases, &siPort, &sProtocolName);

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

    xTEST_CASE("isOnLan")
    {
        // TEST: DnsClient::isOnLan()
    }

    xTEST_CASE("isBroadcast")
    {
        // TEST: DnsClient::isBroadcast()
    }

    xTEST_CASE("isAddressIpv4")
    {
        // http://www.zedwood.com/article/cpp-is-valid-ip-address-ipv4-ipv6

        const Data2<std::tstring_t, bool_t> data[] =
        {
            {"1.1.1.1", true},
            {"1.1.1.1:443", false},
            {"65536", false},
            {"1.1.1.01", false},
            {"256.1.1.1", false},
            {"1.1.1.1.2", false},
            {"1.1.1", false},
            {"a.b.c.d", false},
            {"1::8:", false}
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
        	LogCout() << xTRACE_VAR(data[i].test);
            m_bRv = DnsClient::isAddressIpv4(data[i].test);
            xSTD_VERIFY(m_bRv == data[i].expect);
            xTEST_EQ(m_bRv, data[i].expect);
        }
    }

    xTEST_CASE("isAddressIpv6")
    {
        const Data2<std::tstring_t, bool_t> data[] =
        {
            {"1::8", true},
            {"2400:cb00:2048:1::6ca2:e8c3", true},
            {"2001:db8::ff00:42:8329", true},
            {"2001:0db8:0000:0000:0000:ff00:0042:8329", true},
            {"[2001:db8::ff00:42:8329]", false},
            {"127.0.0.1", false},
            {":1::8", false},
            {"1::8:", false},
            {"1..8", false}
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            m_bRv = DnsClient::isAddressIpv6(data[i].test);
            xTEST_EQ(m_bRv, data[i].expect);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
