/**
 * \file  CxMimeMessage.cpp
 * \brief MIME message (RFC 822)
 */


#include <xLib/Net/CxMimeMessage.h>

#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>


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
    const std::tstring_t &a_csRawMessage,
    CxMimeHeader         &a_Header,
    CxMimeBody           &a_Body
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
    const std::tstring_t &a_csFilePath
)
{
    return false;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxMimeMessage::bSaveToRawFile(
    const std::tstring_t &a_csFilePath
)
{
    return false;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

