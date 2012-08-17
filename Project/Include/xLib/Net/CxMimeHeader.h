/**
 * \file  CxMimeHeader.h
 * \brief MIME header (RFC 822)
 */


#ifndef xLib_Net_CxMimeHeaderH
#define xLib_Net_CxMimeHeaderH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeHeader :
    private CxNonCopyable
    /// MIME header (RFC 822)
{
    public:
                               CxMimeHeader      ();
                              ~CxMimeHeader      ();

        bool                   bParse            (const std::tstring_t &csRawHeader);
        std::tstring_t         sGetField         (const std::tstring_t &csName);
        size_t                 uiCount           ();
        bool                   bLoadFromFile     (const std::tstring_t &csRawMessageFilePath);
        bool                   bSaveToFile       (const std::tstring_t &csFilePath);

        static std::tstring_t  sGenerateMessageID();

    private:
        static const std::tstring_t _ms_csAttrDelimiter;
        static const std::tstring_t _ms_csEndOfHeader;
        static const std::tstring_t _ms_csEndOfLine;

        bool                   _m_bRes;
        std::tstring_t         _m_sRes;
        std::multimap<std::tstring_t, std::tstring_t> _m_mmsHeader;

        //Delivered-To:
        //Return-Path:
        //Received:
        //From:
        //To:
        //CC:
        //BCC:
        //Subject:
        //X-Priority:
        //X-MSMail-Priority:
        //X-Mailer:
        //X-MimeOLE:
        //Reply-To:
        //MIME-Version:
        //Content-Type:
        //Content-Transfer-Encoding:
        //Date:
        //Message-ID:
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxMimeHeaderH

/*
procedure TIdMessage.ClearHeader;
begin
CcList.Clear;
BccList.Clear;
Date := 0;
FromList.Clear;
NewsGroups.Clear;
Organization := '';
References := '';
ReplyTo.Clear;
Subject := '';
Recipients.Clear;
Priority := ID_MSG_PRIORITY;
ReceiptRecipient.Text := '';
ContentType := '';
FCharSet := '';
ContentTransferEncoding := '';
ContentDisposition := '';
FSender.Text := '';
Headers.Clear;
ExtraHeaders.Clear;
FMIMEBoundary.Clear;
//  UseNowForDate := ID_MSG_USENOWFORDATE;
Flags := [];
MsgId := '';
UID := '';
FLastGeneratedHeaders.Clear;
FEncoding := meDefault; {CC3: Changed initial encoding from meMIME to meDefault}
FConvertPreamble := True;  {By default, in MIME, we convert the preamble text to the 1st TIdText part}
FGenerateBCCListInHeader := False;  {Only set True by SaveToFile}
end;
*/


/*
apTIdMessage->Flags;
apTIdMessage->IsEncoded;
apTIdMessage->MsgId;
apTIdMessage->Headers;
apTIdMessage->MessageParts;
apTIdMessage->MIMEBoundary;
apTIdMessage->UID;
apTIdMessage->IsMsgSinglePartMime;
apTIdMessage->AttachmentEncoding;
apTIdMessage->Body;
apTIdMessage->BccList;
apTIdMessage->CharSet;
apTIdMessage->CCList;
apTIdMessage->ContentType;
apTIdMessage->ContentTransferEncoding;
apTIdMessage->ContentDisposition;
apTIdMessage->Date;
apTIdMessage->Encoding;
apTIdMessage->ExtraHeaders;
apTIdMessage->FromList;
apTIdMessage->From;
apTIdMessage->NewsGroups;
apTIdMessage->NoEncode;
apTIdMessage->NoDecode;
apTIdMessage->Organization;
apTIdMessage->Priority;
apTIdMessage->ReceiptRecipient;
apTIdMessage->Recipients;
apTIdMessage->References;
apTIdMessage->InReplyTo;
apTIdMessage->Subject;
apTIdMessage->Sender;
apTIdMessage->UseNowForDate;
apTIdMessage->LastGeneratedHeaders;
apTIdMessage->ConvertPreamble;
apTIdMessage->ExceptionOnBlockedAttachments;
apTIdMessage->AttachmentTempDirectory;
apTIdMessage->OnInitializeISO;
apTIdMessage->OnCreateAttachment;
*/
