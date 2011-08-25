/**
 * \file  CxDnsClient.cpp
 * \brief DNS
 */


#include <xLib/Net/CxDnsClient.h>


/****************************************************************************
*    Public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bGetHostAddrByName
/*static*/
BOOL
CxDnsClient::bGetHostAddrByName(
    const std::tstring &csHostName,
    std::tstring       *psHostAddr
)
{
    /*DEBUG*/xASSERT_RET(false == csHostName.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psHostAddr,         FALSE);

    std::tstring sRes;

    //convert to UNICODE
    std::string casHostName(csHostName.begin(), csHostName.end());

    hostent *pHostent = ::gethostbyname(casHostName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pHostent, FALSE);

    sRes = CxString::sFormat(
                xT("%u.%u.%u.%u"),
                static_cast<UCHAR>(pHostent->h_addr_list[0][0]),
                static_cast<UCHAR>(pHostent->h_addr_list[0][1]),
                static_cast<UCHAR>(pHostent->h_addr_list[0][2]),
                static_cast<UCHAR>(pHostent->h_addr_list[0][3])
    );
    /*DEBUG*/xASSERT_RET(false == sRes.empty(), FALSE);

    (*psHostAddr).assign(sRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetHostNameByAddr
/*static*/
BOOL
CxDnsClient::bGetHostNameByAddr(
    const std::tstring            &csHostAddr,
    CxSocket::EAddressFamily  afFamily,
    std::tstring                  *psHostName
)
{
    /*DEBUG*/xASSERT_RET(false == csHostAddr.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psHostName,         FALSE);

    //convert to UNICODE
    std::string casHostAddr(csHostAddr.begin(), csHostAddr.end());

    hostent *pHostent = NULL;

    switch (afFamily) {
        case CxSocket::afInet6: {
            #if (xWINVER >= xWIN32_VISTA)
                //////////////IN6_ADDR iaAddr6 = {0};

                //////////////_ms_iRes = ::inet_pton(afInet6, casHostAddr.c_str(), &iaAddr6);
                ///////////////*DEBUG*/xASSERT_RET(0 != _ms_iRes, FALSE);

                //////////////pHostent = ::gethostbyaddr((char *) &iaAddr6, 16, afInet6);
                ///////////////*DEBUG*/xASSERT_RET(NULL != pHostent, FALSE);
            #endif //xWIN32_VISTA
            }
            break;

        default: {
                in_addr iaAddr;

                iaAddr.s_addr = ::inet_addr(casHostAddr.c_str());
                /*DEBUG*/xASSERT_RET(iaAddr.s_addr != INADDR_NONE, FALSE);

                pHostent = ::gethostbyaddr((char *) &iaAddr, sizeof(iaAddr)/*4*/, CxSocket::afInet);
                /*DEBUG*/xASSERT_RET(NULL != pHostent, FALSE);
            }
            break;
    }

    //convert to UNICODE
    std::string sRes(pHostent->h_name);

    (*psHostName).assign(sRes.begin(), sRes.end());

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetLocalHostName ()
/*static*/
BOOL
CxDnsClient::bGetLocalHostName(
    std::tstring *psHostName
)
{
    /*DEBUG*/xASSERT_RET(NULL != psHostName, FALSE);

#if defined(xOS_WIN)
    std::string asRes(255 + 1, '0');
#elif defined(xOS_LINUX)
    std::string asRes(HOST_NAME_MAX, '0');
#endif

    _ms_iRes = ::gethostname(&asRes.at(0), asRes.size() * sizeof(std::string::value_type));
    /*DEBUG*/xASSERT_RET(0 == _ms_iRes, FALSE);

    asRes.assign(asRes.c_str());    //delete '0' from end

    //convert to UNICODE
    (*psHostName).assign(asRes.begin(), asRes.end());

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetNameInfo ()
/*static*/
BOOL
CxDnsClient::bGetNameInfo(
    CxSocket::EAddressFamily  afFamily,
    const std::tstring            &csHostAddr,
    USHORT                    usPort
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

    TCHAR szHostName[NI_MAXHOST] = {0};
    TCHAR szServInfo[NI_MAXSERV] = {0};

#if defined(xOS_WIN)
    //TODO: bGetNameInfo
    _ms_iRes = ::GetNameInfo((struct sockaddr *)&saGNI, sizeof(saGNI), &szHostName[0], NI_MAXHOST, &szServInfo[0], NI_MAXSERV, NI_NUMERICSERV);
    /*DEBUG*/xASSERT_RET(0 == _ms_iRes, FALSE);
#elif defined(xOS_LINUX)
    //TODO: bGetNameInfo
    _ms_iRes = getnameinfo((struct sockaddr *)&saGNI, sizeof(saGNI), &szHostName[0], NI_MAXHOST, &szServInfo[0], NI_MAXSERV, NI_NUMERICSERV);
    /*DEBUG*/xASSERT_RET(0 == _ms_iRes, FALSE);
#endif

    //hostname

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bGetHostAddrInfo ()
//NOTE: http://www.geekpage.jp/en/programming/linux-network/getaddrinfo-0.php
/*static*/
BOOL
CxDnsClient::bGetHostAddrInfo(
    const std::tstring    &csHostName,
    const std::tstring    &csPort,
    const ADDRINFOT  *pHints,
    ADDRINFOT       **ppResult
)
{
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);
    /*DEBUG*///xASSERT_RET(NULL != _m_hWnd, FALSE_RET_VALUE);

#if defined(xOS_WIN)
    _ms_iRes = ::GetAddrInfo(csHostName.c_str(), csPort.c_str(), pHints, ppResult);
    /*DEBUG*/xASSERT_RET(0 == _ms_iRes, FALSE);
#elif defined(xOS_LINUX)
    _ms_iRes =   getaddrinfo(csHostName.c_str(), csPort.c_str(), pHints, ppResult);
    /*DEBUG*/xASSERT_MSG_RET(0 == _ms_iRes, CxString::lexical_cast(_ms_iRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetProtocolByName ()
/*static*/
BOOL
CxDnsClient::bGetProtocolByName(
    const std::tstring        &csProtocolName,
    std::tstring              *psName,
    std::vector<std::tstring> *pvsAliases,
    SHORT                *psiNumber
)
{
    /*DEBUG*/xASSERT_RET(false == csProtocolName.empty(), FALSE);
    /*DEBUG*///psName       - n/a
    /*DEBUG*///pvsAliases - n/a
    /*DEBUG*///psiNumber    - n/a

    //convert to UNICODE
    std::string asProtocolName(csProtocolName.begin(), csProtocolName.end());

    protoent/*PROTOENT*/ *pptInfo = ::getprotobyname(asProtocolName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pptInfo, FALSE);

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

        for (CHAR **s = pptInfo->p_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring sRes;
            sRes.assign(asRes.begin(), asRes.end());

            pvsAliases->push_back(sRes);
        }
    }

    //-------------------------------------
    //psiNumber
    xCHECK_DO(NULL != psiNumber, *psiNumber = pptInfo->p_proto);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetProtocolByNumber ()
/*static*/
BOOL
CxDnsClient::bGetProtocolByNumber(
    SHORT                 siNumber,
    std::tstring              *psName,
    std::vector<std::tstring> *pvsAliases,
    SHORT                *psiNumber
)
{
    /*DEBUG*///siNum        - n/a
    /*DEBUG*///psName       - n/a
    /*DEBUG*///pvsAliases - n/a
    /*DEBUG*///psiNum       - n/a

    protoent/*PROTOENT*/*pptInfo = ::getprotobynumber(siNumber);
    /*DEBUG*/xASSERT_RET(NULL != pptInfo, FALSE);

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

        for (CHAR **s = pptInfo->p_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring sRes;
            sRes.assign(asRes.begin(), asRes.end());

            pvsAliases->push_back(sRes);
        }
    }

    //-------------------------------------
    //psiNum
    xCHECK_DO(NULL != psiNumber, *psiNumber = pptInfo->p_proto);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetServiceByName ()
/*static*/
BOOL
CxDnsClient::bGetServiceByName(
    const std::tstring        &csServiceName,
    const std::tstring        &csProtocolName,
    std::tstring              *psName,
    std::vector<std::tstring> *pvsAliases,
    SHORT                *psiPort,
    std::tstring              *psProtocolName
)
{
    /*DEBUG*/xASSERT_RET(false == csServiceName.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csProtocolName.empty(), FALSE);
    /*DEBUG*///psName         - n/a
    /*DEBUG*///pvsAliases   - n/a
    /*DEBUG*///psiPort        - n/a
    /*DEBUG*///psProtocolName - n/a

    //convert to UNICODE
    std::string asServiceName (csServiceName.begin(),  csServiceName.end());
    std::string asProtocolName(csProtocolName.begin(), csProtocolName.end());

    servent *psvInfo = ::getservbyname(asServiceName.c_str(), asProtocolName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != psvInfo, FALSE);

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

        for (CHAR **s = psvInfo->s_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring sRes;
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

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetServiceByPort ()
/*static*/
BOOL
CxDnsClient::bGetServiceByPort(
    SHORT                 siPort,
    const std::tstring        &csProtocolName,
    std::tstring              *psName,
    std::vector<std::tstring> *pvsAliases,
    SHORT                *psiPort,
    std::tstring              *psProtocolName
)
{
    /*DEBUG*///TODO: siPort
    /*DEBUG*/xASSERT_RET(false == csProtocolName.empty(), FALSE);
    /*DEBUG*///psName         - n/a
    /*DEBUG*///pvsAliases   - n/a
    /*DEBUG*///psiPort        - n/a
    /*DEBUG*///psProtocolName - n/a

    //convert to UNICODE
    std::string asProtocolName(csProtocolName.begin(), csProtocolName.end());

    servent *psvInfo = ::getservbyport(siPort, asProtocolName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != psvInfo, FALSE);

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

        for (CHAR **s = psvInfo->s_aliases; s && *s; ++ s) {
            std::string asRes;
            asRes.assign(*s);

            //convert to UNICODE
            std::tstring sRes;
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

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

BOOL CxDnsClient::_ms_bRes = FALSE;
INT  CxDnsClient::_ms_iRes = - 1;

//---------------------------------------------------------------------------
//DONE: CxDnsClient
CxDnsClient::CxDnsClient() {

}
//---------------------------------------------------------------------------
//DONE: ~CxDnsClient
/*virtual*/
CxDnsClient::~CxDnsClient() {

}
//---------------------------------------------------------------------------
