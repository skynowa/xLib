/**
 * \file   CxTest_CxDateTime.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxDateTime.h>


//------------------------------------------------------------------------------
CxTest_CxDateTime::CxTest_CxDateTime() {

}
//------------------------------------------------------------------------------
CxTest_CxDateTime::~CxTest_CxDateTime() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxDateTime::unit(
    const ulonglong_t &cullCaseLoops
)
{
    /*******************************************************************************
    *   public: constructors, destructor
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::CxDateTime", cullCaseLoops)
    {
        CxDateTime dtDT;
        m_sRv = dtDT.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 0:00:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::CxDateTime(const std::tstring_t &, EFormatType)", cullCaseLoops)
    {
        const CxDateTime::ExFormatType caftFormats[] = {
            ////CxDateTime::ftTime,     //HH.MM.SS.MMM
            ////CxDateTime::ftDate,     //DD.MM.YYYY
            ////CxDateTime::ftDateTime, //DD.MM.YYYY HH.MM.SS.MMM
            CxDateTime::ftRFC1123   //Wdy, DD Mon YYYY HH:MM:SS GMT
        };

        const std::tstring_t casDateTime[] = {
            ////xT("23.05.33.555"),             //HH.MM.SS.MMM
            ////xT("31.07.1978"),               //DD.MM.YYYY
            ////xT("24.01.1977 12.12.12.222"),  //DD.MM.YYYY HH.MM.SS.MMM
            xT("Wed, 23 Mar 2011 15:05:49 GMT")  //Wdy, DD Mon YYYY HH:MM:SS GMT
        };
        xTEST_EQ(xARRAY_SIZE(caftFormats), xARRAY_SIZE(casDateTime));

        for (size_t i = 0; i < xARRAY_SIZE(caftFormats); ++ i) {
            CxDateTime dtDT(casDateTime[i], caftFormats[i]);

            m_sRv = dtDT.format(caftFormats[i]);
            xTEST_EQ(casDateTime[i], m_sRv);
        }
    }

    xTEST_CASE("CxDateTime::CxDateTime(const CxDateTime &)", cullCaseLoops)
    {
        CxDateTime dtDT1(2010, 7, 8, 3, 15, 6, 111);
        CxDateTime dtDT2(dtDT1);
        m_sRv = dtDT2.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("08.07.2010 3:15:06:111")), m_sRv);

        CxDateTime dtDT(2010, 1, 14, 17, 0, 55, 666);
        m_sRv = dtDT.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("14.01.2010 17:00:55:666")), m_sRv);
    }

    xTEST_CASE("CxDateTime::CxDateTime(const ulonglong_t &)", cullCaseLoops)
    {
        CxDateTime dtDT(1000 * 60 * 60);
        m_sRv = dtDT.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 1:00:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::CxDateTime(const ushort_t &, const ushort_t &, const ushort_t &, const ushort_t &)", cullCaseLoops)
    {
        CxDateTime dtDT(12, 20, 37, 555);
        m_sRv = dtDT.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 12:20:37:555")), m_sRv);
    }

    xTEST_CASE("CxDateTime::CxDateTime(const ushort_t &, const ushort_t &, const ushort_t &)", cullCaseLoops)
    {
        CxDateTime dtDT(2010, 7, 8);
        m_sRv = dtDT.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("08.07.2010 0:00:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::CxDateTime(const ushort_t &, const ushort_t &, const ushort_t &, const ushort_t &, const ushort_t &, const ushort_t &, const ushort_t &)", cullCaseLoops)
    {
        CxDateTime dtDT(2010, 8, 18, 14, 0, 5, 777);
        m_sRv = dtDT.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("18.08.2010 14:00:05:777")), m_sRv);
    }


    /*******************************************************************************
    *   public: comparison operators
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::operator ==", cullCaseLoops)
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRv = (dtDt1 == dtDt2);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxDateTime::operator !=", cullCaseLoops)
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRv = (dtDt1 != dtDt2);
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxDateTime::operator <", cullCaseLoops)
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRv = (dtDt1 < dtDt2);
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxDateTime::operator <=", cullCaseLoops)
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRv = (dtDt1 <= dtDt2);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxDateTime::operator >", cullCaseLoops)
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRv = (dtDt1 > dtDt2);
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxDateTime::operator >=", cullCaseLoops)
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRv = (dtDt1 >= dtDt2);
        xTEST_EQ(true, m_bRv);
    }


    /*******************************************************************************
    *   public: assignment operators
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::operator +=", cullCaseLoops)
    {
        CxDateTime dtDt(0, 30, 0, 0);
        ulonglong_t  ullMSec = (1000 * 60) * 60; //1 hour

        dtDt = ullMSec;
        m_sRv = dtDt.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 1:00:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::operator (=, +, -)", cullCaseLoops)
    {
        CxDateTime dtDT;

        dtDT = CxDateTime() + CxDateTime(1000 * 60 * 60);
        m_sRv = dtDT.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 1:00:00:000")), m_sRv);

        dtDT = dtDT - CxDateTime(1000 * 60 * 60 / 2);
        m_sRv = dtDT.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 0:30:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::operator +=", cullCaseLoops)
    {
        CxDateTime dtDt1(1, 0, 0, 0);
        CxDateTime dtDt2(1, 30, 0, 0);

        dtDt1 += dtDt2;
        m_sRv = dtDt1.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 2:30:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::operator -=", cullCaseLoops)
    {
        CxDateTime dtDt1(1, 50, 0, 0);
        CxDateTime dtDt2(1, 30, 0, 0);

        dtDt1 -= dtDt2;
        m_sRv = dtDt1.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 0:20:00:000")), m_sRv);
    }


    /*******************************************************************************
    *   public: get, set
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::set get", cullCaseLoops)
    {
        CxDateTime dtDT;

        ushort_t     usYear   = 2010;
        ushort_t     usMonth  = 1;
        ushort_t     usDay    = 14;
        ushort_t     usHour   = 17;
        ushort_t     usMinute = 0;
        ushort_t     usSecond = 55;
        ushort_t     usMSec   = 666;

        dtDT.set(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMSec);
        dtDT.get(&usYear, &usMonth, &usDay, &usHour, &usMinute, &usSecond, &usMSec);

        xTEST_EQ((ushort_t)2010, usYear);
        xTEST_EQ((ushort_t)1,    usMonth);
        xTEST_EQ((ushort_t)14,   usDay);
        xTEST_EQ((ushort_t)17,   usHour);
        xTEST_EQ((ushort_t)0,    usMinute);
        xTEST_EQ((ushort_t)55,   usSecond);
        xTEST_EQ((ushort_t)666,  usMSec);
    }

    xTEST_CASE("CxDateTime::toMilliseconds", cullCaseLoops)
    {
        //1
        {
            m_ullRv = CxDateTime(2010, 1, 14, 17, 0, 55, 666).toMilliseconds();
            xTEST_EQ(62522902855666ULL, m_ullRv);
        }

        //2
        {
            const ulonglong_t caullMsec[] = {
                    12234567890ULL, 2234567890ULL, 32345657890ULL, 4294567890ULL, 5234567890ULL,
                    63565474567ULL, 7354234523ULL, 83451467547ULL, 9234436577ULL, 5354362463ULL
            };

            for (size_t i = 0; i < xARRAY_SIZE(caullMsec); ++ i) {
                m_ullRv = CxDateTime(caullMsec[i]).toMilliseconds();
                xTEST_EQ(caullMsec[i], m_ullRv);
            }
        }
    }

    xTEST_CASE("CxDateTime::set", cullCaseLoops)
    {
        CxDateTime dtDT;

        ulonglong_t  ui64DT = 1000 * 60 * 60; //1 hour

        ushort_t     usYear   = 0;
        ushort_t     usMonth  = 0;
        ushort_t     usDay    = 0;
        ushort_t     usHour   = 0;
        ushort_t     usMinute = 0;
        ushort_t     usSecond = 0;
        ushort_t     usMSec   = 0;

        dtDT.set(ui64DT);
        dtDT.get(&usYear, &usMonth, &usDay, &usHour, &usMinute, &usSecond, &usMSec);

        xTEST_EQ((ushort_t)0, usYear);
        xTEST_EQ((ushort_t)0, usMonth);
        xTEST_EQ((ushort_t)0, usDay);
        xTEST_EQ((ushort_t)1, usHour);
        xTEST_EQ((ushort_t)0, usMinute);
        xTEST_EQ((ushort_t)0, usSecond);
        xTEST_EQ((ushort_t)0, usMSec);
    }

    xTEST_CASE("CxDateTime::dayOfWeek", cullCaseLoops)
    {
        m_usiRv = CxDateTime(2011, 7, 25, 13, 0, 0, 0).dayOfWeek();
        xTEST_EQ((ushort_t)1, m_usiRv);

        m_usiRv = CxDateTime(2011, 7, 31, 0, 0, 0, 0).dayOfWeek();
        xTEST_EQ((ushort_t)0, m_usiRv);

        m_usiRv = CxDateTime(2011, 3, 18, 0, 0, 0, 0).dayOfWeek();
        xTEST_EQ((ushort_t)5, m_usiRv);
    }

    /*******************************************************************************
    *    formating
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::format", cullCaseLoops)
    {
        CxDateTime dtDT(2010, 1, 14, 17, 0, 55, 666);
        m_sRv = dtDT.format(CxDateTime::ftTime);
        xTEST_EQ(std::tstring_t(xT("17:00:55:666")), m_sRv);
    }

    xTEST_CASE("CxDateTime::format", cullCaseLoops)
    {
        CxDateTime dtDT(2010, 1, 14, 17, 0, 55, 666);
        m_sRv = dtDT.format(CxDateTime::ftDate);
        xTEST_EQ(std::tstring_t(xT("14.01.2010")), m_sRv);
    }

    xTEST_CASE("CxDateTime::format", cullCaseLoops)
    {
        CxDateTime dtDT(2010, 1, 14, 17, 0, 55, 666);
        m_sRv = dtDT.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("14.01.2010 17:00:55:666")), m_sRv);
    }

    xTEST_CASE("CxDateTime::format", cullCaseLoops)
    {
        CxDateTime dtDT(2011, 3, 19, 1, 35, 55, 666);
        m_sRv = dtDT.format(CxDateTime::ftRFC1123);
        xTEST_EQ(std::tstring_t(xT("Sat, 19 Mar 2011 01:35:55 GMT")), m_sRv);
    }


    /*******************************************************************************
    * static
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::isValid", cullCaseLoops)
    {
        //valid data
        {
            const ushort_t causiValid[][7] = {
                    //usYear, usMonth, usDay, usHour, usMinute, usSecond, usMSec
                    { 2011,     3,       24,    13,     21,       56,       999 },
                    { 1978,     7,       31,    4,      0,        0,        0   },
                    { 1956,     1,       24,    13,     59,       59,       998 },
                    { 2011,     2,       1,     12,     45,       5,        1   },
                    { 2011,     3,       2,     11,     30,       1,        125 },
                    { 2011,     4,       3,     10,     25,       30,       256 },
                    { 2011,     5,       4,     9,      8,        45,       589 },
                    { 2011,     6,       5,     8,      4,        54,       258 },
                    { 2011,     7,       6,     7,      1,        58,       951 },
                    { 2011,     8,       7,     23,     2,        40,       358 }
            };

            for (size_t i = 0; i < xARRAY_SIZE(causiValid); ++ i) {
    //                ushort_t usYear   = causiValid[i][0];
    //                ushort_t usMonth  = causiValid[i][1];
    //                ushort_t usDay    = causiValid[i][2];
    //                ushort_t usHour   = causiValid[i][3];
    //                ushort_t usMinute = causiValid[i][4];
    //                ushort_t usSecond = causiValid[i][5];
    //                ushort_t usMSec   = causiValid[i][6];
    //
    //                m_bRv = CxDateTime::isValid(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMSec);
    //                xTEST_EQ(true, m_bRv);
            }
        }

        //non valid data
        {
            const ushort_t causiNonValid[][7] = {
                    //usYear, usMonth, usDay, usHour, usMinute, usSecond, usMSec
                    { 10000,    3,       24,    13,     21,       56,       999 },
                    { 2011,     13,      24,    13,     21,       56,       999 },
                    { 2011,     3,       32,    13,     21,       56,       999 },
                    { 2011,     3,       24,    24,     21,       56,       999 },
                    { 2011,     3,       24,    13,     60,       56,       999 },
                    { 2011,     3,       24,    13,     21,       60,       999 },
                    { 2011,     3,       24,    13,     21,       56,       1000 }
            };

            for (size_t i = 0; i < xARRAY_SIZE(causiNonValid); ++ i) {
                ////ushort_t usYear   = causiNonValid[i][0];
                ////ushort_t usMonth  = causiNonValid[i][1];
                ////ushort_t usDay    = causiNonValid[i][2];
                ////ushort_t usHour   = causiNonValid[i][3];
                ////ushort_t usMinute = causiNonValid[i][4];
                ////ushort_t usSecond = causiNonValid[i][5];
                ////ushort_t usMSec   = causiNonValid[i][6];

                ////m_bRv = CxDateTime::isValid(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMSec);
                ////xTEST_EQ(true, m_bRv);
            }
        }
    }

    xTEST_CASE("CxDateTime::isValid(const CxDateTime &)", cullCaseLoops)
    {
        //TODO: tests bIsValid
    }

    xTEST_CASE("CxDateTime::isValid", cullCaseLoops)
    {
        //TODO: tests bIsValid
    }

    xTEST_CASE("CxDateTime::current", cullCaseLoops)
    {
        //1
        {
            CxDateTime dtNowDT;

            m_sRv = dtNowDT.current().format(CxDateTime::ftDateTime);
            xTEST_DIFF(std::tstring_t(xT("00.00.0000 0:00:00:000")), m_sRv);
        }

        //2
        for (size_t i = 0; i < 100; ++ i) {
            CxDateTime _m_dtTimesStart;
            CxDateTime _m_dtTimesStop;

            _m_dtTimesStart = CxDateTime::current();
            {
                for (int x = 0; x < 100; ++ x) {
                    for (int y = 0; y < 20; ++ y) {
                        int z = 0;

                        z++; --z;
                    }
                }
            }
            _m_dtTimesStop = CxDateTime::current();

            xTEST_EQ(true, _m_dtTimesStop >= _m_dtTimesStart);
        }
    }

    xTEST_CASE("CxDateTime::daysInMonth", cullCaseLoops)
    {
        for (ushort_t y = 0; y < 3000; ++ y) {
            for (ushort_t m = 1; m < 13; ++ m) {
                m_usiRv = CxDateTime::daysInMonth(y, m);

                if (2 == m && CxDateTime::isLeapYear(y)) {
                    xTEST_EQ((ushort_t)29, m_usiRv);
                } else {
                    ushort_t arusDaysOfMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

                    xTEST_EQ(m_usiRv, arusDaysOfMonth[m]);
                }
            } //m
        } //y
    }

    xTEST_CASE("CxDateTime::isLeapYear", cullCaseLoops)
    {
        //valid
        {
            ////const ushort_t causValid[] = {
            ////        //TODO: bIsLeapYear
            ////};

            ////for (size_t i = 0; i < xARRAY_SIZE(causValid); ++ i) {
            ////    m_bRv = CxDateTime::isLeapYear(causValid[i]);
            ////    xTEST_EQ(true, m_bRv);
            ////}
        }

        //non valid
        {
            ////const ushort_t causNonValid[] = {
            ////        //TODO: isLeapYear
            ////};

            ////for (size_t i = 0; i < xARRAY_SIZE(causNonValid); ++ i) {
            ////    m_bRv = CxDateTime::isLeapYear(causNonValid[i]);
            ////    xTEST_EQ(true, m_bRv);
            ////}
        }
    }

    xTEST_CASE("CxDateTime::filetimeToInt64", cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            const FILETIME cftTime = {100, 200};

            m_ullRv = CxDateTime::filetimeToInt64(cftTime);
            // TEST: xTEST_EQ( , m_ullRv);
        #endif
    }

    xTEST_CASE("CxDateTime::unixTimeToFileTime", cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            const time_t ctmUnixTime = 1000;
            FILETIME     ftFileTime  = {0};

            CxDateTime::unixTimeToFileTime(ctmUnixTime, &ftFileTime);
        #endif
    }

    xTEST_CASE("CxDateTime::fileTimeToUnixTime", cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            time_t   tmUnixTime = 0;
            FILETIME ftFileTime = {0};

            tmUnixTime = CxDateTime::fileTimeToUnixTime(ftFileTime);
            xTEST_EQ(static_cast<time_t>( -11644473600 ), tmUnixTime);
        #endif
    }


    /*******************************************************************************
    *   other
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::zodiacSign", cullCaseLoops)
    {
        // TEST: CxDateTime::zodiacSign

    #if xTODO
        /*
        -----------------------------------------------------
        |  Знак     |  Символ  |  Западная астрология       |
        -----------------------------------------------------
        |  Овеен    |  U+2648  |  21 марта    — 20 апреля   |
        |  Телец    |  U+2649  |  21 апреля   — 21 мая      |
        |  Близнецы |  U+264A  |  22 мая      — 21 июня     |
        |  Рак      |  U+264B  |  22 июня     — 23 июля     |
        |  Лев      |  U+264С  |  24 июля     — 23 августа  |
        |  Дева     |  U+264D  |  24 августа  — 23 сентября |
        |  Весы     |  U+264E  |  24 сентября — 23 октября  |
        |  Скорпион |  U+264F  |  24 октября  — 22 ноября   |
        |  Стрелец  |  U+2650  |  23 ноября   — 21 декабря  |
        |  Козерог  |  U+2651  |  22 декабря  — 20 января   |
        |  Водолей  |  U+2652  |  21 января   — 19 февраля  |
        |  Рыбы     |  U+2653  |  20 февраля  — 20 марта    |
        -----------------------------------------------------
        */

        const std::tstring_t sTestData[][3] = {
            {xT("7"), xT("31"), xT("Лев")},
            {xT("5"), xT("18"), xT("Телец")},
        };

        for (std::size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxDateTime::zodiacSign(CxString::cast<int>(sTestData[i][0]),
                                                          CxString::cast<int>(sTestData[i][1]));
            std::tstring_t sStr2 = sTestData[i][2];
            xTEST_EQ(sStr1, sStr2);
        }
    #endif
    }

    xTEST_CASE("CxDateTime::monthStr", cullCaseLoops)
    {
        //bIsShortName = false
        m_sRv = CxDateTime::monthStr((ushort_t)- 1, false);
        xTEST_EQ(std::tstring_t(xT("December")), m_sRv);
        m_sRv = CxDateTime::monthStr(0, false);
        xTEST_EQ(std::tstring_t(xT("January")), m_sRv);
        m_sRv = CxDateTime::monthStr(1, false);
        xTEST_EQ(std::tstring_t(xT("January")), m_sRv);
        m_sRv = CxDateTime::monthStr(2, false);
        xTEST_EQ(std::tstring_t(xT("February")), m_sRv);
        m_sRv = CxDateTime::monthStr(3, false);
        xTEST_EQ(std::tstring_t(xT("March")), m_sRv);
        m_sRv = CxDateTime::monthStr(4, false);
        xTEST_EQ(std::tstring_t(xT("April")), m_sRv);
        m_sRv = CxDateTime::monthStr(5, false);
        xTEST_EQ(std::tstring_t(xT("May")), m_sRv);
        m_sRv = CxDateTime::monthStr(6, false);
        xTEST_EQ(std::tstring_t(xT("June")), m_sRv);
        m_sRv = CxDateTime::monthStr(7, false);
        xTEST_EQ(std::tstring_t(xT("July")), m_sRv);
        m_sRv = CxDateTime::monthStr(8, false);
        xTEST_EQ(std::tstring_t(xT("August")), m_sRv);
        m_sRv = CxDateTime::monthStr(9, false);
        xTEST_EQ(std::tstring_t(xT("September")), m_sRv);
        m_sRv = CxDateTime::monthStr(10, false);
        xTEST_EQ(std::tstring_t(xT("October")), m_sRv);
        m_sRv = CxDateTime::monthStr(11, false);
        xTEST_EQ(std::tstring_t(xT("November")), m_sRv);
        m_sRv = CxDateTime::monthStr(12, false);
        xTEST_EQ(std::tstring_t(xT("December")), m_sRv);
        m_sRv = CxDateTime::monthStr(13, false);
        xTEST_EQ(std::tstring_t(xT("December")), m_sRv);

        //bIsShortName = true
        m_sRv = CxDateTime::monthStr((ushort_t)- 1, true);
        xTEST_EQ(std::tstring_t(xT("Dec")), m_sRv);
        m_sRv = CxDateTime::monthStr(0, true);
        xTEST_EQ(std::tstring_t(xT("Jan")), m_sRv);
        m_sRv = CxDateTime::monthStr(1, true);
        xTEST_EQ(std::tstring_t(xT("Jan")), m_sRv);
        m_sRv = CxDateTime::monthStr(2, true);
        xTEST_EQ(std::tstring_t(xT("Feb")), m_sRv);
        m_sRv = CxDateTime::monthStr(3, true);
        xTEST_EQ(std::tstring_t(xT("Mar")), m_sRv);
        m_sRv = CxDateTime::monthStr(4, true);
        xTEST_EQ(std::tstring_t(xT("Apr")), m_sRv);
        m_sRv = CxDateTime::monthStr(5, true);
        xTEST_EQ(std::tstring_t(xT("May")), m_sRv);
        m_sRv = CxDateTime::monthStr(6, true);
        xTEST_EQ(std::tstring_t(xT("Jun")), m_sRv);
        m_sRv = CxDateTime::monthStr(7, true);
        xTEST_EQ(std::tstring_t(xT("Jul")), m_sRv);
        m_sRv = CxDateTime::monthStr(8, true);
        xTEST_EQ(std::tstring_t(xT("Aug")), m_sRv);
        m_sRv = CxDateTime::monthStr(9, true);
        xTEST_EQ(std::tstring_t(xT("Sep")), m_sRv);
        m_sRv = CxDateTime::monthStr(10, true);
        xTEST_EQ(std::tstring_t(xT("Oct")), m_sRv);
        m_sRv = CxDateTime::monthStr(11, true);
        xTEST_EQ(std::tstring_t(xT("Nov")), m_sRv);
        m_sRv = CxDateTime::monthStr(12, true);
        xTEST_EQ(std::tstring_t(xT("Dec")), m_sRv);
        m_sRv = CxDateTime::monthStr(13, true);
        xTEST_EQ(std::tstring_t(xT("Dec")), m_sRv);
    }

    xTEST_CASE("CxDateTime::monthNum", cullCaseLoops)
    {
        const std::tstring_t casMonths[12][2] = {
            { xT("January"),    xT("Jan") },
            { xT("February"),   xT("Feb") },
            { xT("March"),      xT("Mar") },
            { xT("April"),      xT("Apr") },
            { xT("May"),        xT("May") },
            { xT("June"),       xT("Jun") },
            { xT("July"),       xT("Jul") },
            { xT("August"),     xT("Aug") },
            { xT("September"),  xT("Sep") },
            { xT("October"),    xT("Oct") },
            { xT("November"),   xT("Nov") },
            { xT("December"),   xT("Dec") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(casMonths); ++ i) {
            m_usiRv = CxDateTime::monthNum(casMonths[i][0], false);
            xTEST_EQ((ushort_t)(i + 1), m_usiRv);

            m_usiRv = CxDateTime::monthNum(casMonths[i][1], true);
            xTEST_EQ((ushort_t)(i + 1), m_usiRv);

            if (xT("May") == casMonths[i][0] || xT("May") == casMonths[i][1]) {
                m_usiRv = CxDateTime::monthNum(casMonths[i][0], true);
                xTEST_EQ((ushort_t)(i + 1), m_usiRv);

                m_usiRv = CxDateTime::monthNum(casMonths[i][1], false);
                xTEST_EQ((ushort_t)(i + 1), m_usiRv);
            } else {
                m_usiRv = CxDateTime::monthNum(casMonths[i][0], true);
                xTEST_EQ((ushort_t)- 1, m_usiRv);

                m_usiRv = CxDateTime::monthNum(casMonths[i][1], false);
                xTEST_EQ((ushort_t)- 1, m_usiRv);
            }
        }
    }

    xTEST_CASE("CxDateTime::weekDayStr", cullCaseLoops)
    {
        //bIsShortName = false
        m_sRv = CxDateTime::weekDayStr(0, false);
        xTEST_EQ(std::tstring_t(xT("Sunday")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(1, false);
        xTEST_EQ(std::tstring_t(xT("Monday")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(2, false);
        xTEST_EQ(std::tstring_t(xT("Tuesday")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(3, false);
        xTEST_EQ(std::tstring_t(xT("Wednesday")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(4, false);
        xTEST_EQ(std::tstring_t(xT("Thursday")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(5, false);
        xTEST_EQ(std::tstring_t(xT("Friday")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(6, false);
        xTEST_EQ(std::tstring_t(xT("Saturday")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(7, false);
        xTEST_EQ(std::tstring_t(xT("Saturday")), m_sRv);

        //bIsShortName = true
        m_sRv = CxDateTime::weekDayStr(0, true);
        xTEST_EQ(std::tstring_t(xT("Sun")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(1, true);
        xTEST_EQ(std::tstring_t(xT("Mon")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(2, true);
        xTEST_EQ(std::tstring_t(xT("Tue")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(3, true);
        xTEST_EQ(std::tstring_t(xT("Wed")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(4, true);
        xTEST_EQ(std::tstring_t(xT("Thu")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(5, true);
        xTEST_EQ(std::tstring_t(xT("Fri")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(6, true);
        xTEST_EQ(std::tstring_t(xT("Sat")), m_sRv);
        m_sRv = CxDateTime::weekDayStr(7, true);
        xTEST_EQ(std::tstring_t(xT("Sat")), m_sRv);
    }

    xTEST_CASE("CxDateTime::weekDayNum", cullCaseLoops)
    {
        const std::tstring_t casDays[7][2] = {
            { xT("Sunday"),     xT("Sun") },
            { xT("Monday"),     xT("Mon") },
            { xT("Tuesday"),    xT("Tue"} ),
            { xT("Wednesday"),  xT("Wed") },
            { xT("Thursday"),   xT("Thu") },
            { xT("Friday"),     xT("Fri") },
            { xT("Saturday"),   xT("Sat") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(casDays); ++ i) {
            m_usiRv = CxDateTime::weekDayNum(casDays[i][0], false);
            xTEST_EQ((ushort_t)i, m_usiRv);

            m_usiRv = CxDateTime::weekDayNum(casDays[i][1], true);
            xTEST_EQ((ushort_t)i, m_usiRv);

            m_usiRv = CxDateTime::weekDayNum(casDays[i][0], true);
            xTEST_EQ((ushort_t)- 1, m_usiRv);

            m_usiRv = CxDateTime::weekDayNum(casDays[i][1], false);
            xTEST_EQ((ushort_t)- 1, m_usiRv);
        }
    }
}
//------------------------------------------------------------------------------
