/**
 * \file  CxMimeHeader.cpp
 * \brief MIME header (RFC 822)
 */


#include <xLib/Core/CxString.h>
#include <xLib/Core/CxLocale.h>
#include <xLib/Crypt/CxGuid.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/System/CxSystemInfo.h>


xNAMESPACE2_BEGIN(xlib, net)

//-------------------------------------------------------------------------------------------------
inline
CxMimeHeader::CxMimeHeader() :
    _attrDelimiter(xT(":")),
    _endOfHeader  (xT("\r\n\r\n")),
    _endOfLine    (xT("\r\n"))
{
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMimeHeader::parse(
    std::ctstring_t &a_rawHeader
)
{
    xUNUSED(a_rawHeader);

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
    // TODO: CxMimeHeader::parse()

    //-------------------------------------
    //???? ???? "+OK..." ? ?????? ??????, ?? ??????? ??? ??????
    if (vsHeader.at(0).find(xT("+OK")) != std::tstring_t::npos) {
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
        _m_bRv = CxString::bSplitKeyValue(vsHeader.at(i), _attrDelimiter, &vsLines);
        xTEST_EQ(_m_bRv,          true);
        xTEST_EQ(vsLines.empty(), false);

        std::tstring_t sKey   = CxString::trimSpace(vsLines.at(0));
        std::tstring_t sValue = CxString::trimSpace(vsLines.at(1));

        _header.insert(std::pair<std::tstring_t, std::tstring_t>(sKey, sValue));
    }
#endif
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxMimeHeader::field(
    std::ctstring_t &a_name
)
{
    xTEST_EQ(_header.empty(), false);
    xTEST_EQ(a_name.empty(), false);

    std::tstring_t sRv;

    std::pair<std::mmap_tstring_t::const_iterator, std::mmap_tstring_t::const_iterator>
        prEqualRange = _header.equal_range(a_name);

    std::mmap_tstring_t::const_iterator it;
    for (it = prEqualRange.first; it != prEqualRange.second; ++ it) {
        sRv = (*it).second;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline size_t
CxMimeHeader::count()
{
    return _header.size();
}
//-------------------------------------------------------------------------------------------------
#if xTODO

bool_t
CxMimeHeader::loadFromFile(
    std::ctstring_t &filePath
)
{
    // TODO: CxMimeHeader::loadFromFile(()

    xTEST_EQ(filePath.empty(), false);
    xTEST_EQ( CxFile::isExists(filePath), true);

    std::tstring_t sUknownEmail("Uknown@Uknown.Uknown");
    std::tstring_t sLine("");
    std::ifstream  ifsStream(filePath.c_str());
    xTEST_EQ(!!ifsStream, true);
    xTEST_EQ(ifsStream.fail(), false);
    xTEST_EQ(ifsStream.good(), true);
    xTEST_EQ(ifsStream.is_open(), true);
    xTEST_EQ(ifsStream.eof(), false);

    ulong_t ulCountBreaks = 0;
    for (ulong_t i = 0; !ifsStream.eof();  ++ i) {
         std::getline(ifsStream, sLine);

         // (From:)
         if (sLine.find(csFrom + ":") != std::tstring_t::npos) {
            // From: ����<test_1@localhost>
            return sReplaceAll(vsSplit(_attrDelimiter, sLine).at(1), " ", ""); // Uknown@Uknown.Uknown!!!!!!!!!!!
         }

        // "\r\n\r\n"
        if ("" == sLine) {
            ulCountBreaks ++;
            if (2 == ulCountBreaks) {
                return "";
            }
        } else {
            ulCountBreaks = 0;
        }
    }

    return false;
}

#endif

inline void_t
CxMimeHeader::loadFromFile(
    std::ctstring_t &a_rawMessageFilePath
)
{
    xTEST_EQ(a_rawMessageFilePath.empty(), false);
    xTEST_EQ(CxFile::isExists(a_rawMessageFilePath), true);

    std::tstring_t sRawHeader;
    std::tstring_t sLine;

    CxLocale locale;
    locale.setDefault();

    //-------------------------------------
    // (\r\n\r\n)
    std::tifstream_t ifsStream(a_rawMessageFilePath.c_str());
    xTEST_EQ(!!ifsStream, true);
    xTEST_EQ(ifsStream.fail(), false);
    xTEST_EQ(ifsStream.good(), true);
    xTEST_EQ(ifsStream.is_open(), true);
    xTEST_EQ(ifsStream.eof(), false);

    ////ulong_t ulCountBreaks = 0;
    for (; !ifsStream.eof(); ) {
        std::getline(ifsStream, sLine);

        //������ �� "\r\n\r\n" (����� ������)
        xCHECK_DO(sLine.empty(), break);

        sRawHeader.append(sLine + _endOfLine);
    }

    parse(sRawHeader);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMimeHeader::saveToFile(
    std::ctstring_t &a_filePath
)
{
    xUNUSED(a_filePath);

    // TODO: CxMimeHeader::saveToFile()
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxMimeHeader::generateMessageID()
{
    std::tstring_t sRv;

    sRv = CxString::format(xT("%s@%s"), CxGuid().create(CxGuid::tpRandomBased).c_str(),
        CxSystemInfo().hostName().c_str());
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, net)
