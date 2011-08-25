/**
 * \file  CxMimeMessage.cpp
 * \brief MIME message (RFC 822)
 */


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
	const std::tstring &csRawMessage,
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
	const std::tstring &csFilePath
)
{

    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxMimeMessage::bSaveToRawFile(
	const std::tstring &csFilePath
)
{

    return FALSE;
}
//---------------------------------------------------------------------------

