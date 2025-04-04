/**
 * \file  ISocket.h
 * \brief blocking socket
 *
 * \code
 * +-----------------------------------------------------+ +----------------------------------------------------+
 * | TCP Server               | TCP Client               | | UDP Server               | UDP Client              |
 * |--------------------------|--------------------------| |--------------------------|-------------------------|
 * | // Initialize Winsock    | // Initialize Winsock    | | // Initialize Winsock    | // Initialize Winsock   |
 * | WSAStartup()             | WSAStartup()             | | WSAStartup()             | WSAStartup()            |
 * |                          |                          | |                          |                         |
 * | // Create a socket       | // Create a socket       | |                          |                         |
 * | socket()                 | socket()                 | |                          |                         |
 * |                          |                          | |                          |                         |
 * | // Bind the socket       |                          | | // Bind the socket       |                         |
 * | bind()                   |                          | | bind()                   |                         |
 * |                          |                          | |                          |                         |
 * | // Listen on the socket  |                          | |                          |                         |
 * | listen()                 |                          | |                          |                         |
 * |                          |                          | |                          |                         |
 * | // Accept a connection   | // Connect to the server | |                          |                         |
 * | accept()                 | connect()                | |                          |                         |
 * |                          |                          | |                          |                         |
 * | // Receive and send data | // Send and receive data | | // Receive data          | // Send  data           |
 * | send() / recv()          | send() / recv()          | | recvfrom()               | sendto()                |
 * |                          |                          | |                          |                         |
 * | // Disconnect            | // Disconnect            | |                          |                         |
 * | shutdown()               | shutdown()               | |                          |                         |
 * |                          |                          | |                          |                         |
 * | // Close socket          | // Close socket          | | // Close socket          | // Close socket         |
 * | close()                  | close()                  | | close()                  | close()                 |
 * |                          |                          | |                          |                         |
 * | // Deinitialize Winsock  | // Deinitialize Winsock  | | // Deinitialize Winsock  | // Deinitialize Winsock |
 * | WSACleanup()             | WSACleanup()             | | WSACleanup()             | WSACleanup()            |
 * +-----------------------------------------------------+ +----------------------------------------------------+
 * \endcode
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::net
{

class ISocket
	/// socket
{
public:
	enum class AddressFamily
		/// address family
	{
	#if   xENV_WIN
		afUnspecified = AF_UNSPEC,
		afInet        = AF_INET,
		afIpx         = AF_IPX,
		afAppletalk   = AF_APPLETALK,
		afNetbios     = AF_NETBIOS,
		afInet6       = AF_INET6,
		afIrdA        = AF_IRDA
		#if !xCOMPILER_MINGW
			,
			afBluetooth   = AF_BTH
		#endif
	#elif xENV_UNIX
		#if   xENV_LINUX
			afUnix        = AF_UNIX,
			afLocal       = AF_LOCAL,
			afInet        = AF_INET,
			afInet6       = AF_INET6,
			afIpx         = AF_IPX,
			/// afNetlink     = AF_NETLINK, /// TODO: not in Apple
			afX25         = AF_X25,
			afAX25        = AF_AX25,
			afAtmpvc      = AF_ATMPVC,
			afAppletalk   = AF_APPLETALK,
			afPacket      = AF_PACKET
		#elif xENV_BSD
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
		#elif xENV_APPLE
			afUnix        = AF_UNIX,
			afLocal       = AF_LOCAL,
			afInet        = AF_INET,
			afInet6       = AF_INET6,
			afIpx         = AF_IPX,
			afAppletalk   = AF_APPLETALK

			// TODO: [skynowa] ISocket - add AP-*
		#endif
	#endif
	};
	xUSING_CONST(AddressFamily);

	enum class Type
	   /// type
	{
		tpStream      = SOCK_STREAM,
		tpDgram       = SOCK_DGRAM,
		tpRaw         = SOCK_RAW,
		tpRdm         = SOCK_RDM,
		tpSeqPacket   = SOCK_SEQPACKET
	};
	xUSING_CONST(Type);

	enum class Protocol
		/// protocol
	{
	#if xENV_WIN
		ptIp          = IPPROTO_IP,
		ptIcmp        = IPPROTO_ICMP,
		ptIgmp        = IPPROTO_IGMP,
		//// ptRfcomm      = BTHPROTO_RFCOMM,
		ptTcp         = IPPROTO_TCP,
		ptUdp         = IPPROTO_UDP,
		ptIcmpv6      = IPPROTO_ICMPV6,
		//// ptRm          = IPPROTO_RM
	#elif xENV_UNIX
		#if   xENV_LINUX
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
			//// ptTp          = IPPROTO_TP,
			//// ptDccp        = IPPROTO_DCCP,
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
			//// ptMtp         = IPPROTO_MTP,
			//// ptEncap       = IPPROTO_ENCAP,
			ptPim         = IPPROTO_PIM,
			ptComp        = IPPROTO_COMP,
			ptSctp        = IPPROTO_SCTP,
			//// ptUdplite     = IPPROTO_UDPLITE,
			ptRaw         = IPPROTO_RAW,
			ptMax         = IPPROTO_MAX
		#elif xENV_BSD
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
			//// ptTp          = IPPROTO_TP,
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
			//// ptMtp         = IPPROTO_MTP,
			//// ptEncap       = IPPROTO_ENCAP,
			ptPim         = IPPROTO_PIM,
			ptRaw         = IPPROTO_RAW,
			ptMax         = IPPROTO_MAX
		#elif xENV_APPLE
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
			//// ptTp          = IPPROTO_TP,
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
			//// ptMtp         = IPPROTO_MTP,
			//// ptEncap       = IPPROTO_ENCAP,
			ptPim         = IPPROTO_PIM,
			ptSctp        = IPPROTO_SCTP,
			ptRaw         = IPPROTO_RAW,
			ptMax         = IPPROTO_MAX
			// TODO: [skynowa] ISocket - add IPPROTO-*
		#endif
	#endif
	};
	xUSING_CONST(Protocol);

	enum Options
		/// options
	{
		SOCKET_TIMEOUT   = 0,       ///< (1000000 / 10)
		SOCKET_BUFF_SIZE = 32768    ///< 32 KB
	};
	xUSING_CONST(Options);

///\name ctors, dtor
///\{
			 ISocket() = default;
	virtual ~ISocket() = 0;

	xNO_COPY_ASSIGN(ISocket);
///\}

	/*******************************************************************************
	*
	*
	*******************************************************************************/

	void_t         create(cAddressFamily family, cType type, cProtocol protocol);
		///< creates a socket that is bound to a specific transport service provider
	HandleSocket  &handle();
		///< get handle
	bool_t         isReadable() const;
		///< checking for readability
	bool_t         isWritable() const;
		///< checking for writability
	void_t         assign(csocket_t &handle);
		///< assign to another handle
	void_t         close();
		///< close


	/*******************************************************************************
	* I/O
	*
	*******************************************************************************/

	// void_t *, std::tstring_t, std::ustring_t

	std::ssize_t   send(cptr_ctchar_t buff, std::csize_t &buffSize, cint_t &flags);
		///< send data
	void_t         sendAll(std::ctstring_t &buff, cint_t &flags);
		///< send data by blocks

	std::ssize_t   receive(tchar_t *buff,  std::csize_t &buffSize, cint_t &flags);
		///< receive data
	std::tstring_t recvAll(cint_t &flags);
		///< receive data
	std::tstring_t recvAll(cint_t &flags, std::ctstring_t &delimiter);
		///< receive data to delimiter, includes it

	int_t          sendBytes(char *buff, std::ssize_t &messageLength);
		///< send bytes
	int_t          receiveBytes(char *buff, std::ssize_t &stillToReceive);
		///< receive bytes


	/*******************************************************************************
	* Other
	*
	*******************************************************************************/

	void_t         peerName(std::tstring_t *peerAddr, ushort_t *peerPort);
		///< get address of the peer to which a handle is connected
	void_t         socketName(std::tstring_t *socketAddr, ushort_t *socketPort);
		///< get local name for a socket

	/*******************************************************************************
	* static
	*
	*******************************************************************************/

	////getsockopt
	static
	int_t          select(int_t nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
					   timeval *timeout);
		///< determines the status of one or more sockets, waiting if necessary,
		///< to perform synchronous I/O
	static
	int_t          nativeError();
		///< get error status for the last operation that failed

protected:
	HandleSocket   _handle;         ///< socket handle
	sa_family_t    _family {};      ///< family
	std::tstring_t _ip;             ///< IP
	ushort_t       _port {};        ///< port

xPLATFORM_IMPL:
	void_t         _close_impl();
	std::ssize_t   _send_impl(cptr_ctchar_t buff, std::csize_t &buffSize, cint_t &flags);
	std::ssize_t   _receive_impl(cptr_ctchar_t buff, std::csize_t &buffSize, cint_t &flags);
	void_t         _peerName_impl(std::tstring_t *peerAddr, ushort_t *peerPort);
	void_t         _socketName_impl(std::tstring_t *socketAddr, ushort_t *socketPort);

	static
	int_t          _nativeError_impl();
};

} // namespace
//-------------------------------------------------------------------------------------------------

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
	int_t
	ISocket::WaitForData(SOCKET *pSocketForReceiving, SOCKET *pSocketForSending,
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
		TIMEVAL *ptv = nullptr;

		if (_m_timeout) {
			tv.tv_sec =  _m_timeout / 1000;
			tv.tv_usec = _m_timeout * 1000 - tv.tv_sec * 1000000;
			ptv = &tv;
		} else {
			ptv = nullptr; // nullptr for blocking operation (never times out)
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
//-------------------------------------------------------------------------------------------------

