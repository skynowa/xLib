/**
 * \file  CxMimeHeader.cpp
 * \brief MIME header (RFC 822)
 */


#include <xLib/Net/CxMimeHeader.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Common/CxLocale.h>


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
const std::tstring_t CxMimeHeader::_ms_csAttrDelimiter = xT(":");
const std::tstring_t CxMimeHeader::_ms_csEndOfHeader   = xT("\r\n\r\n");
const std::tstring_t CxMimeHeader::_ms_csEndOfLine     = xT("\r\n");
//---------------------------------------------------------------------------
//DONE: CxMimeHeader
CxMimeHeader::CxMimeHeader() :
    _m_bRes     (false),
    _m_sRes     (),
    _m_mmsHeader()
{
}
//---------------------------------------------------------------------------
//DONE: ~CxMimeHeader
/* virtual */
CxMimeHeader::~CxMimeHeader () {

}
//---------------------------------------------------------------------------
//DONE: bParse (��������� ��������� ������� "TOP 10 0" �� ��������, ��������)
bool
CxMimeHeader::bParse(
    const std::tstring_t &a_csRawHeader
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

    std::vec_tstring_t vsHeader;
    _m_bRes = CxString::bSplit(csRawHeader, _ms_csEndOfLine, &vsHeader);
    /*DEBUG*///TODO:

    //-------------------------------------
    //???? ???? "+OK..." ? ?????? ??????, ?? ??????? ??? ??????
    if (std::tstring_t::npos != vsHeader.at(0).find(xT("+OK"))) {
        vsHeader.erase(vsHeader.begin() + 0);
    }

    //-------------------------------------
    //????????????? ?????? -> ? ????????????
    for (size_t i = 0; i < vsHeader.size(); i ++) {
        //???? ?????? ?????? ??? "."
        if ((true == vsHeader.at(i).empty()) || (xT(".") == vsHeader.at(i))) {      /*Trim*/
            //??????? ??????? ??????
            vsHeader.erase(vsHeader.begin() + i);

            //??????? 1-? ?????? - ????????? ?????? ?? 1
            -- i;

            //???? ? ????????? ??????
            continue;
        }

        //???? 1-?? ?????? ??????????, ?? ?????? - ??? ????? ????????????? ?????? "???? : ????????"
        ////if (true == bIsSpaceOrTab(vsHeader.at(i).at(0))) {
        if ((xT(' ') == vsHeader.at(i).at(0)) || (xT('\t') == vsHeader.at(i).at(0))) {
            //????????? ? ?????????? ?????? ?????? (??????, ??? ?????????? ????) ??????? ??????
            vsHeader.at(i - 1).append(vsHeader.at(i));

            //??????? ??????? ?????? (? ??? ???????, ?????? ?? ?? ?????????)
            vsHeader.erase(vsHeader.begin() + i);

            //??????? 1-? ?????? - ????????? ?????? ?? 1
            -- i;

            //???? ? ????????? ??????
            continue;
        }
    }

    //-------------------------------------
    //std::vector -> std::map
    for (size_t i = 0; i < vsHeader.size(); i ++) {
        std::vec_tstring_t vsLines;
        //--vsLines = vsSplit(": ", vsHeader.at(i));
        _m_bRes = CxString::bSplitKeyValue(vsHeader.at(i), _ms_csAttrDelimiter, &vsLines);
        /*DEBUG*/xTEST_EQ(true, _m_bRes,           false);
        /*DEBUG*/xTEST_EQ(false, vsLines.empty(), false);

        //????????? ? ?????? "????" ? "????????"
        std::tstring_t sKey   = CxString::sTrimSpace(vsLines.at(0));
        std::tstring_t sValue = CxString::sTrimSpace(vsLines.at(1));

        _m_mmsHeader.insert(std::pair<std::tstring_t, std::tstring_t>(sKey, sValue));
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
//DONE: sGetField
std::tstring_t
CxMimeHeader::sGetField(
    const std::tstring_t &a_csName
)
{
    /*DEBUG*/xTEST_EQ(false, _m_mmsHeader.empty());
    /*DEBUG*/xTEST_EQ(false, a_csName.empty());

    std::tstring_t sRv;

    std::pair<std::mmap_tstring_t::const_iterator, std::mmap_tstring_t::const_iterator> prEqualRange = _m_mmsHeader.equal_range(a_csName);

    std::mmap_tstring_t::const_iterator it;
    for (it = prEqualRange.first; it != prEqualRange.second; ++ it) {
        sRv = (*it).second;
    }

    return sRv;
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
    bool
    CxMimeHeader::bLoadFromFile(const std::tstring_t &csFilePath) {
     /*DEBUG*/xTEST_EQ(false, csFilePath.empty(),                 false);
     /*DEBUG*/xTEST_EQ(true, CxFile::bIsExists(csFilePath), false);

     std::tstring_t sUknownEmail("Uknown@Uknown.Uknown");
     std::tstring_t sLine("");
     std::ifstream  ifsStream(csFilePath.c_str());
     /*DEBUG*/xTEST_EQ(true,  !! ifsStream);
     /*DEBUG*/xTEST_EQ(false, ifsStream.fail());
     /*DEBUG*/xTEST_EQ(true,  ifsStream.good());
     /*DEBUG*/xTEST_EQ(true,  ifsStream.is_open());
     /*DEBUG*/xTEST_EQ(false, ifsStream.eof());

     ulong_t ulCountBreaks = 0;
     for (ulong_t i = 0; !ifsStream.eof();  ++ i) {
         std::getline(ifsStream, sLine);

         //���� �� ������ csFrom (From:)
         if (std::tstring_t::npos != sLine.find(csFrom + ":")) {
             //From: ����<test_1@localhost>
             return sReplaceAll(vsSplit(_ms_csAttrDelimiter, sLine).at(1), " ", "");    //Uknown@Uknown.Uknown!!!!!!!!!!!
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

     return false;
    }
#endif

bool
CxMimeHeader::bLoadFromFile(
    const std::tstring_t &a_csRawMessageFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, a_csRawMessageFilePath.empty());
    /*DEBUG*/xTEST_EQ(true, CxFile::bIsExists(a_csRawMessageFilePath));

    std::tstring_t sRawHeader;
    std::tstring_t sLine;

    //-------------------------------------
    //������������� ��������� ������
    CxLocale::vSetDefault();

    //-------------------------------------
    //������ ���������� ����� � ������ �� ����� ������ (\r\n\r\n - ������ ������)
    std::tifstream_t ifsStream(a_csRawMessageFilePath.c_str());
    /*DEBUG*/xTEST_EQ(true, !! ifsStream);
    /*DEBUG*/xTEST_EQ(false, ifsStream.fail());
    /*DEBUG*/xTEST_EQ(true,  ifsStream.good());
    /*DEBUG*/xTEST_EQ(true,  ifsStream.is_open());
    /*DEBUG*/xTEST_EQ(false, ifsStream.eof());

    ////ulong_t ulCountBreaks = 0;
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
bool
CxMimeHeader::bSaveToFile(
    const std::tstring_t &a_csFilePath
)
{
    //_m_mmsHeader

    return true;
}
//---------------------------------------------------------------------------
//TODO: sGenerateMessageID (������� Message-ID ��� "<", ">")
/* static */
std::tstring_t
CxMimeHeader::sGenerateMessageID() {
    std::tstring_t sRv;

    sRv = CxString::sFormat(xT("%s@%s"), CxString::sCreateGuid().c_str(), CxSystemInfo::sGetHostName().c_str());
    /*DEBUG*/xTEST_EQ(false, sRv.empty());

    return sRv;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
