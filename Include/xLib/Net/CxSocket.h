/**
 * \file  CxSocket.h
 * \brief blocking socket
 */


#pragma once

#ifndef xLib_CxSocketH
#define xLib_CxSocketH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, net)

class CxSocket
    /// socket
{
public:
    enum ExAddressFamily
        /// address family
    {
    #if   xOS_ENV_WIN
        afUnspecified = AF_UNSPEC,
        afInet        = AF_INET,
        afIpx         = AF_IPX,
        afAppletalk   = AF_APPLETALK,
        afNetbios     = AF_NETBIOS,
        afInet6       = AF_INET6,
        afIrdA        = AF_IRDA
        #if !xCOMPILER_MINGW && !xCOMPILER_CODEGEAR
            ,
            afBluetooth   = AF_BTH
        #endif
    #elif xOS_ENV_UNIX
        #if xOS_FREEBSD
            afLocal     = PF_LOCAL,
            afUnix      = PF_UNIX,
            afInet      = PF_INET,
            afPup       = PF_PUP,
            afAppletalk = PF_APPLETALK,
            afRoute     = PF_ROUTE,
            afLink      = PF_LINK,
            afIpx       = PF_IPX,
            afRtip      = PF_RTIP,
            afPip       = PF_PIP,
            afIsdn      = PF_ISDN,
            afKey       = PF_KEY,
            afInet6     = PF_INET6,
            afNatm      = PF_NATM,
            afAtm       = PF_ATM,
            afNetgraph  = PF_NETGRAPH,
        #else
            afUnix        = AF_UNIX,
            afLocal       = AF_LOCAL,
            afInet        = AF_INET,
            afInet6       = AF_INET6,
            afIpx         = AF_IPX,
            afNetlink     = AF_NETLINK,
            afX25         = AF_X25,
            afAX25        = AF_AX25,
            afAtmpvc      = AF_ATMPVC,
            afAppletalk   = AF_APPLETALK,
            afPacket      = AF_PACKET
        #endif
    #elif xOS_ENV_APPLE
        afUnix        = AF_UNIX,
        afLocal       = AF_LOCAL,
        afInet        = AF_INET,
        afInet6       = AF_INET6,
        afIpx         = AF_IPX,
        afAppletalk   = AF_APPLETALK

        // TODO: CxSocket - add AP-*
    #endif
    };

    enum ExType
       /// type
    {
        tpStream      = SOCK_STREAM,
        tpDgram       = SOCK_DGRAM,
        tpRaw         = SOCK_RAW,
        tpRdm         = SOCK_RDM,
        tpSeqPacket   = SOCK_SEQPACKET
    };

    enum ExProtocol
        /// protocol
    {
    #if xOS_ENV_WIN
        ptIp          = IPPROTO_IP,
        ptIcmp        = IPPROTO_ICMP,
        ptIgmp        = IPPROTO_IGMP,
        ////ptRfcomm      = BTHPROTO_RFCOMM,
        ptTcp         = IPPROTO_TCP,
        ptUdp         = IPPROTO_UDP,
        #if !xCOMPILER_CODEGEAR
        ptIcmpv6      = IPPROTO_ICMPV6,
        #endif
        ////ptRm          = IPPROTO_RM
    #elif xOS_ENV_UNIX
        #if xOS_FREEBSD
            ptIp          = IPPROTO_IP,
            ptHopopts     = IPPROTO_HOPOPTS,
            ptIcmp        = IPPROTO_ICMP,
            ptIgmp        = IPPROTO_IGMP,
            ptIpip        = IPPROTO_IPIP,
            ptTcp         = IPPROTO_TCP,
            ptEgp         = IPPROTO_EGP,
            ptPup         = IPPROTO_PUP,
            ptUdp         = IPPROTO_UDP,
            ptIdp         = IPPROTO_IDP,
            ptTp          = IPPROTO_TP,
            ptIpv6        = IPPROTO_IPV6,
            ptRouting     = IPPROTO_ROUTING,
            ptFragment    = IPPROTO_FRAGMENT,
            ptRsvp        = IPPROTO_RSVP,
            ptGre         = IPPROTO_GRE,
            ptEsp         = IPPROTO_ESP,
            ptAH          = IPPROTO_AH,
            ptICmpv6      = IPPROTO_ICMPV6,
            ptNone        = IPPROTO_NONE,
            ptDstopts     = IPPROTO_DSTOPTS,
            ptMtp         = IPPROTO_MTP,
            ptEncap       = IPPROTO_ENCAP,
            ptPim         = IPPROTO_PIM,
            ptRaw         = IPPROTO_RAW,
            ptMax         = IPPROTO_MAX
        #else
            ptIp          = IPPROTO_IP,
            ptHopopts     = IPPROTO_HOPOPTS,
            ptIcmp        = IPPROTO_ICMP,
            ptIgmp        = IPPROTO_IGMP,
            ptIpip        = IPPROTO_IPIP,
            ptTcp         = IPPROTO_TCP,
            ptEgp         = IPPROTO_EGP,
            ptPup         = IPPROTO_PUP,
            ptUdp         = IPPROTO_UDP,
            ptIdp         = IPPROTO_IDP,
            ptTp          = IPPROTO_TP,
            ////ptDccp        = IPPROTO_DCCP,
            ptIpv6        = IPPROTO_IPV6,
            ptRouting     = IPPROTO_ROUTING,
            ptFragment    = IPPROTO_FRAGMENT,
            ptRsvp        = IPPROTO_RSVP,
            ptGre         = IPPROTO_GRE,
            ptEsp         = IPPROTO_ESP,
            ptAH          = IPPROTO_AH,
            ptICmpv6      = IPPROTO_ICMPV6,
            ptNone        = IPPROTO_NONE,
            ptDstopts     = IPPROTO_DSTOPTS,
            ptMtp         = IPPROTO_MTP,
            ptEncap       = IPPROTO_ENCAP,
            ptPim         = IPPROTO_PIM,
            ptComp        = IPPROTO_COMP,
            ptSctp        = IPPROTO_SCTP,
            ////ptUdplite     = IPPROTO_UDPLITE,
            ptRaw         = IPPROTO_RAW,
            ptMax         = IPPROTO_MAX
        #endif
    #elif xOS_ENV_APPLE
        ptIp          = IPPROTO_IP,
        ptHopopts     = IPPROTO_HOPOPTS,
        ptIcmp        = IPPROTO_ICMP,
        ptIgmp        = IPPROTO_IGMP,
        ptIpip        = IPPROTO_IPIP,
        ptTcp         = IPPROTO_TCP,
        ptEgp         = IPPROTO_EGP,
        ptPup         = IPPROTO_PUP,
        ptUdp         = IPPROTO_UDP,
        ptIdp         = IPPROTO_IDP,
        ptTp          = IPPROTO_TP,
        ptIpv6        = IPPROTO_IPV6,
        ptRouting     = IPPROTO_ROUTING,
        ptFragment    = IPPROTO_FRAGMENT,
        ptRsvp        = IPPROTO_RSVP,
        ptGre         = IPPROTO_GRE,
        ptEsp         = IPPROTO_ESP,
        ptAH          = IPPROTO_AH,
        ptICmpv6      = IPPROTO_ICMPV6,
        ptNone        = IPPROTO_NONE,
        ptDstopts     = IPPROTO_DSTOPTS,
        ptMtp         = IPPROTO_MTP,
        ptEncap       = IPPROTO_ENCAP,
        ptPim         = IPPROTO_PIM,
        ptSctp        = IPPROTO_SCTP,
        ptRaw         = IPPROTO_RAW,
        ptMax         = IPPROTO_MAX
        // TODO: CxSocket - add IPPROTO-*
    #endif
    };

    enum ExOptions
        /// options
    {
        SOCKET_TIMEOUT   = 0,       ///< (1000000 / 10)
        SOCKET_BUFF_SIZE = 32768    ///< 32 KB
    };

                   CxSocket();
        ///< constructor
    virtual       ~CxSocket() = 0;
        ///< destructor

    void_t         assign(csocket_t &socket);
        ///< assign to another socket

    /*******************************************************************************
    * operators
    *
    *******************************************************************************/

    CxSocket &     operator = (csocket_t &socket);
        ///< operator =


    /*******************************************************************************
    *
    *
    *******************************************************************************/

    void_t         create(const ExAddressFamily &family, const ExType &type,
                       const ExProtocol &protocol);
        ///< creates a socket that is bound to a specific transport service provider
    socket_t       handle() const xWARN_UNUSED_RV;
        ///< get socket
    bool_t         isValid() const xWARN_UNUSED_RV;
        ///< checking for validness
    void_t         close();
        ///< close


    /*******************************************************************************
    * I/O
    *
    *******************************************************************************/

    //void_t *, std::tstring_t, std::ustring_t

    ssize_t        send(ctchar_t *buff, std::csize_t &buffSize, cint_t &flags) xWARN_UNUSED_RV;
        ///< send data
    void_t         sendAll(std::ctstring_t &buff, cint_t &flags);
        ///< send data by blocks

    ssize_t        receive(tchar_t *buff,  std::csize_t &buffSize, cint_t &flags) xWARN_UNUSED_RV;
        ///< receive data
    std::tstring_t recvAll(cint_t &flags) xWARN_UNUSED_RV;
        ///< receive data
    std::tstring_t recvAll(cint_t &flags, std::ctstring_t &delimiter) xWARN_UNUSED_RV;
        ///< receive data to delimiter, includes it

    int_t          sendBytes(char *buff, ssize_t &messageLength) xWARN_UNUSED_RV;
        ///< send bytes
    int_t          receiveBytes(char *buff, ssize_t &stillToReceive) xWARN_UNUSED_RV;
        ///< receive bytes


    /*******************************************************************************
    * Other
    *
    *******************************************************************************/

    void_t           peerName(std::tstring_t *peerAddr, ushort_t *peerPort);
        ///< get address of the peer to which a socket is connected
    void_t           socketName(std::tstring_t *socketAddr, ushort_t *socketPort);
        ///< get local name for a socket

    /*******************************************************************************
    * static
    *
    *******************************************************************************/

    ////getsockopt
    static
    int_t            select(int_t nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
                         timeval *timeout) xWARN_UNUSED_RV;
        ///< determines the status of one or more sockets, waiting if necessary,
        ///< to perform synchronous I/O
    static
    int_t            lastError() xWARN_UNUSED_RV;
        ///< get error status for the last operation that failed

protected:
    socket_t         _socket;  ///< handle to socket
    short_t          _family;   ///< family
    std::tstring_t   _ip;        ///< IP
    ushort_t         _port;     ///< port

    xNO_COPY_ASSIGN(CxSocket)
};

xNAMESPACE2_END(xlib, net)
//-------------------------------------------------------------------------------------------------
#include "CxSocket.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSocketH


#if xTODO
    //http://www.yolinux.com/TUTORIALS/Sockets.html
#endif

#if xTODO
    std::tstring_t sStr = xT("Some string!!!");
    ::send(0, reinterpret_cast<char const*>(sStr.data()), sStr.size() *
        sizeof(std::tstring_t::value_type), 0);

    sizeof(std::tstring_t::value_type)
#endif

#if xTODO
    ---Server-----

    Initialize Winsock.
    Create a socket.
    Bind the socket.
    Listen on the socket for a client.
    Accept a connection from a client.
    Receive and send data.
    Disconnect.
    ---Client----

    Initialize Winsock.
    Create a socket.
    Connect to the server.
    Send and receive data.
    Disconnect.
#endif

#if xTODO
    int_t
    CxSocket::WaitForData(SOCKET *pSocketForReceiving, SOCKET *pSocketForSending,
        SOCKET *pSocketForExceptions)
    {
        int_t nSocketsReady = 0;

        fd_set FdSetReceive;    FD_ZERO(&FdSetReceive);
        fd_set FdSetSend;       FD_ZERO(&FdSetSend);
        fd_set FdSetError;      FD_ZERO(&FdSetError);

        if (pSocketForReceiving) {
            FD_SET(*pSocketForReceiving, &FdSetReceive);
        }
        if (pSocketForSending) {
            FD_SET(*pSocketForSending, &FdSetSend);
        }
        if (pSocketForExceptions) {
            FD_SET(*pSocketForExceptions, &FdSetError);
        }

        TIMEVAL tv;
        TIMEVAL *ptv = xPTR_NULL;

        if (_m_timeout) {
            tv.tv_sec =  _m_timeout / 1000;
            tv.tv_usec = _m_timeout * 1000 - tv.tv_sec * 1000000;
            ptv = &tv;
        } else {
            ptv = xPTR_NULL; // xPTR_NULL for blocking operation (never times out)
        }

        nSocketsReady = select(0, &FdSetReceive, &FdSetSend, &FdSetError, ptv);

        //If the operation timed out, set a more natural error message
        if (nSocketsReady == 0) {
            SetLastError(WSAETIMEDOUT);
            nSocketsReady = SOCKET_ERROR;
        }

        return nSocketsReady;
    }
#endif

#if xTODO
    procedure FlushRecvBufferUntil(s:TSOCKET;condition:Char);
    var
        iReceiveRes : integer;
        cDummy : char;
        begin
    repeat
        iReceiveRes := recv(s, cDummy, sizeof(cDummy), 0);
        until NOT ((iReceiveRes<>SOCKET_ERROR) and (iReceiveRes<>0) and
        (cDummy<>condition));
    end;
#endif
