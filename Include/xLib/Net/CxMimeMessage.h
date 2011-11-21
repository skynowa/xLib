/**
 * \file  CxMimeMessage.h
 * \brief MIME message (RFC 822)
 */


#ifndef xLib_Net_CxMimeMessageH
#define xLib_Net_CxMimeMessageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeMessage :
    public CxNonCopyable
    /// MIME message (RFC 822)
{
    public:
                     CxMimeMessage   ();
        virtual           ~CxMimeMessage   ();

        static bool  bParse          (const std::tstring_t &csRawMessage, CxMimeHeader &Header, CxMimeBody &Body);
        static bool  bLoadFromRawFile(const std::tstring_t &csFilePath);       //csFilePath - raw msg
        static bool  bSaveToRawFile  (const std::tstring_t &csFilePath);       //csFilePath - raw msg

    private:
        std::tstring_t _m_csRawMessage;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxMimeMessageH
