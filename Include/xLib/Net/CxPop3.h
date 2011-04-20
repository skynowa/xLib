/****************************************************************************
* Class name:  CxPop3
* Description: POP3
* File name:   CxPop3.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     13.04.2009 16:44:49
*
*****************************************************************************/


#ifndef xLib_Net_CxPop3H 
#define xLib_Net_CxPop3H 
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocketInit.h> 
#include <xLib/Net/CxTcpClientSocket.h> 
#include <xLib/Net/CxDnsClient.h> 
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxMimeMessage.h> 
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxTraceLog.h>
//---------------------------------------------------------------------------
class CxPop3 : public CxNonCopyable { 
    public: 
                          CxPop3              (); 
                         ~CxPop3              (); 

        BOOL              bCreate             (const tString &csUser, const tString &csPass, const tString &csServer, USHORT usPort); 
        BOOL              bConnect            (); 
         BOOL              bLogin              (); 
         
        BOOL              bStat               (ULONG &ulSum, ULONG &ulSize); 
        BOOL              bList               (std::vector<ULONG> &veculList);    
        BOOL              bListAt             (ULONG &ulIndex); 
        BOOL              bNoop               ();
        BOOL              bRset               ();
        BOOL              bTop                (INT iNum, INT iLines, tString &sBuff); 
        
        BOOL      /*RETR*/bRetrive            (INT iNum, const tString &csRawMimeMessage); 
        BOOL      /*RETR*/bRetriveRaw         (INT iNum, const tString &csDirPath, const tString &csFileName);  
        BOOL      /*RETR*/bRetriveRawAndBackup(INT iNum, const tString &csDirPath, const tString &csBackupDirPath, const tString &csFileName);  
        BOOL      /*TOP*/ bRetrieveHeader     (INT iNum, CxMimeHeader &mhMimeHeader); 
        
        BOOL              bDelete             (INT iNum); 
        BOOL              bDisconnect         (); 
        
    private:
        BOOL              _m_bRes;
        tString           _m_sRes;
        /////CxSocketInit      _m_siInit;
        CxTcpClientSocket _m_scktSocket; 
        CxConsoleLog      _m_clLog;
        tString              _m_sUser; 
        tString           _m_sPass; 
        tString           _m_sServer; 
        USHORT            _m_usPort; 
        BOOL              _m_bConnected;

        BOOL              _bCommand           (const tString &csCmd, const tString &csReplyDelimiter, tString *psReply);   
        BOOL              _bIsError           (const tString &csText);   
        ULONG             _ulMailsSum         (const tString &csServerAnswer); 
        ULONG             _ulMailsSize        (const tString &csServerAnswer); 
}; 
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxPop3H 

/*
RFC 1225

USER <SP> name <CRLF>
PASS <SP> secret <CRLF>
STAT <CRLF>
LIST <SP> [msg] <CRLF>
LIST <CRLF>
RETR <SP> msg <CRLF>
DELE <SP> msg <CRLF>
NOOP <CRLF>
LAST <CRLF>
RSET <CRLF>
QUIT <CRLF>
*/
