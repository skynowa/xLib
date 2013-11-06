/**
 * \file  CxDateTime.cpp
 * \brief date, time
 */


#include <xLib/Core/CxDateTime.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxArray.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTracer.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public: constructors, destructor
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxDateTime::CxDateTime() :
    _thisMSec(0ULL),
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0)
{
}
//------------------------------------------------------------------------------
xINLINE_HO
CxDateTime::CxDateTime(
    std::ctstring_t    &a_datetime,
    const ExFormatType &a_format
) :
    _thisMSec(0ULL),
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0)
{
    CxDateTime dtDT;

    _parse(a_datetime, a_format, &dtDT);

    set(dtDT._year, dtDT._month,  dtDT._day,
        dtDT._hour, dtDT._minute, dtDT._second, dtDT._msec);
}
//------------------------------------------------------------------------------
xINLINE_HO
CxDateTime::CxDateTime(
    const CxDateTime &a_datetime
) :
    _thisMSec(0ULL),
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0)
{
    set(a_datetime._year, a_datetime._month,  a_datetime._day,
        a_datetime._hour, a_datetime._minute, a_datetime._second, a_datetime._msec);
}
//------------------------------------------------------------------------------
xINLINE_HO
CxDateTime::CxDateTime(
    culonglong_t &a_msec
) :
    _thisMSec(0ULL),
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0)
{
    set(a_msec);
}
//------------------------------------------------------------------------------
xINLINE_HO
CxDateTime::CxDateTime(
    cushort_t &a_hour,
    cushort_t &a_minute,
    cushort_t &a_second,
    cushort_t &a_msec
) :
    _thisMSec(0ULL),
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0)
{
    set(0, 0, 0, a_hour, a_minute, a_second, a_msec);
}
//------------------------------------------------------------------------------
xINLINE_HO
CxDateTime::CxDateTime(
    cushort_t &a_year,
    cushort_t &a_month,
    cushort_t &a_day
) :
    _thisMSec(0),
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0)
{
    set(a_year, a_month, a_day, 0, 0, 0, 0);
}
//------------------------------------------------------------------------------
xINLINE_HO
CxDateTime::CxDateTime(
    cushort_t &a_year,
    cushort_t &a_month,
    cushort_t &a_day,
    cushort_t &a_hour,
    cushort_t &a_minute,
    cushort_t &a_second,
    cushort_t &a_msec
) :
    _thisMSec(0ULL),
    _year    (0),
    _month   (0),
    _day     (0),
    _hour    (0),
    _minute  (0),
    _second  (0),
    _msec    (0)
{
     set(a_year, a_month, a_day, a_hour, a_minute, a_second, a_msec);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: comparison operators
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDateTime::operator == (
    const CxDateTime &a_datetime
) const
{
    xTEST_EQ(true, isValid());
    xTEST_EQ(true, isValid(a_datetime));

    return (_thisMSec == a_datetime._thisMSec);
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDateTime::operator != (
    const CxDateTime &a_datetime
) const
{
    xTEST_EQ(true, isValid());
    xTEST_EQ(true, isValid(a_datetime));

    return ( _thisMSec != a_datetime._thisMSec );
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDateTime::operator < (
    const CxDateTime &a_datetime
) const
{
    xTEST_EQ(true, isValid());
    xTEST_EQ(true, isValid(a_datetime));

    return ( _thisMSec < a_datetime._thisMSec );
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDateTime::operator <= (
    const CxDateTime &a_datetime
) const
{
    xTEST_EQ(true, isValid());
    xTEST_EQ(true, isValid(a_datetime));

    return ( _thisMSec <= a_datetime._thisMSec );
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDateTime::operator > (
    const CxDateTime &a_datetime
) const
{
    xTEST_EQ(true, isValid());
    xTEST_EQ(true, isValid(a_datetime));

    return ( _thisMSec > a_datetime._thisMSec );
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDateTime::operator >= (
    const CxDateTime &a_datetime
) const
{
    xTEST_EQ(true, isValid());
    xTEST_EQ(true, isValid(a_datetime));

    return ( _thisMSec >= a_datetime._thisMSec );
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: assignment operators
*
*******************************************************************************/

//--------------------------------------------------------------------------
xINLINE_HO const CxDateTime &
CxDateTime::operator = (
    const CxDateTime &a_datetime
)
{
    xTEST_EQ(true, isValid());

    xCHECK_RET(this == &a_datetime, *this);

    set(a_datetime._thisMSec);

    return *this;
}
//------------------------------------------------------------------------------
xINLINE_HO const CxDateTime &
CxDateTime::operator = (
    culonglong_t &a_msec
)
{
    xTEST_EQ(true, isValid());

    set(a_msec);

    return *this;
}
//--------------------------------------------------------------------------
xINLINE_HO CxDateTime
CxDateTime::operator + (
    const CxDateTime &a_datetime
) const
{
    xTEST_EQ(true, isValid());

    return CxDateTime(_thisMSec + a_datetime._thisMSec);
}
//--------------------------------------------------------------------------
xINLINE_HO CxDateTime
CxDateTime::operator - (
    const CxDateTime &a_datetime
) const
{
    xTEST_EQ(true, isValid());

    return CxDateTime(_thisMSec - a_datetime._thisMSec);
}
//--------------------------------------------------------------------------
xINLINE_HO const CxDateTime &
CxDateTime::operator += (
    const CxDateTime &a_datetime
)
{
    xTEST_EQ(true, isValid());

    _thisMSec += a_datetime._thisMSec;

    set(_thisMSec);

    return *this;
}
//--------------------------------------------------------------------------
xINLINE_HO const CxDateTime &
CxDateTime::operator -= (
    const CxDateTime &a_datetime
)
{
    xTEST_EQ(true, isValid());

    _thisMSec -= a_datetime._thisMSec;

    set(_thisMSec);

    return *this;
}
//--------------------------------------------------------------------------


/*******************************************************************************
*    public:
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDateTime::get(
    ushort_t *a_year,
    ushort_t *a_month,
    ushort_t *a_day,
    ushort_t *a_hour,
    ushort_t *a_minute,
    ushort_t *a_second,
    ushort_t *a_msec
) const
{
    xTEST_EQ(true, isValid());
    // n/a

    CxUtils::ptrAssignT(a_year,   _year);
    CxUtils::ptrAssignT(a_month,  _month);
    CxUtils::ptrAssignT(a_day,    _day);
    CxUtils::ptrAssignT(a_hour,   _hour);
    CxUtils::ptrAssignT(a_minute, _minute);
    CxUtils::ptrAssignT(a_second, _second);
    CxUtils::ptrAssignT(a_msec,   _msec);
}
//------------------------------------------------------------------------------
xINLINE_HO ushort_t
CxDateTime::dayOfWeek() const
{
    xTEST_EQ(true, isValid()); //??? - 0

    ushort_t usRv     = 0;
    tm       timeInfo = {0};

    timeInfo.tm_year = _year  - 1900;
    timeInfo.tm_mon  = _month - 1;
    timeInfo.tm_mday = _day;

    time_t tmTime = std::mktime(&timeInfo);
    xTEST_DIFF(static_cast<time_t>( - 1 ), tmTime);

    usRv = timeInfo.tm_wday;
    //xTRACEV(xT("That day is a %s"), sGetWeekDayStr(usRv, false).c_str());

    return usRv;
}
//------------------------------------------------------------------------------
// TODO: toMilliseconds
xINLINE_HO ulonglong_t
CxDateTime::toMilliseconds() const
{
    xTEST_EQ(true, isValid()); //??? - 0

    return _thisMSec;
}
//--------------------------------------------------------------------------
xINLINE_HO void_t
CxDateTime::set(
    culonglong_t &a_msec
)
{
    // n/a
    // ullMSec - n/a

    //--------------------------------------------------
    // datetime msec member
    _thisMSec = a_msec;

    //--------------------------------------------------
    // datetime members
    ulonglong_t msec = a_msec;

    // converts milliseconds to datetime members
    _year    = static_cast<ushort_t>( msec / ((1000ULL * 60 * 60 * 24 * 30) * 12) );

    msec    %= ((1000ULL * 60 * 60 * 24 * 30) * 12);
    _month   = static_cast<ushort_t>( msec / ((1000ULL * 60 * 60 * 24) * 30) );

    msec    %= ((1000ULL * 60 * 60 * 24) * 30);
    _day     = static_cast<ushort_t>( msec / ((1000ULL * 60 * 60) * 24) );

    msec    %= ((1000ULL * 60 * 60) * 24);
    _hour    = static_cast<ushort_t>( msec / ((1000ULL * 60) * 60) );

    msec    %= ((1000ULL * 60) * 60);
    _minute  = static_cast<ushort_t>( msec / ((1000ULL * 60)) );

    msec    %= ((1000ULL * 60));
    _second  = static_cast<ushort_t>( msec / 1000ULL );

    msec    %= 1000ULL;
    _msec    = static_cast<ushort_t>( msec );
}
//--------------------------------------------------------------------------
xINLINE_HO void_t
CxDateTime::set(
    cushort_t &a_year,
    cushort_t &a_month,
    cushort_t &a_day,
    cushort_t &a_hour,
    cushort_t &a_minute,
    cushort_t &a_second,
    cushort_t &a_msec
)
{
    // n/a
    // n/a

    xTEST_EQ(true, isValid(a_year, a_month, a_day, a_hour, a_minute, a_second, a_msec));

    //datetime members
    _year   = a_year;
    _month  = a_month;
    _day    = a_day;
    _hour   = a_hour;
    _minute = a_minute;
    _second = a_second;
    _msec   = a_msec;

    //datetime msec member (convert to milliseconds)
    _thisMSec = _toMilliseconds();

    xTEST_EQ(true, isValid());
}
//--------------------------------------------------------------------------


/*******************************************************************************
*    converting
*
*******************************************************************************/

//--------------------------------------------------------------------------
xINLINE_HO ulonglong_t
CxDateTime::_toMilliseconds() const
{
    xTEST_EQ(true, isValid());

    ulonglong_t ullRv = 0ULL;

    ullRv += _year   * 1000ULL * 60 * 60 * 24 * 30 * 12;      //TODO: days in month 30 or 31 ???
    ullRv += _month  * 1000ULL * 60 * 60 * 24 * 30;
    ullRv += _day    * 1000ULL * 60 * 60 * 24;
    ullRv += _hour   * 1000ULL * 60 * 60;
    ullRv += _minute * 1000ULL * 60;
    ullRv += _second * 1000ULL * 1;
    ullRv += _msec;

    return ullRv;
}
//--------------------------------------------------------------------------


/*******************************************************************************
*    public: formating
*
*******************************************************************************/

//--------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxDateTime::format(
    const ExFormatType &a_format
) const
{
    xTEST_EQ(true, isValid());
    // n/a

    std::tstring_t sRv;

    switch (a_format) {
    case ftTime:
        sRv = CxString::format(
                xT("%d:%.2d:%.2d:%.3d"),
                _hour, _minute, _second, _msec);
        break;
    case ftDate:
        sRv = CxString::format(
                xT("%.2d.%.2d.%.4d"),
                _day, _month, _year);
        break;
    case ftDateTime:
        sRv = CxString::format(
                xT("%.2d.%.2d.%.4d %d:%.2d:%.2d:%.3d"),
                _day, _month, _year,
                _hour, _minute, _second, _msec);
        break;
    case ftRFC1123:
        sRv = CxString::format(
                xT("%s, %.2d %s %.4d %.2d:%.2d:%.2d GMT"),
                weekDayStr(dayOfWeek(), true).c_str(), _day,
                CxDateTime::monthStr(_month, true).c_str(), _year,
                _hour, _minute, _second);
        break;
    default:
        xTEST_FAIL;
        break;
    }

    return sRv;
}
//--------------------------------------------------------------------------


/*******************************************************************************
*    public: static
*
*******************************************************************************/

//--------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxDateTime::isValid(
    cushort_t &a_year,
    cushort_t &a_month,
    cushort_t &a_day,
    cushort_t &a_hour,
    cushort_t &a_minute,
    cushort_t &a_second,
    cushort_t &a_msec
)
{
    bool_t bYear   = (/*cusYear   >= 0U && */a_year   <= 9999U);
    xTEST_EQ(true, bYear);

    bool_t bMonth  = (/*cusMonth  >= 0 /1/ &&*/ a_month  <= 12U);
    xTEST_EQ(true, bMonth);

    bool_t bDay    = true;   ////(usDay    >= 0/*1*/ && usDay    <= usDaysInMonth(a_usYear, a_month));
    xTEST_EQ(true, bDay);

    bool_t bHour   = (/*cusHour   >= 0 &&*/ a_hour   <= 23U);
    xTEST_EQ(true, bHour);

    bool_t bMinute = (/*cusMinute >= 0 &&*/ a_minute <= 59U);
    xTEST_EQ(true, bMinute);

    bool_t bSecond = (/*cusSecond >= 0 &&*/ a_second <= 59U);
    xTEST_EQ(true, bSecond);

    bool_t bMsec   = (/*cusMillisecond >= 0 &&*/ a_msec   <= 999U);
    xTEST_EQ(true, bMsec);

    xCHECK_RET(!(bYear && bMonth && bDay && bHour && bMinute && bSecond && bMsec), false);

    return true;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxDateTime::isValid(
    const CxDateTime &a_datetime
)
{
    return isValid(a_datetime._year, a_datetime._month, a_datetime._day,
        a_datetime._hour, a_datetime._minute, a_datetime._second, a_datetime._msec);
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDateTime::isValid() const
{
    return isValid(*this);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO CxDateTime
CxDateTime::current()
{
#if xOS_ENV_WIN
    SYSTEMTIME dateTime = {0};

    (void_t)::GetLocalTime(&dateTime);
    xTEST_EQ(true, isValid(dateTime.wYear, dateTime.wMonth, dateTime.wDay,
        dateTime.wHour, dateTime.wMinute, dateTime.wSecond, dateTime.wMilliseconds));

    return CxDateTime(dateTime.wYear, dateTime.wMonth, dateTime.wDay,
        dateTime.wHour, dateTime.wMinute, dateTime.wSecond, dateTime.wMilliseconds);
#else
    // get milliseconds
    timeval time = {0};

    int_t iRv = ::gettimeofday(&time, NULL);
    xTEST_DIFF(- 1, iRv);

    // get datetime
    std::tm *dateTime = {0};

    dateTime = std::localtime( reinterpret_cast<const time_t *>( &time.tv_sec ));
    xTEST_PTR(dateTime);

    // set datetime
    ushort_t usYear        = dateTime->tm_year + 1900U;
    ushort_t usMonth       = dateTime->tm_mon  + 1U;   //TODO: +1U ???
    ushort_t usDay         = dateTime->tm_mday;
    ushort_t usHour        = dateTime->tm_hour;
    ushort_t usMinute      = dateTime->tm_min;
    ushort_t usSecond      = dateTime->tm_sec;
    ushort_t usMillisecond = static_cast<ushort_t>( time.tv_usec * 0.001 );

    xTEST_EQ(true, isValid(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond));

    return CxDateTime(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond);
#endif
}
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

/* static */
xINLINE_HO longlong_t
CxDateTime::filetimeToInt64(
    const FILETIME &a_fileTime
)
{
    return Int64ShllMod32(a_fileTime.dwHighDateTime, 32) | a_fileTime.dwLowDateTime;
}

#endif
//--------------------------------------------------------------------------
#if xOS_ENV_WIN

/* static */
xINLINE_HO void_t
CxDateTime::unixTimeToFileTime(
    const time_t &a_unixTime,
    FILETIME     *a_fileTime
)
{
    // ctmTime - n/a
    xTEST_PTR(a_fileTime);

    longlong_t llRv = 0LL;

    llRv = Int32x32To64(a_unixTime, 10000000) + 116444736000000000;
    a_fileTime->dwLowDateTime  = static_cast<ulong_t>( llRv );
    a_fileTime->dwHighDateTime = llRv >> 32;
}

#endif

//------------------------------------------------------------------------------
#if xOS_ENV_WIN

//TODO: make tests tmFileTimeToUnixTime
/* static */
xINLINE_HO time_t
CxDateTime::fileTimeToUnixTime(
    const FILETIME &a_fileTime
)
{
    const __int64 NANOSECS_BETWEEN_EPOCHS = 116444736000000000LL;

    __int64 llRv = 0LL;

    llRv = (static_cast<__int64>( a_fileTime.dwHighDateTime ) << 32) + a_fileTime.dwLowDateTime;
    llRv -= NANOSECS_BETWEEN_EPOCHS;
    llRv /= 10000000;

    return static_cast<time_t>( llRv );
}

#endif
//--------------------------------------------------------------------------
/* static */
xINLINE_HO ushort_t
CxDateTime::daysInMonth(
    cushort_t &a_year,
    cushort_t &a_month
)
{
    xCHECK_RET(2 == a_month && isLeapYear(a_year), 29);

    const CxArray<ushort_t, 13> monthsDays = {{/*31*/0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

    ushort_t usRv = 0;

    usRv = monthsDays[a_month];

    return usRv;
}
//--------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxDateTime::isLeapYear(
    cushort_t &a_year
)
{
    return ( 0 == (a_year % 4) && ( 0 != (a_year % 100) || 0 == (a_year % 400)) );
}
//--------------------------------------------------------------------------


/*******************************************************************************
*    public: other
*
*******************************************************************************/

//------------------------------------------------------------------------------
/*
NOTE: signs of the zodiac

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

/* static */
xINLINE_HO std::tstring_t
CxDateTime::zodiacSign(
    cushort_t &a_month,
    cushort_t &a_day
)
{
    // usDay
    // usMonth

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
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxDateTime::monthStr(
    ushort_t  a_month,
    cbool_t  &a_isShortName
)
{
    // usMonth      - n/a
    // bIsShortName - n/a

    xCHECK_DO(12 < a_month, a_month = 12);
    xCHECK_DO(1  > a_month, a_month = 1);

    std::tstring_t sRv;

    if (!a_isShortName) {
        // months numbering: 1-12
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

        sRv = longMonths[a_month - 1];
    }
    else {
        // months numbering: 1-12
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

        sRv = shortMonths[a_month - 1];
    }

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO ushort_t
CxDateTime::monthNum(
    std::ctstring_t &a_month,
    cbool_t         &a_isShortName
)
{


    // months numbering: 1-12
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

    // months numbering: 1-12
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

    for (ushort_t i = 0; i < static_cast<ushort_t>( longMonths.size() ); ++ i) {
        xCHECK_RET(!a_isShortName && CxString::compareNoCase(a_month, longMonths[i]),  i + 1);
        xCHECK_RET(true  == a_isShortName && CxString::compareNoCase(a_month, shortMonths[i]), i + 1);
    }

    return static_cast<ushort_t>( - 1 );  //TODO: static_cast<ushort_t>( - 1 )
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxDateTime::weekDayStr(
    ushort_t  a_day,
    cbool_t  &a_isShortName
)
{
    // cusDay       - n/a
    // cbIsShortName - n/a

    xCHECK_DO(6 < a_day, a_day = 6);

    std::tstring_t sRv;

    if (!a_isShortName) {
        //days numbering: 0-6
        const CxArray<std::tstring_t, 7> longDays = {{
            xT("Sunday"),
            xT("Monday"),
            xT("Tuesday"),
            xT("Wednesday"),
            xT("Thursday"),
            xT("Friday"),
            xT("Saturday"),
        }};

        sRv = longDays[a_day];
    } else {
        //days numbering: 0-6
        const CxArray<std::tstring_t, 8> shortDays = {{
            xT("Sun"),
            xT("Mon"),
            xT("Tue"),
            xT("Wed"),
            xT("Thu"),
            xT("Fri"),
            xT("Sat")
        }};

        sRv = shortDays[a_day];
    }

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO ushort_t
CxDateTime::weekDayNum(
    std::ctstring_t &a_day,
    cbool_t         &a_isShortName
)
{
    //days numbering: 0-6
    const CxArray<std::tstring_t, 7> longDays = {{
        xT("Sunday"),
        xT("Monday"),
        xT("Tuesday"),
        xT("Wednesday"),
        xT("Thursday"),
        xT("Friday"),
        xT("Saturday")
    }};

    //days numbering: 0-6
    const CxArray<std::tstring_t, 7> shortDays = {{
        xT("Sun"),
        xT("Mon"),
        xT("Tue"),
        xT("Wed"),
        xT("Thu"),
        xT("Fri"),
        xT("Sat")
    }};

    for (ushort_t i = 0; i < static_cast<ushort_t>( longDays.size() ); ++ i) {
        xCHECK_RET(!a_isShortName && CxString::compareNoCase(a_day, longDays[i]),  i);
        xCHECK_RET(true  == a_isShortName && CxString::compareNoCase(a_day, shortDays[i]), i);
    }

    return static_cast<ushort_t>( - 1 );  //TODO: static_cast<ushort_t>( - 1 )
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxDateTime::_parse(
    std::ctstring_t    &a_value,
    const ExFormatType &a_format,
    CxDateTime         *a_datetime
)
{
    switch (a_format) {
    case ftTime:
        // TODO: ftTime
        break;
    case ftDate:
        // TODO: ftDate
        break;
    case ftDateTime:
        // TODO: ftDateTime
        break;
    case ftRFC1123: {
        // Wdy, DD Mon YYYY HH:MM:SS GMT (Wed, 23 Mar 2011 15:05:49 GMT)

        // replace ":" to " ", "-" to " "
        std::tstring_t dateTime = a_value;
        dateTime = CxString::replaceAll(dateTime, CxConst::xCOLON(),  CxConst::xSPACE());
        dateTime = CxString::replaceAll(dateTime, CxConst::xHYPHEN(), CxConst::xSPACE());

        // split by separator " "
        std::vec_tstring_t dates;
        CxString::split(dateTime, CxConst::xSPACE(), &dates);

        //                   = CxString::cast<ushort_t>( dates.at(0) );    // Wed(0),
        (*a_datetime)._day    = CxString::cast<ushort_t>( dates.at(1) );   // 23(1)
        (*a_datetime)._month  = monthNum(dates.at(2), true);               // Mar(2)
        (*a_datetime)._year   = CxString::cast<ushort_t>( dates.at(3) );   // 2011(3)
        (*a_datetime)._hour   = CxString::cast<ushort_t>( dates.at(4) );   // 15(4)
        (*a_datetime)._minute = CxString::cast<ushort_t>( dates.at(5) );   // 05(5)
        (*a_datetime)._second = CxString::cast<ushort_t>( dates.at(6) );   // 49(6)

    #if xTEMP_DISABLED
        xTRACE(xT("-----------------------------------"));
        xTRACE(xFUNCTION);
        xTRACEV(xT("_day:    %i"), (*a_datetime)._day);
        xTRACEV(xT("_month:  %i"), (*a_datetime)._month);
        xTRACEV(xT("_year:   %i"), (*a_datetime)._year);
        xTRACEV(xT("_hour:   %i"), (*a_datetime)._hour);
        xTRACEV(xT("_minute: %i"), (*a_datetime)._minute);
        xTRACEV(xT("_second: %i"), (*a_datetime)._second);
        xTRACE(xT("-----------------------------------"));
    #endif
        break;
    }
    default:
        xTEST_FAIL;
        break;
    }
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
