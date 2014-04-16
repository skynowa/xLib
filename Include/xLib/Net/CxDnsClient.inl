/**
 * \file  CxDnsClient.cpp
 * \brief DNS
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>


xNAMESPACE2_BEGIN(xlib, net)

/**************************************************************************************************
*    Public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxDnsClient::hostAddrByName(
    std::ctstring_t &a_hostName,
    std::tstring_t  *a_hostAddr
)
{
    xTEST_EQ(a_hostName.empty(), false);
    xTEST_PTR(a_hostAddr);

    std::tstring_t sRv;

    // convert to UNICODE
    std::string hostName(a_hostName.begin(), a_hostName.end());

    hostent *host = ::gethostbyname(hostName.c_str());
    xTEST_PTR(host);

    sRv = CxString::format(
        xT("%u.%u.%u.%u"),
        static_cast<uchar_t>(host->h_addr_list[0][0]),
        static_cast<uchar_t>(host->h_addr_list[0][1]),
        static_cast<uchar_t>(host->h_addr_list[0][2]),
        static_cast<uchar_t>(host->h_addr_list[0][3])
    );
    xTEST_EQ(sRv.empty(), false);

    *a_hostAddr = sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxDnsClient::hostNameByAddr(
    std::ctstring_t                 &a_hostAddr,
    const CxSocket::ExAddressFamily &a_family,
    std::tstring_t                  *a_hostName
)
{
    xTEST_EQ(a_hostAddr.empty(), false);
    xTEST_PTR(a_hostName);

    // convert to UNICODE
    std::string hostAddr(a_hostAddr.begin(), a_hostAddr.end());

    hostent *host = xPTR_NULL;

    switch (a_family) {
    case CxSocket::afInet6:
    #if (xWINVER >= xOS_WIN_VISTA)
        #if xTODO
            IN6_ADDR iaAddr6 = {0};

            iRv = ::inet_pton(afInet6, a_casHostAddr.c_str(), &iaAddr6);
            xTEST_DIFF(iRv, 0);

            host = ::gethostbyaddr(static_cast<char *>( &iaAddr6 ), 16, afInet6);
            xTEST_PTR(host, false);
        #endif
    #endif
        break;
    default:
        in_addr iaAddr = {0};

        iaAddr.s_addr = ::inet_addr( hostAddr.c_str() );
        xTEST_EQ(iaAddr.s_addr != INADDR_NONE, true);

        host = ::gethostbyaddr((char *) &iaAddr, sizeof(iaAddr), CxSocket::afInet);
        xTEST_PTR(host);
        break;
    }

    // convert to UNICODE
    std::string sRv(host->h_name);

    a_hostName->assign(sRv.begin(), sRv.end());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxDnsClient::localHostName(
    std::tstring_t *a_hostName
)
{
    xTEST_PTR(a_hostName);

    std::string asRv(xHOST_NAME_MAX, '0');

    int_t iRv = ::gethostname(&asRv.at(0), static_cast<int_t>( asRv.size() *
        sizeof(std::string::value_type) ));
    xTEST_EQ(iRv, 0);

    asRv.assign(asRv.c_str());    // trim '0' from end

    // convert to UNICODE
    a_hostName->assign(asRv.begin(), asRv.end());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxDnsClient::nameInfo(
    CxSocket::ExAddressFamily &a_family,
    std::ctstring_t           &a_hostAddr,
    cushort_t                 &a_usPort
)
{
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);

    // convert to UNICODE
    std::string hostAddr(a_hostAddr.begin(), a_hostAddr.end());

    sockaddr_in socketAddr; xSTRUCT_ZERO(socketAddr);
    socketAddr.sin_family      = a_family;
    socketAddr.sin_addr.s_addr = ::inet_addr(hostAddr.c_str());
    socketAddr.sin_port        = htons(a_usPort);

    tchar_t hostName[NI_MAXHOST + 1] = {0};
    tchar_t servInfo[NI_MAXSERV + 1] = {0};

    // TODO: CxDnsClient::nameInfo()
    int_t iRv = ::xGETNAMEINFO((sockaddr *)&socketAddr, sizeof(socketAddr), &hostName[0],
        NI_MAXHOST, &servInfo[0], NI_MAXSERV, NI_NUMERICSERV);
    xTEST_EQ(iRv, 0);

    //hostname
}
//-------------------------------------------------------------------------------------------------
//NOTE: http://www.geekpage.jp/en/programming/linux-network/getaddrinfo-0.php
/* static */
inline void_t
CxDnsClient::hostAddrInfo(
    std::ctstring_t  &a_hostName,
    std::ctstring_t  &a_port,
    caddrinfo_t      *a_hints,
    addrinfo_t      **a_addrInfo
)
{
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);

    int_t iRv = ::xGETADDRINFO(a_hostName.c_str(), a_port.c_str(), a_hints, a_addrInfo);
    xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxDnsClient::protocolByName(
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

    // convert to UNICODE
    std::string protocolName(a_protocolName.begin(), a_protocolName.end());

    protoent/*PROTOENT*/ *info = ::getprotobyname(protocolName.c_str());
    xTEST_PTR(info);

    //-------------------------------------
    // a_name
    if (a_name != xPTR_NULL) {
        // convert to UNICODE
        std::string name = info->p_name;
        a_name->assign(name.begin(), name.end());
    }

    //-------------------------------------
    // a_aliases
    if (a_aliases != xPTR_NULL) {
        a_aliases->clear();

        for (char **s = info->p_aliases; s && *s; ++ s) {
            std::string asRv;
            asRv.assign(*s);

            // convert to UNICODE
            std::tstring_t sRv;
            sRv.assign(asRv.begin(), asRv.end());

            a_aliases->push_back(sRv);
        }
    }

    //-------------------------------------
    // a_number
    CxUtils::ptrAssignT(a_number, *a_number = info->p_proto);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxDnsClient::protocolByNumber(
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

    //-------------------------------------
    // a_name
    // convert to UNICODE
    if (a_name != xPTR_NULL) {
        std::string name = info->p_name;
        a_name->assign(name.begin(), name.end());
    }

    //-------------------------------------
    // a_aliases
    if (a_aliases != xPTR_NULL) {
        a_aliases->clear();

        for (char **s = info->p_aliases; s && *s; ++ s) {
            std::string asRv;
            asRv.assign(*s);

            // convert to UNICODE
            std::tstring_t sRv;
            sRv.assign(asRv.begin(), asRv.end());

            a_aliases->push_back(sRv);
        }
    }

    //-------------------------------------
    // a_number_rv
    CxUtils::ptrAssignT(a_number_rv, *a_number_rv = info->p_proto);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxDnsClient::serviceByName(
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

    // convert to UNICODE
    std::string serviceName(a_serviceName.begin(), a_serviceName.end());
    std::string protocolName(a_protocolName.begin(), a_protocolName.end());

    servent *info = ::getservbyname(serviceName.c_str(), protocolName.c_str());
    xTEST_PTR(info);

    //-------------------------------------
    // name
    if (a_name != xPTR_NULL) {
        std::string name = info->s_name;
        a_name->assign(name.begin(), name.end());
    }

    //-------------------------------------
    // aliases
    if (a_aliases != xPTR_NULL) {
        a_aliases->clear();

        for (char **s = info->s_aliases; s && *s; ++ s) {
            std::string asRv;
            asRv.assign(*s);

            // convert to UNICODE
            std::tstring_t sRv;
            sRv.assign(asRv.begin(), asRv.end());

            a_aliases->push_back(sRv);
        }
    }

    //-------------------------------------
    // port
    CxUtils::ptrAssignT(a_port, *a_port = info->s_port);

    //-------------------------------------
    // protocolName_rv
    if (a_protocolName_rv != xPTR_NULL) {
        std::string _protocolName = info->s_proto;
        a_protocolName_rv->assign(_protocolName.begin(), _protocolName.end());
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxDnsClient::serviceByPort(
    cshort_t           &a_port,
    std::ctstring_t    &a_protocolName,
    std::tstring_t     *a_name,
    std::vec_tstring_t *a_aliases,
    short_t            *a_port_rv,
    std::tstring_t     *a_protocolName_rv
)
{
    // TODO: CxDnsClient::serviceByPort() - a_port
    xTEST_EQ(a_protocolName.empty(), false);
    xTEST_NA(a_name);
    xTEST_NA(a_aliases);
    xTEST_NA(a_port_rv);
    xTEST_NA(a_protocolName_rv);

    // convert to UNICODE
    std::string protocolName(a_protocolName.begin(), a_protocolName.end());

    servent *info = ::getservbyport(a_port, protocolName.c_str());
    xTEST_PTR(info);

    //-------------------------------------
    // name
    if (a_name != xPTR_NULL) {
        std::string name = info->s_name;
        a_name->assign(name.begin(), name.end());
    }

    //-------------------------------------
    // aliases
    if (a_aliases != xPTR_NULL) {
        a_aliases->clear();

        for (char **s = info->s_aliases; s && *s; ++ s) {
            std::string asRv;
            asRv.assign(*s);

            // convert to UNICODE
            std::tstring_t sRv;
            sRv.assign(asRv.begin(), asRv.end());

            a_aliases->push_back(sRv);
        }
    }

    //-------------------------------------
    // port
    CxUtils::ptrAssignT(a_port_rv, static_cast<short_t>( info->s_port ));

    //-------------------------------------
    // protocolName_rv
    if (a_protocolName_rv != xPTR_NULL) {
        std::string _protocolName = info->s_proto;
        a_protocolName_rv->assign(_protocolName.begin(), _protocolName.end());
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxDnsClient::isOnLan(
    cuint_t &a_ip
)
{
    cuint_t localIp = INADDR_ANY;  // IP of local interface (network order)
    cuint_t netMask = INADDR_NONE; // net mask for IP (network order)

    return (0UL == ((ntohl(a_ip) ^ ntohl(localIp)) & ntohl(netMask)));
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxDnsClient::isBroadcast(
    cuint_t &a_ip
)
{
    cuint_t netMask = INADDR_NONE; // net mask for IP (network order)

    return (0UL == (~ntohl(a_ip) & ~ntohl(netMask)));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, net)
