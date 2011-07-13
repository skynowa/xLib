#if defined(xOS_WIN)
#include "stdafx.h"
#include ".\pop3session.h"
#include <windows.h>

#pragma warning (disable:4786)
#include <list>
#include <string>
#include <iostream>

using namespace std ;

bool CPop3Session::LockMailDrop(void)
{
    printf("Locking maildrop\n");

    WIN32_FIND_DATA FileData;
    HANDLE hSearch;
    //DWORD dwAttrs;
    //char szNewPath[MAX_PATH];

    BOOL bFinished = FALSE;

    m_dwTotalMailSize=0;
    m_nTotalMailCount=0;

    char szSearchPath[MAX_PATH];

    sprintf(szSearchPath, "%s\\%s\\%s",m_szUserHome,USER_MAIL_DIRECTORY_NAME,MSG_SEARCH_WILDCARD);

    printf("Search Path: %s", szSearchPath);
    hSearch = FindFirstFile(szSearchPath, &FileData);

    if (hSearch == INVALID_HANDLE_VALUE)
    {
        printf("No mail message files found.\n");
        return true;
    }

    CPop3Message *pHead=NULL, *pNewMsg=NULL;

    while (true)
    {
        DWORD dwSize=FileData.nFileSizeLow;

        m_nTotalMailCount++;
        m_dwTotalMailSize+=FileData.nFileSizeLow /*+(FileData.nFileSizeHigh * (MAXDWORD+1))*/;
        char msgPath[300];

        sprintf(msgPath,"%s\\%s\\%s",m_szUserHome,USER_MAIL_DIRECTORY_NAME,FileData.cFileName);

        pNewMsg=new CPop3Message(dwSize,POP3_MSG_STATUS_NEW,msgPath);

        pNewMsg->m_pNextMessage=pHead;
        pHead=pNewMsg;

        //printf("Message %d: %s\n",m_nTotalMailCount, FileData.cFileName);
        if (!FindNextFile(hSearch, &FileData))
            break;
    }

    FindClose(hSearch);
    printf("TotalMailCount %d TotalMailSize %d\n", m_nTotalMailCount, m_dwTotalMailSize);

    if(m_nTotalMailCount)
    {
        m_pPop3MessageList=new CPop3Message[m_nTotalMailCount];
        if(!m_pPop3MessageList) return false;

        for(int i=0; i < m_nTotalMailCount; i++)
        {
            pNewMsg=pHead;
            m_pPop3MessageList[i].SetParams(pNewMsg->GetSize(), pNewMsg->GetStatus(), pNewMsg->GetPath());
            pHead=pHead->m_pNextMessage;
        }

        printf("Total %d messages of %ld octates found\n",m_nTotalMailCount, m_dwTotalMailSize);

        for(int i=0; i < m_nTotalMailCount; i++)
        {
            printf("Message %d: %ld %s\n",i+1,m_pPop3MessageList[i].GetSize(), m_pPop3MessageList[i].GetPath());
        }

    }

    return true;
}
#elif defined(xOS_LINUX)

#endif
