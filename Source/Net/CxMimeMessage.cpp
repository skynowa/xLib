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
bool
CxMimeMessage::bParse(
    const std::tstring_t &csRawMessage,
    CxMimeHeader  &Header,
    CxMimeBody    &Body
)
{
    //m_Header;
    //m_Body;

    return false;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxMimeMessage::bLoadFromRawFile(
    const std::tstring_t &csFilePath
)
{

    return false;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxMimeMessage::bSaveToRawFile(
    const std::tstring_t &csFilePath
)
{

    return false;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

