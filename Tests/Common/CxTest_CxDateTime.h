/****************************************************************************
* Class name:  CxTest_CxDateTime
* Description: testing CxDateTime
* File name:   CxTest_CxDateTime.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxDateTimeH
#define CxTest_CxDateTimeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxDateTime.h>
//---------------------------------------------------------------------------
class CxTest_CxDateTime :
    public CxTest
{
    public:
        CxTest_CxDateTime();
        virtual     ~CxTest_CxDateTime();

        virtual     BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxDateTime (comment)
CxTest_CxDateTime::CxTest_CxDateTime() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxDateTime (comment)
CxTest_CxDateTime::~CxTest_CxDateTime() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL CxTest_CxDateTime::bUnit() {
    /****************************************************************************
    *   public: constructors, destructor
    *
    *****************************************************************************/

    //-------------------------------------
    //CxDateTime()
    {
        CxDateTime dtDT;
        m_sRes = dtDT.sFormat(CxDateTime::ftDateTime);
        xASSERT(xT("00.00.0000 0:00:00:000") == m_sRes);
    }

    //-------------------------------------
    //CxDateTime(const tString &csDT, EFormatType ftFormat)
    {
        const CxDateTime::EFormatType caftFormats[] = {
            ////CxDateTime::ftTime,     //HH.MM.SS.MMM
            ////CxDateTime::ftDate,     //DD.MM.YYYY
            ////CxDateTime::ftDateTime, //DD.MM.YYYY HH.MM.SS.MMM
            CxDateTime::ftRFC1123   //Wdy, DD Mon YYYY HH:MM:SS GMT
        };

        const tString casDateTime[] = {
            ////xT("23.05.33.555"),             //HH.MM.SS.MMM
            ////xT("31.07.1978"),               //DD.MM.YYYY
            ////xT("24.01.1977 12.12.12.222"),  //DD.MM.YYYY HH.MM.SS.MMM
            xT("Wed, 23 Mar 2011 15:05:49 GMT")  //Wdy, DD Mon YYYY HH:MM:SS GMT
        };
        xASSERT(xARRAY_SIZE(caftFormats) == xARRAY_SIZE(casDateTime));

        for (size_t i = 0; i < xARRAY_SIZE(caftFormats); ++ i) {
            CxDateTime dtDT(casDateTime[i], caftFormats[i]);

            m_sRes = dtDT.sFormat(caftFormats[i]);
            xASSERT_MSG(casDateTime[i] == m_sRes, m_sRes);
        }
    }

    //CxDateTime(const CxDateTime &dtDT);
    {
        CxDateTime dtDT1(2010, 7, 8, 3, 15, 6, 111);
        CxDateTime dtDT2(dtDT1);
        m_sRes = dtDT2.sFormat(CxDateTime::ftDateTime);
        xASSERT(xT("08.07.2010 3:15:06:111") == m_sRes);

        CxDateTime dtDT(2010, 1, 14, 17, 0, 55, 666);
        m_sRes = dtDT.sFormat(CxDateTime::ftDateTime);
        xASSERT(xT("14.01.2010 17:00:55:666") == m_sRes);
    }

    //CxDateTime(ULONGLONG ullMSec);
    {
        CxDateTime dtDT(1000 * 60 * 60);
        m_sRes = dtDT.sFormat(CxDateTime::ftDateTime);
        xASSERT_MSG(xT("00.00.0000 1:00:00:000") == m_sRes, m_sRes);
    }

    //CxDateTime(USHORT usHour, USHORT usMinute, USHORT usSecond, USHORT usMSec);
    {
        CxDateTime dtDT(12, 20, 37, 555);
        m_sRes = dtDT.sFormat(CxDateTime::ftDateTime);
        xASSERT(xT("00.00.0000 12:20:37:555") == m_sRes);
    }

    //CxDateTime(USHORT usYear, USHORT usMonth, USHORT usDay);
    {
        CxDateTime dtDT(2010, 7, 8);
        m_sRes = dtDT.sFormat(CxDateTime::ftDateTime);
        xASSERT(xT("08.07.2010 0:00:00:000") == m_sRes);
    }

    //CxDateTime(USHORT usYear, USHORT usMonth, USHORT usDay, USHORT usHour, USHORT usMinute, USHORT usSecond, USHORT usMSec);
    {
        CxDateTime dtDT(2010, 8, 18, 14, 0, 5, 777);
        m_sRes = dtDT.sFormat(CxDateTime::ftDateTime);
        xASSERT(xT("18.08.2010 14:00:05:777") == m_sRes);
    }


    /****************************************************************************
    *   public: comparison operators
    *
    *****************************************************************************/

    //-------------------------------------
    //operator ==
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRes = (dtDt1 == dtDt2);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //operator !=
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRes = (dtDt1 != dtDt2);
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //operator <
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRes = (dtDt1 < dtDt2);
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //operator <=
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRes = (dtDt1 <= dtDt2);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //operator >
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRes = (dtDt1 > dtDt2);
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //operator >=
    {
        CxDateTime dtDt1;
        CxDateTime dtDt2;

        m_bRes = (dtDt1 >= dtDt2);
        xASSERT(FALSE != m_bRes);
    }


    /****************************************************************************
    *   public: assignment operators
    *
    *****************************************************************************/

    //-------------------------------------
    //operator +=
    {
        CxDateTime dtDt(0, 30, 0, 0);
        ULONGLONG  ullMSec = (1000 * 60) * 60; //1 hour

        dtDt = ullMSec;
        m_sRes = dtDt.sFormat(CxDateTime::ftDateTime);
        xASSERT(xT("00.00.0000 1:00:00:000") == m_sRes);
    }

    //-------------------------------------
    //operator (=, +, -)
    {
        CxDateTime dtDT;

        dtDT = CxDateTime() + CxDateTime(1000 * 60 * 60);
        m_sRes = dtDT.sFormat(CxDateTime::ftDateTime);
        xASSERT(xT("00.00.0000 1:00:00:000") == m_sRes);

        dtDT = dtDT - CxDateTime(1000 * 60 * 60 / 2);
        m_sRes = dtDT.sFormat(CxDateTime::ftDateTime);
        xASSERT(xT("00.00.0000 0:30:00:000") == m_sRes);
    }

    //-------------------------------------
    //operator +=
    {
        CxDateTime dtDt1(1, 0, 0, 0);
        CxDateTime dtDt2(1, 30, 0, 0);

        dtDt1 += dtDt2;
        m_sRes = dtDt1.sFormat(CxDateTime::ftDateTime);
        xASSERT_MSG(xT("00.00.0000 2:30:00:000") == m_sRes, m_sRes);
    }

    //-------------------------------------
    //operator -=
    {
        CxDateTime dtDt1(1, 50, 0, 0);
        CxDateTime dtDt2(1, 30, 0, 0);

        dtDt1 -= dtDt2;
        m_sRes = dtDt1.sFormat(CxDateTime::ftDateTime);
        xASSERT(xT("00.00.0000 0:20:00:000") == m_sRes);
    }


    /****************************************************************************
    *   public: get, set
    *
    *****************************************************************************/

    //-------------------------------------
    //bSet, bGet
    {
        CxDateTime dtDT;

        USHORT     usYear   = 2010;
        USHORT     usMonth  = 1;
        USHORT     usDay    = 14;
        USHORT     usHour   = 17;
        USHORT     usMinute = 0;
        USHORT     usSecond = 55;
        USHORT     usMSec   = 666;

        m_bRes = dtDT.bSet(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMSec);
        /*DEBUG*/xASSERT(FALSE != m_bRes);

        m_bRes = dtDT.bGet(&usYear, &usMonth, &usDay, &usHour, &usMinute, &usSecond, &usMSec);
        /*DEBUG*/xASSERT(FALSE != m_bRes);

        /*DEBUG*/xASSERT(2010  == usYear);
        /*DEBUG*/xASSERT(1     == usMonth);
        /*DEBUG*/xASSERT(14    == usDay);
        /*DEBUG*/xASSERT(17    == usHour);
        /*DEBUG*/xASSERT(0     == usMinute);
        /*DEBUG*/xASSERT(55    == usSecond);
        /*DEBUG*/xASSERT(666   == usMSec);
    }

    //--------------------------------------------------
    //ullToMilliseconds
    {
        //1
        {
            m_ullRes = CxDateTime(2010, 1, 14, 17, 0, 55, 666).ullToMilliseconds();
            xASSERT(62522902855666ULL == m_ullRes);
        }

        //2
        {
            const ULONGLONG caullMsec[] = {
                    12234567890ULL, 2234567890ULL, 32345657890ULL, 4294567890ULL, 5234567890ULL,
                    63565474567ULL, 7354234523ULL, 83451467547ULL, 9234436577ULL, 5354362463ULL
            };

            for (size_t i = 0; i < xARRAY_SIZE(caullMsec); ++ i) {
                m_ullRes = CxDateTime(caullMsec[i]).ullToMilliseconds();
                xASSERT_MSG(caullMsec[i] == m_ullRes, CxString::sFormat(xT("m_ullRes: %lli, i = %i"), m_ullRes, i));
            }
        }
    }

    //-------------------------------------
    //bSet
    {
        CxDateTime dtDT;

        ULONGLONG  ui64DT = 1000 * 60 * 60; //1 hour

        USHORT     usYear   = 0;
        USHORT     usMonth  = 0;
        USHORT     usDay    = 0;
        USHORT     usHour   = 0;
        USHORT     usMinute = 0;
        USHORT     usSecond = 0;
        USHORT     usMSec   = 0;

        m_bRes = dtDT.bSet(ui64DT);
        /*DEBUG*/xASSERT(FALSE != m_bRes);

        m_bRes = dtDT.bGet(&usYear, &usMonth, &usDay, &usHour, &usMinute, &usSecond, &usMSec);
        /*DEBUG*/xASSERT(FALSE != m_bRes);

        /*DEBUG*/xASSERT(0 == usYear);
        /*DEBUG*/xASSERT(0 == usMonth);
        /*DEBUG*/xASSERT(0 == usDay);
        /*DEBUG*/xASSERT(1 == usHour);
        /*DEBUG*/xASSERT(0 == usMinute);
        /*DEBUG*/xASSERT(0 == usSecond);
        /*DEBUG*/xASSERT(0 == usMSec);
    }

    //-------------------------------------
    //usGetDayOfWeek
    {
        m_usiRes = CxDateTime(2011, 7, 25, 13, 0, 0, 0).usGetDayOfWeek();
        xASSERT(1 == m_usiRes);

        m_usiRes = CxDateTime(2011, 7, 31, 0, 0, 0, 0).usGetDayOfWeek();
        xASSERT(0 == m_usiRes);

        m_usiRes = CxDateTime(2011, 3, 18, 0, 0, 0, 0).usGetDayOfWeek();
        xASSERT(5 == m_usiRes);
    }


    /****************************************************************************
    *    formating
    *
    *****************************************************************************/

    //-------------------------------------
    //formating
    {
        CxDateTime dtDT(2010, 1, 14, 17, 0, 55, 666);
        m_sRes = dtDT.sFormat(CxDateTime::ftTime);
        xASSERT(xT("17:00:55:666") == m_sRes);
    }
    {
        CxDateTime dtDT(2010, 1, 14, 17, 0, 55, 666);
        m_sRes = dtDT.sFormat(CxDateTime::ftDate);
        xASSERT(xT("14.01.2010") == m_sRes);
    }
    {
        CxDateTime dtDT(2010, 1, 14, 17, 0, 55, 666);
        m_sRes = dtDT.sFormat(CxDateTime::ftDateTime);
        xASSERT(xT("14.01.2010 17:00:55:666") == m_sRes);
    }
    {
        CxDateTime dtDT(2011, 3, 19, 1, 35, 55, 666);
        m_sRes = dtDT.sFormat(CxDateTime::ftRFC1123);
        xASSERT_MSG(xT("Sat, 19 Mar 2011 01:35:55 GMT") == m_sRes, m_sRes.c_str());
    }


    /****************************************************************************
    * static
    *
    *****************************************************************************/

    //-------------------------------------
    //bIsValid
    {
        //valid data
        {
            const USHORT causiValid[][7] = {
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
//                USHORT usYear   = causiValid[i][0];
//                USHORT usMonth  = causiValid[i][1];
//                USHORT usDay    = causiValid[i][2];
//                USHORT usHour   = causiValid[i][3];
//                USHORT usMinute = causiValid[i][4];
//                USHORT usSecond = causiValid[i][5];
//                USHORT usMSec   = causiValid[i][6];
//
//                m_bRes = CxDateTime::bIsValid(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMSec);
//                xASSERT_MSG(TRUE == m_bRes, xT("i = ") + CxString::lexical_cast(i));
            }
        }

        //non valid data
        {
            const USHORT causiNonValid[][7] = {
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
                ////USHORT usYear   = causiNonValid[i][0];
                ////USHORT usMonth  = causiNonValid[i][1];
                ////USHORT usDay    = causiNonValid[i][2];
                ////USHORT usHour   = causiNonValid[i][3];
                ////USHORT usMinute = causiNonValid[i][4];
                ////USHORT usSecond = causiNonValid[i][5];
                ////USHORT usMSec   = causiNonValid[i][6];

                ////m_bRes = CxDateTime::bIsValid(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMSec);
                ////xASSERT_MSG(FALSE == m_bRes, xT("i = ") + CxString::lexical_cast(i) + xT("    usYear = ") + CxString::lexical_cast(usYear));
            }
        }
    }

    //-------------------------------------
    //dtGetCurrent
    {
        //1
        {
            CxDateTime dtNowDT;

            m_sRes = dtNowDT.dtGetCurrent().sFormat(CxDateTime::ftDateTime);
            xASSERT(xT("00.00.0000 0:00:00:000") != m_sRes);
        }

        //2
        for (size_t i = 0; i < 100; ++ i) {
            CxDateTime _m_dtTimesStart;
            CxDateTime _m_dtTimesStop;

            _m_dtTimesStart = CxDateTime::dtGetCurrent();
            {
                for (int x = 0; x < 100; ++ x) {
                    for (int y = 0; y < 20; ++ y) {
                        int z = 0;

                        z++; --z;
                    }
                }
            }
            _m_dtTimesStop = CxDateTime::dtGetCurrent();

            /*DEBUG*/xASSERT_MSG(_m_dtTimesStop >= _m_dtTimesStart, CxString::sFormat(xT("i = %i, \n_m_dtTimesStop:  %s, \n_m_dtTimesStart: %s"), i,  _m_dtTimesStop.sFormat(CxDateTime::ftDateTime).c_str(), _m_dtTimesStart.sFormat(CxDateTime::ftDateTime).c_str()));
        }
    }

    //-------------------------------------
    //TODO: usDaysInMonth
    {
        for (USHORT y = 0; y < 3000; ++ y) {
            for (USHORT m = 1; m < 13; ++ m) {
                m_usiRes = CxDateTime::usDaysInMonth(y, m);

                if (2 == m && CxDateTime::bIsLeapYear(y)) {
                    xASSERT(29 == m_usiRes);
                } else {
                    USHORT arusDaysOfMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

                    xASSERT(m_usiRes == arusDaysOfMonth[m]);
                }
            } //m
        } //y
    }

    //-------------------------------------
    //TODO: bIsLeapYear
    {
        //valid
        {
            ////const USHORT causValid[] = {
            ////        //TODO: bIsLeapYear
            ////};

            ////for (size_t i = 0; i < xARRAY_SIZE(causValid); ++ i) {
            ////    m_bRes = CxDateTime::bIsLeapYear(causValid[i]);
            ////    xASSERT(TRUE == m_bRes);
            ////}
        }

        //non valid
        {
            ////const USHORT causNonValid[] = {
            ////        //TODO: bIsLeapYear
            ////};

            ////for (size_t i = 0; i < xARRAY_SIZE(causNonValid); ++ i) {
            ////    m_bRes = CxDateTime::bIsLeapYear(causNonValid[i]);
            ////    xASSERT(FALSE == m_bRes);
            ////}
        }
    }

    //-------------------------------------
    //i64FiletimeToInt64
    {
        #if defined(xOS_WIN)
            const FILETIME cftTime = {100, 200};

            m_ullRes = CxDateTime::i64FiletimeToInt64(cftTime);
            #if xTODO
                xASSERT_EQUAL( == m_ullRes);
            #endif
        #elif defined(xOS_LINUX)
            // n/a
        #endif
    }

    //-------------------------------------
    //bUnixTimeToFileTime
    {
        #if defined(xOS_WIN)
            const time_t ctmUnixTime = 1000;
            FILETIME     ftFileTime  = {0};

            m_bRes = CxDateTime::bUnixTimeToFileTime(ctmUnixTime, &ftFileTime);
        #elif defined(xOS_LINUX)
            // n/a
        #endif
    }


    /****************************************************************************
    *   other
    *
    *****************************************************************************/

    //-------------------------------------
    //sGetZodiacSign
    {
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

        const tString sTestData[][3] = {
            {xT("7"), xT("31"), xT("Лев")},
            {xT("5"), xT("18"), xT("Телец")},
        };

        for (std::size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxDateTime::sGetZodiacSign(CxString::lexical_cast<INT>(sTestData[i][0]),
                                                       CxString::lexical_cast<INT>(sTestData[i][1]));
            tString sStr2 = sTestData[i][2];
            xASSERT(sStr1 == sStr2);
        }
    #endif
    }

    //-------------------------------------
    //sGetMonthStr
    {
        //bIsShortName = FALSE
        m_sRes = CxDateTime::sGetMonthStr((USHORT)- 1, FALSE);
        xASSERT(xT("December") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(0, FALSE);
        xASSERT(xT("January") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(1, FALSE);
        xASSERT(xT("January") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(2, FALSE);
        xASSERT(xT("February") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(3, FALSE);
        xASSERT(xT("March") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(4, FALSE);
        xASSERT(xT("April") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(5, FALSE);
        xASSERT(xT("May") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(6, FALSE);
        xASSERT(xT("June") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(7, FALSE);
        xASSERT(xT("July") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(8, FALSE);
        xASSERT(xT("August") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(9, FALSE);
        xASSERT(xT("September") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(10, FALSE);
        xASSERT(xT("October") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(11, FALSE);
        xASSERT(xT("November") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(12, FALSE);
        xASSERT(xT("December") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(13, FALSE);
        xASSERT(xT("December") == m_sRes);

        //bIsShortName = TRUE
        m_sRes = CxDateTime::sGetMonthStr((USHORT)- 1, TRUE);
        xASSERT(xT("Dec") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(0, TRUE);
        xASSERT(xT("Jan") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(1, TRUE);
        xASSERT(xT("Jan") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(2, TRUE);
        xASSERT(xT("Feb") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(3, TRUE);
        xASSERT(xT("Mar") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(4, TRUE);
        xASSERT(xT("Apr") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(5, TRUE);
        xASSERT(xT("May") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(6, TRUE);
        xASSERT(xT("Jun") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(7, TRUE);
        xASSERT(xT("Jul") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(8, TRUE);
        xASSERT(xT("Aug") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(9, TRUE);
        xASSERT(xT("Sep") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(10, TRUE);
        xASSERT(xT("Oct") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(11, TRUE);
        xASSERT(xT("Nov") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(12, TRUE);
        xASSERT(xT("Dec") == m_sRes);
        m_sRes = CxDateTime::sGetMonthStr(13, TRUE);
        xASSERT(xT("Dec") == m_sRes);
    }

    //--------------------------------------------------
    //usGetMonthNum
    {
        const tString casMonths[12][2] = {
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
            m_usiRes = CxDateTime::usGetMonthNum(casMonths[i][0], FALSE);
            xASSERT_MSG(i + 1 == m_usiRes, casMonths[i][0]);

            m_usiRes = CxDateTime::usGetMonthNum(casMonths[i][1], TRUE);
            xASSERT_MSG(i + 1 == m_usiRes, casMonths[i][1]);

            if (xT("May") == casMonths[i][0] || xT("May") == casMonths[i][1]) {
                m_usiRes = CxDateTime::usGetMonthNum(casMonths[i][0], TRUE);
                xASSERT_MSG(i + 1 == m_usiRes, casMonths[i][0]);

                m_usiRes = CxDateTime::usGetMonthNum(casMonths[i][1], FALSE);
                xASSERT_MSG(i + 1 == m_usiRes, casMonths[i][1]);
            } else {
                m_usiRes = CxDateTime::usGetMonthNum(casMonths[i][0], TRUE);
                xASSERT_MSG((USHORT)- 1 == m_usiRes, casMonths[i][0]);

                m_usiRes = CxDateTime::usGetMonthNum(casMonths[i][1], FALSE);
                xASSERT_MSG((USHORT)- 1 == m_usiRes, casMonths[i][1]);
            }
        }
    }

    //-------------------------------------
    //sGetWeekDayStr
    {
        //bIsShortName = FALSE
        m_sRes = CxDateTime::sGetWeekDayStr(0, FALSE);
        xASSERT(xT("Sunday") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(1, FALSE);
        xASSERT(xT("Monday") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(2, FALSE);
        xASSERT(xT("Tuesday") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(3, FALSE);
        xASSERT(xT("Wednesday") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(4, FALSE);
        xASSERT(xT("Thursday") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(5, FALSE);
        xASSERT(xT("Friday") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(6, FALSE);
        xASSERT(xT("Saturday") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(7, FALSE);
        xASSERT(xT("Saturday") == m_sRes);

        //bIsShortName = TRUE
        m_sRes = CxDateTime::sGetWeekDayStr(0, TRUE);
        xASSERT(xT("Sun") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(1, TRUE);
        xASSERT(xT("Mon") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(2, TRUE);
        xASSERT(xT("Tue") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(3, TRUE);
        xASSERT(xT("Wed") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(4, TRUE);
        xASSERT(xT("Thu") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(5, TRUE);
        xASSERT(xT("Fri") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(6, TRUE);
        xASSERT(xT("Sat") == m_sRes);
        m_sRes = CxDateTime::sGetWeekDayStr(7, TRUE);
        xASSERT(xT("Sat") == m_sRes);
    }

    //--------------------------------------------------
    //usGetWeekDayNum
    {
        const tString casDays[7][2] = {
            { xT("Sunday"),     xT("Sun") },
            { xT("Monday"),     xT("Mon") },
            { xT("Tuesday"),    xT("Tue"} ),
            { xT("Wednesday"),  xT("Wed") },
            { xT("Thursday"),   xT("Thu") },
            { xT("Friday"),     xT("Fri") },
            { xT("Saturday"),   xT("Sat") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(casDays); ++ i) {
            m_usiRes = CxDateTime::usGetWeekDayNum(casDays[i][0], FALSE);
            xASSERT_MSG(i == m_usiRes, casDays[i][0]);

            m_usiRes = CxDateTime::usGetWeekDayNum(casDays[i][1], TRUE);
            xASSERT_MSG(i == m_usiRes, casDays[i][1]);

            m_usiRes = CxDateTime::usGetWeekDayNum(casDays[i][0], TRUE);
            xASSERT_MSG((USHORT)- 1 == m_usiRes, casDays[i][0]);

            m_usiRes = CxDateTime::usGetWeekDayNum(casDays[i][1], FALSE);
            xASSERT_MSG((USHORT)- 1 == m_usiRes, casDays[i][1]);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxDateTimeH
