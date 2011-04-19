/****************************************************************************
* Class name:  CxMimeHeader
* Description: MIME header (RFC 822) 
* File name:   CxMimeHeader.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.07.2009 19:10:09
*
*****************************************************************************/


#ifndef xLib_Net_CxMimeHeaderH 
#define xLib_Net_CxMimeHeaderH 
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxMimeHeader : public CxNonCopyable {
	public:
					         CxMimeHeader      (); 
				            ~CxMimeHeader      (); 

		BOOL                 bParse            (const tString &csRawHeader); 
		tString				 sGetField         (const tString &csName);  
		size_t               uiCount           (); 
		BOOL			     bLoadFromFile     (const tString &csRawMessageFilePath); 
		BOOL		         bSaveToFile       (const tString &csFilePath); 

		static tString		 sGenerateMessageID();

	private:
		static const tString _ms_csAttrDelimiter;
		static const tString _ms_csEndOfHeader;
		static const tString _ms_csEndOfLine;

		BOOL                 _m_bRes;
		tString              _m_sRes;
		TStringMultiMap      _m_mmsHeader;

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
//---------------------------------------------------------------------------
#endif	//xLib_Net_CxMimeHeaderH 

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
