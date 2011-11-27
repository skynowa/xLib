/**
 * \file  CxDnsClient.cpp
 * \brief DNS
 */


#include <xLib/Net/CxDnsClient.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    Public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
bool
CxDnsClient::bGetHostAddrByName(
    const std::tstring_t &csHostName,
    std::tstring_t       *psHostAddr
)
{
    /*DEBUG*/xASSERT_RET(false == csHostName.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != psHostAddr,         false);

    std::tstring_t sRes;

    //convert to UNICODE
    std::string casHostName(csHostName.begin(), csHostName.end());

    hostent *pHostent = ::gethostbyname(casHostName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pHostent, false);

    sRes = CxString::sFormat(
                xT("%u.%u.%u.%u"),
                static_cast<uchar_t>(pHostent->h_addr_list[0][0]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][1]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][2]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][3])
    );
    /*DEBUG*/xASSERT_RET(false == sRes.empty(), false);

    (*psHostAddr) = sRes;

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDnsClient::bGetHostNameByAddr(
    const std::tstring_t       &csHostAddr,
    CxSocket::EAddressFamily  afFamily,
    std::tstring_t             *psHostName
)
{
    /*DEBUG*/xASSERT_RET(false == csHostAddr.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != psHostName,         false);

    //convert to UNICODE
    std::string casHostAddr(csHostAddr.begin(), csHostAddr.end());

    hostent *pHostent = NULL;

    switch (afFamily) {
        case CxSocket::afInet6: {
            #if (xWINVER >= xWIN32_VISTA)
                #if xTODO
                    IN6_ADDR iaAddr6 = {0};

                    iRes = ::inet_pton(afInet6, casHostAddr.c_str(), &iaAddr6);
                    /*DEBUG*/xASSERT_RET(0 != iRes, false);

                    pHostent = ::gethostbyaddr((char *) &iaAddr6, 16, afInet6);
                    /*DEBUG*/xASSERT_RET(NULL != pHostent, false);
                #endif
            #endif //xWIN32_VISTA
            }
            break;

        default: {
                in_addr iaAddr;

                iaAddr.s_addr = ::inet_addr(casHostAddr.c_str());
                /*DEBUG*/xASSERT_RET(iaAddr.s_addr != INADDR_NONE, false);

                pHostent = ::gethostbyaddr((char *) &iaAddr, sizeof(iaAddr)/*4*/, CxSocket::afInet);
                /*DEBUG*/xASSERT_RET(NULL != pHostent, false);
            }
            break;
    }

    //convert to UNICODE
    std::string sRes(pHostent->h_name);

    (*psHostName).assign(sRes.begin(), sRes.end());

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDnsClient::bGetLocalHostName(
    std::tstring_t *psHostName
)
{
    /*DEBUG*/xASSERT_RET(NULL != psHostName, false);

#if xOS_ENV_WIN
    std::string asRes(255 + 1, '0');
#elif xOS_ENV_UNIX
    std::string asRes(HOST_NAME_MAX, '0');
#endif

    int iRes = ::gethostname(&asRes.at(0), asRes.size() * sizeof(std::string::value_type));
    /*DEBUG*/xASSERT_RET(0 == iRes, false);

    asRes.assign(asRes.c_str());    //delete '0' from end

    //convert to UNICODE
    (*psHostName).assign(asRes.begin(), asRes.end());

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDnsClient::bGetNameInfo(
    CxSocket::EAddressFamily  afFamily,
    const std::tstring_t       &csHostAddr,
    ushort_t                    usPort
)
{
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);

    //convert to UNICODE
    std::string casHostAddr(csHostAddr.begin(), csHostAddr.end());

    sockaddr_in saGNI = {0};
    saGNI.sin_family      = afFamily;
    saGNI.sin_addr.s_addr = ::inet_addr(casHostAddr.c_str());
    saGNI.sin_port        = htons(usPort);

    tchar_t szHostName[NI_MAXHOST] = {0};
    tchar_t szServInfo[NI_MAXSERV] = {0};

#if xOS_ENV_WIN
    //TODO: bGetNameInfo
    int iRes = ::GetNameInfo((struct sockaddr *)&saGNI, sizeof(saGNI), &szHostName[0], NI_MAXHOST, &szServInfo[0], NI_MAXSERV, NI_NUMERICSERV);
    /*DEBUG*/xASSERT_RET(0 == iRes, false);
#elif xOS_ENV_UNIX
    //TODO: bGetNameInfo
    int iRes = ::getnameinfo((struct sockaddr *)&saGNI, sizeof(saGNI), &szHostName[0], NI_MAXHOST, &szServInfo[0], NI_MAXSERV, NI_NUMERICSERV);
    /*DEBUG*/xASSERT_RET(0 == iRes, false);
#endif

    //hostname

    return true;
}
//---------------------------------------------------------------------------
//NOTE: http://www.geekpage.jp/en/programming/linux-network/getaddrinfo-0.php
/*static*/
bool
CxDnsClient::bGetHostAddrInfo(
    const std::tstring_t  &csHostName,
    const std::tstring_t  &csPort,
    const addrinfo_t     *pHints,
    addrinfo_t          **ppResult
)
{
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);

#if xOS_ENV_WIN
    int iRes = ::GetAddrInfo(csHostName.c_str(), csPort.c_str(), pHints, ppResult);
    /*DEBUG*/xASSERT_RET(0 == iRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::getaddrinfo(csHostName.c_str(), csPort.c_str(), pHints, ppResult);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxString::lexical_cast(iRes), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDnsClient::bGetProtocolByName(
    const std::tstring_t        &csProtocolName,
    std::tstring_t              *psName,
    std::vector<std::tstring_t> *pvsAliases,
    short_t                     *psiNumber
)
{
    /*DEBUG*/xASSERT_RET(false == csProtocolName.empty(), false);
    /*DEBUG*///psName     - n/a
    /*DEBUG*///pvsAliases - n/a
    /*DEBUG*///psiNumber  - n/a

    //convert to UNICODE
    std::string asProtocolName(csProtocolName.begin(), csProtocolName.end());

    protoent/*PROTOENT*/ *pptInfo = ::getprotobyname(asProtocolName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pptInfo, false);

    //-------------------------------------
    //psName
    if (NULL != psName) {
        //convert to UNICODE
        std::string asName = pptInfo->p_name;
        (*psName).assign(asName.begin(), asName.end());
    }

    //-------------------------------------
    //psAliases
    if (NULL != pvsAliases) {
        pvsAliases->clear();

        for (char **s = pptInfo->p_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring_t sRes;
            sRes.assign(asRes.begin(), asRes.end());

            pvsAliases->push_back(sRes);
        }
    }

    //-------------------------------------
    //psiNumber
    xCHECK_DO(NULL != psiNumber, *psiNumber = pptInfo->p_proto);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDnsClient::bGetProtocolByNumber(
    short_t                      siNumber,
    std::tstring_t              *psName,
    std::vector<std::tstring_t> *pvsAliases,
    short_t                     *psiNumber
)
{
    /*DEBUG*///siNum      - n/a
    /*DEBUG*///psName     - n/a
    /*DEBUG*///pvsAliases - n/a
    /*DEBUG*///psiNum     - n/a

    protoent/*PROTOENT*/*pptInfo = ::getprotobynumber(siNumber);
    /*DEBUG*/xASSERT_RET(NULL != pptInfo, false);

    //-------------------------------------
    //psName
    //convert to UNICODE
    if (NULL != psName) {
        std::string asName = pptInfo->p_name;
        (*psName).assign(asName.begin(), asName.end());
    }

    //-------------------------------------
    //psAliases
    if (NULL != pvsAliases) {
        pvsAliases->clear();

        for (char **s = pptInfo->p_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring_t sRes;
            sRes.assign(asRes.begin(), asRes.end());

            pvsAliases->push_back(sRes);
        }
    }

    //-------------------------------------
    //psiNum
    xCHECK_DO(NULL != psiNumber, *psiNumber = pptInfo->p_proto);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDnsClient::bGetServiceByName(
    const std::tstring_t        &csServiceName,
    const std::tstring_t        &csProtocolName,
    std::tstring_t              *psName,
    std::vector<std::tstring_t> *pvsAliases,
    short_t                     *psiPort,
    std::tstring_t              *psProtocolName
)
{
    /*DEBUG*/xASSERT_RET(false == csServiceName.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csProtocolName.empty(), false);
    /*DEBUG*///psName         - n/a
    /*DEBUG*///pvsAliases   - n/a
    /*DEBUG*///psiPort        - n/a
    /*DEBUG*///psProtocolName - n/a

    //convert to UNICODE
    std::string asServiceName (csServiceName.begin(),  csServiceName.end());
    std::string asProtocolName(csProtocolName.begin(), csProtocolName.end());

    servent *psvInfo = ::getservbyname(asServiceName.c_str(), asProtocolName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != psvInfo, false);

    //-------------------------------------
    //psName
    if (NULL != psName) {
        std::string asName = psvInfo->s_name;
        (*psName).assign(asName.begin(), asName.end());
    }

    //-------------------------------------
    //pvsAliases
    if (NULL != pvsAliases) {
        pvsAliases->clear();

        for (char **s = psvInfo->s_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring_t sRes;
            sRes.assign(asRes.begin(), asRes.end());

            pvsAliases->push_back(sRes);
        }
    }
    //-------------------------------------
    //psiPort
    xCHECK_DO(NULL != psiPort, *psiPort = psvInfo->s_port);

    //-------------------------------------
    //psProtocolName
    if (NULL != psProtocolName) {
        std::string _asProtocolName = psvInfo->s_proto;
        (*psProtocolName).assign(_asProtocolName.begin(), _asProtocolName.end());
    }

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDnsClient::bGetServiceByPort(
    short_t                      siPort,
    const std::tstring_t        &csProtocolName,
    std::tstring_t              *psName,
    std::vector<std::tstring_t> *pvsAliases,
    short_t                     *psiPort,
    std::tstring_t              *psProtocolName
)
{
    /*DEBUG*///TODO: siPort
    /*DEBUG*/xASSERT_RET(false == csProtocolName.empty(), false);
    /*DEBUG*///psName         - n/a
    /*DEBUG*///pvsAliases   - n/a
    /*DEBUG*///psiPort        - n/a
    /*DEBUG*///psProtocolName - n/a

    //convert to UNICODE
    std::string asProtocolName(csProtocolName.begin(), csProtocolName.end());

    servent *psvInfo = ::getservbyport(siPort, asProtocolName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != psvInfo, false);

    //-------------------------------------
    //psName
    if (NULL != psName) {
        std::string asName = psvInfo->s_name;
        (*psName).assign(asName.begin(), asName.end());
    }

    //-------------------------------------
    //pvsAliases
    if (NULL != pvsAliases) {
        pvsAliases->clear();

        for (char **s = psvInfo->s_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring_t sRes;
            sRes.assign(asRes.begin(), asRes.end());

            pvsAliases->push_back(sRes);
        }
    }

    //-------------------------------------
    //psiPort
    xCHECK_DO(NULL != psiPort, *psiPort = psvInfo->s_port);

    //-------------------------------------
    //psProtocolName
    if (NULL != psProtocolName) {
        std::string _asProtocolName = psvInfo->s_proto;
        (*psProtocolName).assign(_asProtocolName.begin(), _asProtocolName.end());
    }

    return true;
}
//---------------------------------------------------------------------------
/*static*/
BOOL 
CxDnsClient::bIsOnLan(
    const ulong_t culIp
)
{ 
    const ulong_t culMyIpAddress = INADDR_ANY;     //IP of local interface (network order)
    const ulong_t culNetMask     = INADDR_NONE;    //netmask for IP (network order)
 
    return (0L == ((::ntohl(culIp) ^ ::ntohl(culMyIpAddress)) & ::ntohl(culNetMask)));
}
//---------------------------------------------------------------------------
/*static*/
BOOL 
CxDnsClient::bIsBroadcast(
    const ulong_t culIp
)
{
    const ulong_t culMyIpAddress = INADDR_ANY;     //IP of local interface (network order)
    const ulong_t culNetMask     = INADDR_NONE;    //netmask for IP (network order)

    return (0L == (~::ntohl(culIp) & ~::ntohl(culNetMask)));
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxDnsClient::CxDnsClient() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxDnsClient::~CxDnsClient() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
