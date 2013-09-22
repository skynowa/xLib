/**
 * \file  CxDnsClient.h
 * \brief DNS client
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxSocket.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDnsClient :
    private CxNonCopyable
    /// DNS client
{
public:
    static void_t hostAddrByName  (std::ctstring_t &csHostName, std::tstring_t *psHostAddr);
        ///< get host address by name
    static void_t hostNameByAddr  (std::ctstring_t &csHostAddr, const CxSocket::ExAddressFamily &afFamily, std::tstring_t *psHostName);
        ///< get host name by address
    static void_t localHostName   (std::tstring_t *psHostName);
        ///< get local host name
    static void_t nameInfo        (CxSocket::ExAddressFamily &afFamily, std::ctstring_t &csHostAddr, cushort_t &cusPort);
        ///< get name info
    static void_t hostAddrInfo    (std::ctstring_t &csHostName, std::ctstring_t &csPort, caddrinfo_t *pHints, addrinfo_t **ppResult);
        ///< get host addr info

    // protocol
    static void_t protocolByName  (std::ctstring_t &csProtocolName, std::tstring_t *psName, std::vec_tstring_t *pvsAliases, short_t *psiNumber);
        ///< get protocol by name
    static void_t protocolByNumber(cshort_t &csiNumber, std::tstring_t *psName, std::vec_tstring_t *pvsAliases, short_t *psiNum);
        ///< get protocol by number

    // service
    static void_t serviceByName   (std::ctstring_t &csServiceName, std::ctstring_t &csProtocolName, std::tstring_t *psName, std::vec_tstring_t *pvsAliases, short_t *psiPort,  std::tstring_t *psProtocolName);
        ///< get service by name
    static void_t serviceByPort   (cshort_t &csiPort, std::ctstring_t &csProtocolName, std::tstring_t *psName, std::vec_tstring_t *pvsAliases, short_t *psiPort, std::tstring_t *psProtocolName);
        ///< get service by port

    static bool_t isOnLan         (culong_t &culIp) xWARN_UNUSED_RV;
        ///< return true if IP is on this LAN
    static bool_t isBroadcast     (culong_t &culIp) xWARN_UNUSED_RV;
        ///< return true if IP is a (directed) IP-broadcast address

private:
                  CxDnsClient     ();
        ///< constructor
    virtual      ~CxDnsClient     ();
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
