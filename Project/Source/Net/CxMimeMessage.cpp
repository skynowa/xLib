/**
 * \file  CxMimeMessage.cpp
 * \brief MIME message (RFC 822)
 */


#include <xLib/Net/CxMimeMessage.h>

#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>


xNAMESPACE_BEGIN(NxLib)

//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxMimeMessage::parse(
    std::ctstring_t &a_rawMessage,
    CxMimeheader    &a_header,
    CxMimebody      &a_body
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxMimeMessage::loadFromRawFile(
    std::ctstring_t &a_filePath
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxMimeMessage::saveToRawFile(
    std::ctstring_t &a_filePath
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

