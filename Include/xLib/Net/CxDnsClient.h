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
class CxDnsClient :
    public CxNonCopyable
    /// DNS client
{
    public:
        static BOOL bGetHostAddrByName  (const std::tstring &csHostName, std::tstring *psHostAddr);
        static BOOL bGetHostNameByAddr  (const std::tstring &csHostAddr, CxSocket::EAddressFamily afFamily, std::tstring *psHostName);
        static BOOL bGetLocalHostName   (std::tstring *psHostName);
        static BOOL bGetNameInfo        (CxSocket::EAddressFamily afFamily, const std::tstring &csHostAddr, USHORT usPort);
        static BOOL bGetHostAddrInfo    (const std::tstring &csHostName, const std::tstring &csPort, const ADDRINFOT *pHints, ADDRINFOT **ppResult);

        //TODO: protocol
        static BOOL bGetProtocolByName  (const std::tstring &csProtocolName, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiNumber);
        static BOOL bGetProtocolByNumber(SHORT siNumber, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiNum);

        //TODO: service
        static BOOL bGetServiceByName   (const std::tstring &csServiceName, const std::tstring &csProtocolName, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiPort,  std::tstring *psProtocolName);
        static BOOL bGetServiceByPort   (SHORT siPort, const std::tstring &csProtocolName, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiPort,  std::tstring *psProtocolName);

    private:
        static BOOL _ms_bRes;
        static INT  _ms_iRes;

                    CxDnsClient         ();
        virtual    ~CxDnsClient         ();
};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxDnsClientH




////- GetAddressByName

////+ getaddrinfo
////+ GetAddrInfoW
////+ freeaddrinfo
////+ FreeAddrInfoW

////- GetAddrInfoEx
////- SetAddrInfoEx
////- FreeAddrInfoEx

////+ gethostbyname
////+ gethostbyaddr
////+ gethostname

////GetNameByType
////GetTypeByName

////getnameinfo
////GetNameInfoW


////+ getprotobyname
////+ getprotobynumber
////+ getservbyname
////+ getservbyport

