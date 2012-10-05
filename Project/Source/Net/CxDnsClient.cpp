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
void
CxDnsClient::vGetHostAddrByName(
    const std::tstring_t &a_csHostName,
    std::tstring_t       *a_psHostAddr
)
{
    /*DEBUG*/xTEST_EQ(false, a_csHostName.empty());
    /*DEBUG*/xTEST_PTR(a_psHostAddr);

    std::tstring_t sRv;

    //convert to UNICODE
    std::string casHostName(a_csHostName.begin(), a_csHostName.end());

    hostent *pHostent = ::gethostbyname(casHostName.c_str());
    /*DEBUG*/xTEST_PTR(pHostent);

    sRv = CxString::sFormat(
                xT("%u.%u.%u.%u"),
                static_cast<uchar_t>(pHostent->h_addr_list[0][0]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][1]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][2]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][3])
    );
    /*DEBUG*/xTEST_EQ(false, sRv.empty());

    (*a_psHostAddr) = sRv;
}
//---------------------------------------------------------------------------
/* static */
void
CxDnsClient::vGetHostNameByAddr(
    const std::tstring_t            &a_csHostAddr,
    const CxSocket::ExAddressFamily &a_afFamily,
    std::tstring_t                  *a_psHostName
)
{
    /*DEBUG*/xTEST_EQ(false, a_csHostAddr.empty());
    /*DEBUG*/xTEST_PTR(a_psHostName);

    //convert to UNICODE
    std::string casHostAddr(a_csHostAddr.begin(), a_csHostAddr.end());

    hostent *pHostent = NULL;

    switch (a_afFamily) {
        case CxSocket::afInet6: {
            #if (xWINVER >= xOS_WIN_VISTA)
                #if xTODO
                    IN6_ADDR iaAddr6 = {0};

                    iRv = ::inet_pton(afInet6, a_casHostAddr.c_str(), &iaAddr6);
                    /*DEBUG*/xTEST_DIFF(0, iRv);

                    pHostent = ::gethostbyaddr((char *) &iaAddr6, 16, afInet6);
                    /*DEBUG*/xTEST_PTR(pHostent, false);
                #endif
            #endif //xOS_WIN_VISTA
            }
            break;

        default: {
                in_addr iaAddr;

                iaAddr.s_addr = ::inet_addr(casHostAddr.c_str());
                /*DEBUG*/xTEST_EQ(true, iaAddr.s_addr != INADDR_NONE);

                pHostent = ::gethostbyaddr((char *) &iaAddr, sizeof(iaAddr)/*4*/, CxSocket::afInet);
                /*DEBUG*/xTEST_PTR(pHostent);
            }
            break;
    }

    //convert to UNICODE
    std::string sRv(pHostent->h_name);

    (*a_psHostName).assign(sRv.begin(), sRv.end());
}
//---------------------------------------------------------------------------
/* static */
void
CxDnsClient::vGetLocalHostName(
    std::tstring_t *a_psHostName
)
{
    /*DEBUG*/xTEST_PTR(a_psHostName);

    std::string asRes(xHOST_NAME_MAX, '0');

    int iRv = ::gethostname(&asRes.at(0), asRes.size() * sizeof(std::string::value_type));
    /*DEBUG*/xTEST_EQ(0, iRv);

    asRes.assign(asRes.c_str());    //delete '0' from end

    //convert to UNICODE
    (*a_psHostName).assign(asRes.begin(), asRes.end());
}
//---------------------------------------------------------------------------
/* static */
void
CxDnsClient::vGetNameInfo(
    CxSocket::ExAddressFamily &a_afFamily,
    const std::tstring_t      &a_csHostAddr,
    const ushort_t            &a_usPort
)
{
    /*DEBUG*///xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    /*DEBUG*///xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    /*DEBUG*///xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);

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
    /*DEBUG*/xTEST_EQ(0, iRv);

    //hostname
}
//---------------------------------------------------------------------------
//NOTE: http://www.geekpage.jp/en/programming/linux-network/getaddrinfo-0.php
/* static */
void
CxDnsClient::vGetHostAddrInfo(
    const std::tstring_t  &a_csHostName,
    const std::tstring_t  &a_csPort,
    const addrinfo_t      *a_pHints,
    addrinfo_t           **a_ppResult
)
{
    /*DEBUG*///xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    /*DEBUG*///xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    /*DEBUG*///xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    /*DEBUG*///xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);

    int iRv = ::xGETADDRINFO(a_csHostName.c_str(), a_csPort.c_str(), a_pHints, a_ppResult);
    /*DEBUG*/xTEST_EQ(0, iRv);
}
//---------------------------------------------------------------------------
/* static */
void
CxDnsClient::vGetProtocolByName(
    const std::tstring_t &a_csProtocolName,
    std::tstring_t       *a_psName,
    std::vec_tstring_t   *a_pvsAliases,
    short_t              *a_psiNumber
)
{
    /*DEBUG*/xTEST_EQ(false, a_csProtocolName.empty());
    /*DEBUG*///psName     - n/a
    /*DEBUG*///pvsAliases - n/a
    /*DEBUG*///psiNumber  - n/a

    //convert to UNICODE
    std::string asProtocolName(a_csProtocolName.begin(), a_csProtocolName.end());

    protoent/*PROTOENT*/ *pptInfo = ::getprotobyname(asProtocolName.c_str());
    /*DEBUG*/xTEST_PTR(pptInfo);

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
    CxUtils::ptrAssignT(a_psiNumber, *a_psiNumber = pptInfo->p_proto);
}
//---------------------------------------------------------------------------
/* static */
void
CxDnsClient::vGetProtocolByNumber(
    const short_t      &a_siNumber,
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
    /*DEBUG*/xTEST_PTR(pptInfo);

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
    CxUtils::ptrAssignT(a_psiNumber, *a_psiNumber = pptInfo->p_proto);
}
//---------------------------------------------------------------------------
/* static */
void
CxDnsClient::vGetServiceByName(
    const std::tstring_t &a_csServiceName,
    const std::tstring_t &a_csProtocolName,
    std::tstring_t       *a_psName,
    std::vec_tstring_t   *a_pvsAliases,
    short_t              *a_psiPort,
    std::tstring_t       *a_psProtocolName
)
{
    /*DEBUG*/xTEST_EQ(false, a_csServiceName.empty());
    /*DEBUG*/xTEST_EQ(false, a_csProtocolName.empty());
    /*DEBUG*///psName         - n/a
    /*DEBUG*///pvsAliases   - n/a
    /*DEBUG*///psiPort        - n/a
    /*DEBUG*///psProtocolName - n/a

    //convert to UNICODE
    std::string asServiceName (a_csServiceName.begin(),  a_csServiceName.end());
    std::string asProtocolName(a_csProtocolName.begin(), a_csProtocolName.end());

    servent *psvInfo = ::getservbyname(asServiceName.c_str(), asProtocolName.c_str());
    /*DEBUG*/xTEST_PTR(psvInfo);

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
    CxUtils::ptrAssignT(a_psiPort, *a_psiPort = psvInfo->s_port);

    //-------------------------------------
    //psProtocolName
    if (NULL != a_psProtocolName) {
        std::string _asProtocolName = psvInfo->s_proto;
        (*a_psProtocolName).assign(_asProtocolName.begin(), _asProtocolName.end());
    }
}
//---------------------------------------------------------------------------
/* static */
void
CxDnsClient::vGetServiceByPort(
    const short_t        &a_siPort,
    const std::tstring_t &a_csProtocolName,
    std::tstring_t       *a_psName,
    std::vec_tstring_t   *a_pvsAliases,
    short_t              *a_psiPort,
    std::tstring_t       *a_psProtocolName
)
{
    /*DEBUG*///TODO: siPort
    /*DEBUG*/xTEST_EQ(false, a_csProtocolName.empty());
    /*DEBUG*///psName         - n/a
    /*DEBUG*///pvsAliases   - n/a
    /*DEBUG*///psiPort        - n/a
    /*DEBUG*///psProtocolName - n/a

    //convert to UNICODE
    std::string asProtocolName(a_csProtocolName.begin(), a_csProtocolName.end());

    servent *psvInfo = ::getservbyport(a_siPort, asProtocolName.c_str());
    /*DEBUG*/xTEST_PTR(psvInfo);

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
    CxUtils::ptrAssignT(a_psiPort, static_cast<short_t>( psvInfo->s_port ));

    //-------------------------------------
    //psProtocolName
    if (NULL != a_psProtocolName) {
        std::string _asProtocolName = psvInfo->s_proto;
        (*a_psProtocolName).assign(_asProtocolName.begin(), _asProtocolName.end());
    }
}
//---------------------------------------------------------------------------
/* static */
bool
CxDnsClient::bIsOnLan(
    const ulong_t &a_culIp
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
    const ulong_t &a_culIp
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
