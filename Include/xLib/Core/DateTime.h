/**
 * \file  DateTime.h
 * \brief date, time
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

class DateTime;

class DateTimeValidator
	///< DateTime validator
{
public:
	xNO_DEFAULT_CONSTRUCT(DateTimeValidator);

	static
	bool_t year(cint_t &year);
	static
	bool_t month(cint_t &month);
	static
	bool_t day(cint_t &day);
	static
	bool_t hour(cint_t &hour);
	static
	bool_t minute(cint_t &minute);
	static
	bool_t second(cint_t &second);
	static
	bool_t msec(cint_t &msec);

	static
	bool_t weekDay(cint_t &weekDay);

	static
	bool_t time(cint_t &hour, cint_t &minute, cint_t &second, cint_t &msec);
	static
	bool_t date(cint_t &year, cint_t &month, cint_t &day);
	static
	bool_t datetime(cint_t &year, cint_t &month, cint_t &day, cint_t &hour,
			   cint_t &minute, cint_t &second, cint_t &msec);
	static
	bool_t datetime(const DateTime &datetime);
	static
	bool_t dateOrTime(cint_t &year, cint_t &month, cint_t &day, cint_t &hour, cint_t &minute,
			   cint_t &second, cint_t &msec);
};

class DateTime
    /// date, time
{
public:
    // constructors, destructor
                    DateTime();
                    DateTime(const DateTime &datetime);
    explicit        DateTime(culonglong_t &msec);
                    DateTime(cint_t &hour, cint_t &minute, cint_t &second, cint_t &msec);
                    DateTime(cint_t &year, cint_t &month, cint_t &day);
                    DateTime(cint_t &year, cint_t &month, cint_t &day, cint_t &hour,
                        cint_t &minute, cint_t &second, cint_t &msec);
    virtual        ~DateTime() {}

    // comparison operators
    bool_t          operator == (const DateTime &datetime) const;
    bool_t          operator != (const DateTime &datetime) const;
    bool_t          operator <  (const DateTime &datetime) const;
    bool_t          operator <= (const DateTime &datetime) const;
    bool_t          operator >  (const DateTime &datetime) const;
    bool_t          operator >= (const DateTime &datetime) const;

    // assignment operators
    DateTime       &operator =  (const DateTime &datetime);
    DateTime       &operator =  (culonglong_t &msec);

    DateTime        operator +  (const DateTime &datetime) const;
    DateTime        operator -  (const DateTime &datetime) const;
    const DateTime &operator += (const DateTime &datetime);
    const DateTime &operator -= (const DateTime &datetime);
    // ++
    // --

    // get/set
    void_t          get(int_t *year, int_t *month, int_t *day,
                        int_t *hour, int_t *minute, int_t *second, int_t *msec) const;
        ///< get datetime data
    int_t           dayOfWeek() const;
        ///< get day of week, days since Sunday 0-6
    void_t          set(culonglong_t &msec);
        ///< set DateTime by milliseconds
    void_t          set(cint_t &year, cint_t &month, cint_t &day,
                        cint_t &hour, cint_t &minute, cint_t &second, cint_t &msec);
        ///< set DateTime by datetime data

    // converting
    ulonglong_t     toMsec() const;
        ///< convert DateTime to milliseconds

    // TODO: [skynowa] ToUniversalTime, ToLocalTime
#if xTODO
	ToUniversalTime();
	ToLocalTime();
#endif

    // formatting
    std::tstring_t  format(std::ctstring_t &format, std::ctstring_t &formatMsec = xT(".%03d")) const
                      ;
        ///< formatting

xPUBLIC_STATIC:
    static
    DateTime        current();
        ///< get current datetime
    static
    int_t           daysInMonth(cint_t &year, cint_t &month);
        ///< get number days in month
    static
    bool_t          isLeapYear(cint_t &year);
        ///< is leap year
#if xENV_WIN
    static
    longlong_t      fileToInt64(const FILETIME &fileTime);
        ///< convert FILETIME to longlong_t
    static
    void_t          unixToFile(const time_t &unixTime, FILETIME *fileTime);
        ///< convert UNIX time_t to Win32 FILETIME
    static
    time_t          fileToUnix(const FILETIME &fileTime);
        ///< convert Win32 FILETIME to UNIX time_t
#endif

    // other
    static
    std::tstring_t  zodiacSign(cint_t &month, cint_t &day);
        ///< sign of the zodiac by date
    static
    std::tstring_t  monthStr(cint_t &month, cbool_t &isShortName);
        ///< get month string
    static
    int_t           monthNum(std::ctstring_t &month, cbool_t &isShortName);
        ///< get month number by string
    static
    std::tstring_t  weekDayStr(cint_t &week_day, cbool_t &isShortName);
        ///< get week day string (days since Sunday)
    static
    int_t           weekDayNum(std::ctstring_t &week_day, cbool_t &isShortName);
        ///< get week day number by string

private:
    int_t       _year;    ///< years since (1900)
    int_t       _month;   ///< months since January (0-11)
    int_t       _day;     ///< day of the month (1-31)
    int_t       _hour;    ///< hours since midnight (0-23)
    int_t       _minute;  ///< minutes after the hour (0-59)
    int_t       _second;  ///< seconds after the minute (0-60*)
    int_t       _msec;    ///< milliseconds (0-999)

    ulonglong_t _thisMSec;///< datetime in milliseconds

    ulonglong_t _toMsec() const;
        ///< convert to milliseconds

    friend class DateTimeValidator;

    friend std::tostream_t& operator << (std::tostream_t &os, const DateTime &dateTime);

xPLATFORM_IMPL:
    // static
    static
    DateTime _current_impl();
};

} // namespace
//-------------------------------------------------------------------------------------------------
