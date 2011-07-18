/****************************************************************************
* Class name:  CxMimeMessage
* Description: �������� ��������� (RFC 822)
* File name:   CxMimeMessage.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.07.2009 19:09:16
*
*****************************************************************************/


#include <xLib/Net/CxMimeMessage.h>


#if defined(xOS_WIN)
//---------------------------------------------------------------------------
CxMimeMessage::CxMimeMessage() {

}
//---------------------------------------------------------------------------
CxMimeMessage::~CxMimeMessage() {

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
#elif defined(xOS_LINUX)

#endif
