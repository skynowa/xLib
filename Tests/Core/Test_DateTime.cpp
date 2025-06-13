/**
 * \file   Test_DateTime.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_DateTime)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_DateTime::unit()
{
	std::ctstring_t dtFormat =
	#if xENV_APPLE
		xT("%d-%m-%Y %H:%M:%S");
	#else
		xT("%d-%m-%4Y %H:%M:%S");
	#endif

    xTEST_CASE("DateTimeValidator")
    {
        // TEST: DateTimeValidator::year()
        // TEST: DateTimeValidator::month()
        // TEST: DateTimeValidator::day()
        // TEST: DateTimeValidator::hour()
        // TEST: DateTimeValidator::minute()
        // TEST: DateTimeValidator::second()
        // TEST: DateTimeValidator::msec()
        // TEST: DateTimeValidator::weekDay()
        // TEST: DateTimeValidator::time()
        // TEST: DateTimeValidator::date()
        // TEST: DateTimeValidator::datetime()
        // TEST: DateTimeValidator::dateOrTime()

        // valid data
        {
            cushort_t valid[][7]
            {
                // year, month, day, hour, minute, second, msec
                {2011, 1,  1,  0,  0,  0,  0},
                {1978, 7,  21, 4,  55, 45, 13},
                {1956, 1,  10, 13, 59, 59, 998},
                {2011, 2,  1,  12, 45, 5,  1},
                {2011, 3,  2,  11, 30, 1,  125},
                {2011, 4,  3,  10, 25, 30, 256},
                {2011, 5,  4,  9,  8,  45, 589},
                {2011, 6,  5,  8,  4,  54, 258},
                {2011, 7,  6,  7,  1,  58, 951},
                {2011, 11, 31, 23, 59, 59, 999}
            };

            for (size_t i = 0; i < xARRAY_SIZE(valid); ++ i) {
                cint_t year   = valid[i][0];
                cint_t month  = valid[i][1];
                cint_t day    = valid[i][2];
                cint_t hour   = valid[i][3];
                cint_t minute = valid[i][4];
                cint_t second = valid[i][5];
                cint_t msec   = valid[i][6];

                m_bRv = DateTimeValidator::datetime(year, month, day, hour, minute, second, msec);
                xTEST(m_bRv);
            }
        }

        // non valid data
        {
            cushort_t nonValid[][7]
            {
                // year, month, day, hour, minute, second, msec

                // year
                {static_cast<ushort_t>(-1),    0,  1,  0,  0,  0,  0},
                {10000, 0,  1,  0,  0,  0,  0},
				// month
                {1978,  static_cast<ushort_t>(-1), 21, 4,  55, 45, 13},
                {1978,  13, 21, 4,  55, 45, 13},
				// day
                {1956,  1,  0,  13, 59, 59, 998},
                {1956,  1,  32, 13, 59, 59, 998},
				// hour
                {2011,  2,  1,  static_cast<ushort_t>(-1), 45, 5,  1},
                {2011,  2,  1,  24, 45, 5,  1},
				// minute
                {2011,  3,  2,  11, static_cast<ushort_t>(-1), 1,  125},
                {2011,  3,  2,  11, 60, 1,  125},
				// second
                {2011,  4,  3,  10, 25, static_cast<ushort_t>(-1), 256},
                {2011,  4,  3,  10, 25, 61, 256},
				// msec
                {2011,  5,  4,  9,  8,  45, static_cast<ushort_t>(-1)},
                {2011,  5,  4,  9,  8,  45, 10000}
            };

            for (size_t i = 0; i < xARRAY_SIZE(nonValid); ++ i) {
                cint_t year   = nonValid[i][0];
                cint_t month  = nonValid[i][1];
                cint_t day    = nonValid[i][2];
                cint_t hour   = nonValid[i][3];
                cint_t minute = nonValid[i][4];
                cint_t second = nonValid[i][5];
                cint_t msec   = nonValid[i][6];

                // LogCout() << xTRACE_VAR_8(i, year, month, day, hour, minute, second, msec);

                m_bRv = DateTimeValidator::datetime(year, month, day, hour, minute, second, msec);
                xTEST(!m_bRv);
            }
        }
    }

    /*******************************************************************************
    *   public: constructors, destructor
    *
    *******************************************************************************/

    xTEST_CASE("DateTime")
    {
        DateTime datetime;
        m_sRv = datetime.format(dtFormat);
        /// TODO: xTEST_EQ(m_sRv, std::tstring_t(xT("01-01-0000 00:00:00.000")));
    }

    xTEST_CASE("DateTime(const DateTime &)")
    {
        DateTime datetime1(2010, 7, 8, 3, 15, 6, 111);
        DateTime datetime2(datetime1);

        m_sRv = datetime2.format(dtFormat);
        xTEST_EQ(m_sRv, std::tstring_t(xT("08-07-2010 03:15:06.111")));

        DateTime datetime(2010, 1, 14, 17, 0, 55, 666);
        m_sRv = datetime.format(dtFormat);
        xTEST_EQ(m_sRv, std::tstring_t(xT("14-01-2010 17:00:55.666")));
    }

    xTEST_CASE("DateTime(culonglong_t)")
    {
        DateTime datetime(1000 * 60 * 60);

		m_sRv = datetime.format(dtFormat);
        xTEST_EQ(m_sRv, std::tstring_t(xT("00-00-0000 01:00:00.000")));
    }

    xTEST_CASE("DateTime(cushort_t, cushort_t, cushort_t, cushort_t)")
    {
        DateTime datetime(12, 20, 37, 555);

        m_sRv = datetime.format(dtFormat);
        xTEST_EQ(m_sRv, std::tstring_t(xT("00-00-0000 12:20:37.555")));
    }

    xTEST_CASE("DateTime(cushort_t, cushort_t, cushort_t)")
    {
        DateTime datetime(2010, 7, 8);

        m_sRv = datetime.format(dtFormat);
        xTEST_EQ(m_sRv, std::tstring_t(xT("08-07-2010 00:00:00.000")));
    }

    xTEST_CASE("DateTime(cushort_t, cushort_t, cushort_t, cushort_t, cushort_t, cushort_t, cushort_t)")
    {
        DateTime datetime(2010, 8, 18, 14, 0, 5, 777);

        m_sRv = datetime.format(dtFormat);
        xTEST_EQ(m_sRv, std::tstring_t(xT("18-08-2010 14:00:05.777")));
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
        xTEST(m_bRv);
    }

    xTEST_CASE("operator !=")
    {
        DateTime datetime1;
        DateTime datetime2;

        m_bRv = (datetime1 != datetime2);
        xTEST(!m_bRv);
    }

    xTEST_CASE("operator <")
    {
        DateTime datetime1;
        DateTime datetime2;

        m_bRv = (datetime1 < datetime2);
        xTEST(!m_bRv);
    }

    xTEST_CASE("operator <=")
    {
        DateTime datetime1;
        DateTime datetime2;

        m_bRv = (datetime1 <= datetime2);
        xTEST(m_bRv);
    }

    xTEST_CASE("operator >")
    {
        DateTime datetime1;
        DateTime datetime2;

        m_bRv = (datetime1 > datetime2);
        xTEST(!m_bRv);
    }

    xTEST_CASE("operator >=")
    {
        DateTime datetime1;
        DateTime datetime2;

        m_bRv = (datetime1 >= datetime2);
        xTEST(m_bRv);
    }


    /*******************************************************************************
    *   public: assignment operators
    *
    *******************************************************************************/

    xTEST_CASE("operator +=")
    {
        DateTime  datetime(0, 30, 0, 0);

        culonglong_t msec = (1000 * 60) * 60; // 1 hour

        datetime = msec;
        m_sRv = datetime.format(dtFormat);
        xTEST_EQ(m_sRv, std::tstring_t(xT("00-00-0000 01:00:00.000")));
    }

    xTEST_CASE("operator (=, +, -)")
    {
    	// TODO: test
	#if 0
		DateTime datetime;

		datetime = DateTime() + DateTime(1000 * 60 * 60);
		m_sRv = datetime.format(dtFormat);
		xTEST_EQ(m_sRv, std::tstring_t(xT("00-01-0000 01:00:00.000")));

		datetime = datetime - DateTime(1000 * 60 * 60 / 2);
		m_sRv = datetime.format(dtFormat);
		xTEST_EQ(m_sRv, std::tstring_t(xT("00-01-0000 00:30:00.000")));
	#endif
    }

    xTEST_CASE("operator +=")
    {
        DateTime datetime1(1, 0, 0, 0);
        DateTime datetime2(1, 30, 0, 0);

        datetime1 += datetime2;
        m_sRv = datetime1.format(dtFormat);
        xTEST_EQ(m_sRv, std::tstring_t(xT("00-00-0000 02:30:00.000")));
    }

    xTEST_CASE("operator -=")
    {
        DateTime datetime1(1, 50, 0, 0);
        DateTime datetime2(1, 30, 0, 0);

        datetime1 -= datetime2;
        m_sRv = datetime1.format(dtFormat);
        xTEST_EQ(m_sRv, std::tstring_t(xT("00-00-0000 00:20:00.000")));
    }


    /*******************************************************************************
    *   public: get
    *
    *******************************************************************************/

    xTEST_CASE("get")
    {
		{
			culonglong_t oneHourSec {1000 * 60 * 60};
			cint_t       oneHour    {1};

			DateTime datetime(oneHourSec);

			int_t year   {};
			int_t month  {};
			int_t day    {};
			int_t hour   {};
			int_t minute {};
			int_t second {};
			int_t msec   {};

			datetime.get(&year, &month, &day, &hour, &minute, &second, &msec);
			xTEST_EQ(year,   0);
			xTEST_EQ(month,  0);
			xTEST_EQ(day,    0);
			xTEST_EQ(hour,   oneHour);
			xTEST_EQ(minute, 0);
			xTEST_EQ(second, 0);
			xTEST_EQ(msec,   0);
		}

		{
			cint_t year   = 2010;
			cint_t month  = 1;
			cint_t day    = 14;
			cint_t hour   = 17;
			cint_t minute = 0;
			cint_t second = 55;
			cint_t msec   = 666;

			DateTime datetime(year, month, day, hour, minute, second, msec);

			int_t year_   {};
			int_t month_  {};
			int_t day_    {};
			int_t hour_   {};
			int_t minute_ {};
			int_t second_ {};
			int_t msec_   {};

			datetime.get(&year_, &month_, &day_, &hour_, &minute_, &second_, &msec_);
			xTEST_EQ(year_,   year);
			xTEST_EQ(month_,  month);
			xTEST_EQ(day_,    day);
			xTEST_EQ(hour_,   hour);
			xTEST_EQ(minute_, minute);
			xTEST_EQ(second_, second);
			xTEST_EQ(msec_,   msec);
		}
    }

    xTEST_CASE("toMsec")
    {
        // 1
        {
            m_ullRv = DateTime(2010, 1, 14, 17, 0, 55, 666).toMsec();
            xTEST_EQ(m_ullRv, 62522902855666ULL);
        }

        // 2
        {
            culonglong_t msecs[]
            {
                12234567890ULL, 2234567890ULL, 32345657890ULL, 4294567890ULL, 5234567890ULL,
                63565474567ULL, 7354234523ULL, 83451467547ULL, 9234436577ULL, 5354362463ULL
            };

            for (size_t i = 0; i < xARRAY_SIZE(msecs); ++ i) {
                m_ullRv = DateTime(msecs[i]).toMsec();
                xTEST_EQ(m_ullRv, msecs[i]);
            }
        }
    }

    xTEST_CASE("dayOfWeek")
    {
        m_iRv = DateTime(2011, 7, 25, 13, 0, 0, 0).dayOfWeek();
        xTEST_EQ(m_iRv, 1);

        m_iRv = DateTime(2011, 7, 31, 0, 0, 0, 0).dayOfWeek();
        xTEST_EQ(m_iRv, 0);

        m_iRv = DateTime(2011, 3, 18, 0, 0, 0, 0).dayOfWeek();
        xTEST_EQ(m_iRv, 5);
    }

    /*******************************************************************************
    * static
    *
    *******************************************************************************/

    xTEST_CASE("current")
    {
        // 1
        {
            DateTime datetimeNow;

            m_sRv = datetimeNow.current().format(dtFormat);
            xTEST_DIFF(m_sRv, std::tstring_t(xT("00-00-0000 0:00:00:000")));
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

            xTEST(stop >= start);
        }
    }

    xTEST_CASE("daysInMonth")
    {
        for (int_t y = 0; y < 3000; ++ y) {
            for (int_t m = 0; m < 12; ++ m) {
                m_iRv = DateTime::daysInMonth(y, m);

                if (2 == m && DateTime::isLeapYear(y)) {
                    xTEST_EQ(m_iRv, 29);
                } else {
                    cint_t daysOfMonth[] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

                    xTEST_EQ(m_iRv, daysOfMonth[m]);
                }
            } // m
        } // y
    }

    xTEST_CASE("isLeapYear")
    {
        // valid
        {
            cint_t valid[] {1812, 1828, 1904};

            for (size_t i = 0; i < xARRAY_SIZE(valid); ++ i) {
                m_bRv = DateTime::isLeapYear(valid[i]);
                xTEST(m_bRv);
            }
        }

        // non valid
        {
            cint_t nonValid[] {1813, 1829, 1905};

            for (size_t i = 0; i < xARRAY_SIZE(nonValid); ++ i) {
                m_bRv = DateTime::isLeapYear(nonValid[i]);
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("fileToInt64")
    {
    #if xENV_WIN
        const FILETIME time {100, 200};

        m_ullRv = DateTime::fileToInt64(time);
        xTEST_EQ(m_ullRv, 0ULL);   // TODO: test - fix
    #endif
    }

    xTEST_CASE("unixToFile")
    {
    #if xENV_WIN
        const time_t unixTime {1000};
        FILETIME     fileTime {};

        DateTime::unixToFile(unixTime, &fileTime);
    #endif
    }

    xTEST_CASE("fileToUnix")
    {
    #if xENV_WIN
        time_t   unixTime {};
        FILETIME fileTime {};

        unixTime = DateTime::fileToUnix(fileTime);
        xTEST_EQ(unixTime, static_cast<time_t>( -11644473600 ));
    #endif
    }


    /*******************************************************************************
    *   other
    *
    *******************************************************************************/

    xTEST_CASE("monthStr")
    {
		// isShortName = false
		m_sRv = DateTime::monthStr(1, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("January")));

		m_sRv = DateTime::monthStr(2, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("February")));

		m_sRv = DateTime::monthStr(3, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("March")));

		m_sRv = DateTime::monthStr(4, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("April")));

		m_sRv = DateTime::monthStr(5, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("May")));

		m_sRv = DateTime::monthStr(6, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("June")));

		m_sRv = DateTime::monthStr(7, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("July")));

		m_sRv = DateTime::monthStr(8, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("August")));

		m_sRv = DateTime::monthStr(9, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("September")));

		m_sRv = DateTime::monthStr(10, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("October")));

		m_sRv = DateTime::monthStr(11, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("November")));

		m_sRv = DateTime::monthStr(12, false);
		xTEST_EQ(m_sRv, std::tstring_t(xT("December")));

		// isShortName = true
		m_sRv = DateTime::monthStr(1, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("Jan")));

		m_sRv = DateTime::monthStr(2, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("Feb")));

		m_sRv = DateTime::monthStr(3, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("Mar")));

		m_sRv = DateTime::monthStr(4, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("Apr")));

		m_sRv = DateTime::monthStr(5, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("May")));

		m_sRv = DateTime::monthStr(6, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("Jun")));

		m_sRv = DateTime::monthStr(7, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("Jul")));

		m_sRv = DateTime::monthStr(8, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("Aug")));

		m_sRv = DateTime::monthStr(9, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("Sep")));

		m_sRv = DateTime::monthStr(10, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("Oct")));

		m_sRv = DateTime::monthStr(11, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("Nov")));

		m_sRv = DateTime::monthStr(12, true);
		xTEST_EQ(m_sRv, std::tstring_t(xT("Dec")));
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
            xTEST_EQ(m_iRv, int_t(i));

            m_iRv = DateTime::monthNum(months[i][1], true);
            xTEST_EQ(m_iRv, int_t(i));

            if (xT("May") == months[i][0] || xT("May") == months[i][1]) {
                m_iRv = DateTime::monthNum(months[i][0], true);
                xTEST_EQ(m_iRv, int_t(i));

                m_iRv = DateTime::monthNum(months[i][1], false);
                xTEST_EQ(m_iRv, int_t(i));
            } else {
                m_iRv = DateTime::monthNum(months[i][0], true);
                xTEST_EQ(m_iRv, - 1);

                m_iRv = DateTime::monthNum(months[i][1], false);
                xTEST_EQ(m_iRv, - 1);
            }
        }
    }

    xTEST_CASE("weekDayStr")
    {
        // isShortName = false
        m_sRv = DateTime::weekDayStr(0, false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Sunday")));

        m_sRv = DateTime::weekDayStr(1, false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Monday")));

        m_sRv = DateTime::weekDayStr(2, false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Tuesday")));

        m_sRv = DateTime::weekDayStr(3, false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Wednesday")));

        m_sRv = DateTime::weekDayStr(4, false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Thursday")));

        m_sRv = DateTime::weekDayStr(5, false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Friday")));

        m_sRv = DateTime::weekDayStr(6, false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Saturday")));

        // isShortName = true
        m_sRv = DateTime::weekDayStr(0, true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Sun")));

        m_sRv = DateTime::weekDayStr(1, true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Mon")));

        m_sRv = DateTime::weekDayStr(2, true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Tue")));

        m_sRv = DateTime::weekDayStr(3, true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Wed")));

        m_sRv = DateTime::weekDayStr(4, true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Thu")));

        m_sRv = DateTime::weekDayStr(5, true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Fri")));

        m_sRv = DateTime::weekDayStr(6, true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Sat")));
    }

    xTEST_CASE("weekDayNum")
    {
        std::ctstring_t days[7][2]
        {
            { xT("Monday"),     xT("Mon") },
            { xT("Tuesday"),    xT("Tue") },
            { xT("Wednesday"),  xT("Wed") },
            { xT("Thursday"),   xT("Thu") },
            { xT("Friday"),     xT("Fri") },
            { xT("Saturday"),   xT("Sat") },
            { xT("Sunday"),     xT("Sun") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(days); ++ i) {
            m_iRv = DateTime::weekDayNum(days[i][0], false);
            xTEST_EQ(m_iRv, (int_t)i);

            m_iRv = DateTime::weekDayNum(days[i][1], true);
            xTEST_EQ(m_iRv, (int_t)i);

            m_iRv = DateTime::weekDayNum(days[i][0], true);
            xTEST_EQ(m_iRv, - 1);

            m_iRv = DateTime::weekDayNum(days[i][1], false);
            xTEST_EQ(m_iRv, - 1);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
