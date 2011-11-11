/**
 * \file  CxDateTime.h
 * \brief date, time
 */


#ifndef xLib_Common_CxDateTimeH
#define xLib_Common_CxDateTimeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDateTime
    /// date, time
{
    public:
        enum EFormatType
            /// format type
        {
            ftTime,     ///< HH.MM.SS.MMM
            ftDate,     ///< DD.MM.YYYY
            ftDateTime, ///< DD.MM.YYYY HH.MM.SS.MMM
            ftRFC1123   ///< Wdy, DD Mon YYYY HH:MM:SS GMT
        };

        //constructors, destructor
                            CxDateTime          ();
            ///< constructor
        explicit            CxDateTime          (const std::string_t &csDT, const EFormatType cftFormat);
            ///< constructor
        /*explicit*/        CxDateTime          (const CxDateTime &cdtDT);
            ///< constructor
        explicit            CxDateTime          (const ULONGLONG cullMilliseconds);
            ///< constructor
                            CxDateTime          (const USHORT cusHour, const USHORT cusMinute, const USHORT cusSecond, const USHORT cusMillisecond);
            ///< constructor
                            CxDateTime          (const USHORT cusYear, const USHORT cusMonth, const USHORT cusDay);
            ///< constructor
                            CxDateTime          (const USHORT cusYear, const USHORT cusMonth, const USHORT cusDay, const USHORT cusHour, const USHORT cusMinute, const USHORT cusSecond, const USHORT cusMillisecond);
            ///< constructor
        virtual            ~CxDateTime          ();
            ///< destructor

        //comparison operators
        BOOL                operator ==         (const CxDateTime &cdtDT) const;
            ///< operator ==
        BOOL                operator !=         (const CxDateTime &cdtDT) const;
            ///< operator !=
        BOOL                operator <          (const CxDateTime &cdtDT) const;
            ///< operator <
        BOOL                operator <=         (const CxDateTime &cdtDT) const;
            ///< operator <=
        BOOL                operator >          (const CxDateTime &cdtDT) const;
            ///< operator >
        BOOL                operator >=         (const CxDateTime &cdtDT) const;
            ///< operator >=

        //assignment operators
        const CxDateTime   &operator =          (const CxDateTime &cdtDT);
            ///< operator =
    #if defined(xOS_ENV_WIN) && defined(xCOMPILER_CODEGEAR)
        const CxDateTime   &operator =          (const TDateTime  &cdtDT);
            ///< operator =
    #endif
        const CxDateTime   &operator =          (const ULONGLONG cullMillisecond);
            ///< operator =

        CxDateTime          operator +          (const CxDateTime &cdtDT) const;
            ///< operator +
        CxDateTime          operator -          (const CxDateTime &cdtDT) const;
            ///< operator -
        const CxDateTime   &operator +=         (const CxDateTime &cdtDT);
            ///< operator +=
        const CxDateTime   &operator -=         (const CxDateTime &cdtDT);
            ///< operator -=
        //++
        //--

        //get/set
        BOOL                bGet                (USHORT *pusYear, USHORT *pusMonth, USHORT *pusDay, USHORT *pusHour, USHORT *pusMinute, USHORT *pusSecond, USHORT *pusMillisecond) const;
            ///< get datetime data
        USHORT              usGetDayOfWeek      () const;
            ///< get day of week, days since Sunday 0-6
        BOOL                bSet                (const ULONGLONG ullMSec);
            ///< set CxDateTime by milliseconds
        BOOL                bSet                (const USHORT cusYear, const USHORT cusMonth, const USHORT cusDay, const USHORT cusHour, const USHORT cusMinute, const USHORT cusSecond, const USHORT cusMillisecond);
            ///< set CxDateTime by datetime data

        //converting
        ULONGLONG           ullToMilliseconds   () const;
            ///< convert CxDateTime to milliseconds
        #if xTODO
            ToUniversalTime();
            ToLocalTime();
        #endif

        //formating
        std::string_t        sFormat             (const EFormatType cftFormat) const;
            ///< formating

        //static
        static BOOL         bIsValid            (const USHORT cusYear, const USHORT cusMonth, const USHORT cusDay, const USHORT cusHour, const USHORT cusMinute, const USHORT cusSecond, const USHORT cusMillisecond);
            ///< checking for a valid datetime
        static BOOL         bIsValid            (const CxDateTime &cdtDT);
            ///< checking for a valid datetime
               BOOL         bIsValid            () const;
            ///< checking for a valid datetime

        static CxDateTime   dtGetCurrent        ();
            ///< get current datetime
        static USHORT       usDaysInMonth       (const USHORT cusYear, const USHORT cusMonth);
            ///< get number days in month
        static BOOL         bIsLeapYear         (const USHORT cusYear);
            ///< is leap year
    #if defined(xOS_ENV_WIN)
        static LONGLONG     i64FiletimeToInt64  (const FILETIME &cftTime);
            ///< convert FILETIME to LONGLONG
        static BOOL         bUnixTimeToFileTime (const time_t ctmUnixTime, FILETIME *pftFileTime);
            ///< convert UNIX time_t to Win32 FILETIME
        static time_t       tmFileTimeToUnixTime(const FILETIME &ftFileTime);
            ///< convert Win32 FILETIME to UNIX time_t
    #endif

        //other
        static std::string_t sGetZodiacSign      (const USHORT cusMonth, const USHORT cusDay);
            ///< sign of the zodiac by date
        static std::string_t sGetMonthStr        (USHORT usMonth, const BOOL cbIsShortName);
            ///< get month string
        static USHORT       usGetMonthNum       (const std::string_t &csMonth, const BOOL cbIsShortName);
            ///< get month number by string
        static std::string_t sGetWeekDayStr      (USHORT usDay, const BOOL cbIsShortName);
            ///< get week day string
        static USHORT       usGetWeekDayNum     (const std::string_t &csDay, const BOOL cbIsShortName);
            ///< get week day number by string

    private:
        ULONGLONG           _m_ullDateTimeInMSec;
            ///< datetime in milliseconds

        //datetime members
        USHORT              _m_usYear;
            ///< 0-2010, Win (1601 through 30827)
        USHORT              _m_usMonth;
            ///< 1-12, Win (1-12)
        USHORT              _m_usDay;
            ///< 1-31, Win (1-31)
        USHORT              _m_usHour;
            ///< 0-23, Win (0-23)
        USHORT              _m_usMinute;
            ///< 0-59, Win (0-59)
        USHORT              _m_usSecond;
            ///< 0-61*, Win (0-59)
        USHORT              _m_usMillisecond;
            ///< 0-999, Win (0-99)

        ULONGLONG           _ullToMilliseconds  () const;
            ///< convert to milliseconds
        static BOOL         _bParse             (const std::string_t &csDT, const EFormatType cftFormat, CxDateTime *pdtDT);
            ///< parsing datetime string
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxDateTimeH


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
            (unsigned long)( ( current % 10000000 + 5 ) / 10 ) );
    }
#endif

