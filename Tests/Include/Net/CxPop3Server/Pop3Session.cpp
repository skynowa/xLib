#if defined(xOS_WIN)
#include "StdAfx.h"
#include ".\pop3session.h"

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

CPop3Session::CPop3Session(SOCKET client_soc)
{
    m_nState=POP3_STATE_AUTHORIZATION;
    m_socConnection=client_soc;
    m_szUserName[0]=0;
    m_szUserHome[0]=0;
    m_pPop3MessageHead=NULL;
    m_pPop3MessageList=NULL;
    m_nLastMsg=0;
}

CPop3Session::~CPop3Session(void)
{
    if(m_pPop3MessageHead)
    {
//TODO: Delete the entire list;
        //delete(m_pPop3MessageList);
    }
}

int CPop3Session::ProcessCMD(char *buf, int len)
{
    if(_strnicmp(buf,"USER",4)==0)
    {
        return ProcessUSER(buf, len);
    }
    else if(_strnicmp(buf,"PASS",4)==0)
    {
        return ProcessPASS(buf, len);
    }
    else if(_strnicmp(buf,"QUIT",4)==0)
    {
        return ProcessQUIT(buf, len);
    }
    else if(_strnicmp(buf,"STAT",4)==0)
    {
        return ProcessSTAT(buf, len);
    }
    else if(_strnicmp(buf,"LIST",4)==0)
    {
        return ProcessLIST(buf, len);
    }
    else if(_strnicmp(buf,"RETR",4)==0)
    {
        return ProcessRETR(buf, len);
    }
    else if(_strnicmp(buf,"DELE",4)==0)
    {
        return ProcessDELE(buf, len);
    }
    else if(_strnicmp(buf,"NOOP",4)==0)
    {
        return ProcessNOOP(buf, len);
    }
    else if(_strnicmp(buf,"LAST",4)==0)
    {
        return ProcessLAST(buf, len);
    }
    else if(_strnicmp(buf,"RSET",4)==0)
    {
        return ProcessRSET(buf, len);
    }
    else if(_strnicmp(buf,"RPOP",4)==0)
    {
        return ProcessRSET(buf, len);
    }
    else if(_strnicmp(buf,"TOP",4)==0)
    {
        return ProcessRSET(buf, len);
    }



    return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);

    return 0;
}


int CPop3Session::SendResponse(char *buf)
{
    int len=(int)strlen(buf);

    printf("Direct Sending: %s",buf);

    send(m_socConnection,buf,len,0);

    return 0;
}

int CPop3Session::SendResponse(int nResponseType, char *msg)
{
    char buf[100];
    int len;

    if(nResponseType==POP3_DEFAULT_AFFERMATIVE_RESPONSE)
    {
        if(strlen(msg))
            sprintf(buf,"+OK %s\r\n",msg);
        else
            sprintf(buf,"+OK %s\r\n","Action performed");
    }
    else if(nResponseType==POP3_DEFAULT_NEGATIVE_RESPONSE)
        sprintf(buf,"-ERR %s\r\n","An error occured");
    else if(nResponseType==POP3_WELCOME_RESPONSE)
        sprintf(buf,"+OK %s %s POP3 Server ready on %s\r\n",APP_TITLE, APP_VERSION,DOMAIN_NAME);
    else if(nResponseType==POP3_STAT_RESPONSE)
        sprintf(buf,"+OK %d %ld\r\n",m_nTotalMailCount, m_dwTotalMailSize);


    len=(int)strlen(buf);

    printf("Sending: %s",buf);
    send(m_socConnection,buf,len,0);

    return nResponseType;
}

int CPop3Session::ProcessUSER(char* buf, int len)
{
    printf("ProcessUSER\n");
    buf[len-2]=0;	buf+=5;

    //printf("User= [%s]\n",buf);
    strcpy(m_szUserName,buf);
    sprintf(m_szUserHome,"%s\\%s",DOMAIN_ROOT_PATH,buf);

//win32

    if(!PathFileExists(m_szUserHome))
    {
        printf("User %s's Home '%s' not found\n",m_szUserName, m_szUserHome);
        return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
    }

    printf("OK User %s Home %s\n",m_szUserName, m_szUserHome);

    if(m_nState!=POP3_STATE_AUTHORIZATION)
    {
        return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
    }

    return SendResponse(POP3_DEFAULT_AFFERMATIVE_RESPONSE);
}

int CPop3Session::ProcessPASS(char* buf, int len)
{
    printf("ProcessPASS\n");
    buf[len-2]=0;	buf+=5;
    if(buf[len-2]==10) buf[len-2]=0;

    //printf("Password= [%s]\n",buf);

    strcpy(m_szPassword,buf);

    if(m_nState!=POP3_STATE_AUTHORIZATION || strlen(m_szUserName)<1)
    {
        return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
    }

    //TODO: Send message count and size also with +OK
    if(Login(m_szUserName, m_szPassword))
        return SendResponse(POP3_DEFAULT_AFFERMATIVE_RESPONSE);
    else
        return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);

    return 0;
}

int CPop3Session::ProcessQUIT(char* buf, int len)
{
    printf("ProcessQUIT\n");
    if(m_nState==POP3_STATE_TRANSACTION)
        m_nState=POP3_STATE_UPDATE;

    SendResponse(POP3_DEFAULT_AFFERMATIVE_RESPONSE,"Goodbye");

    UpdateMails();

    return -1;

}

bool CPop3Session::Login(char* szName, char* szPassword)
{
    printf("Login: ");
    printf("user= [%s] password = [%s]\n",m_szUserName,m_szPassword);

    char lpPwdFile[300], lpUserHome[300];

    sprintf(lpPwdFile,"%s\\%s\\%s.pwd",g_szDomainPath,szName,szPassword);
    printf("Pwd file: %s\n",lpPwdFile);
    if(PathFileExists(lpPwdFile))
    //if(strlen(szName) && strlen(szPassword))
    {
        printf("Password ok\n");
        m_nState=POP3_STATE_TRANSACTION;

        sprintf(lpUserHome,"%s\\%s",g_szDomainPath,szName);
        SetHomePath(lpUserHome);

        LockMailDrop();
        return true;
    }

    return false;
}

int CPop3Session::ProcessSTAT(char* buf, int len)
{
    printf("ProcessSTAT\n");
    if(m_nState!=POP3_STATE_TRANSACTION)
    {
        return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
    }

    m_nLastMsg=1;

    return SendResponse(POP3_STAT_RESPONSE);
}

int CPop3Session::ProcessLIST(char* buf, int len)
{
    //char tbuf[1025];

    buf+=4; buf[4]='0'; buf[len-2]=0;
    int msg_id=atol(buf);

    printf("ProcessLIST %d\n",msg_id);

    if(m_nState!=POP3_STATE_TRANSACTION)
    {
        return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
    }

    if(msg_id>0)
    {
        char resp[100];
        sprintf(resp, "+OK %d %d\r\n",msg_id, m_pPop3MessageList[msg_id-1].GetSize());
        return SendResponse(resp);
    }
    else
    {
        SendResponse("+OK \r\n");

        for(int i=0; i < m_nTotalMailCount; i++)
        {
            char resp[100];
            sprintf(resp, "%d %d\r\n",i+1, m_pPop3MessageList[i].GetSize());
            SendResponse(resp);
        }

        SendResponse(".\r\n");
    }

    return 0;
}


int CPop3Session::ProcessRETR(char* buf, int len)
{
    buf+=4; buf[4]='0'; buf[len-2]=0;
    int msg_id=atol(buf);

    printf("ProcessRETR %d\n", msg_id);
    if(m_nState!=POP3_STATE_TRANSACTION)
    {
        return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
    }

    if(msg_id>m_nTotalMailCount)
    {
        return SendResponse("-ERR Invalid message number\r\n");
    }

    if(m_nLastMsg<(unsigned int)msg_id) m_nLastMsg=msg_id;

    char resp[25];
    sprintf(resp,"+OK %d octets\r\n",m_pPop3MessageList[msg_id-1].GetSize());
    SendResponse(resp);
    SendMessageFile(m_pPop3MessageList[msg_id-1].GetPath());
    SendResponse("\r\n.\r\n");

    return 0;
    //return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
}

int CPop3Session::ProcessDELE(char* buf, int len)
{
    buf+=4; buf[4]='0'; buf[len-2]=0;
    int msg_id=atol(buf);

    printf("ProcessDELE %d\n",msg_id);

    if(m_nState!=POP3_STATE_TRANSACTION || msg_id>m_nTotalMailCount)
    {
        return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
    }

    m_pPop3MessageList[msg_id-1].Delete();
    return SendResponse(POP3_DEFAULT_AFFERMATIVE_RESPONSE);
}

int CPop3Session::ProcessNOOP(char* buf, int len)
{
    printf("ProcessNOOP\n");
    return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
}

int CPop3Session::ProcessLAST(char* buf, int len)
{
    if(m_nState!=POP3_STATE_TRANSACTION)
    {
        return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
    }

    printf("ProcessLAST\n");
    char resp[25];

    sprintf(resp, "+OK %d\r\n",m_nLastMsg);
    return SendResponse(resp);
}

int CPop3Session::ProcessRSET(char* buf, int len)
{
    printf("ProcessRSET\n");

    if(m_nState!=POP3_STATE_TRANSACTION)
    {
        return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
    }

    for(int i=0; i < m_nTotalMailCount; i++)
    {
        m_pPop3MessageList[i].Reset();
        //printf("Message %d: %ld %s\n",i+1,m_pPop3MessageList[i].GetSize(), m_pPop3MessageList[i].GetPath());
    }
    return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
}

void CPop3Session::UpdateMails(void)
{
    printf("Updating mails\n");

    if(m_nState!=POP3_STATE_UPDATE)
    {
        printf("Called update but state is not POP3_STATE_UPDATE (%d)\n",POP3_STATE_UPDATE);
        return;
    }

    for(int i=0; i < m_nTotalMailCount; i++)
    {
        if(m_pPop3MessageList[i].GetStatus()& POP3_MSG_STATUS_DELETED)
        {
            printf("Delete file %s\n",m_pPop3MessageList[i].GetPath());
            DeleteFile(m_pPop3MessageList[i].GetPath());
        }
        //printf("Message %d: %ld %s\n",i+1,m_pPop3MessageList[i].GetSize(), m_pPop3MessageList[i].GetPath());
    }

}

bool CPop3Session::SetHomePath(char *lpPath)
{
    strcpy(m_szUserHome,lpPath);

    return true;
}

int CPop3Session::SendMessageFile(char* szFilePath)
{
    HANDLE findH, fileH;
    WIN32_FIND_DATA findData;
    DWORD lenRead, len;
    char *buf;

    fileH = CreateFile(szFilePath, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileH == INVALID_HANDLE_VALUE)
        return NULL;
    findH = FindFirstFile(szFilePath, &findData);
    if (findH == INVALID_HANDLE_VALUE)
    {
        CloseHandle(fileH);
        return NULL;
    }
    len = findData.nFileSizeLow;
    buf = (char *)malloc(len+5);
    if (buf != NULL)
    {
        ReadFile(fileH, buf, len, &lenRead, NULL);
        if (len != lenRead)
        {
            free(buf);
            buf = NULL;
            printf("Read error (len!=readlen) file %s\n",szFilePath);
            return 0;
        }
    }
    else
    {
        printf("Can not open file %s\n",szFilePath);
        return 0;
    }

    FindClose(findH);
    CloseHandle(fileH);

    printf("Sending: %s\n",szFilePath);
    send(m_socConnection,buf,len,0);

    return len;
}

int CPop3Session::ProcessRPOP(char* buf, int len)
{
    printf("ProcessRPOP\n");
    return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
}

int CPop3Session::ProcessTOP(char* buf, int len)
{
    printf("ProcessTOP\n");
    return SendResponse(POP3_DEFAULT_NEGATIVE_RESPONSE);
}
#elif defined(xOS_LINUX)

#endif
