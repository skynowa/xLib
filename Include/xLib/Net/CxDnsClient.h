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
        	///< get host address by name
        static BOOL bGetHostNameByAddr  (const std::tstring &csHostAddr, CxSocket::EAddressFamily afFamily, std::tstring *psHostName);
        	///< get host name by address
        static BOOL bGetLocalHostName   (std::tstring *psHostName);
        	///< get local host name
        static BOOL bGetNameInfo        (CxSocket::EAddressFamily afFamily, const std::tstring &csHostAddr, USHORT usPort);
        	///< get name info
        static BOOL bGetHostAddrInfo    (const std::tstring &csHostName, const std::tstring &csPort, const ADDRINFOT *pHints, ADDRINFOT **ppResult);
        	///< get host addr info

        //protocol
        static BOOL bGetProtocolByName  (const std::tstring &csProtocolName, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiNumber);
        	///< get protocol by name
        static BOOL bGetProtocolByNumber(SHORT siNumber, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiNum);
        	///< get protocol by number

        //service
        static BOOL bGetServiceByName   (const std::tstring &csServiceName, const std::tstring &csProtocolName, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiPort,  std::tstring *psProtocolName);
        	///< get service by name
        static BOOL bGetServiceByPort   (SHORT siPort, const std::tstring &csProtocolName, std::tstring *psName, std::vector<std::tstring> *pvsAliases, SHORT *psiPort,  std::tstring *psProtocolName);
        	///< get service by port

    private:
                    CxDnsClient         ();
            ///< constructor
        virtual    ~CxDnsClient         ();
        	///< destructor
};
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
