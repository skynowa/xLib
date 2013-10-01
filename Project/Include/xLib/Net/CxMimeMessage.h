/**
 * \file  CxMimeMessage.h
 * \brief MIME message (RFC 822)
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeHeader;
class CxMimeBody;

class CxMimeMessage :
    private CxNonCopyable
    /// MIME message (RFC 822)
{
public:
                   CxMimeMessage  ();
    virtual       ~CxMimeMessage  ();

    static void_t  parse          (std::ctstring_t &csRawMessage,
                                   CxMimeHeader &Header, CxMimeBody &Body);
    static void_t  loadFromRawFile(std::ctstring_t &csFilePath); // csFilePath - raw msg
    static void_t  saveToRawFile  (std::ctstring_t &csFilePath); // csFilePath - raw msg

private:
    std::tstring_t _m_csRawMessage;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
