/**
 * \file  CxMimeMessage.cpp
 * \brief MIME message (RFC 822)
 */


#include <xLib/Net/CxMimeMessage.h>

#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>


xNAMESPACE_BEGIN(NxLib)

//------------------------------------------------------------------------------
CxMimeMessage::CxMimeMessage() {

}
//------------------------------------------------------------------------------
/* virtual */
CxMimeMessage::~CxMimeMessage() {

}
//------------------------------------------------------------------------------
/* static */
void_t
CxMimeMessage::parse(
    std::ctstring_t &a_csRawMessage,
    CxMimeHeader    &a_Header,
    CxMimeBody      &a_Body
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
/* static */
void_t
CxMimeMessage::loadFromRawFile(
    std::ctstring_t &a_csFilePath
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
/* static */
void_t
CxMimeMessage::saveToRawFile(
    std::ctstring_t &a_csFilePath
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

