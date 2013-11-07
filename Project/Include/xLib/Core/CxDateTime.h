/**
 * \file  CxDateTime.h
 * \brief date, time
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDateTime
    /// date, time
{
public:
    enum ExFormatType
        /// format type
    {
        ftTime,     ///< HH.MM.SS.MMM
        ftDate,     ///< DD.MM.YYYY
        ftDateTime, ///< DD.MM.YYYY HH.MM.SS.MMM
        ftRFC1123   ///< Wdy, DD Mon YYYY HH:MM:SS GMT
    };

    // constructors, destructor
                          CxDateTime();
        ///< constructor
    explicit              CxDateTime(std::ctstring_t &datetime, const ExFormatType &format);
        ///< constructor
    /*explicit*/          CxDateTime(const CxDateTime &datetime);
        ///< constructor
    explicit              CxDateTime(culonglong_t &msec);
        ///< constructor
                          CxDateTime(cushort_t &hour, cushort_t &minute, cushort_t &second,
                              cushort_t &msec);
        ///< constructor
                          CxDateTime(cushort_t &year, cushort_t &month, cushort_t &day);
        ///< constructor
                          CxDateTime(cushort_t &year, cushort_t &month, cushort_t &day,
                              cushort_t &hour, cushort_t &minute, cushort_t &second,
                              cushort_t &msec);
        ///< constructor
    virtual              ~CxDateTime() {}
        ///< destructor

    // comparison operators
    bool_t                operator == (const CxDateTime &datetime) const;
        ///< operator ==
    bool_t                operator != (const CxDateTime &datetime) const;
        ///< operator !=
    bool_t                operator <  (const CxDateTime &datetime) const;
        ///< operator <
    bool_t                operator <= (const CxDateTime &datetime) const;
        ///< operator <=
    bool_t                operator >  (const CxDateTime &datetime) const;
        ///< operator >
    bool_t                operator >= (const CxDateTime &datetime) const;
        ///< operator >=

    // assignment operators
    const CxDateTime     &operator =  (const CxDateTime &datetime);
        ///< operator =
    const CxDateTime     &operator =  (culonglong_t &msec);
        ///< operator =

    CxDateTime            operator +  (const CxDateTime &datetime) const;
        ///< operator +
    CxDateTime            operator -  (const CxDateTime &datetime) const;
        ///< operator -
    const CxDateTime     &operator += (const CxDateTime &datetime);
        ///< operator +=
    const CxDateTime     &operator -= (const CxDateTime &datetime);
        ///< operator -=
    //++
    //--

    // get/set
    void_t                get(ushort_t *year, ushort_t *month, ushort_t *day,
                              ushort_t *hour, ushort_t *minute,
                              ushort_t *second, ushort_t *msec) const;
        ///< get datetime data
    ushort_t              dayOfWeek() const xWARN_UNUSED_RV;
        ///< get day of week, days since Sunday 0-6
    void_t                set(culonglong_t &msec);
        ///< set CxDateTime by milliseconds
    void_t                set(cushort_t &year, cushort_t &month, cushort_t &day,
                              cushort_t &hour, cushort_t &minute,
                              cushort_t &second, cushort_t &msec);
        ///< set CxDateTime by datetime data

    // converting
    ulonglong_t           toMsec() const xWARN_UNUSED_RV;
        ///< convert CxDateTime to milliseconds

    // TODO: ToUniversalTime, ToLocalTime
    #if xTODO
        ToUniversalTime();
        ToLocalTime();
    #endif

    // formating
    std::tstring_t        format(const ExFormatType &format) const xWARN_UNUSED_RV;
        ///< formating

    // static
    static bool_t         isValid(cushort_t &year, cushort_t &month, cushort_t &day,
                              cushort_t &hour, cushort_t &minute,
                              cushort_t &second, cushort_t &msec) xWARN_UNUSED_RV;
        ///< checking for a valid datetime
    static bool_t         isValid(const CxDateTime &datetime) xWARN_UNUSED_RV;
        ///< checking for a valid datetime
           bool_t         isValid() const xWARN_UNUSED_RV;
        ///< checking for a valid datetime

    static CxDateTime     current() xWARN_UNUSED_RV;
        ///< get current datetime
    static ushort_t       daysInMonth(cushort_t &year, cushort_t &month) xWARN_UNUSED_RV;
        ///< get number days in month
    static bool_t         isLeapYear(cushort_t &year) xWARN_UNUSED_RV;
        ///< is leap year
#if xOS_ENV_WIN
    static longlong_t     filetimeToInt64(const FILETIME &fileTime) xWARN_UNUSED_RV;
        ///< convert FILETIME to longlong_t
    static void_t         unixTimeToFileTime(const time_t &unixTime, FILETIME *fileTime);
        ///< convert UNIX time_t to Win32 FILETIME
    static time_t         fileTimeToUnixTime(const FILETIME &fileTime) xWARN_UNUSED_RV;
        ///< convert Win32 FILETIME to UNIX time_t
#endif

    // other
    static std::tstring_t zodiacSign(cushort_t &month, cushort_t &day) xWARN_UNUSED_RV;
        ///< sign of the zodiac by date
    static std::tstring_t monthStr(ushort_t month, cbool_t &isShortName) xWARN_UNUSED_RV;
        ///< get month string
    static ushort_t       monthNum(std::ctstring_t &month, cbool_t &isShortName) xWARN_UNUSED_RV;
        ///< get month number by string
    static std::tstring_t weekDayStr(ushort_t day, cbool_t &isShortName) xWARN_UNUSED_RV;
        ///< get week day string
    static ushort_t       weekDayNum(std::ctstring_t &day, cbool_t &isShortName) xWARN_UNUSED_RV;
        ///< get week day number by string

private:
    ulonglong_t           _thisMSec;
        ///< datetime in milliseconds

    // datetime members
    ushort_t              _year;
        ///< 0-2010, Win (1601 through 30827)
    ushort_t              _month;
        ///< 1-12, Win (1-12)
    ushort_t              _day;
        ///< 1-31, Win (1-31)
    ushort_t              _hour;
        ///< 0-23, Win (0-23)
    ushort_t              _minute;
        ///< 0-59, Win (0-59)
    ushort_t              _second;
        ///< 0-61*, Win (0-59)
    ushort_t              _msec;
        ///< 0-999, Win (0-99)

    ulonglong_t           _toMsec() const xWARN_UNUSED_RV;
        ///< convert to milliseconds
    static void_t         _parse(std::ctstring_t &value, const ExFormatType &format,
                              CxDateTime *datetime);
        ///< parsing datetime string
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Core/CxDateTime.cpp>
#endif


#if xTODO
    // http://www.csharp-examples.net/string-format-datetime/
    UTC == GMT == Время по гринвичу

    UTC это локальное время минус часовой пояс.
    GMT работает с летнем/зимнем временем, поэтому оно ни как не может быть равным первому.
#endif

#if xTODO
    __int64 i64DateTimeToSeconds(const TDateTime &dtDateTime) {
        WORD wYear, wMonth, wDay, wHour, wMin, wSec, wMSec;

        DecodeTime(dtDateTime, wHour, wMin, wSec, wMSec);

        return (wHour * 60 * 60) + (wMin * 60) + (wSec);
    }
#endif

#if xTODO
    #define INTERVAL_CENTI      1
    #define INTERVAL_SEC        100
    #define INTERVAL_MIN        6000
    #define INTERVAL_HOUR       360000L
    #define INTERVAL_DAY        8640000L

    #define INTERVAL_SEC_SEC    1
    #define INTERVAL_MIN_SEC    60
    #define INTERVAL_HOUR_SEC    3600
    #define INTERVAL_DAY_SEC    86400
#endif

#if xTODO
    //microSec
    #define FILETIME_TO_USEC(ft) \
        (((unsigned __int64) ft.dwHighDateTime << 32 | ft.dwLowDateTime) / 10)

    GetTimeFormatEx
    GetDateFormat
#endif

#if xTODO
    __time64_t         _m_time;    /*__int64*/
#endif

#if xTODO
    http://www.rsdn.ru/forum/cpp/2099875.flat.aspx

    inline unix_t
    _os_get() {
        typedef unsigned __int64 uint64_type;

        // Смещение UNIX-эпохи (1970.01.01 00:00:00) от Win32-эпохи
        // (1601.01.01 00:00:00).
        const uint64_type delta =
            (((uint64_type) 0x019DB1DE) << 32) |
            ((uint64_type) 0xD53E8000);

        // Определяем текущее время.
        FILETIME ft_current;
        ::GetSystemTimeAsFileTime( &ft_current );

        uint64_type current =
            ((((uint64_type) ft_current.dwHighDateTime) << 32) |
            ((uint64_type) ft_current.dwLowDateTime)) - delta;

        return unix_t(
            // Определяем, сколько прошло секунд.
            (time_t)( ( current ) / 10000000 ),
            // А сколько микросекунд.
            (unsigned long_t)( ( current % 10000000 + 5 ) / 10 ) );
    }
#endif

