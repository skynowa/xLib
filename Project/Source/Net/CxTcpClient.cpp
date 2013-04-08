/**
 * \file  CxTcpClient.cpp
 * \brief client socket
 */


#include <xLib/Net/CxTcpClient.h>

#include <xLib/Common/CxUtils.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* virtual */
CxTcpClient::CxTcpClient() :
    _m_tvTimeout()
{
    setTimeout(0L, SOCKET_TIMEOUT);
}
//------------------------------------------------------------------------------
CxTcpClient::~CxTcpClient() {

}
//------------------------------------------------------------------------------
bool_t
CxTcpClient::isReadable() {
    timeval tvTimeout = {1, 0};     /*seconds, microseconds*/
    fd_set  fds;        FD_ZERO(&fds);

    FD_SET(_m_sktSocket, &fds);

    int_t iRv = ::select(0, &fds, NULL, NULL, &tvTimeout);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_m_sktSocket, &fds), false);

    return true;
}
//------------------------------------------------------------------------------
bool_t
CxTcpClient::isWritable() {
    timeval tvTimeout = {1, 0};     /*seconds, microseconds*/
    fd_set  fds;        FD_ZERO(&fds);

    FD_SET(_m_sktSocket, &fds);

    int_t iRv = ::select(0, NULL, &fds, NULL, &tvTimeout);
    xCHECK_RET(iRv <= 0 || !FD_ISSET(_m_sktSocket, &fds), false);

    return true;
}
//------------------------------------------------------------------------------
void_t
CxTcpClient::connect(
    std::ctstring_t &a_csIp,
    cushort_t       &a_cusPort
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);
    xTEST_EQ(false, a_csIp.empty());
    xTEST_EQ(true, (65535 > a_cusPort) && (0 < a_cusPort));

    //конверт из UNICODE
    std::string asIp(a_csIp.begin(), a_csIp.end());

    sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = _m_siFamily;
    saSockAddr.sin_addr.s_addr = ::inet_addr(asIp.c_str());
    saSockAddr.sin_port        = htons(a_cusPort); //???????

    int_t iRv = ::connect(_m_sktSocket, CxUtils::reinterpretCastT<sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    xTEST_DIFF(xSOCKET_ERROR, iRv);
}
//------------------------------------------------------------------------------
void_t
CxTcpClient::ioctl(
    clong_t &a_cliCmd,
    ulong_t *a_pulArgp
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);

    int_t iRv = xSOCKET_ERROR;

#if xOS_ENV_WIN
    iRv = ioctlsocket(_m_sktSocket, a_cliCmd, a_pulArgp);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#else
    iRv = ::ioctl    (_m_sktSocket, a_cliCmd, a_pulArgp);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
#endif
}
//------------------------------------------------------------------------------
void_t
CxTcpClient::setNonBlockingMode(
    cbool_t &a_cbFlag
)
{
#if xOS_ENV_WIN
    ulong_t ulNonBlockingMode = static_cast<ulong_t>(a_cbFlag);

    ioctl(FIONBIO, static_cast<ulong_t FAR *>(&ulNonBlockingMode));

    /*
    int_t bOptVal = true;
    int_t bOptLen = sizeof(int_t);

    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&bOptVal, bOptLen);
    */
#else
    int_t iFlags = - 1;

    iFlags = ::fcntl(_m_sktSocket, F_GETFL);
    xTEST_DIFF(xSOCKET_ERROR, iFlags);

    if (a_cbFlag) {
        iFlags = (iFlags |  O_NONBLOCK);
    } else {
        iFlags = (iFlags & ~O_NONBLOCK);
    }

    iFlags = ::fcntl(_m_sktSocket, F_SETFL, iFlags);
    xTEST_DIFF(xSOCKET_ERROR, iFlags);
#endif
}
//------------------------------------------------------------------------------
void_t
CxTcpClient::timeout(
    long_t *a_pliSec,
    long_t *a_pliMicroSec
)
{
    // pliSec      - n/a
    // pliMicroSec - n/a

    // BUG: static_cast<long_t>( _m_tvTimeout.tv_sec  )
    CxUtils::ptrAssignT(a_pliSec,      static_cast<long_t>( _m_tvTimeout.tv_sec  ));
    CxUtils::ptrAssignT(a_pliMicroSec, static_cast<long_t>( _m_tvTimeout.tv_usec ));
}
//------------------------------------------------------------------------------
void_t
CxTcpClient::setTimeout(
    clong_t &a_cliSec,
    clong_t &a_cliMicroSec
)
{
    // liSec      - n/a
    // liMicroSec - n/a

    _m_tvTimeout.tv_sec  = a_cliSec;
    _m_tvTimeout.tv_usec = a_cliMicroSec;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: static
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
bool_t
CxTcpClient::isServerAlive(
    std::ctstring_t &a_csIp,
    cushort_t       &a_cusPort
)
{
    xTEST_EQ(false, a_csIp.empty());
    xTEST_EQ(true, (65535 > a_cusPort) && (0 < a_cusPort));

    int_t iRv = - 1;

    CxTcpClient objSocket;

    //-------------------------------------
    //bCreate
    objSocket.create(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);

    //-------------------------------------
    //bConnect
    //convert from UNICODE
    std::string asIp(a_csIp.begin(), a_csIp.end());

    sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = CxSocket::afInet;
    saSockAddr.sin_addr.s_addr = ::inet_addr(asIp.c_str());
    saSockAddr.sin_port        = htons(a_cusPort); //TODO: htons

    //connect - [+] 0 [-] SOCKET_ERROR
    iRv = ::connect(objSocket.handle(), CxUtils::reinterpretCastT<sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    // n/a

    xCHECK_RET(0 != iRv, false);

    return true;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
