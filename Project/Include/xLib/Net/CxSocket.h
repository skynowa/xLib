/**
 * \file  CxSocket.h
 * \brief socket
 */


#ifndef xLib_Net_CxSocket
#define xLib_Net_CxSocket
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSocket :
    private CxNonCopyable
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
    #if   xOS_ENV_WIN
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
    #endif
    };

    enum ExOptions
        /// options
    {
        SOCKET_TIMEOUT   = 0,       ///< (1000000 / 10)
        SOCKET_BUFF_SIZE = 32768    ///< 32 KB
    };

                   CxSocket       ();
        ///< constructor
    virtual       ~CxSocket       () = 0;
        ///< destructor

    void           vAssign        (const socket_t &csktSocket);
        ///< assign to another socket

    /****************************************************************************
    * operators
    *
    *****************************************************************************/

    CxSocket &     operator =     (const socket_t &csktSocket);
        ///< operator =
                   operator socket_t();
        ///< operator socket_t


    /****************************************************************************
    *
    *
    *****************************************************************************/

    void           create        (const ExAddressFamily &cafFamily, const ExType &ctpType, const ExProtocol &cptProtocol);
        ///< creates a socket that is bound to a specific transport service provider
    socket_t       iHandle        () const;
        ///< get socket
    bool           bIsValid       () const;
        ///< checking for validness
    void           vClose         ();
        ///< close


    /****************************************************************************
    * I/O
    *
    *****************************************************************************/

    //void *, std::tstring_t, std::ustring_t

    int            iSend          (const tchar_t *pcszBuff, const int &ciBuffSize, const int &ciFlags);
        ///< send data
    void           vSendAll       (const std::tstring_t &csBuff, const int &ciFlags);
        ///< send data by blocks

    int            iRecv          (tchar_t *pszBuff,  const int &ciBuffSize, const int &ciFlags);
        ///< recieve data
    std::tstring_t sRecvAll       ( const int &ciFlags);
        ///< recieve data
    std::tstring_t sRecvAll       (const int &ciFlags, const std::tstring_t &csDelimiter);
        ///< recive data to delimiter, includs it

    int            iSendBytes     (char *pszBuff, const int &ciMessageLength);
        ///< send bytes
    int            iReceiveBytes  (char *pszBuff, const int &ciStillToReceive);
        ///< recieve bytes


    /****************************************************************************
    * Other
    *
    *****************************************************************************/

    void           vPeerName      (std::tstring_t *psPeerAddr, ushort_t *pusPeerPort);
        ///< get address of the peer to which a socket is connected
    void           vSocketName    (std::tstring_t *psSocketAddr, ushort_t *pusSocketPort);
        ///< get local name for a socket

    /****************************************************************************
    * static
    *
    *****************************************************************************/

    ////getsockopt
    static int     iSelect        (int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, timeval *tvTimeout);
        ///< determines the status of one or more sockets, waiting if necessary, to perform synchronous I/O
    static int     iLastError     ();
        ///< get error status for the last operation that failed

protected:
    socket_t       _m_sktSocket;  ///< handle to socket
    short_t        _m_siFamily;   ///< family
    std::tstring_t _m_sIp;        ///< IP
    ushort_t       _m_usPort;     ///< port

private:
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Net_CxSocket


#if xTODO
    //http://www.yolinux.com/TUTORIALS/Sockets.html
#endif

#if xTODO
    std::tstring_t sStr = xT("Some string!!!");
    ::send(0, reinterpret_cast<char const*>(sStr.data()), sStr.size() * sizeof(std::tstring_t::value_type), 0);

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
    int
    CxSocket::WaitForData(SOCKET *pSocketForReceiving, SOCKET *pSocketForSending, SOCKET *pSocketForExceptions) {
        int nSocketsReady = 0;

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
        TIMEVAL *ptv = NULL;

        if (_m_tvTimeout) {
            tv.tv_sec =  _m_tvTimeout / 1000;
            tv.tv_usec = _m_tvTimeout * 1000 - tv.tv_sec * 1000000;
            ptv = &tv;
        } else {
            ptv = NULL; // NULL for blocking operation (never times out)
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
