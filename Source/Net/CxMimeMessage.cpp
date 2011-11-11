/**
 * \file  CxMimeMessage.cpp
 * \brief MIME message (RFC 822)
 */


#include <xLib/Net/CxMimeMessage.h>


xNAMESPACE_BEGIN(NxLib)

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
    const std::string_t &csRawMessage,
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
    const std::string_t &csFilePath
)
{

    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxMimeMessage::bSaveToRawFile(
    const std::string_t &csFilePath
)
{

    return FALSE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

