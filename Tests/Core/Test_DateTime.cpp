/**
 * \file   Test_DateTime.cpp
 * \brief
 */


#include "Test_DateTime.h"


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_DateTime)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_DateTime::unit()
{
    /*******************************************************************************
    *   public: constructors, destructor
    *
    *******************************************************************************/

    xTEST_CASE("DateTime")
    {
        DateTime datetime;
        m_sRv = datetime.format(xT("%d-%m-%Y %H:%M:%S"));

        xTEST_EQ(std::tstring_t(xT("00-00-0 00:00:00.000")), m_sRv);
    }

    xTEST_CASE("DateTime(const DateTime &)")
    {
        DateTime datetime1(2010, 7, 8, 3, 15, 6, 111);
        DateTime datetime2(datetime1);
        m_sRv = datetime2.format(xT("%d-%m-%Y %H:%M:%S"));
        xTEST_EQ(std::tstring_t(xT("08-07-2010 03:15:06.111")), m_sRv);

        DateTime datetime(2010, 1, 14, 17, 0, 55, 666);
        m_sRv = datetime.format(xT("%d-%m-%Y %H:%M:%S"));
        xTEST_EQ(std::tstring_t(xT("14-01-2010 17:00:55.666")), m_sRv);
    }

    xTEST_CASE("DateTime(culonglong_t &)")
    {
        DateTime datetime(1000 * 60 * 60);
        m_sRv = datetime.format(xT("%d-%m-%Y %H:%M:%S"));
        xTEST_EQ(std::tstring_t(xT("00-00-0 01:00:00.000")), m_sRv);
    }

    xTEST_CASE("DateTime(cushort_t &, cushort_t &, cushort_t &, cushort_t &)")
    {
        DateTime datetime(12, 20, 37, 555);
        m_sRv = datetime.format(xT("%d-%m-%Y %H:%M:%S"));
        xTEST_EQ(std::tstring_t(xT("00-00-0 12:20:37.555")), m_sRv);
    }

    xTEST_CASE("DateTime(cushort_t &, cushort_t &, cushort_t &)")
    {
        DateTime datetime(2010, 7, 8);
        m_sRv = datetime.format(xT("%d-%m-%Y %H:%M:%S"));
        xTEST_EQ(std::tstring_t(xT("08-07-2010 00:00:00.000")), m_sRv);
    }

    xTEST_CASE("DateTime(cushort_t &, cushort_t &, cushort_t &, cushort_t &, cushort_t &, cushort_t &, cushort_t &)")
    {
        DateTime datetime(2010, 8, 18, 14, 0, 5, 777);
        m_sRv = datetime.format(xT("%d-%m-%Y %H:%M:%S"));
        xTEST_EQ(std::tstring_t(xT("18-08-2010 14:00:05.777")), m_sRv);
    }


    /*******************************************************************************
    *   public: validate
    *
    *******************************************************************************/


    /*******************************************************************************
    *   public: comparison operators
    *
    *******************************************************************************/

    xTEST_CASE("operator ==")
    {
        DateTime datetime1;
        DateTime datetime2;

        m_bRv = (datetime1 == datetime2);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("operator !=")
    {
        DateTime datetime1;
        DateTime datetime2;

        m_bRv = (datetime1 != datetime2);
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("operator <")
    {
        DateTime datetime1;
        DateTime datetime2;

        m_bRv = (datetime1 < datetime2);
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("operator <=")
    {
        DateTime datetime1;
        DateTime datetime2;

        m_bRv = (datetime1 <= datetime2);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("operator >")
    {
        DateTime datetime1;
        DateTime datetime2;

        m_bRv = (datetime1 > datetime2);
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("operator >=")
    {
        DateTime datetime1;
        DateTime datetime2;

        m_bRv = (datetime1 >= datetime2);
        xTEST_EQ(m_bRv, true);
    }


    /*******************************************************************************
    *   public: assignment operators
    *
    *******************************************************************************/

    xTEST_CASE("operator +=")
    {
        DateTime  datetime(0, 30, 0, 0);
        ulonglong_t msec = (1000 * 60) * 60; // 1 hour

        datetime = msec;
        m_sRv = datetime.format(xT("%d-%m-%Y %H:%M:%S"));
        xTEST_EQ(std::tstring_t(xT("00-00-0 01:00:00.000")), m_sRv);
    }

    xTEST_CASE("operator (=, +, -)")
    {
        DateTime datetime;

        datetime = DateTime() + DateTime(1000 * 60 * 60);
        m_sRv = datetime.format(xT("%d-%m-%Y %H:%M:%S"));
        xTEST_EQ(std::tstring_t(xT("00-00-0 01:00:00.000")), m_sRv);

        datetime = datetime - DateTime(1000 * 60 * 60 / 2);
        m_sRv = datetime.format(xT("%d-%m-%Y %H:%M:%S"));
        xTEST_EQ(std::tstring_t(xT("00-00-0 00:30:00.000")), m_sRv);
    }

    xTEST_CASE("operator +=")
    {
        DateTime datetime1(1, 0, 0, 0);
        DateTime datetime2(1, 30, 0, 0);

        datetime1 += datetime2;
        m_sRv = datetime1.format(xT("%d-%m-%Y %H:%M:%S"));
        xTEST_EQ(std::tstring_t(xT("00-00-0 02:30:00.000")), m_sRv);
    }

    xTEST_CASE("operator -=")
    {
        DateTime datetime1(1, 50, 0, 0);
        DateTime datetime2(1, 30, 0, 0);

        datetime1 -= datetime2;
        m_sRv = datetime1.format(xT("%d-%m-%Y %H:%M:%S"));
        xTEST_EQ(std::tstring_t(xT("00-00-0 00:20:00.000")), m_sRv);
    }


    /*******************************************************************************
    *   public: get, set
    *
    *******************************************************************************/

    xTEST_CASE("set get")
    {
        DateTime datetime;

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

    xTEST_CASE("toMsec")
    {
        // 1
        {
            m_ullRv = DateTime(2010, 1, 14, 17, 0, 55, 666).toMsec();
            xTEST_EQ(62522902855666ULL, m_ullRv);
        }

        // 2
        {
            culonglong_t msecs[] = {
                12234567890ULL, 2234567890ULL, 32345657890ULL, 4294567890ULL, 5234567890ULL,
                63565474567ULL, 7354234523ULL, 83451467547ULL, 9234436577ULL, 5354362463ULL
            };

            for (size_t i = 0; i < xARRAY_SIZE(msecs); ++ i) {
                m_ullRv = DateTime(msecs[i]).toMsec();
                xTEST_EQ(msecs[i], m_ullRv);
            }
        }
    }

    xTEST_CASE("set")
    {
        DateTime  datetime;
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

    xTEST_CASE("dayOfWeek")
    {
        m_iRv = DateTime(2011, 7, 25, 13, 0, 0, 0).dayOfWeek();
        xTEST_EQ(1, m_iRv);

        m_iRv = DateTime(2011, 7, 31, 0, 0, 0, 0).dayOfWeek();
        xTEST_EQ(0, m_iRv);

        m_iRv = DateTime(2011, 3, 18, 0, 0, 0, 0).dayOfWeek();
        xTEST_EQ(5, m_iRv);
    }

    /*******************************************************************************
    * static
    *
    *******************************************************************************/

    xTEST_CASE("Validator")
    {
        // TEST: DateTime::Validator::year()
        // TEST: DateTime::Validator::month()
        // TEST: DateTime::Validator::day()
        // TEST: DateTime::Validator::hour()
        // TEST: DateTime::Validator::minute()
        // TEST: DateTime::Validator::second()
        // TEST: DateTime::Validator::msec()
        // TEST: DateTime::Validator::weekDay()
        // TEST: DateTime::Validator::time()
        // TEST: DateTime::Validator::date()
        // TEST: DateTime::Validator::datetime()
        // TEST: DateTime::Validator::dateOrTime()

        // valid data
        {
            cushort_t valid[][7] = {
                // year, month, day, hour, minute, second, msec
                { 2011,  0,     1,   0,    0,      0,      0 },
                { 1978,  7,     21,  4,    55,     45,     13  },
                { 1956,  1,     10,  13,   59,     59,     998 },
                { 2011,  2,     1,   12,   45,     5,      1   },
                { 2011,  3,     2,   11,   30,     1,      125 },
                { 2011,  4,     3,   10,   25,     30,     256 },
                { 2011,  5,     4,   9,    8,      45,     589 },
                { 2011,  6,     5,   8,    4,      54,     258 },
                { 2011,  7,     6,   7,    1,      58,     951 },
                { 2011,  11,    31,  23,   59,     60,     999 }
            };

            for (size_t i = 0; i < xARRAY_SIZE(valid); ++ i) {
                int_t year   = valid[i][0];
                int_t month  = valid[i][1];
                int_t day    = valid[i][2];
                int_t hour   = valid[i][3];
                int_t minute = valid[i][4];
                int_t second = valid[i][5];
                int_t msec   = valid[i][6];

                m_bRv = DateTime::Validator::datetime(year, month, day, hour, minute, second, msec);
                xTEST_EQ(m_bRv, true);
            }
        }

        // non valid data
        {
        #if xTEST_IGNORE
            cushort_t nonValid[][7] = {
                // year, month, day, hour, minute, second, msec
                { 2011,  0,     1,   0,    0,      0,      0 },
                { 2011,  0,     1,   0,    0,      0,      0 },
                { 2011,  0,     1,   0,    0,      0,      0 },

                { 1978,  7,     21,  4,    55,     45,     13  },
                { 1978,  7,     21,  4,    55,     45,     13  },
                { 1978,  7,     21,  4,    55,     45,     13  },

                { 1956,  1,     10,  13,   59,     59,     998 },
                { 1956,  1,     10,  13,   59,     59,     998 },
                { 1956,  1,     10,  13,   59,     59,     998 },

                { 2011,  2,     1,   12,   45,     5,      1   },
                { 2011,  2,     1,   12,   45,     5,      1   },
                { 2011,  2,     1,   12,   45,     5,      1   },

                { 2011,  3,     2,   11,   30,     1,      125 },
                { 2011,  3,     2,   11,   30,     1,      125 },
                { 2011,  3,     2,   11,   30,     1,      125 },

                { 2011,  4,     3,   10,   25,     30,     256 },
                { 2011,  4,     3,   10,   25,     30,     256 },
                { 2011,  4,     3,   10,   25,     30,     256 },

                { 2011,  5,     4,   9,    8,      45,     589 },
                { 2011,  5,     4,   9,    8,      45,     589 },
                { 2011,  5,     4,   9,    8,      45,     589 },

                { 2011,  6,     5,   8,    4,      54,     258 },
                { 2011,  6,     5,   8,    4,      54,     258 },
                { 2011,  6,     5,   8,    4,      54,     258 },

                { 2011,  7,     6,   7,    1,      58,     951 },
                { 2011,  7,     6,   7,    1,      58,     951 },
                { 2011,  7,     6,   7,    1,      58,     951 },

                { 2011,  11,    31,  23,   59,     60,     999 },
                { 2011,  11,    31,  23,   59,     60,     999 },
                { 2011,  11,    31,  23,   59,     60,     999 }
            };

            for (size_t i = 0; i < xARRAY_SIZE(nonValid); ++ i) {
                int_t year   = nonValid[i][0];
                int_t month  = nonValid[i][1];
                int_t day    = nonValid[i][2];
                int_t hour   = nonValid[i][3];
                int_t minute = nonValid[i][4];
                int_t second = nonValid[i][5];
                int_t msec   = nonValid[i][6];

                m_bRv = DateTime::Validator::datetime(year, month, day, hour, minute, second, msec);
                xTEST_EQ(m_bRv, false);
            }
        #endif
        }
    }

    xTEST_CASE("current")
    {
        // 1
        {
            DateTime datetimeNow;

            m_sRv = datetimeNow.current().format(xT("%d-%m-%Y %H:%M:%S"));
            xTEST_DIFF(std::tstring_t(xT("00-00-0000 0:00:00:000")), m_sRv);
        }

        // 2
        for (size_t i = 0; i < 100; ++ i) {
            DateTime start;
            DateTime stop;

            start = DateTime::current();
            {
                for (int_t x = 0; x < 100; ++ x) {
                    for (int_t y = 0; y < 20; ++ y) {
                        int_t z = 0;

                        z++; --z;
                    }
                }
            }
            stop = DateTime::current();

            xTEST_EQ(true, stop >= start);
        }
    }

    xTEST_CASE("daysInMonth")
    {
        for (int_t y = 0; y < 3000; ++ y) {
            for (int_t m = 0; m < 12; ++ m) {
                m_iRv = DateTime::daysInMonth(y, m);

                if (2 == m && DateTime::isLeapYear(y)) {
                    xTEST_EQ(29, m_iRv);
                } else {
                    int_t daysOfMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

                    xTEST_EQ(m_iRv, daysOfMonth[m]);
                }
            } // m
        } // y
    }

    xTEST_CASE("isLeapYear")
    {
        // valid
        {
            cint_t valid[] = {
                1812, 1828, 1904
            };

            for (size_t i = 0; i < xARRAY_SIZE(valid); ++ i) {
                m_bRv = DateTime::isLeapYear(valid[i]);
                xTEST_EQ(m_bRv, true);
            }
        }

        // non valid
        {
            cint_t nonValid[] = {
                1813, 1829, 1905
            };

            for (size_t i = 0; i < xARRAY_SIZE(nonValid); ++ i) {
                m_bRv = DateTime::isLeapYear(nonValid[i]);
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("filetimeToInt64")
    {
    #if xENV_WIN
        const FILETIME time = {100, 200};

        m_ullRv = DateTime::filetimeToInt64(time);
        xTEST_EQ( , m_ullRv);
    #endif
    }

    xTEST_CASE("unixTimeToFileTime")
    {
    #if xENV_WIN
        const time_t unixTime = 1000;
        FILETIME     fileTime = {0};

        DateTime::unixTimeToFileTime(unixTime, &fileTime);
    #endif
    }

    xTEST_CASE("fileTimeToUnixTime")
    {
    #if xENV_WIN
        time_t   unixTime = 0;
        FILETIME fileTime = {0};

        unixTime = DateTime::fileTimeToUnixTime(fileTime);
        xTEST_EQ(static_cast<time_t>( -11644473600 ), unixTime);
    #endif
    }


    /*******************************************************************************
    *   other
    *
    *******************************************************************************/

    xTEST_CASE("zodiacSign")
    {
        // TEST: DateTime::zodiacSign

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

        const Data3<int_t, int_t, std::tstring_t> data[] = {
            { 7, 31, xT("Лев")   },
            { 5, 18, xT("Телец") }
        };

        for (std::size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::ctstring_t str1 = DateTime::zodiacSign(data[i].test1, data[i].test2);
            xTEST_EQ(str1, data[i].expect);
        }
    }

    xTEST_CASE("monthStr")
    {
        // isShortName = false
        m_sRv = DateTime::monthStr(0, false);
        xTEST_EQ(std::tstring_t(xT("January")), m_sRv);
        m_sRv = DateTime::monthStr(1, false);
        xTEST_EQ(std::tstring_t(xT("February")), m_sRv);
        m_sRv = DateTime::monthStr(2, false);
        xTEST_EQ(std::tstring_t(xT("March")), m_sRv);
        m_sRv = DateTime::monthStr(3, false);
        xTEST_EQ(std::tstring_t(xT("April")), m_sRv);
        m_sRv = DateTime::monthStr(4, false);
        xTEST_EQ(std::tstring_t(xT("May")), m_sRv);
        m_sRv = DateTime::monthStr(5, false);
        xTEST_EQ(std::tstring_t(xT("June")), m_sRv);
        m_sRv = DateTime::monthStr(6, false);
        xTEST_EQ(std::tstring_t(xT("July")), m_sRv);
        m_sRv = DateTime::monthStr(7, false);
        xTEST_EQ(std::tstring_t(xT("August")), m_sRv);
        m_sRv = DateTime::monthStr(8, false);
        xTEST_EQ(std::tstring_t(xT("September")), m_sRv);
        m_sRv = DateTime::monthStr(9, false);
        xTEST_EQ(std::tstring_t(xT("October")), m_sRv);
        m_sRv = DateTime::monthStr(10, false);
        xTEST_EQ(std::tstring_t(xT("November")), m_sRv);
        m_sRv = DateTime::monthStr(11, false);
        xTEST_EQ(std::tstring_t(xT("December")), m_sRv);

        // isShortName = true
        m_sRv = DateTime::monthStr(0, true);
        xTEST_EQ(std::tstring_t(xT("Jan")), m_sRv);
        m_sRv = DateTime::monthStr(1, true);
        xTEST_EQ(std::tstring_t(xT("Feb")), m_sRv);
        m_sRv = DateTime::monthStr(2, true);
        xTEST_EQ(std::tstring_t(xT("Mar")), m_sRv);
        m_sRv = DateTime::monthStr(3, true);
        xTEST_EQ(std::tstring_t(xT("Apr")), m_sRv);
        m_sRv = DateTime::monthStr(4, true);
        xTEST_EQ(std::tstring_t(xT("May")), m_sRv);
        m_sRv = DateTime::monthStr(5, true);
        xTEST_EQ(std::tstring_t(xT("Jun")), m_sRv);
        m_sRv = DateTime::monthStr(6, true);
        xTEST_EQ(std::tstring_t(xT("Jul")), m_sRv);
        m_sRv = DateTime::monthStr(7, true);
        xTEST_EQ(std::tstring_t(xT("Aug")), m_sRv);
        m_sRv = DateTime::monthStr(8, true);
        xTEST_EQ(std::tstring_t(xT("Sep")), m_sRv);
        m_sRv = DateTime::monthStr(9, true);
        xTEST_EQ(std::tstring_t(xT("Oct")), m_sRv);
        m_sRv = DateTime::monthStr(10, true);
        xTEST_EQ(std::tstring_t(xT("Nov")), m_sRv);
        m_sRv = DateTime::monthStr(11, true);
        xTEST_EQ(std::tstring_t(xT("Dec")), m_sRv);
    }

    xTEST_CASE("monthNum")
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
            m_iRv = DateTime::monthNum(months[i][0], false);
            xTEST_EQ(int_t(i), m_iRv);

            m_iRv = DateTime::monthNum(months[i][1], true);
            xTEST_EQ(int_t(i), m_iRv);

            if (xT("May") == months[i][0] || xT("May") == months[i][1]) {
                m_iRv = DateTime::monthNum(months[i][0], true);
                xTEST_EQ(int_t(i), m_iRv);

                m_iRv = DateTime::monthNum(months[i][1], false);
                xTEST_EQ(int_t(i), m_iRv);
            } else {
                m_iRv = DateTime::monthNum(months[i][0], true);
                xTEST_EQ(- 1, m_iRv);

                m_iRv = DateTime::monthNum(months[i][1], false);
                xTEST_EQ(- 1, m_iRv);
            }
        }
    }

    xTEST_CASE("weekDayStr")
    {
        // isShortName = false
        m_sRv = DateTime::weekDayStr(0, false);
        xTEST_EQ(std::tstring_t(xT("Sunday")), m_sRv);
        m_sRv = DateTime::weekDayStr(1, false);
        xTEST_EQ(std::tstring_t(xT("Monday")), m_sRv);
        m_sRv = DateTime::weekDayStr(2, false);
        xTEST_EQ(std::tstring_t(xT("Tuesday")), m_sRv);
        m_sRv = DateTime::weekDayStr(3, false);
        xTEST_EQ(std::tstring_t(xT("Wednesday")), m_sRv);
        m_sRv = DateTime::weekDayStr(4, false);
        xTEST_EQ(std::tstring_t(xT("Thursday")), m_sRv);
        m_sRv = DateTime::weekDayStr(5, false);
        xTEST_EQ(std::tstring_t(xT("Friday")), m_sRv);
        m_sRv = DateTime::weekDayStr(6, false);
        xTEST_EQ(std::tstring_t(xT("Saturday")), m_sRv);

        // isShortName = true
        m_sRv = DateTime::weekDayStr(0, true);
        xTEST_EQ(std::tstring_t(xT("Sun")), m_sRv);
        m_sRv = DateTime::weekDayStr(1, true);
        xTEST_EQ(std::tstring_t(xT("Mon")), m_sRv);
        m_sRv = DateTime::weekDayStr(2, true);
        xTEST_EQ(std::tstring_t(xT("Tue")), m_sRv);
        m_sRv = DateTime::weekDayStr(3, true);
        xTEST_EQ(std::tstring_t(xT("Wed")), m_sRv);
        m_sRv = DateTime::weekDayStr(4, true);
        xTEST_EQ(std::tstring_t(xT("Thu")), m_sRv);
        m_sRv = DateTime::weekDayStr(5, true);
        xTEST_EQ(std::tstring_t(xT("Fri")), m_sRv);
        m_sRv = DateTime::weekDayStr(6, true);
        xTEST_EQ(std::tstring_t(xT("Sat")), m_sRv);
    }

    xTEST_CASE("weekDayNum")
    {
        std::ctstring_t days[7][2] = {
            { xT("Monday"),     xT("Mon") },
            { xT("Tuesday"),    xT("Tue"} ),
            { xT("Wednesday"),  xT("Wed") },
            { xT("Thursday"),   xT("Thu") },
            { xT("Friday"),     xT("Fri") },
            { xT("Saturday"),   xT("Sat") },
            { xT("Sunday"),     xT("Sun") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(days); ++ i) {
            m_iRv = DateTime::weekDayNum(days[i][0], false);
            xTEST_EQ((int_t)i, m_iRv);

            m_iRv = DateTime::weekDayNum(days[i][1], true);
            xTEST_EQ((int_t)i, m_iRv);

            m_iRv = DateTime::weekDayNum(days[i][0], true);
            xTEST_EQ(- 1, m_iRv);

            m_iRv = DateTime::weekDayNum(days[i][1], false);
            xTEST_EQ(- 1, m_iRv);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
