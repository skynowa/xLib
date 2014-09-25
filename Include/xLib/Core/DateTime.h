/**
 * \file  DateTime.h
 * \brief date, time
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class DateTime
    /// date, time
{
public:
    // constructors, destructor
                   DateTime();
        ///< constructor
    /* explicit */ DateTime(const DateTime &datetime);
        ///< constructor
    explicit       DateTime(culonglong_t &msec);
        ///< constructor
                   DateTime(cint_t &hour, cint_t &minute, cint_t &second, cint_t &msec);
        ///< constructor
                   DateTime(cint_t &year, cint_t &month, cint_t &day);
        ///< constructor
                   DateTime(cint_t &year, cint_t &month, cint_t &day, cint_t &hour,
                       cint_t &minute, cint_t &second, cint_t &msec);
        ///< constructor
    virtual       ~DateTime() {}
        ///< destructor

    // validate
    struct Validator
        ///< DateTime validator
    {
        static
        bool_t year(cint_t &year) xWARN_UNUSED_RV;
        static
        bool_t month(cint_t &month) xWARN_UNUSED_RV;
        static
        bool_t day(cint_t &day) xWARN_UNUSED_RV;
        static
        bool_t hour(cint_t &hour) xWARN_UNUSED_RV;
        static
        bool_t minute(cint_t &minute) xWARN_UNUSED_RV;
        static
        bool_t second(cint_t &second) xWARN_UNUSED_RV;
        static
        bool_t msec(cint_t &msec) xWARN_UNUSED_RV;

        static
        bool_t weekDay(cint_t &weekDay) xWARN_UNUSED_RV;

        static
        bool_t time(cint_t &hour, cint_t &minute, cint_t &second, cint_t &msec) xWARN_UNUSED_RV;
        static
        bool_t date(cint_t &year, cint_t &month, cint_t &day) xWARN_UNUSED_RV;
        static
        bool_t datetime(cint_t &year, cint_t &month, cint_t &day, cint_t &hour,
                   cint_t &minute, cint_t &second, cint_t &msec) xWARN_UNUSED_RV;
        static
        bool_t datetime(const DateTime &datetime) xWARN_UNUSED_RV;
        static
        bool_t dateOrTime(cint_t &year, cint_t &month, cint_t &day, cint_t &hour, cint_t &minute,
                   cint_t &second, cint_t &msec) xWARN_UNUSED_RV;
    };

    // comparison operators
    bool_t            operator == (const DateTime &datetime) const;
        ///< operator ==
    bool_t            operator != (const DateTime &datetime) const;
        ///< operator !=
    bool_t            operator <  (const DateTime &datetime) const;
        ///< operator <
    bool_t            operator <= (const DateTime &datetime) const;
        ///< operator <=
    bool_t            operator >  (const DateTime &datetime) const;
        ///< operator >
    bool_t            operator >= (const DateTime &datetime) const;
        ///< operator >=

    // assignment operators
    const DateTime &operator =  (const DateTime &datetime);
        ///< operator =
    const DateTime &operator =  (culonglong_t &msec);
        ///< operator =

    DateTime        operator +  (const DateTime &datetime) const;
        ///< operator +
    DateTime        operator -  (const DateTime &datetime) const;
        ///< operator -
    const DateTime &operator += (const DateTime &datetime);
        ///< operator +=
    const DateTime &operator -= (const DateTime &datetime);
        ///< operator -=
    //++
    //--

    // get/set
    void_t         get(int_t *year, int_t *month, int_t *day,
                       int_t *hour, int_t *minute, int_t *second, int_t *msec) const;
        ///< get datetime data
    int_t          dayOfWeek() const xWARN_UNUSED_RV;
        ///< get day of week, days since Sunday 0-6
    void_t         set(culonglong_t &msec);
        ///< set DateTime by milliseconds
    void_t         set(cint_t &year, cint_t &month, cint_t &day,
                       cint_t &hour, cint_t &minute, cint_t &second, cint_t &msec);
        ///< set DateTime by datetime data

    // converting
    ulonglong_t    toMsec() const xWARN_UNUSED_RV;
        ///< convert DateTime to milliseconds

    // TODO: ToUniversalTime, ToLocalTime
    #if xTODO
        ToUniversalTime();
        ToLocalTime();
    #endif

    // formatting
    std::tstring_t format(std::ctstring_t &format, std::ctstring_t &formatMsec = xT(".%03d")) const
                       xWARN_UNUSED_RV;
        ///< formatting

    // static
    static
    DateTime     current() xWARN_UNUSED_RV;
        ///< get current datetime
    static
    int_t          daysInMonth(cint_t &year, cint_t &month) xWARN_UNUSED_RV;
        ///< get number days in month
    static
    bool_t         isLeapYear(cint_t &year) xWARN_UNUSED_RV;
        ///< is leap year
#if xENV_WIN
    static
    longlong_t     filetimeToInt64(const FILETIME &fileTime) xWARN_UNUSED_RV;
        ///< convert FILETIME to longlong_t
    static
    void_t         unixTimeToFileTime(const time_t &unixTime, FILETIME *fileTime);
        ///< convert UNIX time_t to Win32 FILETIME
    static
    time_t         fileTimeToUnixTime(const FILETIME &fileTime) xWARN_UNUSED_RV;
        ///< convert Win32 FILETIME to UNIX time_t
#endif

    // other
    static
    std::tstring_t zodiacSign(cint_t &month, cint_t &day) xWARN_UNUSED_RV;
        ///< sign of the zodiac by date
    static
    std::tstring_t monthStr(cint_t &month, cbool_t &isShortName) xWARN_UNUSED_RV;
        ///< get month string
    static
    int_t          monthNum(std::ctstring_t &month, cbool_t &isShortName) xWARN_UNUSED_RV;
        ///< get month number by string
    static
    std::tstring_t weekDayStr(cint_t &week_day, cbool_t &isShortName) xWARN_UNUSED_RV;
        ///< get week day string (days since Sunday)
    static
    int_t          weekDayNum(std::ctstring_t &week_day, cbool_t &isShortName) xWARN_UNUSED_RV;
        ///< get week day number by string

private:
    int_t          _year;    ///< years since (1900)
    int_t          _month;   ///< months since January (0-11)
    int_t          _day;     ///< day of the month (1-31)
    int_t          _hour;    ///< hours since midnight (0-23)
    int_t          _minute;  ///< minutes after the hour (0-59)
    int_t          _second;  ///< seconds after the minute (0-60*)
    int_t          _msec;    ///< milliseconds (0-999)

    ulonglong_t    _thisMSec;///< datetime in milliseconds

    ulonglong_t    _toMsec() const xWARN_UNUSED_RV;
        ///< convert to milliseconds

xPLATFORM:
    // static
    static
    DateTime     _current_impl() xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "DateTime.inl"
#endif
