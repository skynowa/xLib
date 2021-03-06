/**
 * \file  MimeHeader.h
 * \brief MIME header (RFC 822)
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::net
{

class MimeHeader
    /// MIME header (RFC 822)
{
public:
///@name ctors, dtor
///@{
			 MimeHeader();
	virtual ~MimeHeader() = default;

	xNO_COPY_ASSIGN(MimeHeader)
///@}

    void_t              parse(std::ctstring_t &rawHeader);
    std::tstring_t      field(std::ctstring_t &name);
    size_t              count();
    void_t              loadFromFile(std::ctstring_t &rawMessageFilePath);
    void_t              saveToFile(std::ctstring_t &filePath);

    static
    std::tstring_t      generateMessageID();

private:
    std::ctstring_t     _attrDelimiter;
    std::ctstring_t     _endOfHeader;
    std::ctstring_t     _endOfLine;

    std::mmap_tstring_t _header;

    // Delivered-To:
    // Return-Path:
    // Received:
    // From:
    // To:
    // CC:
    // BCC:
    // Subject:
    // X-Priority:
    // X-MSMail-Priority:
    // X-Mailer:
    // X-MimeOLE:
    // Reply-To:
    // MIME-Version:
    // Content-Type:
    // Content-Transfer-Encoding:
    // Date:
    // Message-ID:
};

} // namespace
//-------------------------------------------------------------------------------------------------

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
