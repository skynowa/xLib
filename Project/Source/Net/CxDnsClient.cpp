/**
 * \file  CxDnsClient.cpp
 * \brief DNS
 */


#include <xLib/Net/CxDnsClient.h>

#include <xLib/Common/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    Public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
bool
CxDnsClient::bGetHostAddrByName(
    const std::tstring_t &a_csHostName,
    std::tstring_t       *a_psHostAddr
)
{
    /*DEBUG*/xASSERT_RET(false == a_csHostName.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != a_psHostAddr,         false);

    std::tstring_t sRv;

    //convert to UNICODE
    std::string casHostName(a_csHostName.begin(), a_csHostName.end());

    hostent *pHostent = ::gethostbyname(casHostName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pHostent, false);

    sRv = CxString::sFormat(
                xT("%u.%u.%u.%u"),
                static_cast<uchar_t>(pHostent->h_addr_list[0][0]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][1]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][2]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][3])
    );
    /*DEBUG*/xASSERT_RET(false == sRv.empty(), false);

    (*a_psHostAddr) = sRv;

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDnsClient::bGetHostNameByAddr(
    const std::tstring_t      &a_csHostAddr,
    CxSocket::ExAddressFamily  a_afFamily,
    std::tstring_t            *a_psHostName
)
{
    /*DEBUG*/xASSERT_RET(false == a_csHostAddr.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != a_psHostName,         false);

    //convert to UNICODE
    std::string casHostAddr(a_csHostAddr.begin(), a_csHostAddr.end());

    hostent *pHostent = NULL;

    switch (a_afFamily) {
        case CxSocket::afInet6: {
            #if (xWINVER >= xOS_WIN_VISTA)
                #if xTODO
                    IN6_ADDR iaAddr6 = {0};

                    iRv = ::inet_pton(afInet6, a_casHostAddr.c_str(), &iaAddr6);
                    /*DEBUG*/xASSERT_RET(0 != iRv, false);

                    pHostent = ::gethostbyaddr((char *) &iaAddr6, 16, afInet6);
                    /*DEBUG*/xASSERT_RET(NULL != pHostent, false);
                #endif
            #endif //xOS_WIN_VISTA
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
    std::string sRv(pHostent->h_name);

    (*a_psHostName).assign(sRv.begin(), sRv.end());

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDnsClient::bGetLocalHostName(
    std::tstring_t *a_psHostName
)
{
    /*DEBUG*/xASSERT_RET(NULL != a_psHostName, false);

    std::string asRes(xHOST_NAME_MAX, '0');

    int iRv = ::gethostname(&asRes.at(0), asRes.size() * sizeof(std::string::value_type));
    /*DEBUG*/xASSERT_RET(0 == iRv, false);

    asRes.assign(asRes.c_str());    //delete '0' from end

    //convert to UNICODE
    (*a_psHostName).assign(asRes.begin(), asRes.end());

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDnsClient::bGetNameInfo(
    CxSocket::ExAddressFamily  a_afFamily,
    const std::tstring_t      &a_csHostAddr,
    ushort_t                   a_usPort
)
{
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);

    //convert to UNICODE
    std::string casHostAddr(a_csHostAddr.begin(), a_csHostAddr.end());

    sockaddr_in saGNI = {0};
    saGNI.sin_family      = a_afFamily;
    saGNI.sin_addr.s_addr = ::inet_addr(casHostAddr.c_str());
    saGNI.sin_port        = htons(a_usPort);

    tchar_t szHostName[NI_MAXHOST + 1] = {0};
    tchar_t szServInfo[NI_MAXSERV + 1] = {0};

    //TODO: bGetNameInfo
    int iRv = ::xGETNAMEINFO((struct sockaddr *)&saGNI, sizeof(saGNI), &szHostName[0], NI_MAXHOST, &szServInfo[0], NI_MAXSERV, NI_NUMERICSERV);
    /*DEBUG*/xASSERT_RET(0 == iRv, false);

    //hostname

    return true;
}
//---------------------------------------------------------------------------
//NOTE: http://www.geekpage.jp/en/programming/linux-network/getaddrinfo-0.php
/* static */
bool
CxDnsClient::bGetHostAddrInfo(
    const std::tstring_t  &a_csHostName,
    const std::tstring_t  &a_csPort,
    const addrinfo_t      *a_pHints,
    addrinfo_t           **a_ppResult
)
{
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);

    int iRv = ::xGETADDRINFO(a_csHostName.c_str(), a_csPort.c_str(), a_pHints, a_ppResult);
    /*DEBUG*/xASSERT_RET(0 == iRv, false);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDnsClient::bGetProtocolByName(
    const std::tstring_t &a_csProtocolName,
    std::tstring_t       *a_psName,
    std::vec_tstring_t   *a_pvsAliases,
    short_t              *a_psiNumber
)
{
    /*DEBUG*/xASSERT_RET(false == a_csProtocolName.empty(), false);
    /*DEBUG*///psName     - n/a
    /*DEBUG*///pvsAliases - n/a
    /*DEBUG*///psiNumber  - n/a

    //convert to UNICODE
    std::string asProtocolName(a_csProtocolName.begin(), a_csProtocolName.end());

    protoent/*PROTOENT*/ *pptInfo = ::getprotobyname(asProtocolName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pptInfo, false);

    //-------------------------------------
    //psName
    if (NULL != a_psName) {
        //convert to UNICODE
        std::string asName = pptInfo->p_name;
        (*a_psName).assign(asName.begin(), asName.end());
    }

    //-------------------------------------
    //psAliases
    if (NULL != a_pvsAliases) {
        (*a_pvsAliases).clear();

        for (char **s = pptInfo->p_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring_t sRv;
            sRv.assign(asRes.begin(), asRes.end());

            (*a_pvsAliases).push_back(sRv);
        }
    }

    //-------------------------------------
    //psiNumber
    CxMacros::ptrAssignT(a_psiNumber, *a_psiNumber = pptInfo->p_proto);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDnsClient::bGetProtocolByNumber(
    short_t             a_siNumber,
    std::tstring_t     *a_psName,
    std::vec_tstring_t *a_pvsAliases,
    short_t            *a_psiNumber
)
{
    /*DEBUG*///siNum      - n/a
    /*DEBUG*///psName     - n/a
    /*DEBUG*///pvsAliases - n/a
    /*DEBUG*///psiNum     - n/a

    protoent/*PROTOENT*/*pptInfo = ::getprotobynumber(a_siNumber);
    /*DEBUG*/xASSERT_RET(NULL != pptInfo, false);

    //-------------------------------------
    //psName
    //convert to UNICODE
    if (NULL != a_psName) {
        std::string asName = pptInfo->p_name;
        (*a_psName).assign(asName.begin(), asName.end());
    }

    //-------------------------------------
    //psAliases
    if (NULL != a_pvsAliases) {
        (*a_pvsAliases).clear();

        for (char **s = pptInfo->p_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring_t sRv;
            sRv.assign(asRes.begin(), asRes.end());

            (*a_pvsAliases).push_back(sRv);
        }
    }

    //-------------------------------------
    //psiNum
    CxMacros::ptrAssignT(a_psiNumber, *a_psiNumber = pptInfo->p_proto);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDnsClient::bGetServiceByName(
    const std::tstring_t &a_csServiceName,
    const std::tstring_t &a_csProtocolName,
    std::tstring_t       *a_psName,
    std::vec_tstring_t   *a_pvsAliases,
    short_t              *a_psiPort,
    std::tstring_t       *a_psProtocolName
)
{
    /*DEBUG*/xASSERT_RET(false == a_csServiceName.empty(), false);
    /*DEBUG*/xASSERT_RET(false == a_csProtocolName.empty(), false);
    /*DEBUG*///psName         - n/a
    /*DEBUG*///pvsAliases   - n/a
    /*DEBUG*///psiPort        - n/a
    /*DEBUG*///psProtocolName - n/a

    //convert to UNICODE
    std::string asServiceName (a_csServiceName.begin(),  a_csServiceName.end());
    std::string asProtocolName(a_csProtocolName.begin(), a_csProtocolName.end());

    servent *psvInfo = ::getservbyname(asServiceName.c_str(), asProtocolName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != psvInfo, false);

    //-------------------------------------
    //psName
    if (NULL != a_psName) {
        std::string asName = psvInfo->s_name;
        (*a_psName).assign(asName.begin(), asName.end());
    }

    //-------------------------------------
    //pvsAliases
    if (NULL != a_pvsAliases) {
        (*a_pvsAliases).clear();

        for (char **s = psvInfo->s_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring_t sRv;
            sRv.assign(asRes.begin(), asRes.end());

            (*a_pvsAliases).push_back(sRv);
        }
    }
    //-------------------------------------
    //psiPort
    CxMacros::ptrAssignT(a_psiPort, *a_psiPort = psvInfo->s_port);

    //-------------------------------------
    //psProtocolName
    if (NULL != a_psProtocolName) {
        std::string _asProtocolName = psvInfo->s_proto;
        (*a_psProtocolName).assign(_asProtocolName.begin(), _asProtocolName.end());
    }

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDnsClient::bGetServiceByPort(
    short_t               a_siPort,
    const std::tstring_t &a_csProtocolName,
    std::tstring_t       *a_psName,
    std::vec_tstring_t   *a_pvsAliases,
    short_t              *a_psiPort,
    std::tstring_t       *a_psProtocolName
)
{
    /*DEBUG*///TODO: siPort
    /*DEBUG*/xASSERT_RET(false == a_csProtocolName.empty(), false);
    /*DEBUG*///psName         - n/a
    /*DEBUG*///pvsAliases   - n/a
    /*DEBUG*///psiPort        - n/a
    /*DEBUG*///psProtocolName - n/a

    //convert to UNICODE
    std::string asProtocolName(a_csProtocolName.begin(), a_csProtocolName.end());

    servent *psvInfo = ::getservbyport(a_siPort, asProtocolName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != psvInfo, false);

    //-------------------------------------
    //psName
    if (NULL != a_psName) {
        std::string asName = psvInfo->s_name;
        (*a_psName).assign(asName.begin(), asName.end());
    }

    //-------------------------------------
    //pvsAliases
    if (NULL != a_pvsAliases) {
        (*a_pvsAliases).clear();

        for (char **s = psvInfo->s_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring_t sRv;
            sRv.assign(asRes.begin(), asRes.end());

            (*a_pvsAliases).push_back(sRv);
        }
    }

    //-------------------------------------
    //psiPort
    CxMacros::ptrAssignT(a_psiPort, static_cast<short_t>( psvInfo->s_port ));

    //-------------------------------------
    //psProtocolName
    if (NULL != a_psProtocolName) {
        std::string _asProtocolName = psvInfo->s_proto;
        (*a_psProtocolName).assign(_asProtocolName.begin(), _asProtocolName.end());
    }

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDnsClient::bIsOnLan(
    const ulong_t a_culIp
)
{
    const ulong_t culMyIpAddress = INADDR_ANY;     //IP of local interface (network order)
    const ulong_t culNetMask     = INADDR_NONE;    //netmask for IP (network order)

    return (0L == ((ntohl(a_culIp) ^ ntohl(culMyIpAddress)) & ntohl(culNetMask)));
}
//---------------------------------------------------------------------------
/* static */
bool
CxDnsClient::bIsBroadcast(
    const ulong_t a_culIp
)
{
    const ulong_t culNetMask     = INADDR_NONE;    //netmask for IP (network order)

    return (0L == (~ntohl(a_culIp) & ~ntohl(culNetMask)));
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
/* virtual */
CxDnsClient::~CxDnsClient() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
