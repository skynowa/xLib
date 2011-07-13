// MailSocket.cpp : Defines the entry point for the console application.
// Date: [1/30/2005]
//---------------------------------------------------------------------------
#include "stdafx.h"
#include <Winsock2.h>
#include "MailSession.h"
#include "../MailAddress.h"
//---------------------------------------------------------------------------
char g_szDomain[300]="KuashaLabs.com";

char g_szDirectoryPath[300];

extern CMailAddress m_FromAddress, m_ToAddress[MAX_RCPT_ALLOWED+1];
//---------------------------------------------------------------------------
DWORD WINAPI ConnectionThread(void *param) {
	int len;
	char buf[2050];
	CMailSession *pSession=(CMailSession *)param;
	
	pSession->SendResponse(220);	

	int i = 0;
	//while(!ReceiveLine(pSession->m_socConnection,buf,sizeof(buf)))
	while (len = recv(pSession->m_socConnection,buf,sizeof(buf),0)) {
		if (221 == pSession->ProcessCMD(buf, len)) {
			printf("Connection thread closing...\n");
			return 0;
		}
		/*LOG*/buf[len]=0;   printf("%s",buf);

		if (i == 1) {


			MessageBox(0, std::string(buf, len).c_str(), "", MB_OK);
		}

		std::string sCmd = std::string(buf, len);
		if (std::string::npos != sCmd.find("DATA")) {
			i = 1;
			////MessageBox(0, "DATA", "", MB_OK);
		}

	}


	return -1;
}
//---------------------------------------------------------------------------

void AcceptConnections(SOCKET server_soc) {
CMailSession *pSession;

	SOCKET        soc_client;

	printf("SMTP Server is ready and listening to TCP port %d ...\n",SMTP_PORT);
	printf("--------------------------------------------------------------\n\n\n");

	while (true)	{
		sockaddr nm;
		int len = sizeof(sockaddr);

		printf("\nWaiting for incoming connection...\n");

		if (INVALID_SOCKET==(soc_client=accept(server_soc,&nm,&len))) {
			printf("Error: Invalid Soceket returned by accept(): %d\n",WSAGetLastError());
		} else {
			printf("Accepted new connection. Now creating session thread...\n");
		}	

		pSession = new CMailSession(soc_client);

		DWORD dwThreadId, dwThrdParam = 1; 
		HANDLE hThread; 

		hThread = ::CreateThread( 
			NULL,                        // default security attributes 
			0,                           // use default stack size  
			ConnectionThread,                  // thread function 
			(void *)pSession,                // argument to thread function 
			0,                           // use default creation flags 
			&dwThreadId);                // returns the thread identifier 

		// Check the return value for success. 
		if (hThread == NULL) {
			printf( "CreateThread failed." ); 
		}
	}
}
//---------------------------------------------------------------------------
void Greetings()
{
	printf("Welcome to %s %s \r\n",APP_TITLE, APP_VERSION);
	printf("Developed by Maruf Maniruzzaman (kuasha@acm.org)\n");
	printf("This is minimal implementation of RFC 821\n\n");
}
//---------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 2, 2 );

	Greetings();

	err = WSAStartup( wVersionRequested, &wsaData );

	if ( err != 0 ) {
		printf("Error in  initializing.\nQuiting with error code: %d\n",WSAGetLastError());
		Sleep(5000);
		exit(WSAGetLastError());
	}

	SOCKET soc=socket(PF_INET, SOCK_STREAM, 0) ;

	if(soc==INVALID_SOCKET)
	{
		printf("Error: Invalid socket\nQuiting with error code: %d\n",WSAGetLastError());
		Sleep(5000);
		exit(WSAGetLastError());
	}

	SOCKADDR_IN soc_addr;

	LPHOSTENT lpHost=gethostbyname("localhost");

	soc_addr.sin_family=AF_INET;
	soc_addr.sin_port=htons(SMTP_PORT);
	soc_addr.sin_addr=*(LPIN_ADDR)(lpHost->h_addr_list[0]);

	if(bind(soc,(const struct sockaddr*)&soc_addr,sizeof(soc_addr)))
	{
		printf("Error: Can not bind socket. Another server running?\nQuiting with error code: %d\n",WSAGetLastError());
		Sleep(5000);
		exit(WSAGetLastError());
	}

	if(SOCKET_ERROR==listen(soc,SOMAXCONN))
	{
		printf("Error: Can not listen to socket\nQuiting with error code: %d\n",WSAGetLastError());
		Sleep(5000);
		exit(WSAGetLastError());
	}

	char direct[300], f[300];
	
	GetFullPathName("./",255,(LPTSTR)direct,(LPTSTR *)f);

	strcpy(g_szDirectoryPath, direct);

	printf("Active directory path %s\n",g_szDirectoryPath);

	AcceptConnections(soc);
	printf("You should not see this message.\nIt is an abnormal condition.\nTerminating...");
	
	return 0;
}
//---------------------------------------------------------------------------
