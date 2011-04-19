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
class CxSocket : public CxNonCopyable {
    public:
        /****************************************************************************
        *   constants
        *
        *****************************************************************************/

        //address family
        enum EAddressFamily {
        #if defined(xOS_WIN)
            afUnspecified = AF_UNSPEC,          //The address family is unspecified.
            afInet        = AF_INET,            //The Internet Protocol version 4 (IPv4) address family
            afIpx         = AF_IPX,             //The IPX/SPX address family
            afAppletalk   = AF_APPLETALK,       //The AppleTalk address family
            afNetbios     = AF_NETBIOS,         //The NetBIOS address family
            afInet6       = AF_INET6,           //The Internet Protocol version 6 (IPv6) address family
            afIrdA        = AF_IRDA,            //The Infrared Data Association (IrDA) address family
            ////TODO: G++ afBluetooth   = AF_BTH              //The Bluetooth address family
        #elif defined(xOS_LINUX)
            afUnix        = AF_UNIX,            //Local communication
            afLocal       = AF_LOCAL,           //Local communication
            afInet        = AF_INET,            //IPv4 Internet protocols
            afInet6       = AF_INET6,           //IPv6 Internet protocols
            afIpx         = AF_IPX,             //IPX - Novell protocols
            afNetlink     = AF_NETLINK,         //Kernel user interface device
            afX25         = AF_X25,             //ITU-T X.25 / ISO-8208 protocol
            afAX25        = AF_AX25,            //Amateur radio AX.25 protocol
            afAtmpvc      = AF_ATMPVC,          //Access to raw ATM PVCs
            afAppletalk   = AF_APPLETALK,       //Appletalk
            afPacket      = AF_PACKET           //Low level packet interface
        #endif
        };

        //type
        enum EType {
            tpStream      = SOCK_STREAM,        //A socket type that provides sequenced, reliable, two-way, connection-based byte streams with an OOB data transmission mechanism
            tpDgram       = SOCK_DGRAM,         //A socket type that supports datagrams, which are connectionless, unreliable buffers of a fixed (typically small) maximum length
            tpRaw         = SOCK_RAW,           //A socket type that provides a raw socket that allows an application to manipulate the next upper-layer protocol header
            tpRdm         = SOCK_RDM,           //A socket type that provides a reliable message datagram
            tpSeqPacket   = SOCK_SEQPACKET      //A socket type that provides a pseudo-stream packet based on datagrams
        };

        //protocol
        enum EProtocol {
        #if defined(xOS_WIN)
            ptIp          = IPPROTO_IP,         //dummy for IP
            ptIcmp        = IPPROTO_ICMP,       //The Internet Control Message Protocol (ICMP)
            ptIgmp        = IPPROTO_IGMP,       //The Internet Group Management Protocol (IGMP)
            //ptRfcomm      = BTHPROTO_RFCOMM,    //The Bluetooth Radio Frequency Communications (Bluetooth RFCOMM) protocol
            ptTcp         = IPPROTO_TCP,        //The Transmission Control Protocol (TCP)
            ptUdp         = IPPROTO_UDP,        //The User Datagram Protocol (UDP)
            ptIcmpv6      = IPPROTO_ICMPV6,     //The Internet Control Message Protocol Version 6 (ICMPv6)
            //ptRm          = IPPROTO_RM          //The PGM protocol for reliable multicast
        #elif defined(xOS_LINUX)
            ptIp          = IPPROTO_IP,         //Dummy protocol for TCP
            ptHopopts     = IPPROTO_HOPOPTS,    //IPv6 Hop-by-Hop options
            ptIcmp        = IPPROTO_ICMP,       //Internet Control Message Protocol
            ptIgmp        = IPPROTO_IGMP,       //Internet Group Management Protocol
            ptIpip        = IPPROTO_IPIP,       //IPIP tunnels (older KA9Q tunnels use 94)
            ptTcp         = IPPROTO_TCP,        //Transmission Control Protocol
            ptEgp         = IPPROTO_EGP,        //Exterior Gateway Protocol
            ptPup         = IPPROTO_PUP,        //PUP protocol
            ptUdp         = IPPROTO_UDP,        //User Datagram Protocol
            ptIdp         = IPPROTO_IDP,        //XNS IDP protocol
            ptTp          = IPPROTO_TP,         //SO Transport Protocol Class 4
            ptDccp        = IPPROTO_DCCP,       //Datagram Congestion Control Protocol
            ptIpv6        = IPPROTO_IPV6,       //IPv6 header
            ptRouting     = IPPROTO_ROUTING,    //IPv6 routing header
            ptFragment    = IPPROTO_FRAGMENT,   //IPv6 fragmentation header
            ptRsvp        = IPPROTO_RSVP,       //Reservation Protocol
            ptGre         = IPPROTO_GRE,        //General Routing Encapsulation
            ptEsp         = IPPROTO_ESP,        //encapsulating security payload
            ptAH          = IPPROTO_AH,         //authentication header
            ptICmpv6      = IPPROTO_ICMPV6,     //ICMPv6
            ptNone        = IPPROTO_NONE,       //IPv6 no next header
            ptDstopts     = IPPROTO_DSTOPTS,    //IPv6 destination options
            ptMtp         = IPPROTO_MTP,        //Multicast Transport Protocol
            ptEncap       = IPPROTO_ENCAP,      //Encapsulation Header
            ptPim         = IPPROTO_PIM,        //Protocol Independent Multicast
            ptComp        = IPPROTO_COMP,       //Compression Header Protocol
            ptSctp        = IPPROTO_SCTP,       //Stream Control Transmission Protocol
            ptUdplite     = IPPROTO_UDPLITE,    //UDP-Lite protocol
            ptRaw         = IPPROTO_RAW,        //Raw IP packets
            ptMax         = IPPROTO_MAX
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

        INT         iSend              (LPCTSTR pcszBuff, INT iBuffSize, INT iFlags);    //<<
        BOOL        bSendAll           (const tString &csBuff, INT iFlags);             //<<

        INT         iRecv              (LPTSTR  pszBuff,  INT iBuffSize, INT iFlags);        //<<
        tString     sRecvAll           (INT iFlags);                                    //<<
        tString     sRecvAll           (INT iFlags, const tString &csDelimiter);    //<<

        INT         iSendBytes         (LPSTR pszBuff, INT iMessageLength);                //<<
        INT         iReceiveBytes      (LPSTR pszBuff, INT iStillToReceive);            //<<


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

        ////static INT  _ms_iRes;

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

tString sStr = _T("Some string!!!");
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
