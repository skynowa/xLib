#pragma once

#include <Winsock2.h>

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

class CPop3Message
{
	char m_szMessagePath[MAX_PATH];
	int m_nStatus;
	DWORD m_dwSize;
public:
	CPop3Message *m_pNextMessage;

	CPop3Message(int nStatus=POP3_MSG_STATUS_UNDEFINED,DWORD nSize=0, char *szMessagepath="")
	{
		m_nStatus=nStatus;
		m_dwSize=nSize;
		strcpy(m_szMessagePath,szMessagepath);
		m_pNextMessage=NULL;
	}

	void SetParams(int nStatus=POP3_MSG_STATUS_UNDEFINED,DWORD nSize=0, char *szMessagepath="")
	{
		m_nStatus=nStatus;
		m_dwSize=nSize;
		strcpy(m_szMessagePath,szMessagepath);
	}

	void SetParams(CPop3Message *pMsg)
	{
		m_nStatus=pMsg->GetStatus();
		m_dwSize=pMsg->GetSize();
		strcpy(m_szMessagePath,pMsg->GetPath());
	}

	void Delete(){m_nStatus|=POP3_MSG_STATUS_DELETED;}

	void Reset(){m_nStatus&= ~POP3_MSG_STATUS_DELETED;}
	DWORD GetSize(){return m_dwSize;}
	int GetStatus(){return m_nStatus;}
	char *GetPath(){return m_szMessagePath;}

};
class CPop3Session
{
	CPop3Message *m_pPop3MessageHead, *m_pPop3MessageList;

	unsigned int m_nState;
	unsigned int m_nLastMsg;
	char m_szUserHome[MAX_PATH];
	char m_szUserName[MAX_PATH];
	char m_szPassword[MAX_PATH];
	int m_nTotalMailCount, m_dwTotalMailSize;
public:
	SOCKET m_socConnection;

	CPop3Session(SOCKET client_soc);
	virtual ~CPop3Session(void);

	int ProcessCMD(char *buf, int len);
	int SendResponse(int nResponseType, char *msg="");
	int SendResponse(char *buf);

protected:
	int ProcessUSER(char* buf, int len);
	int ProcessPASS(char* buf, int len);
	int ProcessQUIT(char* buf, int len);
	int ProcessRETR(char* buf, int len);
	int ProcessDELE(char* buf, int len);
	int ProcessNOOP(char* buf, int len);
	int ProcessLAST(char* buf, int len);
	int ProcessRSET(char* buf, int len);
	int ProcessSTAT(char* buf, int len);
	int ProcessLIST(char* buf, int len);

	bool Login(char* szName, char* szPassword);

public:
	bool LockMailDrop(void);
	void UpdateMails(void);
	bool SetHomePath(char *szUserName);
	int SendMessageFile(char* szFilePath);
	int ProcessRPOP(char* buf, int len);
	int ProcessTOP(char* buf, int len);
};
