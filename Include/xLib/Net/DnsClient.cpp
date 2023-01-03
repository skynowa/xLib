/**
 * \file  DnsClient.inl
 * \brief DNS client
 */


#include "DnsClient.h"

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Utils.h>


namespace xl::net
{

/**************************************************************************************************
*    Public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
DnsClient::hostAddrByName(
    std::ctstring_t &a_hostName,
    std::tstring_t  *out_hostAddr
)
{
    xTEST(!a_hostName.empty());
    xTEST_PTR(out_hostAddr);

    std::tstring_t sRv;

    hostent *host = ::gethostbyname( xT2A(a_hostName).c_str() );
    xTEST_PTR(host);
    xCHECK_DO(host == nullptr, return);

    auto addrList = reinterpret_cast<struct in_addr **>(host->h_addr_list);

    for (std::size_t i = 0; addrList[i] != nullptr; ++ i) {
        sRv = Format::str(xT("{} "), ::inet_ntoa(*addrList[i]));
    }

    sRv = String::trimSpace(sRv);
    xTEST(!sRv.empty());

    if (host->h_name != nullptr) {
        std::cstring_t hostName = host->h_name;
        xTEST(!hostName.empty());
    }

    *out_hostAddr = sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
DnsClient::hostNameByAddr(
    std::ctstring_t              &a_hostAddr,
    const ISocket::AddressFamily &a_family,
    std::tstring_t               *out_hostName
)
{
    xTEST(!a_hostAddr.empty());
    xTEST_PTR(out_hostName);

    hostent *host {};

    switch (a_family) {
    case ISocket::AddressFamily::afInet:
		{
			in_addr iaAddr {};
			iaAddr.s_addr = ::inet_addr( xT2A(a_hostAddr).c_str() );
			xTEST_DIFF(iaAddr.s_addr, INADDR_NONE);

			host = ::gethostbyaddr(reinterpret_cast<char *>(&iaAddr), sizeof(iaAddr),
				static_cast<int_t>(ISocket::AddressFamily::afInet));
			xTEST_PTR(host);
		}
        break;
#if (xWINVER >= xOS_WIN_VISTA)
    case ISocket::AddressFamily::afInet6:
		{
		#if xTODO
			IN6_ADDR iaAddr6 {};
			iRv = ::inet_pton(afInet6, a_casHostAddr.c_str(), &iaAddr6);
			xTEST_DIFF(iRv, 0);

			*out_hostName = ::gethostbyaddr(reinterpret_cast<char *>( &iaAddr6 ), 16,
				static_cast<std::size_t>(ISocket::AddressFamily::afInet6));
			xTEST_PTR(host);
		#endif
		}
        break;
#endif
    default:
		{
			*out_hostName = xA2T("");
			return;
		}
    	break;
    }

    xCHECK_DO(host == nullptr, return);

    *out_hostName = xA2T(host->h_name);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
DnsClient::localHostName(
    std::tstring_t *out_hostName
)
{
    xTEST_PTR(out_hostName);

    std::string asRv(xHOST_NAME_MAX, '0');

#if   xENV_WIN
    const auto   hostNameSize = static_cast<int_t>(asRv.size() * sizeof(std::string::value_type));
#elif xENV_UNIX
    std::csize_t hostNameSize = asRv.size() * sizeof(std::string::value_type);
#endif

    int_t iRv = ::gethostname(&asRv.at(0), hostNameSize);
    xTEST_EQ(iRv, 0);

    asRv.assign(asRv.c_str());    // trim '0' from end

    *out_hostName = xA2T(asRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
DnsClient::nameInfo(
    ISocket::cAddressFamily &a_family,		///< address family
    std::ctstring_t         &a_hostAddr,	///< IP address
    cushort_t               &a_hostPort,	///< port
	std::tstring_t          *out_name,		///< [out] host name
	std::tstring_t          *out_port		///< [out] service name
)
{
    xTEST_NA(a_family);
    xTEST(!a_hostAddr.empty());
    xTEST_GR(a_hostPort, static_cast<ushort_t>(0));
	xTEST_NA(out_name);
	xTEST_NA(out_port);

    sockaddr_in socketAddr {};
    socketAddr.sin_family      = static_cast<sa_family_t>(a_family);
    socketAddr.sin_addr.s_addr = ::inet_addr( xT2A(a_hostAddr).c_str() );
    socketAddr.sin_port        = htons(a_hostPort);

    tchar_t hostName[NI_MAXHOST + 1] = {0};
    tchar_t hostPort[NI_MAXSERV + 1] = {0};

    int_t iRv = xNAME_INFO_GET(reinterpret_cast<sockaddr *>(&socketAddr), sizeof(socketAddr),
        &hostName[0], NI_MAXHOST, &hostPort[0], NI_MAXSERV, NI_NUMERICSERV);
#if   xENV_WIN
    xTEST_EQ(iRv, 0);
#elif xENV_UNIX
    xTEST_EQ_MSG(iRv, 0, ::gai_strerror(iRv));
#endif

    // [out]
    if (out_name != nullptr) {
    	*out_name = hostName;
    }

    if (out_port != nullptr) {
    	xTEST_EQ(a_hostPort, (ushort_t)std::atoi(hostPort));
    	*out_port = hostPort;
    }
}
//-------------------------------------------------------------------------------------------------
// NOTE: http://www.geekpage.jp/en/programming/linux-network/getaddrinfo-0.php
/* static */
void_t
DnsClient::hostAddrInfo(
    std::ctstring_t  &a_hostName,
    std::ctstring_t  &a_port,
    caddrinfo_t      *out_hints,		///< maybe nullptr
    addrinfo_t      **out_addrInfo
)
{
    xTEST(!a_hostName.empty());
    xTEST(!a_port.empty());
    xTEST_NA(out_hints);
    xTEST_PTR(out_addrInfo);

    int_t iRv = xADDR_INFO_GET(a_hostName.c_str(), a_port.c_str(), out_hints, out_addrInfo);
#if   xENV_WIN
    xTEST_EQ(iRv, 0);
#elif xENV_UNIX
    xTEST_EQ_MSG(iRv, 0, ::gai_strerror(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
DnsClient::protocolByName(
    std::ctstring_t    &a_protocolName,
    std::tstring_t     *a_name,
    std::vec_tstring_t *out_aliases,
    int_t              *out_number
)
{
    xTEST(!a_protocolName.empty());
    xTEST_NA(a_name);
    xTEST_NA(out_aliases);
    xTEST_NA(out_number);

    protoent/*PROTOENT*/ *info = ::getprotobyname( xT2A(a_protocolName).c_str() );
    xTEST_PTR(info);
    xCHECK_DO(info == nullptr, return);

    // a_name
    if (a_name != nullptr) {
        *a_name = xA2T(info->p_name);
    }

    // out_aliases
    if (out_aliases != nullptr) {
        out_aliases->clear();

        for (char **s = info->p_aliases; s && *s; ++ s) {
            out_aliases->push_back( xA2T(*s) );
        }
    }

    // a_number
    Utils::ptrAssignT(out_number, *out_number = info->p_proto);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
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
    xCHECK_DO(info == nullptr, return);

    // a_name
    if (a_name != nullptr) {
        *a_name = xA2T(info->p_name);
    }

    // a_aliases
    if (a_aliases != nullptr) {
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
void_t
DnsClient::serviceByName(
    std::ctstring_t    &a_serviceName,
    std::ctstring_t    &a_protocolName,
    std::tstring_t     *a_name,
    std::vec_tstring_t *a_aliases,
    int_t              *a_port,
    std::tstring_t     *a_protocolName_rv
)
{
    xTEST(!a_serviceName.empty());
    xTEST(!a_protocolName.empty());
    xTEST_NA(a_name);
    xTEST_NA(a_aliases);
    xTEST_NA(a_port);
    xTEST_NA(a_protocolName_rv);

    servent *info = ::getservbyname(xT2A(a_serviceName).c_str(), xT2A(a_protocolName).c_str());
    xTEST_PTR(info);
    xCHECK_DO(info == nullptr, return);

    // name
    if (a_name != nullptr) {
       *a_name = xA2T(info->s_name);
    }

    // aliases
    if (a_aliases != nullptr) {
        a_aliases->clear();

        for (char **s = info->s_aliases; s && *s; ++ s) {
            a_aliases->push_back( xA2T(*s) );
        }
    }

    // port
    Utils::ptrAssignT(a_port, *a_port = info->s_port);

    // protocolName_rv
    if (a_protocolName_rv != nullptr) {
        *a_protocolName_rv = xA2T(info->s_proto);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
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
    xTEST(!a_protocolName.empty());
    xTEST_NA(a_name);
    xTEST_NA(a_aliases);
    xTEST_NA(a_port_rv);
    xTEST_NA(a_protocolName_rv);

    servent *info = ::getservbyport(a_port, xT2A(a_protocolName).c_str());
    xTEST_PTR(info);
    xCHECK_DO(info == nullptr, return);

    // name
    if (a_name != nullptr) {
        *a_name = xA2T(info->s_name);
    }

    // aliases
    if (a_aliases != nullptr) {
        a_aliases->clear();

        for (char **s = info->s_aliases; s && *s; ++ s) {
            a_aliases->push_back( xA2T(*s) );
        }
    }

    // port
    Utils::ptrAssignT(a_port_rv, static_cast<short_t>( info->s_port ));

    // protocolName_rv
    if (a_protocolName_rv != nullptr) {
        *a_protocolName_rv = xA2T(info->s_proto);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
DnsClient::isOnLan(
    cuint_t &a_ip
)
{
    cuint_t localIp = INADDR_ANY;  // IP of local interfaCe (network order)
    cuint_t netMask = INADDR_NONE; // net mask for IP (network order)

    return (((ntohl(a_ip) ^ ntohl(localIp)) & ntohl(netMask)) == 0UL);
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
DnsClient::isBroadcast(
    cuint_t &a_ip
)
{
    cuint_t netMask = INADDR_NONE; // net mask for IP (network order)

    return ((~ntohl(a_ip) & ~ntohl(netMask)) == 0UL);
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
DnsClient::isAddressIpv4(
    std::ctstring_t &a_ip
)
{
    sockaddr_in sa {};

    return (::inet_pton(AF_INET, xT2A(a_ip).c_str(), &sa.sin_addr) != 0);
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
DnsClient::isAddressIpv6(
    std::ctstring_t &a_ip
)
{
    sockaddr_in6 sa {};

    return (::inet_pton(AF_INET6, xT2A(a_ip).c_str(), &sa.sin6_addr) != 0);
}
//-------------------------------------------------------------------------------------------------

} // namespace
