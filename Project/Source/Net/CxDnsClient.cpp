/**
 * \file  CxDnsClient.cpp
 * \brief DNS
 */


#include <xLib/Net/CxDnsClient.h>

#include <xLib/Core/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    Public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
void_t
CxDnsClient::hostAddrByName(
    std::ctstring_t &a_csHostName,
    std::tstring_t  *a_psHostAddr
)
{
    xTEST_EQ(false, a_csHostName.empty());
    xTEST_PTR(a_psHostAddr);

    std::tstring_t sRv;

    //convert to UNICODE
    std::string casHostName(a_csHostName.begin(), a_csHostName.end());

    hostent *pHostent = ::gethostbyname(casHostName.c_str());
    xTEST_PTR(pHostent);

    sRv = CxString::format(
                xT("%u.%u.%u.%u"),
                static_cast<uchar_t>(pHostent->h_addr_list[0][0]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][1]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][2]),
                static_cast<uchar_t>(pHostent->h_addr_list[0][3])
    );
    xTEST_EQ(false, sRv.empty());

    (*a_psHostAddr) = sRv;
}
//------------------------------------------------------------------------------
/* static */
void_t
CxDnsClient::hostNameByAddr(
    std::ctstring_t                 &a_csHostAddr,
    const CxSocket::ExAddressFamily &a_afFamily,
    std::tstring_t                  *a_psHostName
)
{
    xTEST_EQ(false, a_csHostAddr.empty());
    xTEST_PTR(a_psHostName);

    //convert to UNICODE
    std::string casHostAddr(a_csHostAddr.begin(), a_csHostAddr.end());

    hostent *pHostent = NULL;

    switch (a_afFamily) {
        case CxSocket::afInet6:
        #if (xWINVER >= xOS_WIN_VISTA)
            #if xTODO
                IN6_ADDR iaAddr6 = {0};

                iRv = ::inet_pton(afInet6, a_casHostAddr.c_str(), &iaAddr6);
                xTEST_DIFF(0, iRv);

                pHostent = ::gethostbyaddr((char *) &iaAddr6, 16, afInet6);
                xTEST_PTR(pHostent, false);
            #endif
        #endif // xOS_WIN_VISTA
            break;
        default:
            in_addr iaAddr;

            iaAddr.s_addr = ::inet_addr(casHostAddr.c_str());
            xTEST_EQ(true, iaAddr.s_addr != INADDR_NONE);

            pHostent = ::gethostbyaddr((char *) &iaAddr, sizeof(iaAddr)/*4*/, CxSocket::afInet);
            xTEST_PTR(pHostent);
            break;
    }

    // convert to UNICODE
    std::string sRv(pHostent->h_name);

    (*a_psHostName).assign(sRv.begin(), sRv.end());
}
//------------------------------------------------------------------------------
/* static */
void_t
CxDnsClient::localHostName(
    std::tstring_t *a_psHostName
)
{
    xTEST_PTR(a_psHostName);

    std::string asRes(xHOST_NAME_MAX, '0');

    int_t iRv = ::gethostname(&asRes.at(0), static_cast<int_t>( asRes.size() * sizeof(std::string::value_type) ));
    xTEST_EQ(0, iRv);

    asRes.assign(asRes.c_str());    //delete '0' from end

    //convert to UNICODE
    (*a_psHostName).assign(asRes.begin(), asRes.end());
}
//------------------------------------------------------------------------------
/* static */
void_t
CxDnsClient::nameInfo(
    CxSocket::ExAddressFamily &a_afFamily,
    std::ctstring_t           &a_csHostAddr,
    cushort_t                 &a_usPort
)
{
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);

    //convert to UNICODE
    std::string casHostAddr(a_csHostAddr.begin(), a_csHostAddr.end());

    sockaddr_in saGNI = {0};
    saGNI.sin_family      = a_afFamily;
    saGNI.sin_addr.s_addr = ::inet_addr(casHostAddr.c_str());
    saGNI.sin_port        = htons(a_usPort);

    tchar_t szHostName[NI_MAXHOST + 1] = {0};
    tchar_t szServInfo[NI_MAXSERV + 1] = {0};

    //TODO: bGetNameInfo
    int_t iRv = ::xGETNAMEINFO((struct sockaddr *)&saGNI, sizeof(saGNI), &szHostName[0], NI_MAXHOST, &szServInfo[0], NI_MAXSERV, NI_NUMERICSERV);
    xTEST_EQ(0, iRv);

    //hostname
}
//------------------------------------------------------------------------------
//NOTE: http://www.geekpage.jp/en/programming/linux-network/getaddrinfo-0.php
/* static */
void_t
CxDnsClient::hostAddrInfo(
    std::ctstring_t  &a_csHostName,
    std::ctstring_t  &a_csPort,
    caddrinfo_t      *a_pHints,
    addrinfo_t      **a_ppResult
)
{
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    //xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);

    int_t iRv = ::xGETADDRINFO(a_csHostName.c_str(), a_csPort.c_str(), a_pHints, a_ppResult);
    xTEST_EQ(0, iRv);
}
//------------------------------------------------------------------------------
/* static */
void_t
CxDnsClient::protocolByName(
    std::ctstring_t    &a_csProtocolName,
    std::tstring_t     *a_psName,
    std::vec_tstring_t *a_pvsAliases,
    short_t            *a_psiNumber
)
{
    xTEST_EQ(false, a_csProtocolName.empty());
    //psName     - n/a
    //pvsAliases - n/a
    //psiNumber  - n/a

    //convert to UNICODE
    std::string asProtocolName(a_csProtocolName.begin(), a_csProtocolName.end());

    protoent/*PROTOENT*/ *pptInfo = ::getprotobyname(asProtocolName.c_str());
    xTEST_PTR(pptInfo);

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
//------------------------------------------------------------------------------
/* static */
void_t
CxDnsClient::protocolByNumber(
    cshort_t           &a_siNumber,
    std::tstring_t     *a_psName,
    std::vec_tstring_t *a_pvsAliases,
    short_t            *a_psiNumber
)
{
    //siNum      - n/a
    //psName     - n/a
    //pvsAliases - n/a
    //psiNum     - n/a

    protoent/*PROTOENT*/*pptInfo = ::getprotobynumber(a_siNumber);
    xTEST_PTR(pptInfo);

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
//------------------------------------------------------------------------------
/* static */
void_t
CxDnsClient::serviceByName(
    std::ctstring_t    &a_csServiceName,
    std::ctstring_t    &a_csProtocolName,
    std::tstring_t     *a_psName,
    std::vec_tstring_t *a_pvsAliases,
    short_t            *a_psiPort,
    std::tstring_t     *a_psProtocolName
)
{
    xTEST_EQ(false, a_csServiceName.empty());
    xTEST_EQ(false, a_csProtocolName.empty());
    //psName         - n/a
    //pvsAliases   - n/a
    //psiPort        - n/a
    //psProtocolName - n/a

    //convert to UNICODE
    std::string asServiceName (a_csServiceName.begin(),  a_csServiceName.end());
    std::string asProtocolName(a_csProtocolName.begin(), a_csProtocolName.end());

    servent *psvInfo = ::getservbyname(asServiceName.c_str(), asProtocolName.c_str());
    xTEST_PTR(psvInfo);

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
//------------------------------------------------------------------------------
/* static */
void_t
CxDnsClient::serviceByPort(
    cshort_t           &a_siPort,
    std::ctstring_t    &a_csProtocolName,
    std::tstring_t     *a_psName,
    std::vec_tstring_t *a_pvsAliases,
    short_t            *a_psiPort,
    std::tstring_t     *a_psProtocolName
)
{
    //TODO: siPort
    xTEST_EQ(false, a_csProtocolName.empty());
    //psName         - n/a
    //pvsAliases   - n/a
    //psiPort        - n/a
    //psProtocolName - n/a

    //convert to UNICODE
    std::string asProtocolName(a_csProtocolName.begin(), a_csProtocolName.end());

    servent *psvInfo = ::getservbyport(a_siPort, asProtocolName.c_str());
    xTEST_PTR(psvInfo);

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
//------------------------------------------------------------------------------
/* static */
bool_t
CxDnsClient::isOnLan(
    culong_t &a_culIp
)
{
    culong_t culMyIpAddress = INADDR_ANY;     // IP of local interface (network order)
    culong_t culNetMask     = INADDR_NONE;    // net mask for IP (network order)

    return (0L == ((ntohl(a_culIp) ^ ntohl(culMyIpAddress)) & ntohl(culNetMask)));
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxDnsClient::isBroadcast(
    culong_t &a_culIp
)
{
    culong_t culNetMask = INADDR_NONE;    // net mask for IP (network order)

    return (0L == (~ntohl(a_culIp) & ~ntohl(culNetMask)));
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxDnsClient::CxDnsClient() {

}
//------------------------------------------------------------------------------
/* virtual */
CxDnsClient::~CxDnsClient() {

}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
