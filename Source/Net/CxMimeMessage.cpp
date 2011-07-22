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


//---------------------------------------------------------------------------
CxMimeMessage::CxMimeMessage() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxMimeMessage::~CxMimeMessage() {

}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxMimeMessage::bParse(
	const tString &csRawMessage,
	CxMimeHeader  &Header,
	CxMimeBody    &Body
)
{
    //m_Header;
    //m_Body;

    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxMimeMessage::bLoadFromRawFile(
	const tString &csFilePath
)
{

    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxMimeMessage::bSaveToRawFile(
	const tString &csFilePath
)
{

    return FALSE;
}
//---------------------------------------------------------------------------

