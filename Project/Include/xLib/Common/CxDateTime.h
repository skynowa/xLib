/**
 * \file  CxDateTime.h
 * \brief date, time
 */


#ifndef xLib_Common_CxDateTimeH
#define xLib_Common_CxDateTimeH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
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
                          CxDateTime        ();
        ///< constructor
    explicit              CxDateTime        (const std::tstring_t &csDT, const ExFormatType &cftFormat);
        ///< constructor
    /*explicit*/          CxDateTime        (const CxDateTime &cdtDT);
        ///< constructor
    explicit              CxDateTime        (culonglong_t &cullMilliseconds);
        ///< constructor
                          CxDateTime        (cushort_t &cusHour, cushort_t &cusMinute, cushort_t &cusSecond, cushort_t &cusMillisecond);
        ///< constructor
                          CxDateTime        (cushort_t &cusYear, cushort_t &cusMonth, cushort_t &cusDay);
        ///< constructor
                          CxDateTime        (cushort_t &cusYear, cushort_t &cusMonth, cushort_t &cusDay,
                                             cushort_t &cusHour, cushort_t &cusMinute,
                                             cushort_t &cusSecond, cushort_t &cusMillisecond);
        ///< constructor
    virtual              ~CxDateTime        ();
        ///< destructor

    // comparison operators
    bool_t                  operator ==       (const CxDateTime &cdtDT) const;
        ///< operator ==
    bool_t                  operator !=       (const CxDateTime &cdtDT) const;
        ///< operator !=
    bool_t                  operator <        (const CxDateTime &cdtDT) const;
        ///< operator <
    bool_t                  operator <=       (const CxDateTime &cdtDT) const;
        ///< operator <=
    bool_t                  operator >        (const CxDateTime &cdtDT) const;
        ///< operator >
    bool_t                  operator >=       (const CxDateTime &cdtDT) const;
        ///< operator >=

    // assignment operators
    const CxDateTime     &operator =        (const CxDateTime &cdtDT);
        ///< operator =
    const CxDateTime     &operator =        (culonglong_t &cullMillisecond);
        ///< operator =

    CxDateTime            operator +        (const CxDateTime &cdtDT) const;
        ///< operator +
    CxDateTime            operator -        (const CxDateTime &cdtDT) const;
        ///< operator -
    const CxDateTime     &operator +=       (const CxDateTime &cdtDT);
        ///< operator +=
    const CxDateTime     &operator -=       (const CxDateTime &cdtDT);
        ///< operator -=
    //++
    //--

    // get/set
    void                  get               (ushort_t *pusYear, ushort_t *pusMonth, ushort_t *pusDay,
                                             ushort_t *pusHour, ushort_t *pusMinute,
                                             ushort_t *pusSecond, ushort_t *pusMillisecond) const;
        ///< get datetime data
    ushort_t              dayOfWeek         () const xWARN_UNUSED_RV;
        ///< get day of week, days since Sunday 0-6
    void                  set               (culonglong_t &ullMSec);
        ///< set CxDateTime by milliseconds
    void                  set               (cushort_t &cusYear, cushort_t &cusMonth, cushort_t &cusDay,
                                             cushort_t &cusHour, cushort_t &cusMinute,
                                             cushort_t &cusSecond, cushort_t &cusMillisecond);
        ///< set CxDateTime by datetime data

    // converting
    ulonglong_t           toMilliseconds    () const xWARN_UNUSED_RV;
        ///< convert CxDateTime to milliseconds

    // TODO: ToUniversalTime, ToLocalTime
    #if xTODO
        ToUniversalTime();
        ToLocalTime();
    #endif

    //formating
    std::tstring_t        format            (const ExFormatType &cftFormat) const xWARN_UNUSED_RV;
        ///< formating

    //static
    static bool_t           isValid           (cushort_t &cusYear, cushort_t &cusMonth, cushort_t &cusDay,
                                             cushort_t &cusHour, cushort_t &cusMinute,
                                             cushort_t &cusSecond, cushort_t &cusMillisecond) xWARN_UNUSED_RV;
        ///< checking for a valid datetime
    static bool_t           isValid           (const CxDateTime &cdtDT) xWARN_UNUSED_RV;
        ///< checking for a valid datetime
           bool_t           isValid           () const xWARN_UNUSED_RV;
        ///< checking for a valid datetime

    static CxDateTime     current           () xWARN_UNUSED_RV;
        ///< get current datetime
    static ushort_t       daysInMonth       (cushort_t &cusYear, cushort_t &cusMonth) xWARN_UNUSED_RV;
        ///< get number days in month
    static bool_t           isLeapYear        (cushort_t &cusYear) xWARN_UNUSED_RV;
        ///< is leap year
#if   xOS_ENV_WIN
    static longlong_t     filetimeToInt64   (const FILETIME &cftTime) xWARN_UNUSED_RV;
        ///< convert FILETIME to longlong_t
    static void           unixTimeToFileTime(const time_t &ctmUnixTime, FILETIME *pftFileTime);
        ///< convert UNIX time_t to Win32 FILETIME
    static time_t         fileTimeToUnixTime(const FILETIME &ftFileTime) xWARN_UNUSED_RV;
        ///< convert Win32 FILETIME to UNIX time_t
#endif

    //other
    static std::tstring_t zodiacSign        (cushort_t &cusMonth, cushort_t &cusDay) xWARN_UNUSED_RV;
        ///< sign of the zodiac by date
    static std::tstring_t monthStr          (ushort_t usMonth, cbool_t &cbIsShortName) xWARN_UNUSED_RV;
        ///< get month string
    static ushort_t       monthNum          (const std::tstring_t &csMonth, cbool_t &cbIsShortName) xWARN_UNUSED_RV;
        ///< get month number by string
    static std::tstring_t weekDayStr        (ushort_t usDay, cbool_t &cbIsShortName) xWARN_UNUSED_RV;
        ///< get week day string
    static ushort_t       weekDayNum        (const std::tstring_t &csDay, cbool_t &cbIsShortName) xWARN_UNUSED_RV;
        ///< get week day number by string

private:
    ulonglong_t           _m_ullDateTimeInMSec;
        ///< datetime in milliseconds

    //datetime members
    ushort_t              _m_usYear;
        ///< 0-2010, Win (1601 through 30827)
    ushort_t              _m_usMonth;
        ///< 1-12, Win (1-12)
    ushort_t              _m_usDay;
        ///< 1-31, Win (1-31)
    ushort_t              _m_usHour;
        ///< 0-23, Win (0-23)
    ushort_t              _m_usMinute;
        ///< 0-59, Win (0-59)
    ushort_t              _m_usSecond;
        ///< 0-61*, Win (0-59)
    ushort_t              _m_usMillisecond;
        ///< 0-999, Win (0-99)

    ulonglong_t           _toMilliseconds   () const xWARN_UNUSED_RV;
        ///< convert to milliseconds
    static void           _parse            (const std::tstring_t &csDT, const ExFormatType &cftFormat, CxDateTime *pdtDT);
        ///< parsing datetime string
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Common_CxDateTimeH


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
    #define FILETIME_TO_USEC(ft) (((unsigned __int64) ft.dwHighDateTime << 32 | ft.dwLowDateTime) / 10)

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

