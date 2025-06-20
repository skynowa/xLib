/**
 * \file  DateTime.cpp
 * \brief date, time
 */


#include "DateTime.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/Units.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>

#if 0
	#include <xLib/Debug/NativeError.h>
	#include <xLib/Debug/StackTrace.h>
	#include <xLib/Debug/ErrorReport.h>
	#include <xLib/Debug/Debugger.h>
#else
	#include <xLib/Test/TestMsg.h>
#endif

#if   xENV_WIN
    #include "Platform/Win/DateTime_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/DateTime_unix.inl"
#endif

//-------------------------------------------------------------------------------------------------
namespace
{

/**
 * https://www.cplusplus.com/reference/ctime/tm/?kw=tm
 *
 * Member   Type  Meaning                    Range
 *
 * tm_sec   int   seconds after the minute   0-60*
 * tm_min   int   minutes after the hour     0-59
 * tm_hour  int   hours since midnight       0-23
 * tm_mday  int   day of the month           1-31
 * tm_mon   int   months since January       0-11
 * tm_year  int   years since                1900
 * tm_wday  int   days since Sunday          0-6
 * tm_yday  int   days since January 1       0-365
 * tm_isdst int   Daylight Saving Time flag  <, 0, >
 *
 * * tm_sec - is generally 0-59.
 *   The extra range is to accommodate for leap seconds in certain systems
 */

constexpr xl::int_t yearMin     = 0;
constexpr xl::int_t yearMax     = 9999;

constexpr xl::int_t monthMin    = 1;
constexpr xl::int_t monthMax    = 12;

constexpr xl::int_t dayMin      = 1;
constexpr xl::int_t dayMax      = 31;

constexpr xl::int_t hourMin     = 0;
constexpr xl::int_t hourMax     = 23;

constexpr xl::int_t minuteMin   = 0;
constexpr xl::int_t minuteMax   = 59;

constexpr xl::int_t secondMin   = 0;
constexpr xl::int_t secondMax   = 60;	// (1 leap second)

constexpr xl::int_t msecMin     = 0;
constexpr xl::int_t msecMax     = 999;

constexpr xl::int_t microsecMin = 0;
constexpr xl::int_t microsecMax = 999;

constexpr xl::int_t weekDayMin  = 0;
constexpr xl::int_t weekDayMax  = 6;

} // namespace
//-------------------------------------------------------------------------------------------------

namespace xl::core
{

/**************************************************************************************************
*   public: validate
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::year(
    cint_t a_year
)
{
    return (a_year >= ::yearMin && a_year <= ::yearMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::month(
    cint_t a_month
)
{
    return (a_month >= ::monthMin && a_month <= ::monthMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::day(
    cint_t a_day
)
{
    return (a_day >= ::dayMin && a_day <= ::dayMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::hour(
    cint_t a_hour
)
{
    return (a_hour >= ::hourMin && a_hour <= ::hourMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::minute(
    cint_t a_minute
)
{
    return (a_minute >= ::minuteMin && a_minute <= ::minuteMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::second(
    cint_t a_second
)
{
    return (a_second >= ::secondMin && a_second <= ::secondMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::msec(
    cint_t a_msec
)
{
    return (a_msec >= ::msecMin && a_msec <= ::msecMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::weekDay(
    cint_t a_weekDay
)
{
    return (a_weekDay >= ::weekDayMin && a_weekDay <= ::weekDayMax);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::date(
    cint_t a_year,
    cint_t a_month,
    cint_t a_day
)
{
    return (year(a_year) && month(a_month) && day(a_day));
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::time(
    cint_t a_hour,
    cint_t a_minute,
    cint_t a_second,
    cint_t a_msec
)
{
    return (hour(a_hour) && minute(a_minute) && second(a_second) && msec(a_msec));
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTimeValidator::datetime(
    cint_t a_year,
    cint_t a_month,
    cint_t a_day,
    cint_t a_hour,
    cint_t a_minute,
    cint_t a_second,
    cint_t a_msec
)
{
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
    cint_t a_year,
    cint_t a_month,
    cint_t a_day,
    cint_t a_hour,
    cint_t a_minute,
    cint_t a_second,
    cint_t a_msec
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
	DateTime(::yearMin, ::monthMin, ::dayMin, ::hourMin, ::minuteMin, ::secondMin, ::msecMin)
{
}
//-------------------------------------------------------------------------------------------------
DateTime::DateTime(
    const DateTime &a_datetime
) :
    DateTime(a_datetime._year, a_datetime._month,  a_datetime._day,
        a_datetime._hour, a_datetime._minute, a_datetime._second, a_datetime._msec)
{
}
//-------------------------------------------------------------------------------------------------
// TODO: review
DateTime::DateTime(
    culonglong_t a_msec
)
{
    _construct(a_msec);
}
//-------------------------------------------------------------------------------------------------
DateTime::DateTime(
    cint_t a_hour,
    cint_t a_minute,
    cint_t a_second,
    cint_t a_msec
) :
    DateTime(0, 0, 0, a_hour, a_minute, a_second, a_msec)
{
}
//-------------------------------------------------------------------------------------------------
DateTime::DateTime(
    cint_t a_year,
    cint_t a_month,
    cint_t a_day
) :
    DateTime(a_year, a_month, a_day, 0, 0, 0, 0)
{
}
//-------------------------------------------------------------------------------------------------
DateTime::DateTime(
    cint_t a_year,
    cint_t a_month,
    cint_t a_day,
    cint_t a_hour,
    cint_t a_minute,
    cint_t a_second,
    cint_t a_msec
) :
    // datetime
    _year    {a_year},
    _month   {a_month},
    _day     {a_day},
    _hour    {a_hour},
    _minute  {a_minute},
    _second  {a_second},
    _msec    {a_msec},

    // REVIEW: datetime msec member (convert to msec)
	_thisMSec{ _toMsec() }
{
#if 0
	xTEST(DateTimeValidator::date(a_year, a_month, a_day));
	xTEST(DateTimeValidator::time(a_hour, a_minute, a_second, a_msec));
#endif
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
    return (_thisMSec == a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTime::operator != (
    const DateTime &a_datetime
) const
{
    return (_thisMSec != a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTime::operator < (
    const DateTime &a_datetime
) const
{
    return (_thisMSec < a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTime::operator <= (
    const DateTime &a_datetime
) const
{
    return (_thisMSec <= a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTime::operator > (
    const DateTime &a_datetime
) const
{
    return (_thisMSec > a_datetime._thisMSec);
}
//-------------------------------------------------------------------------------------------------
bool_t
DateTime::operator >= (
    const DateTime &a_datetime
) const
{
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
    if (this == &a_datetime) {
        return *this;
    }

    // TODO: fix
    _construct(a_datetime._thisMSec);

    return *this;
}
//-------------------------------------------------------------------------------------------------
DateTime &
DateTime::operator = (
    culonglong_t a_msec
)
{
    // TODO: fix
	_construct(a_msec);

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

    // TODO: fix
    _construct(_thisMSec);

    return *this;
}
//-------------------------------------------------------------------------------------------------
const DateTime &
DateTime::operator -= (
    const DateTime &a_datetime
)
{
    _thisMSec -= a_datetime._thisMSec;

    // TODO: fix
    _construct(_thisMSec);

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
    xTESTS_NA

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
    xTEST(DateTimeValidator::datetime(*this));

    std::tm timeInfo {};
    timeInfo.tm_year = _year  - 1900;
    timeInfo.tm_mon  = _month - 1;
    timeInfo.tm_mday = _day;

    const time_t time = std::mktime(&timeInfo);
    xTEST_DIFF(time, static_cast<time_t>(- 1));

    return timeInfo.tm_wday;
}
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] toMsec
ulonglong_t
DateTime::toMsec() const
{
    return _thisMSec;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    converting
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
DateTime::_construct(
    culonglong_t a_msec
)
{
    xTEST_NA(a_msec);

    // datetime msec member
    this->_thisMSec = a_msec;

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
// TODO: [skynowa] DateTime::_toMsec() - days in month 30 or 31 ???
ulonglong_t
DateTime::_toMsec() const
{
    ulonglong_t ullRv {};

    ullRv += xYEAR(_year);
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
    xTESTS_NA
    xTEST(!a_format.empty());
    xTEST_NA(a_formatMsec);

    std::tstring_t sRv;

	std::tm date {};
	date.tm_sec   = _second;
	date.tm_min   = _minute;
	date.tm_hour  = _hour;
	date.tm_mday  = _day;
	date.tm_mon   = _month - 1;
	date.tm_year  = _year  - 1900;
	date.tm_wday  = {};
	date.tm_yday  = {};
	date.tm_isdst = {};

#if 0
	LogCout() << date;
	LogCout() << xTRACE_VAR(a_format);
	LogCout() << xTRACE_VAR(a_formatMsec);
#endif

	tchar_t buff[80 + 1] {};

	std::csize_t buffSize = xSTRFTIME(&buff[0], sizeof(buff) - 1, a_format.c_str(), &date);
	xCHECK_RET(buffSize == 0, std::tstring_t());

	sRv.assign(&buff[0], buffSize);

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
    cint_t a_year,
    cint_t a_month
)
{
    xCHECK_RET(a_month == 2 && isLeapYear(a_year), 29);

    const std::array<int_t, ::monthMax + 1> monthsDays =
    {{
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    }};

    return monthsDays[ static_cast<std::size_t>(a_month) ];
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
DateTime::isLeapYear(
    cint_t a_year
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
DateTime::monthStr(
    cint_t  a_month,
    cbool_t a_isShortName
)
{
    xTEST(DateTimeValidator::month(a_month));
    xTEST_NA(a_isShortName);

    std::tstring_t sRv;

    if (!a_isShortName) {
        // months numbering: 1-12
        const std::array<std::tstring_t, ::monthMax + 1> longMonths =
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

        sRv = longMonths[static_cast<std::size_t>(a_month) - 1];
    } else {
        // months numbering: 1-12
        const std::array<std::tstring_t, ::monthMax + 1> shortMonths =
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

        sRv = shortMonths[static_cast<std::size_t>(a_month) - 1];
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
int_t
DateTime::monthNum(
    std::ctstring_t &a_month,
    cbool_t          a_isShortName
)
{
    xTEST_NA(a_month);
    xTEST_NA(a_isShortName);

    // months numbering: 0-11
    const std::array<std::tstring_t, ::monthMax + 1> longMonths =
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
    const std::array<std::tstring_t, ::monthMax + 1> shortMonths =
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
    cint_t  a_week_day,
    cbool_t a_isShortName
)
{
    xTEST(DateTimeValidator::weekDay(a_week_day));
    xTEST_NA(a_isShortName);

    // days since Sunday (0-6)

    std::tstring_t sRv;

    if (!a_isShortName) {
        const std::array<std::tstring_t, ::weekDayMax + 1> longDays =
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
        const std::array<std::tstring_t, ::weekDayMax + 1> shortDays =
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
    cbool_t          a_isShortName
)
{
    xTEST_NA(a_week_day);
    xTEST_NA(a_isShortName);

    const std::array<std::tstring_t, ::weekDayMax + 1> longDays =
    {{
        xT("Monday"),
        xT("Tuesday"),
        xT("Wednesday"),
        xT("Thursday"),
        xT("Friday"),
        xT("Saturday"),
        xT("Sunday")
    }};

    const std::array<std::tstring_t, ::weekDayMax + 1> shortDays =
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

} // namespace
