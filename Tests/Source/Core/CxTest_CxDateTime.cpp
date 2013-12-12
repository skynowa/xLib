/**
 * \file   CxTest_CxDateTime.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxDateTime.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxDateTime::unit(
    culonglong_t &a_caseLoops
)
{
    /*******************************************************************************
    *   public: constructors, destructor
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::CxDateTime", a_caseLoops)
    {
        CxDateTime datetime;
        m_sRv = datetime.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 0:00:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::CxDateTime(std::ctstring_t &, EFormatType)", a_caseLoops)
    {
        const CxDateTime::ExFormatType formats[] = {
        #if xTODO
            CxDateTime::ftTime,     // HH.MM.SS.MMM
            CxDateTime::ftDate,     // DD.MM.YYYY
            CxDateTime::ftDateTime, // DD.MM.YYYY HH.MM.SS.MMM
        #endif
            CxDateTime::ftRFC1123   // Wdy, DD Mon YYYY HH:MM:SS GMT
        };

        std::ctstring_t datetimes[] = {
        #if xTODO
            xT("23.05.33.555"),             // HH.MM.SS.MMM
            xT("31.07.1978"),               // DD.MM.YYYY
            xT("24.01.1977 12.12.12.222"),  // DD.MM.YYYY HH.MM.SS.MMM
        #endif
            xT("Wed, 23 Mar 2011 15:05:49 GMT")  // Wdy, DD Mon YYYY HH:MM:SS GMT
        };
        xTEST_EQ(xARRAY_SIZE(formats), xARRAY_SIZE(datetimes));

        for (size_t i = 0; i < xARRAY_SIZE(formats); ++ i) {
            CxDateTime datetime(datetimes[i], formats[i]);

            m_sRv = datetime.format(formats[i]);
            xTEST_EQ(datetimes[i], m_sRv);
        }
    }

    xTEST_CASE("CxDateTime::CxDateTime(const CxDateTime &)", a_caseLoops)
    {
        CxDateTime datetime1(2010, 7, 8, 3, 15, 6, 111);
        CxDateTime datetime2(datetime1);
        m_sRv = datetime2.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("08.07.2010 3:15:06:111")), m_sRv);

        CxDateTime datetime(2010, 1, 14, 17, 0, 55, 666);
        m_sRv = datetime.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("14.01.2010 17:00:55:666")), m_sRv);
    }

    xTEST_CASE("CxDateTime::CxDateTime(culonglong_t &)", a_caseLoops)
    {
        CxDateTime datetime(1000 * 60 * 60);
        m_sRv = datetime.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 1:00:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::CxDateTime(cushort_t &, cushort_t &, cushort_t &, cushort_t &)", a_caseLoops)
    {
        CxDateTime datetime(12, 20, 37, 555);
        m_sRv = datetime.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 12:20:37:555")), m_sRv);
    }

    xTEST_CASE("CxDateTime::CxDateTime(cushort_t &, cushort_t &, cushort_t &)", a_caseLoops)
    {
        CxDateTime datetime(2010, 7, 8);
        m_sRv = datetime.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("08.07.2010 0:00:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::CxDateTime(cushort_t &, cushort_t &, cushort_t &, cushort_t &, cushort_t &, cushort_t &, cushort_t &)", a_caseLoops)
    {
        CxDateTime datetime(2010, 8, 18, 14, 0, 5, 777);
        m_sRv = datetime.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("18.08.2010 14:00:05:777")), m_sRv);
    }


    /*******************************************************************************
    *   public: validate
    *
    *******************************************************************************/


    /*******************************************************************************
    *   public: comparison operators
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::operator ==", a_caseLoops)
    {
        CxDateTime datetime1;
        CxDateTime datetime2;

        m_bRv = (datetime1 == datetime2);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxDateTime::operator !=", a_caseLoops)
    {
        CxDateTime datetime1;
        CxDateTime datetime2;

        m_bRv = (datetime1 != datetime2);
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxDateTime::operator <", a_caseLoops)
    {
        CxDateTime datetime1;
        CxDateTime datetime2;

        m_bRv = (datetime1 < datetime2);
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxDateTime::operator <=", a_caseLoops)
    {
        CxDateTime datetime1;
        CxDateTime datetime2;

        m_bRv = (datetime1 <= datetime2);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxDateTime::operator >", a_caseLoops)
    {
        CxDateTime datetime1;
        CxDateTime datetime2;

        m_bRv = (datetime1 > datetime2);
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxDateTime::operator >=", a_caseLoops)
    {
        CxDateTime datetime1;
        CxDateTime datetime2;

        m_bRv = (datetime1 >= datetime2);
        xTEST_EQ(true, m_bRv);
    }


    /*******************************************************************************
    *   public: assignment operators
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::operator +=", a_caseLoops)
    {
        CxDateTime  datetime(0, 30, 0, 0);
        ulonglong_t msec = (1000 * 60) * 60; // 1 hour

        datetime = msec;
        m_sRv = datetime.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 1:00:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::operator (=, +, -)", a_caseLoops)
    {
        CxDateTime datetime;

        datetime = CxDateTime() + CxDateTime(1000 * 60 * 60);
        m_sRv = datetime.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 1:00:00:000")), m_sRv);

        datetime = datetime - CxDateTime(1000 * 60 * 60 / 2);
        m_sRv = datetime.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 0:30:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::operator +=", a_caseLoops)
    {
        CxDateTime datetime1(1, 0, 0, 0);
        CxDateTime datetime2(1, 30, 0, 0);

        datetime1 += datetime2;
        m_sRv = datetime1.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 2:30:00:000")), m_sRv);
    }

    xTEST_CASE("CxDateTime::operator -=", a_caseLoops)
    {
        CxDateTime datetime1(1, 50, 0, 0);
        CxDateTime datetime2(1, 30, 0, 0);

        datetime1 -= datetime2;
        m_sRv = datetime1.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("00.00.0000 0:20:00:000")), m_sRv);
    }


    /*******************************************************************************
    *   public: get, set
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::set get", a_caseLoops)
    {
        CxDateTime datetime;

        int_t     year   = 2010;
        int_t     month  = 1;
        int_t     day    = 14;
        int_t     hour   = 17;
        int_t     minute = 0;
        int_t     second = 55;
        int_t     msec   = 666;

        datetime.set(year, month, day, hour, minute, second, msec);
        datetime.get(&year, &month, &day, &hour, &minute, &second, &msec);

        xTEST_EQ(2010, year);
        xTEST_EQ(1,    month);
        xTEST_EQ(14,   day);
        xTEST_EQ(17,   hour);
        xTEST_EQ(0,    minute);
        xTEST_EQ(55,   second);
        xTEST_EQ(666,  msec);
    }

    xTEST_CASE("CxDateTime::toMilliseconds", a_caseLoops)
    {
        // 1
        {
            m_ullRv = CxDateTime(2010, 1, 14, 17, 0, 55, 666).toMsec();
            xTEST_EQ(62522902855666ULL, m_ullRv);
        }

        // 2
        {
            culonglong_t msecs[] = {
                12234567890ULL, 2234567890ULL, 32345657890ULL, 4294567890ULL, 5234567890ULL,
                63565474567ULL, 7354234523ULL, 83451467547ULL, 9234436577ULL, 5354362463ULL
            };

            for (size_t i = 0; i < xARRAY_SIZE(msecs); ++ i) {
                m_ullRv = CxDateTime(msecs[i]).toMsec();
                xTEST_EQ(msecs[i], m_ullRv);
            }
        }
    }

    xTEST_CASE("CxDateTime::set", a_caseLoops)
    {
        CxDateTime  datetime;
        ulonglong_t datetimeValue = 1000 * 60 * 60; // 1 hour
        int_t       year   = 0;
        int_t       month  = 0;
        int_t       day    = 0;
        int_t       hour   = 0;
        int_t       minute = 0;
        int_t       second = 0;
        int_t       msec   = 0;

        datetime.set(datetimeValue);
        datetime.get(&year, &month, &day, &hour, &minute, &second, &msec);

        xTEST_EQ(0, year);
        xTEST_EQ(0, month);
        xTEST_EQ(0, day);
        xTEST_EQ(1, hour);
        xTEST_EQ(0, minute);
        xTEST_EQ(0, second);
        xTEST_EQ(0, msec);
    }

    xTEST_CASE("CxDateTime::dayOfWeek", a_caseLoops)
    {
        m_iRv = CxDateTime(2011, 7, 25, 13, 0, 0, 0).dayOfWeek();
        xTEST_EQ(1, m_iRv);

        m_iRv = CxDateTime(2011, 7, 31, 0, 0, 0, 0).dayOfWeek();
        xTEST_EQ(0, m_iRv);

        m_iRv = CxDateTime(2011, 3, 18, 0, 0, 0, 0).dayOfWeek();
        xTEST_EQ(5, m_iRv);
    }

    /*******************************************************************************
    *    formating
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::format", a_caseLoops)
    {
        CxDateTime datetime(2010, 1, 14, 17, 0, 55, 666);
        m_sRv = datetime.format(CxDateTime::ftTime);
        xTEST_EQ(std::tstring_t(xT("17:00:55:666")), m_sRv);
    }

    xTEST_CASE("CxDateTime::format", a_caseLoops)
    {
        CxDateTime datetime(2010, 1, 14, 17, 0, 55, 666);
        m_sRv = datetime.format(CxDateTime::ftDate);
        xTEST_EQ(std::tstring_t(xT("14.01.2010")), m_sRv);
    }

    xTEST_CASE("CxDateTime::format", a_caseLoops)
    {
        CxDateTime datetime(2010, 1, 14, 17, 0, 55, 666);
        m_sRv = datetime.format(CxDateTime::ftDateTime);
        xTEST_EQ(std::tstring_t(xT("14.01.2010 17:00:55:666")), m_sRv);
    }

    xTEST_CASE("CxDateTime::format", a_caseLoops)
    {
        CxDateTime datetime(2011, 3, 19, 1, 35, 55, 666);
        m_sRv = datetime.format(CxDateTime::ftRFC1123);
        xTEST_EQ(std::tstring_t(xT("Sat, 19 Mar 2011 01:35:55 GMT")), m_sRv);
    }


    /*******************************************************************************
    * static
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::isValid", a_caseLoops)
    {
        //valid data
        {
            cushort_t valid[][7] = {
                // year, month, day, hour, minute, second, msec
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

            for (size_t i = 0; i < xARRAY_SIZE(valid); ++ i) {
            #if xTODO
                int_t year   = valid[i][0];
                int_t month  = valid[i][1];
                int_t day    = valid[i][2];
                int_t hour   = valid[i][3];
                int_t minute = valid[i][4];
                int_t second = valid[i][5];
                int_t msec   = valid[i][6];

                m_bRv = CxDateTime::isValid(year, month, day, hour, minute, second, msec);
                xTEST_EQ(true, m_bRv);
            #endif
            }
        }

        //non valid data
        {
            cushort_t nonValid[][7] = {
                // year, month, day, hour, minute, second, msec
                { 10000,    3,       24,    13,     21,       56,       999 },
                { 2011,     13,      24,    13,     21,       56,       999 },
                { 2011,     3,       32,    13,     21,       56,       999 },
                { 2011,     3,       24,    24,     21,       56,       999 },
                { 2011,     3,       24,    13,     60,       56,       999 },
                { 2011,     3,       24,    13,     21,       60,       999 },
                { 2011,     3,       24,    13,     21,       56,       1000 }
            };

            for (size_t i = 0; i < xARRAY_SIZE(nonValid); ++ i) {
            #if xTODO
                int_t year   = nonValid[i][0];
                int_t month  = nonValid[i][1];
                int_t day    = nonValid[i][2];
                int_t hour   = nonValid[i][3];
                int_t minute = nonValid[i][4];
                int_t second = nonValid[i][5];
                int_t msec   = nonValid[i][6];

                m_bRv = CxDateTime::isValid(year, month, day, hour, minute, second, msec);
                xTEST_EQ(true, m_bRv);
            #endif
            }
        }
    }

    xTEST_CASE("CxDateTime::isValid(const CxDateTime &)", a_caseLoops)
    {
        // TODO: tests isValid
    }

    xTEST_CASE("CxDateTime::isValid", a_caseLoops)
    {
        // TODO: tests isValid
    }

    xTEST_CASE("CxDateTime::current", a_caseLoops)
    {
        // 1
        {
            CxDateTime datetimeNow;

            m_sRv = datetimeNow.current().format(CxDateTime::ftDateTime);
            xTEST_DIFF(std::tstring_t(xT("00.00.0000 0:00:00:000")), m_sRv);
        }

        // 2
        for (size_t i = 0; i < 100; ++ i) {
            CxDateTime start;
            CxDateTime stop;

            start = CxDateTime::current();
            {
                for (int_t x = 0; x < 100; ++ x) {
                    for (int_t y = 0; y < 20; ++ y) {
                        int_t z = 0;

                        z++; --z;
                    }
                }
            }
            stop = CxDateTime::current();

            xTEST_EQ(true, stop >= start);
        }
    }

    xTEST_CASE("CxDateTime::daysInMonth", a_caseLoops)
    {
        for (int_t y = 0; y < 3000; ++ y) {
            for (int_t m = 1; m < 13; ++ m) {
                m_iRv = CxDateTime::daysInMonth(y, m);

                if (2 == m && CxDateTime::isLeapYear(y)) {
                    xTEST_EQ(29, m_iRv);
                } else {
                    int_t arusDaysOfMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

                    xTEST_EQ(m_iRv, arusDaysOfMonth[m]);
                }
            } // m
        } // y
    }

    xTEST_CASE("CxDateTime::isLeapYear", a_caseLoops)
    {
        // valid
        {
        #if xTODO
            cushort_t valid[] = {
                // TODO: isLeapYear
            };

            for (size_t i = 0; i < xARRAY_SIZE(valid); ++ i) {
                m_bRv = CxDateTime::isLeapYear(valid[i]);
                xTEST_EQ(true, m_bRv);
            }
        #endif
        }

        // non valid
        {
        #if xTODO
            cushort_t nonValid[] = {
                // TODO: isLeapYear
            };

            for (size_t i = 0; i < xARRAY_SIZE(nonValid); ++ i) {
                m_bRv = CxDateTime::isLeapYear(nonValid[i]);
                xTEST_EQ(true, m_bRv);
            }
        #endif
        }
    }

    xTEST_CASE("CxDateTime::filetimeToInt64", a_caseLoops)
    {
    #if xOS_ENV_WIN
        const FILETIME time = {100, 200};

        m_ullRv = CxDateTime::filetimeToInt64(time);
        // TEST: xTEST_EQ( , m_ullRv);
    #endif
    }

    xTEST_CASE("CxDateTime::unixTimeToFileTime", a_caseLoops)
    {
    #if xOS_ENV_WIN
        const time_t unixTime = 1000;
        FILETIME     fileTime  = {0};

        CxDateTime::unixTimeToFileTime(unixTime, &fileTime);
    #endif
    }

    xTEST_CASE("CxDateTime::fileTimeToUnixTime", a_caseLoops)
    {
    #if xOS_ENV_WIN
        time_t   unixTime = 0;
        FILETIME fileTime = {0};

        unixTime = CxDateTime::fileTimeToUnixTime(fileTime);
        xTEST_EQ(static_cast<time_t>( -11644473600 ), unixTime);
    #endif
    }


    /*******************************************************************************
    *   other
    *
    *******************************************************************************/

    xTEST_CASE("CxDateTime::zodiacSign", a_caseLoops)
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

        std::ctstring_t data[][3] = {
            {xT("7"), xT("31"), xT("Лев")},
            {xT("5"), xT("18"), xT("Телец")},
        };

        for (std::size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = CxDateTime::zodiacSign(CxString::cast<int_t>(data[i][0]),
                                                         CxString::cast<int_t>(data[i][1]));
            std::tstring_t str2 = data[i][2];
            xTEST_EQ(str1, str2);
        }
    #endif
    }

    xTEST_CASE("CxDateTime::monthStr", a_caseLoops)
    {
        // isShortName = false
        m_sRv = CxDateTime::monthStr(- 1, false);
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

        // isShortName = true
        m_sRv = CxDateTime::monthStr(- 1, true);
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

    xTEST_CASE("CxDateTime::monthNum", a_caseLoops)
    {
        std::ctstring_t months[12][2] = {
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

        for (size_t i = 0; i < xARRAY_SIZE(months); ++ i) {
            m_iRv = CxDateTime::monthNum(months[i][0], false);
            xTEST_EQ(int_t(i + 1), m_iRv);

            m_iRv = CxDateTime::monthNum(months[i][1], true);
            xTEST_EQ(int_t(i + 1), m_iRv);

            if (xT("May") == months[i][0] || xT("May") == months[i][1]) {
                m_iRv = CxDateTime::monthNum(months[i][0], true);
                xTEST_EQ(int_t(i + 1), m_iRv);

                m_iRv = CxDateTime::monthNum(months[i][1], false);
                xTEST_EQ(int_t(i + 1), m_iRv);
            } else {
                m_iRv = CxDateTime::monthNum(months[i][0], true);
                xTEST_EQ(- 1, m_iRv);

                m_iRv = CxDateTime::monthNum(months[i][1], false);
                xTEST_EQ(- 1, m_iRv);
            }
        }
    }

    xTEST_CASE("CxDateTime::weekDayStr", a_caseLoops)
    {
        // isShortName = false
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

        // isShortName = true
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

    xTEST_CASE("CxDateTime::weekDayNum", a_caseLoops)
    {
        std::ctstring_t days[7][2] = {
            { xT("Sunday"),     xT("Sun") },
            { xT("Monday"),     xT("Mon") },
            { xT("Tuesday"),    xT("Tue"} ),
            { xT("Wednesday"),  xT("Wed") },
            { xT("Thursday"),   xT("Thu") },
            { xT("Friday"),     xT("Fri") },
            { xT("Saturday"),   xT("Sat") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(days); ++ i) {
            m_iRv = CxDateTime::weekDayNum(days[i][0], false);
            xTEST_EQ((int_t)i, m_iRv);

            m_iRv = CxDateTime::weekDayNum(days[i][1], true);
            xTEST_EQ((int_t)i, m_iRv);

            m_iRv = CxDateTime::weekDayNum(days[i][0], true);
            xTEST_EQ(- 1, m_iRv);

            m_iRv = CxDateTime::weekDayNum(days[i][1], false);
            xTEST_EQ(- 1, m_iRv);
        }
    }
}
//------------------------------------------------------------------------------
