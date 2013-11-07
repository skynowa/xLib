/**
 * \file  CxMimeMessage.h
 * \brief MIME message (RFC 822)
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeheader;
class CxMimebody;

class CxMimeMessage :
    public CxNonCopyable
    /// MIME message (RFC 822)
{
public:
                   CxMimeMessage();
    virtual       ~CxMimeMessage();

    static void_t  parse(std::ctstring_t &rawMessage, CxMimeheader &header, CxMimebody &body);
    static void_t  loadFromRawFile(std::ctstring_t &filePath); // filePath - raw msg
    static void_t  saveToRawFile(std::ctstring_t &filePath); // filePath - raw msg

private:
    std::tstring_t _rawMessage;
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Net/CxMimeMessage.cpp>
#endif
