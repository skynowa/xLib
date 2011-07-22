/****************************************************************************
* Class name:  CxMimeHeader
* Description: MIME header (RFC 822)
* File name:   CxMimeHeader.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.07.2009 19:10:09
*
*****************************************************************************/


#include <xLib/Net/CxMimeHeader.h>

#include <xLib/Filesystem/CxStdioFile.h>
#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Common/CxLocale.h>


//---------------------------------------------------------------------------
const tString CxMimeHeader::_ms_csAttrDelimiter = xT(":");
const tString CxMimeHeader::_ms_csEndOfHeader   = xT("\r\n\r\n");
const tString CxMimeHeader::_ms_csEndOfLine     = xT("\r\n");
//---------------------------------------------------------------------------
//DONE: CxMimeHeader
CxMimeHeader::CxMimeHeader() :
    _m_bRes     (FALSE),
    _m_sRes     (),
    _m_mmsHeader()
{
}
//---------------------------------------------------------------------------
//DONE: ~CxMimeHeader
/*virtual*/
CxMimeHeader::~CxMimeHeader () {

}
//---------------------------------------------------------------------------
//DONE: bParse (��������� ��������� ������� "TOP 10 0" �� ��������, ��������)
BOOL
CxMimeHeader::bParse(
	const tString &csRawHeader
)
{
#if xTODO
    /*
    +OK message 1 (570821 octets)
    Return-Path: <Administrator@localhost>
    Received: from SERGEY ([192.168.1.48])
    by Sergey (Kerio MailServer 6.7.0);
    Thu, 11 Jun 2009 15:13:38 +0400
    Date: Thu, 9 Apr 2009 13:53:34 +0400
    From: Administrator <Administrator@localhost>
    X-Mailer: The Bat! (v2.12.00) Educational
    Reply-To: Administrator <Administrator@localhost>
    X-Priority: 3 (Normal)
    Message-ID: <936634544.20090409135334@localhost>
    To: test_1@localhost, test_2@localhost, test_3@localhost, test_4@localhost
    Subject: =?Windows-1251?B?8uXs4A==?=
    MIME-Version: 1.0
    Content-Type: multipart/mixed;
      boundary="----------544A15625820D78"


    .

    */

    std::vector<tString> vecsHeader;
    _m_bRes = CxString::bSplit(csRawHeader, _ms_csEndOfLine, &vecsHeader);
    /*DEBUG*///TODO:

    //-------------------------------------
    //???? ???? "+OK..." ? ?????? ??????, ?? ??????? ??? ??????
    if (tString::npos != vecsHeader.at(0).find(xT("+OK"))) {
        vecsHeader.erase(vecsHeader.begin() + 0);
    }

    //-------------------------------------
    //????????????? ?????? -> ? ????????????
    for (size_t i = 0; i < vecsHeader.size(); i ++) {
        //???? ?????? ?????? ??? "."
        if ((true == vecsHeader.at(i).empty()) || (xT(".") == vecsHeader.at(i))) {      /*Trim*/
            //??????? ??????? ??????
            vecsHeader.erase(vecsHeader.begin() + i);

            //??????? 1-? ?????? - ????????? ?????? ?? 1
            -- i;

            //???? ? ????????? ??????
            continue;
        }

        //???? 1-?? ?????? ??????????, ?? ?????? - ??? ????? ????????????? ?????? "???? : ????????"
        ////if (TRUE == bIsSpaceOrTab(vecsHeader.at(i).at(0))) {
        if ((xT(' ') == vecsHeader.at(i).at(0)) || (xT('\t') == vecsHeader.at(i).at(0))) {
            //????????? ? ?????????? ?????? ?????? (??????, ??? ?????????? ????) ??????? ??????
            vecsHeader.at(i - 1).append(vecsHeader.at(i));

            //??????? ??????? ?????? (? ??? ???????, ?????? ?? ?? ?????????)
            vecsHeader.erase(vecsHeader.begin() + i);

            //??????? 1-? ?????? - ????????? ?????? ?? 1
            -- i;

            //???? ? ????????? ??????
            continue;
        }
    }

    //-------------------------------------
    //std::vector -> std::map
    for (size_t i = 0; i < vecsHeader.size(); i ++) {
        std::vector<tString> vecsLines;
        //--vecsLines = vecsSplit(": ", vecsHeader.at(i));
        _m_bRes = CxString::bSplitKeyValue(vecsHeader.at(i), _ms_csAttrDelimiter, &vecsLines);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,           FALSE);
        /*DEBUG*/xASSERT_RET(false == vecsLines.empty(), FALSE);

        //????????? ? ?????? "????" ? "????????"
        tString sKey   = CxString::sTrimSpace(vecsLines.at(0));
        tString sValue = CxString::sTrimSpace(vecsLines.at(1));

        _m_mmsHeader.insert(std::pair<tString, tString>(sKey, sValue));
    }
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetField
tString
CxMimeHeader::sGetField(
	const tString &csName
)
{
    /*DEBUG*/xASSERT_RET(false == _m_mmsHeader.empty(), tString());
    /*DEBUG*/xASSERT_RET(false == csName.empty(),       tString());

    tString sRes;

    std::pair<std::multimap<tString, tString>::iterator, std::multimap<tString, tString>::iterator> prEqualRange = _m_mmsHeader.equal_range(csName);

    std::multimap<tString, tString>::iterator it;
    for (it = prEqualRange.first; it != prEqualRange.second; ++ it) {
        sRes = (*it).second;
    }

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: uiCount
size_t
CxMimeHeader::uiCount() {
    return _m_mmsHeader.size();
}
//---------------------------------------------------------------------------
//TODO:  bLoadFromFile
#if xTODO
	BOOL
	CxMimeHeader::bLoadFromFile(const tString &csFilePath) {
	 /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),                 FALSE);
	 /*DEBUG*/xASSERT_RET(TRUE  == CxStdioFile::bIsExists(csFilePath), FALSE);

	 tString       sUknownEmail("Uknown@Uknown.Uknown");
	 tString       sLine("");
	 std::ifstream     ifsStream(csFilePath.c_str());
	 /*DEBUG*/xASSERT_RET(ifsStream,           FALSE);
	 /*DEBUG*/xASSERT_RET(!ifsStream.fail(),   FALSE);
	 /*DEBUG*/xASSERT_RET(ifsStream.good(),    FALSE);
	 /*DEBUG*/xASSERT_RET(ifsStream.is_open(), FALSE);
	 /*DEBUG*/xASSERT_RET(!ifsStream.eof(),    FALSE);

	 ULONG ulCountBreaks = 0;
	 for (ULONG i = 0; !ifsStream.eof();  ++ i) {
		 std::getline(ifsStream, sLine);

		 //���� �� ������ csFrom (From:)
		 if (tString::npos != sLine.find(csFrom + ":")) {
			 //From: ����<test_1@localhost>
			 return sReplaceAll(vecsSplit(_ms_csAttrDelimiter, sLine).at(1), " ", "");    //Uknown@Uknown.Uknown!!!!!!!!!!!
		 }

		 //������ �� "\r\n\r\n" (����� ������)
		 if ("" == sLine) {
			 ulCountBreaks ++;
			 if (2 == ulCountBreaks) {
				 return "";
			 }
		 } else {
			 ulCountBreaks = 0;
		 }
	 }

	 return "";

	 return FALSE;
	}
#endif
BOOL
CxMimeHeader::bLoadFromFile(
	const tString &csRawMessageFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csRawMessageFilePath.empty(),                 FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == CxStdioFile::bIsExists(csRawMessageFilePath), FALSE);

    tString sRawHeader;
    tString sLine;

    //-------------------------------------
    //������������� ��������� ������
    _m_bRes = CxLocale::bSetDefault();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //������ ���������� ����� � ������ �� ����� ������ (\r\n\r\n - ������ ������)
    tifstream ifsStream(csRawMessageFilePath.c_str());
    /*DEBUG*/xASSERT_RET(ifsStream,           FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.fail(),   FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.good(),    FALSE);
    /*DEBUG*/xASSERT_RET(ifsStream.is_open(), FALSE);
    /*DEBUG*/xASSERT_RET(!ifsStream.eof(),    FALSE);

    ////ULONG ulCountBreaks = 0;
    for (; !ifsStream.eof(); ) {
        std::getline(ifsStream, sLine);

        //������ �� "\r\n\r\n" (����� ������)
        xCHECK_DO(true == sLine.empty(), break);

        sRawHeader.append(sLine + _ms_csEndOfLine);
    }

    //-------------------------------------
    //����������
    _m_bRes = bParse(sRawHeader);

    return _m_bRes;
}
//---------------------------------------------------------------------------
//TODO: bSaveToFile
BOOL
CxMimeHeader::bSaveToFile(
	const tString &csFilePath
)
{
    //_m_mmsHeader

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: sGenerateMessageID (������� Message-ID ��� "<", ">")
/*static*/
tString
CxMimeHeader::sGenerateMessageID() {
    tString sRes;

    sRes = CxString::sFormat(xT("%s@%s"), CxString::sCreateGuid().c_str(), CxSystemInfo::sGetComputerName().c_str());
    /*DEBUG*/xASSERT_RET(false == sRes.empty(), tString());

    return sRes;
}
//---------------------------------------------------------------------------

