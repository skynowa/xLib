/****************************************************************************
* Class name:  CxMimeMessage
* Description: MIME message (RFC 822)
* File name:   CxMimeMessage.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.07.2009 19:09:16
*
*****************************************************************************/


#ifndef xLib_Net_CxMimeMessageH
#define xLib_Net_CxMimeMessageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxMimeMessage :
    public CxNonCopyable
{
    public:
                CxMimeMessage();
               ~CxMimeMessage();
        static BOOL bParse          (const tString &csRawMessage, CxMimeHeader &Header, CxMimeBody &Body);
        static BOOL    bLoadFromRawFile(const tString &csFilePath);       //csFilePath - raw msg
        static BOOL bSaveToRawFile  (const tString &csFilePath);       //csFilePath - raw msg

    private:
        tString _m_csRawMessage;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxMimeMessageH
