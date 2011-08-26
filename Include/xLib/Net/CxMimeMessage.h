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
class CxMimeMessage :
    public CxNonCopyable
    /// MIME message (RFC 822)
{
    public:
					 CxMimeMessage   ();
		virtual	   	~CxMimeMessage   ();

		static BOOL  bParse          (const std::tstring &csRawMessage, CxMimeHeader &Header, CxMimeBody &Body);
		static BOOL  bLoadFromRawFile(const std::tstring &csFilePath);       //csFilePath - raw msg
		static BOOL  bSaveToRawFile  (const std::tstring &csFilePath);       //csFilePath - raw msg

    private:
        std::tstring      _m_csRawMessage;
};
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxMimeMessageH
