/**
 * \file  DateTime.inl
 * \brief date, time
 */


#include "DateTime.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Array.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/Units.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/DateTime_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/DateTime_unix.inl"

    #if   xENV_LINUX

    #elif xENV_BSD

    #elif xENV_APPLE

    #endif
#endif


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   public: validate
*
**************************************************************************************************/

xNAMESPACE_ANONYM_BEGIN

cint_t yearMin     = 0;
cint_t yearMax     = 9999;

cint_t monthMin    = 0;
cint_t monthMax    = 11;

cint_t dayMin      = 1;
cint_t dayMax      = 31;

cint_t hourMin     = 0;
cint_t hourMax     = 23;

cint_t minuteMin   = 0;
cint_t minuteMax   = 59;

cint_t secondMin   = 0;
cint_t secondMax   = 60;	// (1 leap second)

cint_t msecMin     = 0;
cint_t msecMax     = 999;

cint_t microsecMin = 0;
cint_t microsecMax = 999;

cint_t weekDayMin  = 0;
cint_t weekDayMax  = 6;

xNAMESPACE_ANONYM_END

//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::year(
    cint_t &a_year
)
{
    return (a_year >= yearMin && a_year <= yearMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::month(
    cint_t &a_month
)
{
    return (a_month >= monthMin && a_month <= monthMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::day(
    cint_t &a_day
)
{
    return (a_day >= dayMin && a_day <= dayMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::hour(
    cint_t &a_hour
)
{
    return (a_hour >= hourMin && a_hour <= hourMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::minute(
    cint_t &a_minute
)
{
    return (a_minute >= minuteMin && a_minute <= minuteMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::second(
    cint_t &a_second
)
{
    return (a_second >= secondMin && a_second <= secondMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::msec(
    cint_t &a_msec
)
{
    return (a_msec >= msecMin && a_msec <= msecMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::weekDay(
    cint_t &a_weekDay
)
{
    return (a_weekDay >= weekDayMin && a_weekDay <= weekDayMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::date(
    cint_t &a_year,
    cint_t &a_month,
    cint_t &a_day
)
{
    return (year(a_year) && month(a_month) && day(a_day));
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::time(
    cint_t &a_hour,
    cint_t &a_minute,
    cint_t &a_second,
    cint_t &a_msec
)
{
    return (hour(a_hour) && minute(a_minute) && second(a_second) && msec(a_msec));
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::datetime(
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

    return (date(a_year, a_month, a_day) && time(a_hour, a_minute, a_second, a_msec));
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::datetime(
    const DateTime &a_datetime
)
{
    return (date(a_datetime._year, a_datetime._month, a_datetime._day) &&
            time(a_datetime._hour, a_datetime._minute, a_datetime._second, a_datetime._msec));
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::dateOrTime(
    cint_t &a_year,
    cint_t &a_month,
    cint_t &a_day,
    cint_t &a_hour,
    cint_t &a_minute,
    cint_t &a_second,
    cint_t &a_msec
)
{
    return (date(a_year, a_month, a_day) || time(a_hour, a_minute, a_second, a_msec));
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: constructors, destructor
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
DateTime::DateTime() :
    _year    (yearMin),
    _month   (monthMin),
    _day     (0),
    _hour    (hourMin),
    _minute  (minuteMin),
    _second  (secondMin),
    _msec    (msecMin),
    _thisMSec(0ULL)
{
}
//-------------------------------------------------------------------------------------------------
DateTime::DateTime(
    const DateTime &a_datetime
) :
    _year    (yearMin),
    _month   (monthMin),
    _day     (0),
    _hour    (hourMin),
    _minute  (minuteMin),
    _second  (secondMin),
    _msec    (msecMin),
    _thisMSec(0ULL)
{
    xTEST_EQ(DateTimeValidator::date(a_datetime._year, a_datetime._month, a_datetime._day) &&
        DateTimeValidator::time(a_datetime._hour, a_datetime._minute, a_datetime._second,
        a_datetime._msec), true);

    set(a_datetime._year, a_datetime._month,  a_datetime._day,
        a_datetime._hour, a_datetime._minute, a_datetime._second, a_datetime._msec);
}
//-------------------------------------------------------------------------------------------------
DateTime::DateTime(
    culonglong_t &a_msec
) :
    _year    (yearMin),
    _month   (monthMin),
    _day     (0),
    _hour    (hourMin),
    _minute  (minuteMin),
    _second  (secondMin),
    _msec    (msecMin),
    _thisMSec(0ULL)
{
    set(a_msec);
}
//-------------------------------------------------------------------------------------------------
DateTime::DateTime(
    cint_t &a_hour,
    cint_t &a_minute,
    cint_t &a_second,
    cint_t &a_msec
) :
    _year    (yearMin),
    _month   (monthMin),
    _day     (0),
    _hour    (hourMin),
    _minute  (minuteMin),
    _second  (secondMin),
    _msec    (msecMin),
    _thisMSec(0ULL)
{
    xTEST_EQ(DateTimeValidator::time(a_hour, a_minute, a_second, a_msec), true);

    set(0, 0, 0, a_hour, a_minute, a_second, a_msec);
}
//-------------------------------------------------------------------------------------------------
DateTime::DateTime(
    cint_t &a_year,
    cint_t &a_month,
    cint_t &a_day
) :
    _year    (yearMin),
    _month   (monthMin),
    _day     (0),
    _hour    (hourMin),
    _minute  (minuteMin),
    _second  (secondMin),
    _msec    (msecMin),
    _thisMSec(0ULL)
{
    xTEST_EQ(DateTimeValidator::date(a_year, a_month, a_day), true);

    set(a_year, a_month, a_day, 0, 0, 0, 0);
}
//-------------------------------------------------------------------------------------------------
DateTime::DateTime(
    cint_t &a_year,
    cint_t &a_month,
    cint_t &a_day,
    cint_t &a_hour,
    cint_t &a_minute,
    cint_t &a_second,
    cint_t &a_msec
) :
    _year    (yearMin),
    _month   (monthMin),
    _day     (0),
    _hour    (hourMin),
    _minute  (minuteMin),
    _second  (secondMin),
    _msec    (msecMin),
    _thisMSec(0ULL)
{
    xTEST_EQ(DateTimeValidator::date(a_year, a_month, a_day) &&
        DateTimeValidator::time(a_hour, a_minute, a_second, a_msec), true);

    set(a_year, a_month, a_day, a_hour, a_minute, a_second, a_msec);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: comparison operators
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
DateTime::operator == (
    const DateTime &a_datetime
) const
{
	xTEST_NA;

    return (_thisMSec == a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTime::operator != (
    const DateTime &a_datetime
) const
{
	xTEST_NA;

    return (_thisMSec != a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTime::operator < (
    const DateTime &a_datetime
) const
{
	xTEST_NA;

    return (_thisMSec < a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTime::operator <= (
    const DateTime &a_datetime
) const
{
	xTEST_NA;

    return (_thisMSec <= a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTime::operator > (
    const DateTime &a_datetime
) const
{
	xTEST_NA;

    return (_thisMSec > a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTime::operator >= (
    const DateTime &a_datetime
) const
{
	xTEST_NA;

    return (_thisMSec >= a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: assignment operators
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
DateTime &
DateTime::operator = (
    const DateTime &a_datetime
)
{
    xCHECK_RET(this == &a_datetime, *this);

    set(a_datetime._thisMSec);

    return *this;
}
//-------------------------------------------------------------------------------------------------
DateTime &
DateTime::operator = (
    culonglong_t &a_msec
)
{
    set(a_msec);

    return *this;
}
//-------------------------------------------------------------------------------------------------
DateTime
DateTime::operator + (
    const DateTime &a_datetime
) const
{
    return DateTime(_thisMSec + a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
DateTime
DateTime::operator - (
    const DateTime &a_datetime
) const
{
    return DateTime(_thisMSec - a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
const DateTime &
DateTime::operator += (
    const DateTime &a_datetime
)
{
    _thisMSec += a_datetime._thisMSec;

    set(_thisMSec);

    return *this;
}
//-------------------------------------------------------------------------------------------------
const DateTime &
DateTime::operator -= (
    const DateTime &a_datetime
)
{
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
void_t
DateTime::get(
    int_t *a_year,
    int_t *a_month,
    int_t *a_day,
    int_t *a_hour,
    int_t *a_minute,
    int_t *a_second,
    int_t *a_msec
) const
{
    xTEST_NA;

    Utils::ptrAssignT(a_year,   _year);
    Utils::ptrAssignT(a_month,  _month);
    Utils::ptrAssignT(a_day,    _day);
    Utils::ptrAssignT(a_hour,   _hour);
    Utils::ptrAssignT(a_minute, _minute);
    Utils::ptrAssignT(a_second, _second);
    Utils::ptrAssignT(a_msec,   _msec);
}
//-------------------------------------------------------------------------------------------------
int_t
DateTime::dayOfWeek() const
{
    xTEST_EQ(DateTimeValidator::datetime(*this), true);

    int_t   iRv = 0;
    std::tm timeInfo;  Utils::structZeroT(timeInfo);

    timeInfo.tm_year = _year  - 1900;
    timeInfo.tm_mon  = _month - 1;
    timeInfo.tm_mday = _day;

    time_t time = std::mktime(&timeInfo);
    xTEST_DIFF(static_cast<time_t>( - 1 ), time);

    iRv = timeInfo.tm_wday;

    return iRv;
}
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] toMsec
ulonglong_t
DateTime::toMsec() const
{
    return _thisMSec;
}
//-------------------------------------------------------------------------------------------------
void_t
DateTime::set(
    culonglong_t &a_msec
)
{
    xTEST_NA;

    // datetime msec member
    _thisMSec = a_msec;

    // datetime members
    ulonglong_t msec = a_msec;

    // converts milliseconds to datetime members
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
}
//-------------------------------------------------------------------------------------------------
void_t
DateTime::set(
    cint_t &a_year,
    cint_t &a_month,
    cint_t &a_day,
    cint_t &a_hour,
    cint_t &a_minute,
    cint_t &a_second,
    cint_t &a_msec
)
{
    xTEST_NA;

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
ulonglong_t
DateTime::_toMsec() const
{
    xTEST_NA;

    ulonglong_t ullRv = 0ULL;

    ullRv += xYEAR(_year);    // TODO: [skynowa] DateTime::_toMsec() - days in month 30 or 31 ???
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
std::tstring_t
DateTime::format(
    std::ctstring_t &a_format,                         ///< datetime format
    std::ctstring_t &a_formatMsec /* = xT(".%03d") */  ///< milliseconds format
) const
{
    xTEST_NA;
    xTEST_EQ(a_format.empty(), false);
    xTEST_NA(a_formatMsec);

    std::tstring_t sRv;
    tchar_t        buff[80 + 1] = {};

    std::tm time; Utils::structZeroT(time);
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
        sRv += FormatC::str(a_formatMsec.c_str(), _msec);
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
DateTime
DateTime::current()
{
    return _current_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
int_t
DateTime::daysInMonth(
    cint_t &a_year,
    cint_t &a_month
)
{
    xCHECK_RET(a_month == 2 && isLeapYear(a_year), 29);

    const Array<int_t, monthMax + 1> monthsDays =
    {{
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    }};

    return monthsDays[ static_cast<std::size_t>(a_month) ];
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
DateTime::isLeapYear(
    cint_t &a_year
)
{
    return ((a_year % 4) == 0 && ((a_year % 100) != 0 || (a_year % 400) == 0));
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
DateTime::zodiacSign(
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
std::tstring_t
DateTime::monthStr(
    cint_t  &a_month,
    cbool_t &a_isShortName
)
{
    xTEST_EQ(DateTimeValidator::month(a_month), true);
    xTEST_NA(a_isShortName);

    std::tstring_t sRv;

    if (!a_isShortName) {
        // months numbering: 0-11
        const Array<std::tstring_t, monthMax + 1> longMonths =
        {{
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

        sRv = longMonths[ static_cast<std::size_t>(a_month) ];
    } else {
        // months numbering: 0-11
        const Array<std::tstring_t, monthMax + 1> shortMonths =
        {{
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

        sRv = shortMonths[ static_cast<std::size_t>(a_month) ];
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
int_t
DateTime::monthNum(
    std::ctstring_t &a_month,
    cbool_t         &a_isShortName
)
{
    xTEST_NA(a_month);
    xTEST_NA(a_isShortName);

    // months numbering: 0-11
    const Array<std::tstring_t, monthMax + 1> longMonths =
    {{
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
    const Array<std::tstring_t, monthMax + 1> shortMonths =
    {{
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
            xCHECK_RET(StringCI::compare(a_month, shortMonths[ static_cast<std::size_t>(i) ]), i);
        } else {
            xCHECK_RET(StringCI::compare(a_month, longMonths[ static_cast<std::size_t>(i) ]),  i);
        }
    }

    return - 1;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
DateTime::weekDayStr(
    cint_t  &a_week_day,
    cbool_t &a_isShortName
)
{
    xTEST_EQ(DateTimeValidator::weekDay(a_week_day), true);
    xTEST_NA(a_isShortName);

    // days since Sunday (0-6)

    std::tstring_t sRv;

    if (!a_isShortName) {
        const Array<std::tstring_t, weekDayMax + 1> longDays =
        {{
            xT("Sunday"),
            xT("Monday"),
            xT("Tuesday"),
            xT("Wednesday"),
            xT("Thursday"),
            xT("Friday"),
            xT("Saturday")
        }};

        sRv = longDays[ static_cast<std::size_t>(a_week_day) ];
    } else {
        const Array<std::tstring_t, weekDayMax + 1> shortDays =
        {{
            xT("Sun"),
            xT("Mon"),
            xT("Tue"),
            xT("Wed"),
            xT("Thu"),
            xT("Fri"),
            xT("Sat")
        }};

        sRv = shortDays[ static_cast<std::size_t>(a_week_day) ];
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
int_t
DateTime::weekDayNum(
    std::ctstring_t &a_week_day,
    cbool_t         &a_isShortName
)
{
    xTEST_NA(a_week_day);
    xTEST_NA(a_isShortName);

    const Array<std::tstring_t, weekDayMax + 1> longDays =
    {{
        xT("Monday"),
        xT("Tuesday"),
        xT("Wednesday"),
        xT("Thursday"),
        xT("Friday"),
        xT("Saturday"),
        xT("Sunday")
    }};

    const Array<std::tstring_t, weekDayMax + 1> shortDays =
    {{
        xT("Mon"),
        xT("Tue"),
        xT("Wed"),
        xT("Thu"),
        xT("Fri"),
        xT("Sat"),
        xT("Sun")
    }};

    for (int_t i = 0; i < static_cast<int_t>( longDays.size() ); ++ i) {
        xCHECK_RET(!a_isShortName && StringCI::compare(a_week_day, longDays[ static_cast<std::size_t>(i) ]),  i);
        xCHECK_RET( a_isShortName && StringCI::compare(a_week_day, shortDays[ static_cast<std::size_t>(i) ]), i);
    }

    return - 1;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   operator <<
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tostream_t &
operator << (
	std::tostream_t &a_os,
	const DateTime  &a_dateTime
)
{
	a_os << a_dateTime.format(xT("%d-%m-%Y %H:%M:%S"));

	return a_os;
};
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
