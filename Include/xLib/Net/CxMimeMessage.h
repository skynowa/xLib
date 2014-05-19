/**
 * \file  CxMimeMessage.h
 * \brief MIME message (RFC 822)
 */


#pragma once

#ifndef xLib_CxMimeMessageH
#define xLib_CxMimeMessageH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, net)

class CxMimeHeader;
class CxMimeBody;

class CxMimeMessage
    /// MIME message (RFC 822)
{
public:
                   CxMimeMessage();
    virtual       ~CxMimeMessage() {}

    void_t         parse(std::ctstring_t &rawMessage, CxMimeHeader &header, CxMimeBody &body);
    void_t         loadFromRawFile(std::ctstring_t &filePath);
    void_t         saveToRawFile(std::ctstring_t &filePath);

private:
    std::tstring_t _rawMessage;

    xNO_COPY_ASSIGN(CxMimeMessage)
};

xNAMESPACE_END2(xlib, net)
//-------------------------------------------------------------------------------------------------
#include "CxMimeMessage.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxMimeMessageH
