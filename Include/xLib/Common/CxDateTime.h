/****************************************************************************
* Class name:  CxDateTime
* Description: date, time
* File name:   CxDateTime.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     12.06.2009 15:37:34
*
*****************************************************************************/


#ifndef xLib_Common_CxDateTimeH
#define xLib_Common_CxDateTimeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#ifdef __BORLANDC__
    #include <vcl.h>
#endif
//---------------------------------------------------------------------------
class CxDateTime {
    public:
        //format type
        enum EFormatType {
            ftTime,     //HH.MM.SS.MMM
            ftDate,     //DD.MM.YYYY
            ftDateTime, //DD.MM.YYYY HH.MM.SS.MMM
            ftRFC1123   //Wdy, DD Mon YYYY HH:MM:SS GMT
        };

        //constructors, destructor
                           CxDateTime          ();
        explicit           CxDateTime          (const tString &csDT, EFormatType ftFormat);
        /*explicit*/       CxDateTime          (const CxDateTime &cdtDT);
        explicit           CxDateTime          (ULONGLONG ullMilliseconds);
                           CxDateTime          (USHORT usHour, USHORT usMinute, USHORT usSecond, USHORT usMillisecond);
                           CxDateTime          (USHORT usYear, USHORT usMonth, USHORT usDay);
                           CxDateTime          (USHORT usYear, USHORT usMonth, USHORT usDay, USHORT usHour, USHORT usMinute, USHORT usSecond, USHORT usMillisecond);
        virtual           ~CxDateTime          ();

        //comparison operators
        BOOL               operator ==         (const CxDateTime &cdtDT) const;
        BOOL               operator !=         (const CxDateTime &cdtDT) const;
        BOOL               operator <          (const CxDateTime &cdtDT) const;
        BOOL               operator <=         (const CxDateTime &cdtDT) const;
        BOOL               operator >          (const CxDateTime &cdtDT) const;
        BOOL               operator >=         (const CxDateTime &cdtDT) const;

        //assignment operators
        const CxDateTime  &operator =          (const CxDateTime &cdtDT);
    #ifdef xCOMPILER_CODEGEAR
        const CxDateTime  &operator =          (const TDateTime  &cdtDT);
    #endif
        const CxDateTime  &operator =          (ULONGLONG ullMillisecond);

        CxDateTime         operator +          (const CxDateTime &cdtDT) const;
        CxDateTime         operator -          (const CxDateTime &cdtDT) const;
        const CxDateTime  &operator +=         (const CxDateTime &cdtDT);
        const CxDateTime  &operator -=         (const CxDateTime &cdtDT);
        //++
        //--

        //get/set
        BOOL               bGet                (USHORT *pusYear, USHORT *pusMonth, USHORT *pusDay, USHORT *pusHour, USHORT *pusMinute, USHORT *pusSecond, USHORT *pusMillisecond) const;
        USHORT             usGetDayOfWeek      () const;
        BOOL               bSet                (ULONGLONG ullMSec);
        BOOL               bSet                (USHORT  usYear,  USHORT  usMonth,  USHORT  usDay,  USHORT  usHour,  USHORT  usMinute,  USHORT  usSecond,  USHORT  usMillisecond);

        //converting
        ULONGLONG          ullToMilliseconds   () const;
        ////ToUniversalTime();
        ////ToLocalTime();

        //formating
        tString            sFormat             (EFormatType ftFormat) const;

        //static
        static BOOL        bIsValid            (USHORT usYear, USHORT usMonth, USHORT usDay, USHORT usHour, USHORT usMinute, USHORT usSecond, USHORT usMillisecond);
        static BOOL        bIsValid            (const CxDateTime &cdtDT); //TODO: tests
               BOOL        bIsValid            () const; //TODO: tests

        static CxDateTime  dtGetCurrent        ();
        static USHORT      usDaysInMonth       (USHORT usYear, USHORT usMonth);
        static BOOL        bIsLeapYear         (USHORT usYear);
    #if defined(xOS_WIN)
        static LONGLONG    i64FiletimeToInt64  (const FILETIME &cftTime);
        static BOOL        bUnixTimeToFileTime (const time_t ctmUnixTime, FILETIME *pftFileTime);
    #endif

        //other
        static tString     sGetZodiacSign      (USHORT usMonth, USHORT usDay);
        static tString     sGetMonthStr        (USHORT usMonth, BOOL bIsShortName);
        static USHORT      usGetMonthNum       (const tString &csMonth, BOOL bIsShortName);
        static tString     sGetWeekDayStr      (USHORT usDay, BOOL bIsShortName);
        static USHORT      usGetWeekDayNum     (const tString &csDay, BOOL bIsShortName);

       private:
        BOOL               _m_bRes;

        //datetime msec member
        ULONGLONG          _m_ullDateTimeInMSec;    //LARGE_INTEGER

        //datetime members
        USHORT               _m_usYear;           //0-2010    Win (1601 through 30827)
        USHORT               _m_usMonth;          //1-12      Win (1-12)
        USHORT               _m_usDay;            //1-31      Win (1-31)
        USHORT               _m_usHour;           //0-23      Win (0-23)
        USHORT               _m_usMinute;         //0-59      Win (0-59)
        USHORT               _m_usSecond;         //0-61*     Win (0-59)
        USHORT               _m_usMillisecond;    //0-999     Win (0-99)

        static BOOL        _bParse             (const tString &csDT, EFormatType ftFormat, CxDateTime *pdtDT);
        ULONGLONG          _ullToMilliseconds  () const;
};
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxDateTimeH

// http://www.csharp-examples.net/string-format-datetime/
/*
UTC == GMT == Время по гринвичу

UTC это локальное время минус часовой пояс.
GMT работает с летнем/зимнем временем, поэтому оно ни как не может быть равным первому.
*/


/*
//---------------------------------------------------------------------------
__int64 i64DateTimeToSeconds(const TDateTime &dtDateTime) {
    WORD wYear, wMonth, wDay, wHour, wMin, wSec, wMSec;

    DecodeTime(dtDateTime, wHour, wMin, wSec, wMSec);

    return (wHour * 60 * 60) + (wMin * 60) + (wSec);
}
//---------------------------------------------------------------------------
*/


/*
#define INTERVAL_CENTI      1
#define INTERVAL_SEC        100
#define INTERVAL_MIN        6000
#define INTERVAL_HOUR       360000L
#define INTERVAL_DAY        8640000L

#define INTERVAL_SEC_SEC    1
#define INTERVAL_MIN_SEC    60
#define INTERVAL_HOUR_SEC    3600
#define INTERVAL_DAY_SEC    86400
*/






/*
typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
*/

//microSec
//#define FILETIME_TO_USEC(ft) (((unsigned __int64) ft.dwHighDateTime << 32 | ft.dwLowDateTime) / 10)



//GetTimeFormatEx
//GetDateFormat


/////__time64_t         _m_time;    /*__int64*/

/*
http://www.rsdn.ru/forum/cpp/2099875.flat.aspx

inline unix_t      _os_get()
    {
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
    }*/
