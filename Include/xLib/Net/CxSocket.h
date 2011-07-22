/****************************************************************************
* Class name:  CxSocket
* Description: socket
* File name:   CxSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.04.2009 6:21:18
*
*****************************************************************************/


#ifndef xLib_Net_CxSocket
#define xLib_Net_CxSocket
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_LINUX)
    typedef INT SOCKET;
#endif
//---------------------------------------------------------------------------
class CxSocket :
    public CxNonCopyable
{
    public:
        /****************************************************************************
        *   constants
        *
        *****************************************************************************/

        //address family
        enum EAddressFamily {
        #if defined(xOS_WIN)
            afUnspecified = AF_UNSPEC,
            afInet        = AF_INET,
            afIpx         = AF_IPX,
            afAppletalk   = AF_APPLETALK,
            afNetbios     = AF_NETBIOS,
            afInet6       = AF_INET6,
            afIrdA        = AF_IRDA
			#if !defined(xCOMPILER_MINGW32)
				,
				afBluetooth   = AF_BTH
			#endif
        #elif defined(xOS_LINUX)
            #if !defined(xOS_FREEBSD)
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
            #elif defined(xOS_FREEBSD)
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
            #endif
        #endif
        };

        //type
        enum EType {
            tpStream      = SOCK_STREAM,
            tpDgram       = SOCK_DGRAM,
            tpRaw         = SOCK_RAW,
            tpRdm         = SOCK_RDM,
            tpSeqPacket   = SOCK_SEQPACKET
        };

        //protocol
        enum EProtocol {
        #if defined(xOS_WIN)
            ptIp          = IPPROTO_IP,
            ptIcmp        = IPPROTO_ICMP,
            ptIgmp        = IPPROTO_IGMP,
            ////ptRfcomm      = BTHPROTO_RFCOMM,
            ptTcp         = IPPROTO_TCP,
            ptUdp         = IPPROTO_UDP,
            ptIcmpv6      = IPPROTO_ICMPV6,
            ////ptRm          = IPPROTO_RM
        #elif defined(xOS_LINUX)
            #if defined(xOS_FREEBSD)
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
            #elif
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
                ptDccp        = IPPROTO_DCCP,
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
                ptUdplite     = IPPROTO_UDPLITE,
                ptRaw         = IPPROTO_RAW,
                ptMax         = IPPROTO_MAX
            #endif
        #endif
        };


        //errors
        enum EErrorType {
        #if defined(xOS_WIN)
            etInvalid = INVALID_SOCKET,  //~0
            etError   = SOCKET_ERROR     //-1
        #elif defined(xOS_LINUX)
            etInvalid = - 1,
            etError   = - 1
        #endif
        };

        //options
        enum EOptions {
            SOCKET_TIMEOUT   = 0,       // (1000000 / 10)
            SOCKET_BUFF_SIZE = 32768    // 32 KB      /*8192*//*1024*/
        };

                    CxSocket           ();
        virtual    ~CxSocket           () = 0;

        BOOL        bAssign            (SOCKET scktSocket);

        /****************************************************************************
        * operators
        *
        *****************************************************************************/

        CxSocket&   operator =         (SOCKET s);
                    operator SOCKET    ();


        /****************************************************************************
        *
        *
        *****************************************************************************/

        BOOL        bCreate            (EAddressFamily afFamily, EType tpType, EProtocol ptProtocol);
        SOCKET      iGetSocket         () const;
        BOOL        bIsValid           () const;
        BOOL        bClose             ();


        /****************************************************************************
        * I/O
        *
        *****************************************************************************/

        //VOID *, tString, uString

        INT         iSend              (LPCTSTR pcszBuff, INT iBuffSize, INT iFlags);
        BOOL        bSendAll           (const tString &csBuff, INT iFlags);

        INT         iRecv              (LPTSTR  pszBuff,  INT iBuffSize, INT iFlags);
        tString     sRecvAll           (INT iFlags);
        tString     sRecvAll           (INT iFlags, const tString &csDelimiter);

        INT         iSendBytes         (LPSTR pszBuff, INT iMessageLength);
        INT         iReceiveBytes      (LPSTR pszBuff, INT iStillToReceive);


        /****************************************************************************
        * Other
        *
        *****************************************************************************/

        BOOL        bGetPeerName       (tString *psPeerAddr, USHORT *pusPeerPort);
        BOOL        bGetSocketName     (tString *psSocketAddr, USHORT *pusSocketPort);

        /****************************************************************************
        * static
        *
        *****************************************************************************/

        ////getsockopt
        static INT  iSelect            (INT nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, timeval *tvTimeout);
        static INT  iGetLastError      ();

    protected:
        BOOL        _m_bRes;
        SOCKET      _m_puiSocket;
        SHORT       _m_siFamily;
        tString     _m_sIp;
        USHORT      _m_usPort;

    private:
};
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxSocket


//http://www.yolinux.com/TUTORIALS/Sockets.html

/*

tString sStr = xT("Some string!!!");
::send(0, reinterpret_cast<char const*>(sStr.data()), sStr.size() * sizeof(tString::value_type), 0);

sizeof(tString::value_type)

*/
/*
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
*/
