#if defined(xOS_WIN)
// KLPop3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include ".\pop3session.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

char g_szDomain[100];
char g_szDirectoryPath[300];
char g_szDomainPath[400];

DWORD WINAPI ConnectionThread(void *param)
{
    int len;
    char buf[2050];
    CPop3Session *pSession=(CPop3Session *)param;

    pSession->SendResponse(POP3_WELCOME_RESPONSE);

    //while(!ReceiveLine(pSession->m_socConnection,buf,sizeof(buf)))
    while(len=recv(pSession->m_socConnection,buf,sizeof(buf),0))
    {
        if(-1==pSession->ProcessCMD(buf,len))
        {
            printf("Connection thread closing...\n");
            return 0;
        }
        //buf[len]=0;printf("%s",buf);
    }
    return -1;
}

void AcceptConnections(SOCKET server_soc)
{
    CPop3Session *pSession;
    SOCKET soc_client;

    printf("POP3 Server is ready and listening to TCP port %d ...\n",POP3_PORT);
    printf("--------------------------------------------------------------\n\n\n");

    while(true)
    {
        sockaddr nm;
        int len=sizeof(sockaddr);

        printf("\nWaiting for incoming connection...\n");

        if(INVALID_SOCKET==(soc_client=accept(server_soc,&nm,&len)))
        {
            printf("Error: Invalid Soceket returned by accept(): %d\n",WSAGetLastError());
        }
        else
        {
            printf("Accepted new connection. Now creating session thread...\n");
        }

        pSession=new CPop3Session(soc_client);

        DWORD dwThreadId, dwThrdParam = 1;
        HANDLE hThread;

        hThread = CreateThread(
            NULL,                        // default security attributes
            0,                           // use default stack size
            ConnectionThread,                  // thread function
            (void *)pSession,                // argument to thread function
            0,                           // use default creation flags
            &dwThreadId);                // returns the thread identifier

        // Check the return value for success.

        if(hThread == NULL)
        {
            printf( "CreateThread failed." );
        }
    }
}
void Greetings()
{

    printf("Welcome to %s %s \r\n",APP_TITLE, APP_VERSION);
    printf("Developed by Maruf Maniruzzaman (kuasha@acm.org)\n");
    printf("Home page: http://www.kuashaonline.com.com/%s\n",APP_TITLE);
    printf("This is an implementation of RFC 1225\n\n");

}

BOOL Init(char *lpDomain)
{
    if(strlen(lpDomain)<1)
    {
        strcpy(g_szDomain,"kuashaonline.com");
    }
    else
    {
        strcpy(g_szDomain,lpDomain);
    }

    printf("Registering domain: %s\n", g_szDomain);

    char direct[300], f[300];

    GetFullPathName("./",255,(LPTSTR)direct,(LPTSTR *)f);

    strcpy(g_szDirectoryPath, direct);

    printf("Active directory path %s\n",g_szDirectoryPath);

    if(!PathFileExists(g_szDirectoryPath))
    {
        printf("Active directory path not found\n");
        return FALSE;
    }

    sprintf(g_szDomainPath,"%s%s",g_szDirectoryPath,g_szDomain);

    if(!PathFileExists(g_szDomainPath))
    {

        printf("Domain not found on Active Directory:\nThere should be a directory->\n%s\\\nCreate it and try again.\n", g_szDomainPath);
        return FALSE;
    }

    printf("Domain path %s\n",g_szDomainPath);

    return TRUE;
}
int _tmain(int argc, _TCHAR* argv[])
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    char *lpDomain="";

    wVersionRequested = MAKEWORD( 2, 2 );

    Greetings();

    if(argc>1)
    {

        lpDomain=argv[1];
    }

    if(!Init(lpDomain)) return -1;

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
    soc_addr.sin_port=htons(POP3_PORT);
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

    AcceptConnections(soc);

    printf("You should not see this message.\nIt is an abnormal condition.\nTerminating...");
    return 0;
}
#elif defined(xOS_LINUX)

#endif
