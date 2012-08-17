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
        static bool bGetHostAddrByName  (const std::tstring_t &csHostName, std::tstring_t *psHostAddr);
            ///< get host address by name
        static bool bGetHostNameByAddr  (const std::tstring_t &csHostAddr, CxSocket::EAddressFamily afFamily, std::tstring_t *psHostName);
            ///< get host name by address
        static bool bGetLocalHostName   (std::tstring_t *psHostName);
            ///< get local host name
        static bool bGetNameInfo        (CxSocket::EAddressFamily afFamily, const std::tstring_t &csHostAddr, ushort_t usPort);
            ///< get name info
        static bool bGetHostAddrInfo    (const std::tstring_t &csHostName, const std::tstring_t &csPort, const addrinfo_t *pHints, addrinfo_t **ppResult);
            ///< get host addr info

        //protocol
        static bool bGetProtocolByName  (const std::tstring_t &csProtocolName, std::tstring_t *psName, std::vector<std::tstring_t> *pvsAliases, short_t *psiNumber);
            ///< get protocol by name
        static bool bGetProtocolByNumber(short_t siNumber, std::tstring_t *psName, std::vector<std::tstring_t> *pvsAliases, short_t *psiNum);
            ///< get protocol by number

        //service
        static bool bGetServiceByName   (const std::tstring_t &csServiceName, const std::tstring_t &csProtocolName, std::tstring_t *psName, std::vector<std::tstring_t> *pvsAliases, short_t *psiPort,  std::tstring_t *psProtocolName);
            ///< get service by name
        static bool bGetServiceByPort   (short_t siPort, const std::tstring_t &csProtocolName, std::tstring_t *psName, std::vector<std::tstring_t> *pvsAliases, short_t *psiPort,  std::tstring_t *psProtocolName);
            ///< get service by port

        static bool bIsOnLan            (const ulong_t culIp);
            ///< return true if IP is on this LAN
        static bool bIsBroadcast        (const ulong_t culIp);
            ///< return true if IP is a (directed) ip-broadcast address

    private:
                    CxDnsClient         ();
            ///< constructor
        virtual    ~CxDnsClient         ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Net_CxDnsClientH


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
