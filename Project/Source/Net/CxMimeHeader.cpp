/**
 * \file  CxMimeHeader.cpp
 * \brief MIME header (RFC 822)
 */


#include <xLib/Net/CxMimeHeader.h>

#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/System/CxSystemInfo.h>
#include <xLib/Core/CxLocale.h>


xNAMESPACE_BEGIN(NxLib)

//------------------------------------------------------------------------------
xINLINE_HO
CxMimeHeader::CxMimeHeader() :
    _attrDelimiter(xT(":")),
    _endOfHeader  (xT("\r\n\r\n")),
    _endOfLine    (xT("\r\n"))
{
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxMimeHeader::parse(
    std::ctstring_t &a_rawHeader
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
    _m_bRv = CxString::bSplit(rawHeader, _endOfLine, &vsHeader);
    //TODO:

    //-------------------------------------
    //???? ???? "+OK..." ? ?????? ??????, ?? ??????? ??? ??????
    if (std::tstring_t::npos != vsHeader.at(0).find(xT("+OK"))) {
        vsHeader.erase(vsHeader.begin() + 0);
    }

    //-------------------------------------
    //????????????? ?????? -> ? ????????????
    for (size_t i = 0; i < vsHeader.size(); i ++) {
        //???? ?????? ?????? ??? "."
        if ((vsHeader.at(i).empty()) || (xT(".") == vsHeader.at(i))) {      /*Trim*/
            //??????? ??????? ??????
            vsHeader.erase(vsHeader.begin() + i);

            //??????? 1-? ?????? - ????????? ?????? ?? 1
            -- i;

            //???? ? ????????? ??????
            continue;
        }

        //???? 1-?? ?????? ??????????, ?? ?????? - ??? ????? ????????????? ?????? "???? : ????????"
        ////if (bIsSpaceOrTab(vsHeader.at(i).at(0))) {
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
        _m_bRv = CxString::bSplitKeyValue(vsHeader.at(i), _attrDelimiter, &vsLines);
        xTEST_EQ(true, _m_bRv,           false);
        xTEST_EQ(false, vsLines.empty(), false);

        //????????? ? ?????? "????" ? "????????"
        std::tstring_t sKey   = CxString::trimSpace(vsLines.at(0));
        std::tstring_t sValue = CxString::trimSpace(vsLines.at(1));

        _header.insert(std::pair<std::tstring_t, std::tstring_t>(sKey, sValue));
    }
#endif
}
//------------------------------------------------------------------------------
//DONE: sGetField
xINLINE_HO std::tstring_t
CxMimeHeader::field(
    std::ctstring_t &a_name
)
{
    xTEST_EQ(false, _header.empty());
    xTEST_EQ(false, a_name.empty());

    std::tstring_t sRv;

    std::pair<std::mmap_tstring_t::const_iterator, std::mmap_tstring_t::const_iterator>
        prEqualRange = _header.equal_range(a_name);

    std::mmap_tstring_t::const_iterator it;
    for (it = prEqualRange.first; it != prEqualRange.second; ++ it) {
        sRv = (*it).second;
    }

    return sRv;
}
//------------------------------------------------------------------------------
//DONE: uiCount
xINLINE_HO size_t
CxMimeHeader::count()
{
    return _header.size();
}
//------------------------------------------------------------------------------
//TODO:  bLoadFromFile
#if xTODO
    bool_t
    CxMimeHeader::bLoadFromFile(std::ctstring_t &filePath) {
     xTEST_EQ(false, filePath.empty(),                 false);
     xTEST_EQ(true, CxFile::isExists(filePath), false);

     std::tstring_t sUknownEmail("Uknown@Uknown.Uknown");
     std::tstring_t sLine("");
     std::ifstream  ifsStream(filePath.c_str());
     xTEST_EQ(true,  !! ifsStream);
     xTEST_EQ(false, ifsStream.fail());
     xTEST_EQ(true,  ifsStream.good());
     xTEST_EQ(true,  ifsStream.is_open());
     xTEST_EQ(false, ifsStream.eof());

     ulong_t ulCountBreaks = 0;
     for (ulong_t i = 0; !ifsStream.eof();  ++ i) {
         std::getline(ifsStream, sLine);

         //���� �� ������ csFrom (From:)
         if (std::tstring_t::npos != sLine.find(csFrom + ":")) {
             //From: ����<test_1@localhost>
             return sReplaceAll(vsSplit(_attrDelimiter, sLine).at(1), " ", ""); // Uknown@Uknown.Uknown!!!!!!!!!!!
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

xINLINE_HO void_t
CxMimeHeader::loadFromFile(
    std::ctstring_t &a_rawMessageFilePath
)
{
    xTEST_EQ(false, a_rawMessageFilePath.empty());
    xTEST_EQ(true, CxFile::isExists(a_rawMessageFilePath));

    std::tstring_t sRawHeader;
    std::tstring_t sLine;

    //-------------------------------------
    //������������� ��������� ������
    CxLocale::setDefault();

    //-------------------------------------
    //������ ���������� ����� � ������ �� ����� ������ (\r\n\r\n - ������ ������)
    std::tifstream_t ifsStream(a_rawMessageFilePath.c_str());
    xTEST_EQ(true, !! ifsStream);
    xTEST_EQ(false, ifsStream.fail());
    xTEST_EQ(true,  ifsStream.good());
    xTEST_EQ(true,  ifsStream.is_open());
    xTEST_EQ(false, ifsStream.eof());

    ////ulong_t ulCountBreaks = 0;
    for (; !ifsStream.eof(); ) {
        std::getline(ifsStream, sLine);

        //������ �� "\r\n\r\n" (����� ������)
        xCHECK_DO(sLine.empty(), break);

        sRawHeader.append(sLine + _endOfLine);
    }

    //-------------------------------------
    //����������
    parse(sRawHeader);
}
//------------------------------------------------------------------------------
//TODO: bSaveToFile
xINLINE_HO void_t
CxMimeHeader::saveToFile(
    std::ctstring_t &a_filePath
)
{
    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: sGenerateMessageID (������� Message-ID ��� "<", ">")
/* static */
xINLINE_HO std::tstring_t
CxMimeHeader::generateMessageID()
{
    std::tstring_t sRv;

    sRv = CxString::format(xT("%s@%s"), CxString::createGuid().c_str(),
        CxSystemInfo().hostName().c_str());
    xTEST_EQ(false, sRv.empty());

    return sRv;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
