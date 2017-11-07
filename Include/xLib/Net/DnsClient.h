/**
 * \file  DnsClient.h
 * \brief DNS client
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Net/ISocket.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, net)

class DnsClient
    /// DNS client
{
public:
    static
    void_t   hostAddrByName(std::ctstring_t &hostName, std::tstring_t *hostAddr);
        ///< get host address by name
    static
    void_t   hostNameByAddr(std::ctstring_t &hostAddr, const ISocket::AddressFamily &family,
                 std::tstring_t *hostName);
        ///< get host name by address
    static
    void_t   localHostName(std::tstring_t *hostName);
        ///< get local host name
    static
    void_t   nameInfo(ISocket::AddressFamily &family, std::ctstring_t &hostAddr, cushort_t &port);
        ///< get name info
    static
    void_t   hostAddrInfo(std::ctstring_t &hostName, std::ctstring_t &port, caddrinfo_t *hints,
                 addrinfo_t **addrInfo);
        ///< get host addr info

    // protocol
    static
    void_t   protocolByName(std::ctstring_t &protocolName, std::tstring_t *name,
                 std::vec_tstring_t *aliases, int_t *number);
        ///< get protocol by name
    static
    void_t   protocolByNumber(cint_t &number, std::tstring_t *name, std::vec_tstring_t *aliases,
                 int_t *number_rv);
        ///< get protocol by number

    // service
    static
    void_t   serviceByName(std::ctstring_t &serviceName, std::ctstring_t &protocolName,
                 std::tstring_t *name, std::vec_tstring_t *aliases, int_t *port,
                 std::tstring_t *protocolName_rv);
        ///< get service by name
    static
    void_t   serviceByPort(cushort_t &port, std::ctstring_t &protocolName, std::tstring_t *name,
                 std::vec_tstring_t *aliases, short_t *port_rv, std::tstring_t *protocolName_rv);
        ///< get service by port

    static
    bool_t   isOnLan(cuint_t &ip) xWARN_UNUSED_RV;
        ///< return true if IP is on this LAN
    static
    bool_t   isBroadcast(cuint_t &ip) xWARN_UNUSED_RV;
        ///< return true if IP is a (directed) IP-broadcast address
    static
    bool_t   isAddressIpv4(std::ctstring_t &ip) xWARN_UNUSED_RV;
        ///< is address IP v4
    static
    bool_t   isAddressIpv6(std::ctstring_t &ip) xWARN_UNUSED_RV;
        ///< is address IP v6

private:
             DnsClient();
        ///< constructor
    virtual ~DnsClient();
        ///< destructor

    xNO_COPY_ASSIGN(DnsClient)
};

xNAMESPACE_END2(xl, net)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "DnsClient.cpp"
#endif
