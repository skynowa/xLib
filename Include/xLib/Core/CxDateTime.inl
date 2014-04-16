/**
 * \file  CxDateTime.cpp
 * \brief date, time
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxArray.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTrace.h>


xNAMESPACE2_BEGIN(xlib, core)

/**************************************************************************************************
*    public: constructors, destructor
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxDateTime::CxDateTime() :
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0),
    _thisMSec(0ULL)
{
}
//-------------------------------------------------------------------------------------------------
inline
CxDateTime::CxDateTime(
    const CxDateTime &a_datetime
) :
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0),
    _thisMSec(0ULL)
{
    xTEST_EQ(CxValidator::date(a_datetime._year, a_datetime._month, a_datetime._day) &&
        CxValidator::time(a_datetime._hour, a_datetime._minute, a_datetime._second,
        a_datetime._msec), true);

    set(a_datetime._year, a_datetime._month,  a_datetime._day,
        a_datetime._hour, a_datetime._minute, a_datetime._second, a_datetime._msec);
}
//-------------------------------------------------------------------------------------------------
inline
CxDateTime::CxDateTime(
    culonglong_t &a_msec
) :
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0),
    _thisMSec(0ULL)
{
    set(a_msec);
}
//-------------------------------------------------------------------------------------------------
inline
CxDateTime::CxDateTime(
    cint_t &a_hour,
    cint_t &a_minute,
    cint_t &a_second,
    cint_t &a_msec
) :
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0),
    _thisMSec(0ULL)
{
    xTEST_EQ(CxValidator::time(a_hour, a_minute, a_second, a_msec), true);

    set(0, 0, 0, a_hour, a_minute, a_second, a_msec);
}
//-------------------------------------------------------------------------------------------------
inline
CxDateTime::CxDateTime(
    cint_t &a_year,
    cint_t &a_month,
    cint_t &a_day
) :
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0),
    _thisMSec(0ULL)
{
    xTEST_EQ(CxValidator::date(a_year, a_month, a_day), true);

    set(a_year, a_month, a_day, 0, 0, 0, 0);
}
//-------------------------------------------------------------------------------------------------
inline
CxDateTime::CxDateTime(
    cint_t &a_year,
    cint_t &a_month,
    cint_t &a_day,
    cint_t &a_hour,
    cint_t &a_minute,
    cint_t &a_second,
    cint_t &a_msec
) :
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0),
    _thisMSec(0ULL)
{
    xTEST_EQ(true, CxValidator::date(a_year, a_month, a_day) &&
                   CxValidator::time(a_hour, a_minute, a_second, a_msec));

    set(a_year, a_month, a_day, a_hour, a_minute, a_second, a_msec);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public: validate
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::year(
    cint_t &a_year
)
{
    cbool_t bRv = (a_year >= 0 && a_year <= 9999);
    xTEST_EQ(bRv, true);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::month(
    cint_t &a_month
)
{
    cbool_t bRv = (a_month >= 0 && a_month <= 11);
    xTEST_EQ(bRv, true);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::day(
    cint_t &a_day
)
{
    cbool_t bRv = (a_day >= 1 && a_day <= 31);
    xTEST_EQ(bRv, true);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::hour(
    cint_t &a_hour
)
{
    cbool_t bRv = (a_hour >= 0 && a_hour <= 23);
    xTEST_EQ(bRv, true);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::minute(
    cint_t &a_minute
)
{
    cbool_t bRv = (a_minute >= 0 && a_minute <= 59);
    xTEST_EQ(bRv, true);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::second(
    cint_t &a_second
)
{
    cbool_t bRv = (a_second >= 0 && a_second <= 60);
    xTEST_EQ(bRv, true);

    return  bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::msec(
    cint_t &a_msec
)
{
    cbool_t bRv = (a_msec >= 0 && a_msec <= 999);
    xTEST_EQ(bRv, true);

    return  bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::weekDay(
    cint_t &a_weekDay
)
{
    cbool_t bRv = (a_weekDay >= 0 && a_weekDay <= 6);
    xTEST_EQ(bRv, true);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::date(
    cint_t &a_year,
    cint_t &a_month,
    cint_t &a_day
)
{
    xCHECK_RET(!year(a_year) || !month(a_month) || !day(a_day), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::time(
    cint_t &a_hour,
    cint_t &a_minute,
    cint_t &a_second,
    cint_t &a_msec
)
{
    xCHECK_RET(!hour(a_hour) || !minute(a_minute) || !second(a_second) || !msec(a_msec), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::datetime(
    cint_t &a_year,
    cint_t &a_month,
    cint_t &a_day,
    cint_t &a_hour,
    cint_t &a_minute,
    cint_t &a_second,
    cint_t &a_msec
)
{
    xUNUSED(a_day);

    xCHECK_RET((!date(a_year, a_month, a_day) || !time(a_hour, a_minute, a_second, a_msec)), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::datetime(
    const CxDateTime &a_datetime
)
{
    xCHECK_RET((!date(a_datetime._year, a_datetime._month, a_datetime._day) ||
        !time(a_datetime._hour, a_datetime._minute, a_datetime._second, a_datetime._msec)), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::CxValidator::dateOrTime(
    cint_t &a_year,
    cint_t &a_month,
    cint_t &a_day,
    cint_t &a_hour,
    cint_t &a_minute,
    cint_t &a_second,
    cint_t &a_msec
)
{
    xCHECK_RET((!date(a_year, a_month, a_day) && !time(a_hour, a_minute, a_second, a_msec)), false);

    return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: comparison operators
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::operator == (
    const CxDateTime &a_datetime
) const
{
//    xTEST_EQ(CxValidator::datetime(*this), true);
//    xTEST_EQ(CxValidator::datetime(a_datetime), true);

    return (_thisMSec == a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::operator != (
    const CxDateTime &a_datetime
) const
{
//    xTEST_EQ(CxValidator::datetime(*this), true);
//    xTEST_EQ(CxValidator::datetime(a_datetime), true);

    return ( _thisMSec != a_datetime._thisMSec );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::operator < (
    const CxDateTime &a_datetime
) const
{
//    xTEST_EQ(CxValidator::datetime(*this), true);
//    xTEST_EQ(CxValidator::datetime(a_datetime), true);

    return ( _thisMSec < a_datetime._thisMSec );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::operator <= (
    const CxDateTime &a_datetime
) const
{
//    xTEST_EQ(CxValidator::datetime(*this), true);
//    xTEST_EQ(CxValidator::datetime(a_datetime), true);

    return ( _thisMSec <= a_datetime._thisMSec );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::operator > (
    const CxDateTime &a_datetime
) const
{
//    xTEST_EQ(CxValidator::datetime(*this), true);
//    xTEST_EQ(CxValidator::datetime(a_datetime), true);

    return ( _thisMSec > a_datetime._thisMSec );
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDateTime::operator >= (
    const CxDateTime &a_datetime
) const
{
//    xTEST_EQ(CxValidator::datetime(*this), true);
//    xTEST_EQ(CxValidator::datetime(a_datetime), true);

    return ( _thisMSec >= a_datetime._thisMSec );
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: assignment operators
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline const CxDateTime &
CxDateTime::operator = (
    const CxDateTime &a_datetime
)
{
    xCHECK_RET(this == &a_datetime, *this);

    set(a_datetime._thisMSec);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline const CxDateTime &
CxDateTime::operator = (
    culonglong_t &a_msec
)
{
    set(a_msec);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxDateTime
CxDateTime::operator + (
    const CxDateTime &a_datetime
) const
{
//    xTEST_EQ(CxValidator::datetime(*this), true);

    return CxDateTime(_thisMSec + a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
inline CxDateTime
CxDateTime::operator - (
    const CxDateTime &a_datetime
) const
{
//    xTEST_EQ(CxValidator::datetime(*this), true);

    return CxDateTime(_thisMSec - a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
inline const CxDateTime &
CxDateTime::operator += (
    const CxDateTime &a_datetime
)
{
//    xTEST_EQ(CxValidator::datetime(*this), true);

    _thisMSec += a_datetime._thisMSec;

    set(_thisMSec);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline const CxDateTime &
CxDateTime::operator -= (
    const CxDateTime &a_datetime
)
{
//    xTEST_EQ(CxValidator::datetime(*this), true);

    _thisMSec -= a_datetime._thisMSec;

    set(_thisMSec);

    return *this;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public:
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxDateTime::get(
    int_t *a_year,
    int_t *a_month,
    int_t *a_day,
    int_t *a_hour,
    int_t *a_minute,
    int_t *a_second,
    int_t *a_msec
) const
{
//    xTEST_EQ(CxValidator::datetime(*this), true);
    xTESTS_NA;

    CxUtils::ptrAssignT(a_year,   _year);
    CxUtils::ptrAssignT(a_month,  _month);
    CxUtils::ptrAssignT(a_day,    _day);
    CxUtils::ptrAssignT(a_hour,   _hour);
    CxUtils::ptrAssignT(a_minute, _minute);
    CxUtils::ptrAssignT(a_second, _second);
    CxUtils::ptrAssignT(a_msec,   _msec);
}
//-------------------------------------------------------------------------------------------------
inline int_t
CxDateTime::dayOfWeek() const
{
//    xTEST_EQ(CxValidator::datetime(*this), true);

    int_t iRv     = 0;
    tm    timeInfo;  xSTRUCT_ZERO(timeInfo);

    timeInfo.tm_year = _year  - 1900;
    timeInfo.tm_mon  = _month - 1;
    timeInfo.tm_mday = _day;

    time_t time = std::mktime(&timeInfo);
    xTEST_DIFF(static_cast<time_t>( - 1 ), time);

    iRv = timeInfo.tm_wday;

    return iRv;
}
//-------------------------------------------------------------------------------------------------
// TODO: toMsec
inline ulonglong_t
CxDateTime::toMsec() const
{
    return _thisMSec;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDateTime::set(
    culonglong_t &a_msec
)
{
    xTESTS_NA;

    //--------------------------------------------------
    // datetime msec member
    _thisMSec = a_msec;

    //--------------------------------------------------
    // datetime members
    ulonglong_t msec = a_msec;

    // converts milliseconds to datetime members
#if xDEPRECIATE
    _year    = static_cast<int_t>( msec / ((1000ULL * 60 * 60 * 24 * 30) * 12) );

    msec    %= ((1000ULL * 60 * 60 * 24 * 30) * 12);
    _month   = static_cast<int_t>( msec / ((1000ULL * 60 * 60 * 24) * 30) );

    msec    %= ((1000ULL * 60 * 60 * 24) * 30);
    _day     = static_cast<int_t>( msec / ((1000ULL * 60 * 60) * 24) );

    msec    %= ((1000ULL * 60 * 60) * 24);
    _hour    = static_cast<int_t>( msec / ((1000ULL * 60) * 60) );

    msec    %= ((1000ULL * 60) * 60);
    _minute  = static_cast<int_t>( msec / ((1000ULL * 60)) );

    msec    %= ((1000ULL * 60));
    _second  = static_cast<int_t>( msec / 1000ULL );

    msec    %= 1000ULL;
    _msec    = static_cast<int_t>( msec );
#else
    _year    = static_cast<int_t>( msec / ((1000ULL * 60 * 60 * 24 * 30) * 12) );

    msec    %= ((1000ULL * 60 * 60 * 24 * 30) * 12);
    _month   = static_cast<int_t>( msec / ((1000ULL * 60 * 60 * 24) * 30) );

    msec    %= ((1000ULL * 60 * 60 * 24) * 30);
    _day     = static_cast<int_t>( msec / ((1000ULL * 60 * 60) * 24) );

    msec    %= ((1000ULL * 60 * 60) * 24);
    _hour    = static_cast<int_t>( msec / ((1000ULL * 60) * 60) );

    msec    %= ((1000ULL * 60) * 60);
    _minute  = static_cast<int_t>( msec / ((1000ULL * 60)) );

    msec    %= ((1000ULL * 60));
    _second  = static_cast<int_t>( msec / 1000ULL );

    msec    %= 1000ULL;
    _msec    = static_cast<int_t>( msec );
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDateTime::set(
    cint_t &a_year,
    cint_t &a_month,
    cint_t &a_day,
    cint_t &a_hour,
    cint_t &a_minute,
    cint_t &a_second,
    cint_t &a_msec
)
{
    xTESTS_NA;

    // datetime members
    _year   = a_year;
    _month  = a_month;
    _day    = a_day;
    _hour   = a_hour;
    _minute = a_minute;
    _second = a_second;
    _msec   = a_msec;

    // datetime msec member (convert to msec)
    _thisMSec = _toMsec();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    converting
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline ulonglong_t
CxDateTime::_toMsec() const
{
    xTESTS_NA;

    ulonglong_t ullRv = 0ULL;

    ullRv += xYEAR(_year);    // TODO: CxDateTime::_toMsec() - days in month 30 or 31 ???
    ullRv += xMONTH(_month);
    ullRv += xDAY(_day);
    ullRv += xHOUR(_hour);
    ullRv += xMINUTE(_minute);
    ullRv += xSECOND(_second);
    ullRv += xMSEC(_msec);

    return ullRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: formating
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxDateTime::format(
    std::ctstring_t &a_format,                         ///< datetime format
    std::ctstring_t &a_formatMsec /* = xT(".%03d") */  ///< milliseconds format
) const
{
    //xTEST_EQ(CxValidator::datetime(*this), true);
    xTEST_EQ(a_format.empty(), false);
    xTEST_NA(a_formatMsec);

    std::tstring_t sRv;
    tchar_t        buff[80 + 1] = {};

    std::tm time; xSTRUCT_ZERO(time);
    time.tm_year = _year  - 1900;
    time.tm_mon  = _month - 1;
    time.tm_mday = _day;
    time.tm_hour = _hour;
    time.tm_min  = _minute;
    time.tm_sec  = _second;

    size_t uiRv = xSTRFTIME(buff, sizeof(buff) - 1, a_format.c_str(), &time);
    xCHECK_RET(uiRv == 0, std::tstring_t());

    sRv.assign(&buff[0], uiRv);

    if ( !a_formatMsec.empty() ) {
        sRv += CxString::format(a_formatMsec.c_str(), _msec);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline CxDateTime
CxDateTime::current()
{
#if   xOS_ENV_WIN
    SYSTEMTIME dateTime = {0};

    (void_t)::GetLocalTime(&dateTime);
    xTEST_EQ(CxValidator::datetime(dateTime.wYear, dateTime.wMonth, dateTime.wDay,
        dateTime.wHour, dateTime.wMinute, dateTime.wSecond, dateTime.wMilliseconds), true);

    return CxDateTime(dateTime.wYear, dateTime.wMonth, dateTime.wDay,
        dateTime.wHour, dateTime.wMinute, dateTime.wSecond, dateTime.wMilliseconds);
#elif xOS_ENV_UNIX
    // get msec
    timeval timeNow;   xSTRUCT_ZERO(timeNow);

    int_t iRv = ::gettimeofday(&timeNow, xPTR_NULL);
    xTEST_DIFF(iRv, - 1);

    // get datetime
    std::tm dateTime; xSTRUCT_ZERO(dateTime);

    std::tm *dtRv = ::localtime_r(&timeNow.tv_sec, &dateTime);
    xTEST_PTR(dtRv);

    // set datetime
    cint_t year   = dateTime.tm_year + 1900;
    cint_t month  = dateTime.tm_mon  + 1;
    cint_t day    = dateTime.tm_mday;
    cint_t hour   = dateTime.tm_hour;
    cint_t minute = dateTime.tm_min;
    cint_t second = dateTime.tm_sec;
    cint_t msec   = static_cast<int_t>( static_cast<double>(timeNow.tv_usec) * 0.001 );

    return CxDateTime(year, month, day, hour, minute, second, msec);
#endif
}
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

/* static */
inline longlong_t
CxDateTime::filetimeToInt64(
    const FILETIME &a_fileTime
)
{
    return Int64ShllMod32(a_fileTime.dwHighDateTime, 32) | a_fileTime.dwLowDateTime;
}

#endif
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

/* static */
inline void_t
CxDateTime::unixTimeToFileTime(
    const time_t &a_unixTime,
    FILETIME     *a_fileTime
)
{
    xTEST_NA(a_unixTime);
    xTEST_PTR(a_fileTime);

    longlong_t llRv = 0LL;

    llRv = Int32x32To64(a_unixTime, 10000000) + 116444736000000000;
    a_fileTime->dwLowDateTime  = static_cast<ulong_t>( llRv );
    a_fileTime->dwHighDateTime = llRv >> 32;
}

#endif
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

/* static */
inline time_t
CxDateTime::fileTimeToUnixTime(
    const FILETIME &a_fileTime
)
{
    // TEST: CxDateTime::fileTimeToUnixTime()

    const __int64 nanosecsBetweenEpochs = 116444736000000000LL;

    __int64 llRv = 0LL;

    llRv = (static_cast<__int64>( a_fileTime.dwHighDateTime ) << 32) + a_fileTime.dwLowDateTime;
    llRv -= nanosecsBetweenEpochs;
    llRv /= 10000000;

    return static_cast<time_t>( llRv );
}

#endif
//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxDateTime::daysInMonth(
    cint_t &a_year,
    cint_t &a_month
)
{
    xCHECK_RET(a_month == 2 && isLeapYear(a_year), 29);

    const CxArray<int_t, 12> monthsDays = {{
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    }};

    return monthsDays[a_month];
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxDateTime::isLeapYear(
    cint_t &a_year
)
{
    return ( 0 == (a_year % 4) && ( 0 != (a_year % 100) || 0 == (a_year % 400)) );
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxDateTime::zodiacSign(
    cint_t &a_month,
    cint_t &a_day
)
{
    xTEST_NA(a_month);
    xTEST_NA(a_day);

   /**
    * NOTE: signs of the zodiac
    *
    *  -----------------------------------------------------
    *  |  Знак     |  Символ  |  Западная астрология       |
    *  -----------------------------------------------------
    *  |  Овен     |  U+2648  |  21 марта    — 20 апреля   |
    *  |  Телец    |  U+2649  |  21 апреля   — 21 мая      |
    *  |  Близнецы |  U+264A  |  22 мая      — 21 июня     |
    *  |  Рак      |  U+264B  |  22 июня     — 23 июля     |
    *  |  Лев      |  U+264С  |  24 июля     — 23 августа  |
    *  |  Дева     |  U+264D  |  24 августа  — 23 сентября |
    *  |  Весы     |  U+264E  |  24 сентября — 23 октября  |
    *  |  Скорпион |  U+264F  |  24 октября  — 22 ноября   |
    *  |  Стрелец  |  U+2650  |  23 ноября   — 21 декабря  |
    *  |  Козерог  |  U+2651  |  22 декабря  — 20 января   |
    *  |  Водолей  |  U+2652  |  21 января   — 19 февраля  |
    *  |  Рыбы     |  U+2653  |  20 февраля  — 20 марта    |
    *  -----------------------------------------------------
    */

    // day
    // month

    // Овен     |  U+2648  |  21 марта    — 20 апреля
    xCHECK_RET(a_month == 3  && a_day >= 21, xT("Овен"));
    xCHECK_RET(a_month == 4  && a_day <= 20, xT("Овен"));

    // Телец    |  U+2649  |  21 апреля   — 21 мая
    xCHECK_RET(a_month == 4  && a_day >= 21, xT("Телец"));
    xCHECK_RET(a_month == 5  && a_day <= 21, xT("Телец"));

    // Близнецы |  U+264A  |  22 мая      — 21 июня
    xCHECK_RET(a_month == 5  && a_day >= 22, xT("Близнецы"));
    xCHECK_RET(a_month == 6  && a_day <= 21, xT("Близнецы"));

    // Рак      |  U+264B  |  22 июня     — 23 июля
    xCHECK_RET(a_month == 6  && a_day >= 22, xT("Рак"));
    xCHECK_RET(a_month == 7  && a_day <= 23, xT("Рак"));

    // Лев      |  U+264С  |  24 июля     — 23 августа
    xCHECK_RET(a_month == 7  && a_day >= 24, xT("Лев"));
    xCHECK_RET(a_month == 8  && a_day <= 23, xT("Лев"));

    // Дева     |  U+264D  |  24 августа  — 23 сентября
    xCHECK_RET(a_month == 8  && a_day >= 24, xT("Дева"));
    xCHECK_RET(a_month == 9  && a_day <= 23, xT("Дева"));

    // Весы     |  U+264E  |  24 сентября — 23 октября
    xCHECK_RET(a_month == 9  && a_day >= 24, xT("Весы"));
    xCHECK_RET(a_month == 10 && a_day <= 23, xT("Весы"));

    // Скорпион |  U+264F  |  24 октября  — 22 ноября
    xCHECK_RET(a_month == 10 && a_day >= 24, xT("Скорпион"));
    xCHECK_RET(a_month == 11 && a_day <= 22, xT("Скорпион"));

    // Стрелец  |  U+2650  |  23 ноября   — 21 декабря
    xCHECK_RET(a_month == 11 && a_day >= 23, xT("Стрелец"));
    xCHECK_RET(a_month == 12 && a_day <= 21, xT("Стрелец"));

    // Козерог  |  U+2651  |  22 декабря  — 20 января
    xCHECK_RET(a_month == 12 && a_day >= 22, xT("Козерог"));
    xCHECK_RET(a_month == 1  && a_day <= 20, xT("Козерог"));

    // Водолей  |  U+2652  |  21 января   — 19 февраля
    xCHECK_RET(a_month == 1  && a_day >= 21, xT("Водолей"));
    xCHECK_RET(a_month == 2  && a_day <= 19, xT("Водолей"));

    // Рыбы     |  U+2653  |  20 февраля  — 20 марта
    xCHECK_RET(a_month == 2  && a_day >= 20, xT("Рыбы"));
    xCHECK_RET(a_month == 3  && a_day <= 20, xT("Рыбы"));

    xTEST_FAIL;

    return std::tstring_t();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxDateTime::monthStr(
    cint_t  &a_month,
    cbool_t &a_isShortName
)
{
    xTEST_EQ(CxValidator::month(a_month), true);
    xTEST_NA(a_isShortName);

    std::tstring_t sRv;

    if (!a_isShortName) {
        // months numbering: 0-11
        const CxArray<std::tstring_t, 12> longMonths = {{
            xT("January"),
            xT("February"),
            xT("March"),
            xT("April"),
            xT("May"),
            xT("June"),
            xT("July"),
            xT("August"),
            xT("September"),
            xT("October"),
            xT("November"),
            xT("December")
        }};

        sRv = longMonths[a_month];
    }
    else {
        // months numbering: 0-11
        const CxArray<std::tstring_t, 12> shortMonths = {{
            xT("Jan"),
            xT("Feb"),
            xT("Mar"),
            xT("Apr"),
            xT("May"),
            xT("Jun"),
            xT("Jul"),
            xT("Aug"),
            xT("Sep"),
            xT("Oct"),
            xT("Nov"),
            xT("Dec")
        }};

        sRv = shortMonths[a_month];
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxDateTime::monthNum(
    std::ctstring_t &a_month,
    cbool_t         &a_isShortName
)
{
    xTEST_NA(a_month);
    xTEST_NA(a_isShortName);

    // months numbering: 0-11
    const CxArray<std::tstring_t, 12> longMonths = {{
        xT("January"),
        xT("February"),
        xT("March"),
        xT("April"),
        xT("May"),
        xT("June"),
        xT("July"),
        xT("August"),
        xT("September"),
        xT("October"),
        xT("November"),
        xT("December")
    }};

    // months numbering: 0-11
    const CxArray<std::tstring_t, 12> shortMonths = {{
        xT("Jan"),
        xT("Feb"),
        xT("Mar"),
        xT("Apr"),
        xT("May"),
        xT("Jun"),
        xT("Jul"),
        xT("Aug"),
        xT("Sep"),
        xT("Oct"),
        xT("Nov"),
        xT("Dec")
    }};

    for (int_t i = 0; i < static_cast<int_t>( longMonths.size() ); ++ i) {
        if (a_isShortName) {
            xCHECK_RET(CxStringCI::compare(a_month, shortMonths[i]), i);
        } else {
            xCHECK_RET(CxStringCI::compare(a_month, longMonths[i]),  i);
        }
    }

    return - 1;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxDateTime::weekDayStr(
    cint_t  &a_week_day,
    cbool_t &a_isShortName
)
{
    xTEST_EQ(CxValidator::weekDay(a_week_day), true);
    xTEST_NA(a_isShortName);

    // days since Sunday (0-6)

    std::tstring_t sRv;

    if (!a_isShortName) {
        const CxArray<std::tstring_t, 7> longDays = {{
            xT("Sunday"),
            xT("Monday"),
            xT("Tuesday"),
            xT("Wednesday"),
            xT("Thursday"),
            xT("Friday"),
            xT("Saturday")
        }};

        sRv = longDays[a_week_day];
    } else {
        const CxArray<std::tstring_t, 8> shortDays = {{
            xT("Sun"),
            xT("Mon"),
            xT("Tue"),
            xT("Wed"),
            xT("Thu"),
            xT("Fri"),
            xT("Sat")
        }};

        sRv = shortDays[a_week_day];
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxDateTime::weekDayNum(
    std::ctstring_t &a_week_day,
    cbool_t         &a_isShortName
)
{
    xTEST_NA(a_week_day);
    xTEST_NA(a_isShortName);

    const CxArray<std::tstring_t, 7> longDays = {{
        xT("Monday"),
        xT("Tuesday"),
        xT("Wednesday"),
        xT("Thursday"),
        xT("Friday"),
        xT("Saturday"),
        xT("Sunday")
    }};

    const CxArray<std::tstring_t, 7> shortDays = {{
        xT("Mon"),
        xT("Tue"),
        xT("Wed"),
        xT("Thu"),
        xT("Fri"),
        xT("Sat"),
        xT("Sun")
    }};

    for (int_t i = 0; i < static_cast<int_t>( longDays.size() ); ++ i) {
        xCHECK_RET(!a_isShortName && CxStringCI::compare(a_week_day, longDays[i]),  i);
        xCHECK_RET( a_isShortName && CxStringCI::compare(a_week_day, shortDays[i]), i);
    }

    return - 1;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, core)
