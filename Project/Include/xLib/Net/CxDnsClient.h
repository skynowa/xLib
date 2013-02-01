/**
 * \file  CxDnsClient.h
 * \brief DNS client
 */


#ifndef xLib_Net_CxDnsClientH
#define xLib_Net_CxDnsClientH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxSocket.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDnsClient :
    private CxNonCopyable
    /// DNS client
{
public:
    static void hostAddrByName  (const std::tstring_t &csHostName, std::tstring_t *psHostAddr);
        ///< get host address by name
    static void hostNameByAddr  (const std::tstring_t &csHostAddr, const CxSocket::ExAddressFamily &afFamily, std::tstring_t *psHostName);
        ///< get host name by address
    static void localHostName   (std::tstring_t *psHostName);
        ///< get local host name
    static void nameInfo        (CxSocket::ExAddressFamily &afFamily, const std::tstring_t &csHostAddr, const ushort_t &cusPort);
        ///< get name info
    static void hostAddrInfo    (const std::tstring_t &csHostName, const std::tstring_t &csPort, const addrinfo_t *pHints, addrinfo_t **ppResult);
        ///< get host addr info

    //protocol
    static void protocolByName  (const std::tstring_t &csProtocolName, std::tstring_t *psName, std::vec_tstring_t *pvsAliases, short_t *psiNumber);
        ///< get protocol by name
    static void protocolByNumber(const short_t &csiNumber, std::tstring_t *psName, std::vec_tstring_t *pvsAliases, short_t *psiNum);
        ///< get protocol by number

    //service
    static void serviceByName   (const std::tstring_t &csServiceName, const std::tstring_t &csProtocolName, std::tstring_t *psName, std::vec_tstring_t *pvsAliases, short_t *psiPort,  std::tstring_t *psProtocolName);
        ///< get service by name
    static void serviceByPort   (const short_t &csiPort, const std::tstring_t &csProtocolName, std::tstring_t *psName, std::vec_tstring_t *pvsAliases, short_t *psiPort, std::tstring_t *psProtocolName);
        ///< get service by port

    static bool isOnLan         (const ulong_t &culIp);
        ///< return true if IP is on this LAN
    static bool isBroadcast     (const ulong_t &culIp);
        ///< return true if IP is a (directed) IP-broadcast address

private:
                CxDnsClient     ();
        ///< constructor
    virtual    ~CxDnsClient     ();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Net_CxDnsClientH


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
