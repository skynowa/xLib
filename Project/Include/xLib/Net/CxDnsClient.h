/**
 * \file  CxDnsClient.h
 * \brief DNS client
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Net/CxSocket.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDnsClient :
    private CxNonCopyable
    /// DNS client
{
public:
    static void_t hostAddrByName(std::ctstring_t &hostName, std::tstring_t *hostAddr);
        ///< get host address by name
    static void_t hostNameByAddr(std::ctstring_t &hostAddr,
                      const CxSocket::ExAddressFamily &family, std::tstring_t *hostName);
        ///< get host name by address
    static void_t localHostName(std::tstring_t *hostName);
        ///< get local host name
    static void_t nameInfo(CxSocket::ExAddressFamily &family, std::ctstring_t &hostAddr,
                      cushort_t &port);
        ///< get name info
    static void_t hostAddrInfo(std::ctstring_t &hostName, std::ctstring_t &port,
                      caddrinfo_t *hints, addrinfo_t **addrInfo);
        ///< get host addr info

    // protocol
    static void_t protocolByName(std::ctstring_t &protocolName, std::tstring_t *name,
                      std::vec_tstring_t *aliases, short_t *number);
        ///< get protocol by name
    static void_t protocolByNumber(cshort_t &number, std::tstring_t *name,
                      std::vec_tstring_t *aliases, short_t *number_rv);
        ///< get protocol by number

    // service
    static void_t serviceByName(std::ctstring_t &serviceName, std::ctstring_t &protocolName,
                      std::tstring_t *name, std::vec_tstring_t *aliases, short_t *port,
                      std::tstring_t *protocolName_rv);
        ///< get service by name
    static void_t serviceByPort(cshort_t &port, std::ctstring_t &protocolName,
                      std::tstring_t *name, std::vec_tstring_t *aliases, short_t *port_rv,
                      std::tstring_t *protocolName_rv);
        ///< get service by port

    static bool_t isOnLan(culong_t &ip) xWARN_UNUSED_RV;
        ///< return true if IP is on this LAN
    static bool_t isBroadcast(culong_t &ip) xWARN_UNUSED_RV;
        ///< return true if IP is a (directed) IP-broadcast address

private:
                  CxDnsClient();
        ///< constructor
    virtual      ~CxDnsClient();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------


#if xTODO
    - GetAddressByName

    + getaddrinfo
    + GetAddrInfoW
    + freeaddrinfo
    + FreeAddrInfoW

    - GetAddrInfoEx
    - SetAddrInfoEx
    - FreeAddrInfoEx

    + gethostbyname
    + gethostbyaddr
    + gethostname

    GetNameByType
    GetTypeByName

    getnameinfo
    GetNameInfoW


    + getprotobyname
    + getprotobynumber
    + getservbyname
    + getservbyport
#endif
