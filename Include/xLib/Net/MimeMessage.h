/**
 * \file  MimeMessage.h
 * \brief MIME message (RFC 822)
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, net)

class MimeHeader;
class MimeBody;

class MimeMessage
    /// MIME message (RFC 822)
{
public:
                   MimeMessage();
    virtual       ~MimeMessage() {}

    void_t         parse(std::ctstring_t &rawMessage, MimeHeader &header, MimeBody &body);
    void_t         loadFromRawFile(std::ctstring_t &filePath);
    void_t         saveToRawFile(std::ctstring_t &filePath);

private:
    std::tstring_t _rawMessage;

    xNO_COPY_ASSIGN(MimeMessage)
};

xNAMESPACE_END2(xlib, net)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "MimeMessage.cpp"
#endif
