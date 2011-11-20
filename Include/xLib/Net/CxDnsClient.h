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
    public CxNonCopyable
    /// DNS client
{
    public:
        static bool bGetHostAddrByName  (const std::tstring &csHostName, std::tstring *psHostAddr);
            ///< get host address by name
        static bool bGetHostNameByAddr  (const std::tstring &csHostAddr, CxSocket::EAddressFamily afFamily, std::tstring *psHostName);
            ///< get host name by address
        static bool bGetLocalHostName   (std::tstring *psHostName);
            ///< get local host name
        static bool bGetNameInfo        (CxSocket::EAddressFamily afFamily, const std::tstring &csHostAddr, USHORT usPort);
            ///< get name info
        static bool bGetHostAddrInfo    (const std::tstring &csHostName, const std::tstring &csPort, const ADDRINFOT *pHints, ADDRINFOT **ppResult);
            ///< get host addr info

        //protocol
        static bool bGetProtocolByName  (const std::tstring &csProtocolName, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiNumber);
            ///< get protocol by name
        static bool bGetProtocolByNumber(SHORT siNumber, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiNum);
            ///< get protocol by number

        //service
        static bool bGetServiceByName   (const std::tstring &csServiceName, const std::tstring &csProtocolName, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiPort,  std::tstring *psProtocolName);
            ///< get service by name
        static bool bGetServiceByPort   (SHORT siPort, const std::tstring &csProtocolName, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiPort,  std::tstring *psProtocolName);
            ///< get service by port

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
