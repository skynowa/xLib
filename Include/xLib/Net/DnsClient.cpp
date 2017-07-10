/**
 * \file  DnsClient.inl
 * \brief DNS client
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "DnsClient.h"
#endif

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Utils.h>


xNAMESPACE_BEGIN2(xl, net)

/**************************************************************************************************
*    Public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
DnsClient::hostAddrByName(
    std::ctstring_t &a_hostName,
    std::tstring_t  *a_hostAddr
)
{
    xTEST_EQ(a_hostName.empty(), false);
    xTEST_PTR(a_hostAddr);

    std::tstring_t sRv;

    hostent *host = ::gethostbyname( xT2A(a_hostName).c_str() );
    xTEST_PTR(host);

    struct in_addr **addrList = reinterpret_cast<struct in_addr **>(host->h_addr_list);

    for (std::size_t i = 0; addrList[i] != xPTR_NULL; ++ i) {
        sRv = inet_ntoa(*addrList[i]);

        break;
    }

    xTEST_EQ(sRv.empty(), false);

    if (host->h_name != xPTR_NULL) {
        const std::string hostName = host->h_name;
        xTEST_EQ(hostName.empty(), false);
        xTEST_EQ(a_hostName, xA2T(hostName));
    }

    *a_hostAddr = sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
DnsClient::hostNameByAddr(
    std::ctstring_t               &a_hostAddr,
    const ISocket::ExAddressFamily &a_family,
    std::tstring_t                *a_hostName
)
{
    xTEST_EQ(a_hostAddr.empty(), false);
    xTEST_PTR(a_hostName);

    hostent *host = xPTR_NULL;

    switch (a_family) {
    case ISocket::afInet:
		{
			in_addr iaAddr = {0};

			iaAddr.s_addr = ::inet_addr( xT2A(a_hostAddr).c_str() );
			xTEST_DIFF(iaAddr.s_addr, INADDR_NONE);

			host = ::gethostbyaddr(reinterpret_cast<char *>(&iaAddr), sizeof(iaAddr), ISocket::afInet);
			xTEST_PTR(host);
		}
        break;
#if (xWINVER >= xOS_WIN_VISTA)
    case ISocket::afInet6:
		{
		#if xTODO
			IN6_ADDR iaAddr6 = {0};

			iRv = ::inet_pton(afInet6, a_casHostAddr.c_str(), &iaAddr6);
			xTEST_DIFF(iRv, 0);

			host = ::gethostbyaddr(reinterpret_cast<char *>( &iaAddr6 ), 16, afInet6);
			xTEST_PTR(host);
		#endif
		}
        break;
#endif
    default:
		{
			*a_hostName = xA2T("");
			return;
		}
    	break;
    }

    *a_hostName = xA2T(host->h_name);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
DnsClient::localHostName(
    std::tstring_t *a_hostName
)
{
    xTEST_PTR(a_hostName);

    std::string asRv(xHOST_NAME_MAX, '0');

    int_t iRv = ::gethostname(&asRv.at(0), (asRv.size() * sizeof(std::string::value_type) ));
    xTEST_EQ(iRv, 0);

    asRv.assign(asRv.c_str());    // trim '0' from end

    *a_hostName = xA2T(asRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
DnsClient::nameInfo(
    ISocket::ExAddressFamily &a_family,
    std::ctstring_t         &a_hostAddr,
    cushort_t               &a_port
)
{
    xTEST_NA(a_family);
    xTEST_EQ(a_hostAddr.empty(), false);
    xTEST_GR(a_port, static_cast<ushort_t>(0));

    sockaddr_in socketAddr; xSTRUCT_ZERO(socketAddr);
    socketAddr.sin_family      = a_family;
    socketAddr.sin_addr.s_addr = ::inet_addr( xT2A(a_hostAddr).c_str() );
    socketAddr.sin_port        = htons(a_port);

    tchar_t hostName[NI_MAXHOST + 1] = {0};
    tchar_t servInfo[NI_MAXSERV + 1] = {0};

    // TODO: DnsClient::nameInfo()
    int_t iRv = xGETNAMEINFO(reinterpret_cast<sockaddr *>(&socketAddr), sizeof(socketAddr),
        &hostName[0], NI_MAXHOST, &servInfo[0], NI_MAXSERV, NI_NUMERICSERV);
    xTEST_EQ(iRv, 0);

    //hostname
}
//-------------------------------------------------------------------------------------------------
// NOTE: http://www.geekpage.jp/en/programming/linux-network/getaddrinfo-0.php
/* static */
xINLINE void_t
DnsClient::hostAddrInfo(
    std::ctstring_t  &a_hostName,
    std::ctstring_t  &a_port,
    caddrinfo_t      *a_hints,
    addrinfo_t      **a_addrInfo
)
{
    xTEST_EQ(a_hostName.empty(), false);
    xTEST_EQ(a_port.empty(), false);
    xTEST_PTR(a_hints);
    xTEST_PTR(a_addrInfo);
    xTEST_PTR(*a_addrInfo);

    int_t iRv = xGETADDRINFO(a_hostName.c_str(), a_port.c_str(), a_hints, a_addrInfo);
    xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
DnsClient::protocolByName(
    std::ctstring_t    &a_protocolName,
    std::tstring_t     *a_name,
    std::vec_tstring_t *a_aliases,
    int_t              *a_number
)
{
    xTEST_EQ(a_protocolName.empty(), false);
    xTEST_NA(a_name);
    xTEST_NA(a_aliases);
    xTEST_NA(a_number);

    protoent/*PROTOENT*/ *info = ::getprotobyname( xT2A(a_protocolName).c_str() );
    xTEST_PTR(info);

    // a_name
    if (a_name != xPTR_NULL) {
        *a_name = xA2T(info->p_name);
    }

    // a_aliases
    if (a_aliases != xPTR_NULL) {
        a_aliases->clear();

        for (char **s = info->p_aliases; s && *s; ++ s) {
            a_aliases->push_back( xA2T(*s) );
        }
    }

    // a_number
    Utils::ptrAssignT(a_number, *a_number = info->p_proto);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
DnsClient::protocolByNumber(
    cint_t             &a_number,
    std::tstring_t     *a_name,
    std::vec_tstring_t *a_aliases,
    int_t              *a_number_rv
)
{
    xTEST_NA(a_number);
    xTEST_NA(a_name);
    xTEST_NA(a_aliases);
    xTEST_NA(a_number_rv);

    protoent/*PROTOENT*/ *info = ::getprotobynumber(a_number);
    xTEST_PTR(info);

    // a_name
    if (a_name != xPTR_NULL) {
        *a_name = xA2T(info->p_name);
    }

    // a_aliases
    if (a_aliases != xPTR_NULL) {
        a_aliases->clear();

        for (char **s = info->p_aliases; s && *s; ++ s) {
            a_aliases->push_back( xA2T(*s) );
        }
    }

    // a_number_rv
    Utils::ptrAssignT(a_number_rv, *a_number_rv = info->p_proto);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
DnsClient::serviceByName(
    std::ctstring_t    &a_serviceName,
    std::ctstring_t    &a_protocolName,
    std::tstring_t     *a_name,
    std::vec_tstring_t *a_aliases,
    int_t              *a_port,
    std::tstring_t     *a_protocolName_rv
)
{
    xTEST_EQ(a_serviceName.empty(), false);
    xTEST_EQ(a_protocolName.empty(), false);
    xTEST_NA(a_name);
    xTEST_NA(a_aliases);
    xTEST_NA(a_port);
    xTEST_NA(a_protocolName_rv);

    servent *info = ::getservbyname(xT2A(a_serviceName).c_str(), xT2A(a_protocolName).c_str());
    xTEST_PTR(info);

    // name
    if (a_name != xPTR_NULL) {
       *a_name = xA2T(info->s_name);
    }

    // aliases
    if (a_aliases != xPTR_NULL) {
        a_aliases->clear();

        for (char **s = info->s_aliases; s && *s; ++ s) {
            a_aliases->push_back( xA2T(*s) );
        }
    }

    // port
    Utils::ptrAssignT(a_port, *a_port = info->s_port);

    // protocolName_rv
    if (a_protocolName_rv != xPTR_NULL) {
        *a_protocolName_rv = xA2T(info->s_proto);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
DnsClient::serviceByPort(
    cushort_t          &a_port,
    std::ctstring_t    &a_protocolName,
    std::tstring_t     *a_name,
    std::vec_tstring_t *a_aliases,
    short_t            *a_port_rv,
    std::tstring_t     *a_protocolName_rv
)
{
    xTEST_GR(a_port, static_cast<ushort_t>(0));
    xTEST_EQ(a_protocolName.empty(), false);
    xTEST_NA(a_name);
    xTEST_NA(a_aliases);
    xTEST_NA(a_port_rv);
    xTEST_NA(a_protocolName_rv);

    servent *info = ::getservbyport(a_port, xT2A(a_protocolName).c_str());
    xTEST_PTR(info);

    // name
    if (a_name != xPTR_NULL) {
        *a_name = xA2T(info->s_name);
    }

    // aliases
    if (a_aliases != xPTR_NULL) {
        a_aliases->clear();

        for (char **s = info->s_aliases; s && *s; ++ s) {
            a_aliases->push_back( xA2T(*s) );
        }
    }

    // port
    Utils::ptrAssignT(a_port_rv, static_cast<short_t>( info->s_port ));

    // protocolName_rv
    if (a_protocolName_rv != xPTR_NULL) {
        *a_protocolName_rv = xA2T(info->s_proto);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE bool_t
DnsClient::isOnLan(
    cuint_t &a_ip
)
{
    cuint_t localIp = INADDR_ANY;  // IP of local interface (network order)
    cuint_t netMask = INADDR_NONE; // net mask for IP (network order)

    return (((ntohl(a_ip) ^ ntohl(localIp)) & ntohl(netMask)) == 0UL);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE bool_t
DnsClient::isBroadcast(
    cuint_t &a_ip
)
{
    cuint_t netMask = INADDR_NONE; // net mask for IP (network order)

    return ((~ntohl(a_ip) & ~ntohl(netMask)) == 0UL);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE bool_t
DnsClient::isAddressIpv4(
    std::ctstring_t &a_ip
)
{
    sockaddr_in sa; xSTRUCT_ZERO(sa);

    return (::inet_pton(AF_INET, xT2A(a_ip).c_str(), &sa.sin_addr) != 0);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE bool_t
DnsClient::isAddressIpv6(
    std::ctstring_t &a_ip
)
{
    sockaddr_in6 sa; xSTRUCT_ZERO(sa);

    return (::inet_pton(AF_INET6, xT2A(a_ip).c_str(), &sa.sin6_addr) != 0);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, net)
