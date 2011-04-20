/****************************************************************************
* Class name:  CxMimeMessage
* Description: почтовое сообщение (RFC 822)
* File name:   CxMimeMessage.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.07.2009 19:09:16
*
*****************************************************************************/


#include <xLib/Net/CxMimeMessage.h>
//---------------------------------------------------------------------------
CxMimeMessage::CxMimeMessage() {
    //code
}
//---------------------------------------------------------------------------
CxMimeMessage::~CxMimeMessage() {
    //code
}
//---------------------------------------------------------------------------
/*static*/BOOL CxMimeMessage::bParse(const tString &csRawMessage, CxMimeHeader &Header, CxMimeBody &Body) {
    BOOL bRes = FALSE;
    
    //m_Header;
    //m_Body;
    
    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/BOOL    bLoadFromRawFile(const tString &csFilePath) {
    BOOL bRes = FALSE;

    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/BOOL bSaveToRawFile  (const tString &csFilePath) {
    BOOL bRes = FALSE;

    return FALSE;
}
//---------------------------------------------------------------------------