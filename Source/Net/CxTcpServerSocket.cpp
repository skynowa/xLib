/****************************************************************************
* Class name:  CxTcpServerSocket
* Description: server socket
* File name:   CxTcpServerSocket.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.04.2009 6:21:18
*
*****************************************************************************/


#include <xLib/Net/CxTcpServerSocket.h>


//---------------------------------------------------------------------------
//DONE: CxTcpServerSocket (construcor)
CxTcpServerSocket::CxTcpServerSocket() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTcpServerSocket (destructor)
CxTcpServerSocket::~CxTcpServerSocket() {

}
//---------------------------------------------------------------------------
//DONE: bBind (associates a local address with a socket)
BOOL
CxTcpServerSocket::bBind(USHORT usPort) {
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket,        FALSE);
    /*DEBUG*/xASSERT_RET((32767 > usPort) && (0 < usPort), FALSE);

    struct sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = _m_siFamily;
    saSockAddr.sin_addr.s_addr = INADDR_ANY;
    saSockAddr.sin_port        = htons(usPort);

    INT iRes = bind(_m_puiSocket, CxMacros::xreinterpret_cast<const struct sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);

    ////INT iOpt = 1;
    //???
    ////if (::setsockopt(_m_puiSocket, SOL_SOCKET, SO_REUSEADDR, (LPSTR)&iOpt, sizeof(iOpt)) < 0) {
    ////    return FALSE;
    ////}

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bListen (places a socket in a state in which it is listening for an incoming connection)
BOOL
CxTcpServerSocket::bListen(INT iBacklog /*= SOMAXCONN*/) {
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket, FALSE);

    INT iRes = listen(_m_puiSocket, iBacklog);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bAccept (permits an incoming connection attempt on a socket)
BOOL
CxTcpServerSocket::bAccept(CxTcpServerSocket *pscktAcceptSocket, tString *psFromIp) {
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket,      FALSE);
    /*DEBUG*/xASSERT_RET(NULL      != pscktAcceptSocket, FALSE);
    /*DEBUG*/xASSERT_RET(NULL      != psFromIp,          FALSE);

    SOCKET scktClient = etInvalid;

#if defined(xOS_WIN)
    struct sockaddr_in cliaddr  = {0};
    INT                iAddrlen = sizeof(cliaddr);

    scktClient = accept(_m_puiSocket, CxMacros::xreinterpret_cast<struct sockaddr *>( &cliaddr ), &iAddrlen);
    /*DEBUG*/xASSERT_RET(etInvalid != scktClient, FALSE);
#elif defined(xOS_LINUX)
    struct sockaddr_in cliaddr  = {0};
    socklen_t          iAddrlen = sizeof(cliaddr);

    scktClient = accept(_m_puiSocket, CxMacros::xreinterpret_cast<struct sockaddr *>( &cliaddr ), &iAddrlen);
    /*DEBUG*/xASSERT_RET(etInvalid != scktClient, FALSE);
#endif

    //TODO: bAccept
    ////scktAcceptSocket = scktClient;
    _m_bRes = (* pscktAcceptSocket).bAssign(scktClient);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //конверт из UNICODE
    std::string asFromIp = inet_ntoa(cliaddr.sin_addr);

    (*psFromIp).assign(asFromIp.begin(), asFromIp.end());

    return TRUE;
}
//---------------------------------------------------------------------------

