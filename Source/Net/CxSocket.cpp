/****************************************************************************
* Class name:  CxSocket
* Description: socket
* File name:   CxSocket.cpp
* String type: Ansi
* Compilers:   Visual C++ 2008
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     04.04.2009 6:21:18
*
*****************************************************************************/    
    
    
#include <xLib/Net/CxSocket.h> 


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
////--BOOL CxSocket::_ms_iRes = FALSE;
//---------------------------------------------------------------------------  
//DONE: CxSocket (constructor)
CxSocket::CxSocket() :
	_m_bRes     (FALSE),
	_m_puiSocket(etInvalid),
	_m_siFamily (- 1),
	_m_sIp      (),
	_m_usPort   (0)
{   

} 
//---------------------------------------------------------------------------   
//DONE: ~CxSocket (destructor)
CxSocket::~CxSocket() {
	/*DEBUG*/// n/a

    xCHECK_DO(TRUE == bIsValid(), bClose());
}   
//---------------------------------------------------------------------------
//DONE: bAssign (assign to another socket)
BOOL 
CxSocket::bAssign(SOCKET scktSocket) {
    /*DEBUG*/// _m_puiSocket - n/a
    /*DEBUG*/// scktSocket   - n/a

	_m_puiSocket = scktSocket; 

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
* operators
*
*****************************************************************************/

//--------------------------------------------------------------------------- 
//DONE: operator = (operator =)
CxSocket &
CxSocket::operator = (SOCKET puiSocket) {   
    /*DEBUG*/// _m_puiSocket - n/a
    /*DEBUG*/// scktSocket   - n/a

	_m_puiSocket = puiSocket;  

	return *this;   
}   
//--------------------------------------------------------------------------- 
//DONE: operator SOCKET (operator SOCKET)
CxSocket::operator SOCKET () {   
    /*DEBUG*/// _m_puiSocket - n/a
    /*DEBUG*/// scktSocket   - n/a

	return _m_puiSocket;   
} 
//---------------------------------------------------------------------------


/****************************************************************************
* 
*
*****************************************************************************/
  
//--------------------------------------------------------------------------- 
//TODO: bCreate (creates a socket that is bound to a specific transport service provider)
BOOL 
CxSocket::bCreate(EAddressFamily afFamily, EType tpType, EProtocol ptProtocol) {
	/*DEBUG*/xASSERT_RET(etInvalid == _m_puiSocket, FALSE);

	_m_puiSocket = socket(afFamily, tpType, ptProtocol);
	/*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket, FALSE);

	_m_siFamily = afFamily;

	return TRUE;   
}  
//--------------------------------------------------------------------------- 
//DONE: iGetSocket (get socket)
SOCKET 
CxSocket::iGetSocket() const {
	/*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket, etInvalid);

	return _m_puiSocket;  
}
//---------------------------------------------------------------------------
//DONE: bIsValid (checking for validness)
BOOL 
CxSocket::bIsValid() const {
	/*DEBUG*/// n/a

	return static_cast<BOOL>( _m_puiSocket >= 0 );
}
//---------------------------------------------------------------------------
//DONE: bClose (close)
BOOL 
CxSocket::bClose() {		
	/*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket, FALSE);

	INT iRes = etError;

#if defined(xOS_WIN)
	iRes = shutdown(_m_puiSocket, SD_BOTH);
	/*DEBUG*/xASSERT_RET(etError != iRes, FALSE);

	iRes = closesocket(_m_puiSocket);
	/*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#elif defined(xOS_LINUX)
	iRes = close(_m_puiSocket);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#endif

    _m_puiSocket = etInvalid;

    return TRUE;
}  
//---------------------------------------------------------------------------



/****************************************************************************
* I/O
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: iSend (send data)
//TODO: LINUX: ssize_t send(int sockfd, const void *buf, size_t len, int flags);
INT 
CxSocket::iSend(LPCTSTR pcszBuff, INT iBuffSize, INT iFlags) { 
	/*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket,        etError);
	/*DEBUG*/xASSERT_RET(NULL      != pcszBuff,            etError);
	/*DEBUG*//////xASSERT_RET(0         <  ::lstrlen(pcszBuff), etError);

#if defined(xOS_WIN)
	INT     iRes = send(_m_puiSocket, (LPCSTR)pcszBuff, iBuffSize * sizeof(TCHAR), iFlags);
	/*DEBUG*/xASSERT_RET(etError                        != iRes && WSAEWOULDBLOCK != iGetLastError(), etError);
	/*DEBUG*/xASSERT_RET(iBuffSize * (INT)sizeof(TCHAR) >= iRes,                                      etError);
#elif defined(xOS_LINUX)
	ssize_t iRes = send(_m_puiSocket, pcszBuff, iBuffSize, MSG_NOSIGNAL);
    /*DEBUG*/xASSERT_RET(etError                        != iRes, etError);
    /*DEBUG*/xASSERT_RET(iBuffSize * (INT)sizeof(TCHAR) >= iRes, etError);
#endif

	return iRes / sizeof(TCHAR);
}  
//---------------------------------------------------------------------------
//TODO: bSendAll (send data blocks)
BOOL 
CxSocket::bSendAll(const tString &csBuff, INT iFlags) { 
	/*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket,   FALSE);
	/*DEBUG*/xASSERT_RET(false     == csBuff.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(0         <  csBuff.size(),  FALSE);

	//-------------------------------------
	//������ �� ������ ������� � ����� � ������
	INT iCurrPos  = 0;
	INT iLeftSize = csBuff.size() * sizeof(TCHAR);			//TODO: !!!!!!  bSendAll (overflow)

	//if size of data more than size of buffer - sizeof buffer SOCKET_BUFF_SIZE
	INT iBuffOutSize  = 0;
	if (iLeftSize >= SOCKET_BUFF_SIZE) {
		iBuffOutSize = SOCKET_BUFF_SIZE;
	} else {
		iBuffOutSize = iLeftSize;
	}

	for (;;) {		/*uiLeftSize > 0*/
		INT iRes = iSend(&csBuff.at(0) + iCurrPos, iBuffOutSize, iFlags);
		xCHECK_DO(etError == iRes, break);
		xCHECK_DO(0       == iRes, break);

		iCurrPos  += iRes;
		iLeftSize -= iRes;

		xCHECK_DO(iLeftSize < iBuffOutSize, iBuffOutSize = iLeftSize);

		//id data is finished - exit from loop
		if (0 >= iLeftSize) {
			/*DEBUG*/xASSERT_RET((INT)csBuff.size() * (INT)sizeof(TCHAR) == iCurrPos, FALSE);
			break;
		}
	} 

	return TRUE;    
} 
//---------------------------------------------------------------------------  
//TODO: + iRecv (recieve data)
INT 
CxSocket::iRecv(LPTSTR pszBuff, INT iBuffSize, INT iFlags) {  
	/*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket, etError);
	/*DEBUG*/xASSERT_RET(NULL      != pszBuff,      etError);
	/*DEBUG*/xASSERT_RET(0          < iBuffSize,    etError);

	memset(pszBuff, 0, iBuffSize * sizeof(TCHAR));

#if defined(xOS_WIN)
    INT     iRes = recv(_m_puiSocket, (LPSTR)pszBuff, iBuffSize * sizeof(TCHAR), iFlags);
    /*DEBUG*/xASSERT_RET(etError                        != iRes && WSAEWOULDBLOCK != iGetLastError(), etError);
    /*DEBUG*/xASSERT_RET(0                              != iRes,                                      etError);  //gracefully closed
    /*DEBUG*/xASSERT_RET(iBuffSize * (INT)sizeof(TCHAR) >= iRes,                                      etError);
#elif defined(xOS_LINUX)
    ssize_t iRes = recv(_m_puiSocket, (LPSTR)pszBuff, iBuffSize * sizeof(TCHAR), iFlags);
    /*DEBUG*/xASSERT_RET(etError                        != iRes,                                      etError);
    /*DEBUG*/xASSERT_RET(0                              != iRes,                                      etError);  //gracefully closed
    /*DEBUG*/xASSERT_RET(iBuffSize * (INT)sizeof(TCHAR) >= iRes,                                      etError);
#endif

	return iRes / sizeof(TCHAR);
}   
//--------------------------------------------------------------------------- 
//TODO: + sRecvBytes ()
tString 
CxSocket::sRecvAll(INT iFlags) {
	tString      sRes;
	
	const size_t cuiBuffSize             = 1024 * sizeof(TCHAR);
	TCHAR        szBuff[cuiBuffSize + 1] = {0};

	for (;;) {
		INT   iRes  = - 1;
	    ULONG ulArg = (ULONG)FALSE;
		
    #if defined(xOS_WIN)
        iRes = ioctlsocket(_m_puiSocket, FIONREAD, &ulArg);
    #elif defined(xOS_LINUX)
        iRes = ioctl      (_m_puiSocket, FIONREAD, &ulArg);
    #endif

		xCHECK_DO(0 != iRes,           break);
		xCHECK_DO(0 == ulArg,          break);
		xCHECK_DO(cuiBuffSize < ulArg, ulArg = cuiBuffSize);

		iRes = recv(_m_puiSocket, (LPSTR)&szBuff[0], ulArg, 0);
		xCHECK_DO(iRes <= 0, break);

		sRes.append(szBuff, iRes);
	}

	return sRes;
}
//---------------------------------------------------------------------------
//TODO: + sRecvBytes (recive data to delimiter, includs it)
tString 
CxSocket::sRecvAll(INT iFlags, const tString &csDelimiter) {   
	tString      sRes;
	const size_t cuiInSize = SOCKET_BUFF_SIZE * sizeof(TCHAR);
	tString      sIn(cuiInSize, xT('\0'));

	//-------------------------------------
	//read from socket by blocks, write to string
	for (;;) {   
		INT iRes = iRecv(&sIn.at(0), cuiInSize, iFlags);
		xCHECK_DO(etError == iRes, break);
		xCHECK_DO(0       == iRes, break);

		sRes.append(sIn.begin(), sIn.begin() + iRes);
		
		//if delimiter was finded - break
		size_t uiDelimiterPos = sRes.find(csDelimiter);		//TODO: from unicode ???
		xCHECK_DO(tString::npos != uiDelimiterPos, break);
	} 
	
	return sRes;  
} 
//---------------------------------------------------------------------------
//TODO: iSendBytes
INT 
CxSocket::iSendBytes(LPSTR pszBuff, INT iMessageLength) {
	INT     iRC         = 0;
	INT     iSendStatus = 0;
	timeval SendTimeout = {0};

	//sSetting the timeout
	SendTimeout.tv_sec  = 0;
	SendTimeout.tv_usec = SOCKET_TIMEOUT;

	fd_set fds;	FD_ZERO(&fds);
	FD_SET(_m_puiSocket, &fds);

	//..as long as we need to send data...
	while (iMessageLength > 0) {
		iRC = select(0, NULL, &fds, NULL, &SendTimeout);

		//timed out, return error
		xCHECK_RET(!iRC, etError);

		//An error occurred
		xCHECK_RET(iRC < 0, iGetLastError());

		//send a few bytes
		iSendStatus = send(_m_puiSocket, pszBuff, iMessageLength, 0);

		//An error occurred when sending data
		xCHECK_RET(iSendStatus < 0, iGetLastError());

		//update the buffer and the counter
		iMessageLength -= iSendStatus;
		pszBuff        += iSendStatus;
	}

	return 0;
}
//---------------------------------------------------------------------------
//TODO: ReceiveNBytes
INT 
CxSocket::iReceiveBytes(LPSTR pszBuff, INT iStillToReceive) {
	INT     iRC               = 0;
	INT     iReceiveStatus    = 0;
	timeval ReceiveTimeout    = {0};

	//Setting the timeout
	ReceiveTimeout.tv_sec  = 0;
	ReceiveTimeout.tv_usec = SOCKET_TIMEOUT;             //500 ms

	fd_set fds = {{0}};
	FD_ZERO(&fds);
	FD_SET(_m_puiSocket, &fds);

	//.. Until the data is sent ..
	while (iStillToReceive > 0) {
		iRC = select(0, &fds, NULL, NULL, &ReceiveTimeout);

		//return by timeout
		xCHECK_RET(!iRC, etError);

		//An error occurred
		xCHECK_RET(iRC < 0, iGetLastError());

		//recive a few bytes
		iReceiveStatus = recv(_m_puiSocket, pszBuff, iStillToReceive, 0);

		//An error occurred when the function recv ()
		xCHECK_RET(iReceiveStatus < 0, iGetLastError());

		//changed the value of the counter and the buffer
		iStillToReceive -= iReceiveStatus;
		pszBuff         += iReceiveStatus;
	}

	return 0;
}
//---------------------------------------------------------------------------


/****************************************************************************
* ... 
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bGetPeerName (get address of the peer to which a socket is connected)
BOOL 
CxSocket::bGetPeerName(tString *psPeerAddr, USHORT *pusPeerPort) {
	/*DEBUG*///psPeerAddr  - n/a
	/*DEBUG*///pusPeerPort - n/a

#if defined(xOS_WIN)
    SOCKADDR_IN sockAddr     = {0};
    INT         iSockAddrLen = sizeof(sockAddr);

    INT iRes = getpeername(_m_puiSocket, CxMacros::xreinterpret_cast<SOCKADDR *>( &sockAddr ), &iSockAddrLen);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#elif defined(xOS_LINUX)
    sockaddr_in sockAddr      = {0};
    socklen_t   uiSockAddrLen = sizeof(sockAddr);

    INT iRes = getpeername(_m_puiSocket, CxMacros::xreinterpret_cast<sockaddr *>( &sockAddr ), &uiSockAddrLen);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#endif

    if (NULL != psPeerAddr) {
        //convert to UNICODE
        std::string asPeerAddr = ::inet_ntoa(sockAddr.sin_addr);

        (*psPeerAddr).assign(asPeerAddr.begin(), asPeerAddr.end());
    }

    if (NULL != pusPeerPort) {
        *pusPeerPort = ::ntohs(sockAddr.sin_port);
    }

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetSocketName (get local name for a socket)
BOOL 
CxSocket::bGetSocketName(tString *psSocketAddr, USHORT *pusSocketPort) {
	/*DEBUG*///psPeerAddr  - n/a
	/*DEBUG*///pusPeerPort - n/a

#if defined(xOS_WIN)
    SOCKADDR_IN sockAddr     = {0};
    INT         iSockAddrLen = sizeof(sockAddr);

    INT iRes = ::getsockname(_m_puiSocket, CxMacros::xreinterpret_cast<SOCKADDR *>( &sockAddr ), &iSockAddrLen);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#elif defined(xOS_LINUX)
    sockaddr_in sockAddr     = {0};
    socklen_t   iSockAddrLen = sizeof(sockAddr);

    INT iRes = ::getsockname(_m_puiSocket, CxMacros::xreinterpret_cast<sockaddr *>( &sockAddr ), &iSockAddrLen);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);
#endif

    if (NULL != psSocketAddr) {
        //convert to UNICODE
        std::string asSocketAddr = ::inet_ntoa(sockAddr.sin_addr);

        (*psSocketAddr).assign(asSocketAddr.begin(), asSocketAddr.end());
    }

    if (NULL != pusSocketPort) {
        *pusSocketPort = ::ntohs(sockAddr.sin_port);
    }

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
* static 
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: iGetLastError (get error status for the last operation that failed)
/*static*/
INT 
CxSocket::iGetLastError() { 
    /*DEBUG*/// n/a

#if defined(xOS_WIN)
	return ::WSAGetLastError(); 
#elif defined(xOS_LINUX)
	return errno;
#endif     
}   
//---------------------------------------------------------------------------
//TODO: + iSelect (determines the status of one or more sockets, waiting if necessary, to perform synchronous I/O.)
/*static*/
INT 
CxSocket::iSelect(INT nfds, fd_set *pReadfds, fd_set *pWritefds, fd_set *pExceptfds, timeval *tvTimeout) {
    /*DEBUG*/// nfds
    /*DEBUG*/// pReadfds
    /*DEBUG*/// pWritefds
    /*DEBUG*/// pExceptfds
	 
	 INT iRes = select(nfds, pReadfds, pWritefds, pExceptfds, tvTimeout);
	 /*DEBUG*/xASSERT_RET(etError != iRes, etError);
	 /*DEBUG*/xASSERT_RET(0       != iRes, 0);  //zero if the time limit expired

	 return iRes;
}
//---------------------------------------------------------------------------











/*
INT 
CxSocket::WaitForData(SOCKET *pSocketForReceiving, SOCKET *pSocketForSending, SOCKET *pSocketForExceptions) {
	int nSocketsReady = 0;
	
	fd_set FdSetReceive;	FD_ZERO(&FdSetReceive);
	fd_set FdSetSend;   	FD_ZERO(&FdSetSend);
	fd_set FdSetError;  	FD_ZERO(&FdSetError);

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
*/



/*
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
*/


