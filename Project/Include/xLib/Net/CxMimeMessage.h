/**
 * \file  CxMimeMessage.h
 * \brief MIME message (RFC 822)
 */


#ifndef xLib_Net_CxMimeMessageH
#define xLib_Net_CxMimeMessageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeHeader;
class CxMimeBody;

class CxMimeMessage :
    private CxNonCopyable
    /// MIME message (RFC 822)
{
public:
                   CxMimeMessage   ();
    virtual       ~CxMimeMessage   ();

    static void    vParse          (const std::tstring_t &csRawMessage, CxMimeHeader &Header, CxMimeBody &Body);
    static void    vLoadFromRawFile(const std::tstring_t &csFilePath);       //csFilePath - raw msg
    static void    vSaveToRawFile  (const std::tstring_t &csFilePath);       //csFilePath - raw msg

private:
    std::tstring_t _m_csRawMessage;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Net_CxMimeMessageH
