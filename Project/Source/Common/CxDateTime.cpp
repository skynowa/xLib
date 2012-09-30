/**
 * \file  CxDateTime.cpp
 * \brief date, time
 */


#include <xLib/Common/CxDateTime.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>
#include <xLib/Common/CxArray.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public: constructors, destructor
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxDateTime::CxDateTime() :
    _m_ullDateTimeInMSec(0),
    _m_usYear           (0),
    _m_usMonth          (0),
    _m_usDay            (0),
    _m_usHour           (0),
    _m_usMinute         (0),
    _m_usSecond         (0),
    _m_usMillisecond    (0)
{
    /*DEBUG*/
}
//---------------------------------------------------------------------------
CxDateTime::CxDateTime(
    const std::tstring_t &a_csDT,
    const ExFormatType    a_cftFormat
) :
    _m_ullDateTimeInMSec(0),
    _m_usYear           (0),
    _m_usMonth          (0),
    _m_usDay            (0),
    _m_usHour           (0),
    _m_usMinute         (0),
    _m_usSecond         (0),
    _m_usMillisecond    (0)
{
    /*DEBUG*/

    CxDateTime dtDT;

    bool bRv = _bParse(a_csDT, a_cftFormat, &dtDT);
    /*DEBUG*/xASSERT_DO(true == bRv, return);

    bRv = bSet(dtDT._m_usYear, dtDT._m_usMonth,  dtDT._m_usDay,
                   dtDT._m_usHour, dtDT._m_usMinute, dtDT._m_usSecond, dtDT._m_usMillisecond);
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
CxDateTime::CxDateTime(
    const CxDateTime &a_cdtDT
) :
    _m_ullDateTimeInMSec(0),
    _m_usYear           (0),
    _m_usMonth          (0),
    _m_usDay            (0),
    _m_usHour           (0),
    _m_usMinute         (0),
    _m_usSecond         (0),
    _m_usMillisecond    (0)
{
    /*DEBUG*/

    bool bRv = bSet(a_cdtDT._m_usYear, a_cdtDT._m_usMonth,  a_cdtDT._m_usDay,
                    a_cdtDT._m_usHour, a_cdtDT._m_usMinute, a_cdtDT._m_usSecond, a_cdtDT._m_usMillisecond);
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
CxDateTime::CxDateTime(
    const ulonglong_t a_cullMilliseconds
) :
    _m_ullDateTimeInMSec(0),
    _m_usYear           (0),
    _m_usMonth          (0),
    _m_usDay            (0),
    _m_usHour           (0),
    _m_usMinute         (0),
    _m_usSecond         (0),
    _m_usMillisecond    (0)
{
    /*DEBUG*/

    bool bRv = bSet(a_cullMilliseconds);
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
CxDateTime::CxDateTime(
    const ushort_t a_cusHour,
    const ushort_t a_cusMinute,
    const ushort_t a_cusSecond,
    const ushort_t a_cusMillisecond
) :
    _m_ullDateTimeInMSec(0),
    _m_usYear           (0),
    _m_usMonth          (0),
    _m_usDay            (0),
    _m_usHour           (0),
    _m_usMinute         (0),
    _m_usSecond         (0),
    _m_usMillisecond    (0)
{
    /*DEBUG*/

    bool bRv = bSet(0, 0, 0, a_cusHour, a_cusMinute, a_cusSecond, a_cusMillisecond);
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
CxDateTime::CxDateTime(
    const ushort_t a_cusYear,
    const ushort_t a_cusMonth,
    const ushort_t a_cusDay
) :
    _m_ullDateTimeInMSec(0),
    _m_usYear           (0),
    _m_usMonth          (0),
    _m_usDay            (0),
    _m_usHour           (0),
    _m_usMinute         (0),
    _m_usSecond         (0),
    _m_usMillisecond    (0)
{
    /*DEBUG*/

    bool bRv = bSet(a_cusYear, a_cusMonth, a_cusDay, 0, 0, 0, 0);
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
CxDateTime::CxDateTime(
    const ushort_t a_cusYear,
    const ushort_t a_cusMonth,
    const ushort_t a_cusDay,
    const ushort_t a_cusHour,
    const ushort_t a_cusMinute,
    const ushort_t a_cusSecond,
    const ushort_t a_cusMillisecond
) :
    _m_ullDateTimeInMSec(0),
    _m_usYear           (0),
    _m_usMonth          (0),
    _m_usDay            (0),
    _m_usHour           (0),
    _m_usMinute         (0),
    _m_usSecond         (0),
    _m_usMillisecond    (0)
{
    /*DEBUG*/

    bool bRv = bSet(a_cusYear, a_cusMonth, a_cusDay, a_cusHour, a_cusMinute, a_cusSecond, a_cusMillisecond);
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
CxDateTime::~CxDateTime() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: comparison operators
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxDateTime::operator == (
    const CxDateTime &a_cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(),        false);
    /*DEBUG*/xASSERT_RET(false != bIsValid(a_cdtDT), false);

    return (_m_ullDateTimeInMSec == a_cdtDT._m_ullDateTimeInMSec);
}
//---------------------------------------------------------------------------
bool
CxDateTime::operator != (
    const CxDateTime &a_cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(),        false);
    /*DEBUG*/xASSERT_RET(false != bIsValid(a_cdtDT), false);

    return ( _m_ullDateTimeInMSec != a_cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
bool
CxDateTime::operator <  (
    const CxDateTime &a_cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(),        false);
    /*DEBUG*/xASSERT_RET(false != bIsValid(a_cdtDT), false);

    return ( _m_ullDateTimeInMSec < a_cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
bool
CxDateTime::operator <= (
    const CxDateTime &a_cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(),        false);
    /*DEBUG*/xASSERT_RET(false != bIsValid(a_cdtDT), false);

    return ( _m_ullDateTimeInMSec <= a_cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
bool
CxDateTime::operator > (
    const CxDateTime &a_cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(),        false);
    /*DEBUG*/xASSERT_RET(false != bIsValid(a_cdtDT), false);

    return ( _m_ullDateTimeInMSec > a_cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
bool
CxDateTime::operator >= (
    const CxDateTime &a_cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(),        false);
    /*DEBUG*/xASSERT_RET(false != bIsValid(a_cdtDT), false);

    return ( _m_ullDateTimeInMSec >= a_cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: assignment operators
*
*****************************************************************************/

//--------------------------------------------------------------------------
const CxDateTime &
CxDateTime::operator = (
    const CxDateTime &a_cdtDT
)
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), *this);
    /*DEBUG*/

    xCHECK_RET(this == &a_cdtDT, *this);

    bool bRv = bSet(a_cdtDT._m_ullDateTimeInMSec);
    /*DEBUG*/xASSERT_DO(true == bRv, return *this);

    return *this;
}
//---------------------------------------------------------------------------
const CxDateTime &
CxDateTime::operator = (
    const ulonglong_t a_cullMillisecond
)
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), *this);
    /*DEBUG*/

    bool bRv = bSet(a_cullMillisecond);
    /*DEBUG*/xASSERT_DO(true == bRv, return *this);

    return *this;
}
//--------------------------------------------------------------------------
CxDateTime
CxDateTime::operator + (
    const CxDateTime &a_cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), CxDateTime());
    /*DEBUG*/

    return CxDateTime(_m_ullDateTimeInMSec + a_cdtDT._m_ullDateTimeInMSec);
}
//--------------------------------------------------------------------------
CxDateTime
CxDateTime::operator - (
    const CxDateTime &a_dtDT
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), CxDateTime());
    /*DEBUG*/

    return CxDateTime(_m_ullDateTimeInMSec - a_dtDT._m_ullDateTimeInMSec);
}
//--------------------------------------------------------------------------
const CxDateTime &
CxDateTime::operator += (
    const CxDateTime &a_cdtDT
)
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), *this);
    /*DEBUG*/

    _m_ullDateTimeInMSec += a_cdtDT._m_ullDateTimeInMSec;

    bool bRv = bSet(_m_ullDateTimeInMSec);
    /*DEBUG*/xASSERT_DO(true == bRv, return *this);

    return *this;
}
//--------------------------------------------------------------------------
const CxDateTime &
CxDateTime::operator -= (
    const CxDateTime &a_cdtDT
)
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), *this);
    /*DEBUG*/

    _m_ullDateTimeInMSec -= a_cdtDT._m_ullDateTimeInMSec;

    bool bRv = bSet(_m_ullDateTimeInMSec);
    /*DEBUG*/xASSERT_DO(true == bRv, return *this);

    return *this;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    public:
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxDateTime::bGet(
    ushort_t *a_pusYear,
    ushort_t *a_pusMonth,
    ushort_t *a_pusDay,
    ushort_t *a_pusHour,
    ushort_t *a_pusMinute,
    ushort_t *a_pusSecond,
    ushort_t *a_pusMillisecond
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*/// n/a
    
    CxUtils::ptrAssignT(a_pusYear,        _m_usYear);
    CxUtils::ptrAssignT(a_pusMonth,       _m_usMonth);
    CxUtils::ptrAssignT(a_pusDay,         _m_usDay);
    CxUtils::ptrAssignT(a_pusHour,        _m_usHour);
    CxUtils::ptrAssignT(a_pusMinute,      _m_usMinute);
    CxUtils::ptrAssignT(a_pusSecond,      _m_usSecond);
    CxUtils::ptrAssignT(a_pusMillisecond, _m_usMillisecond);

    return true;
}
//---------------------------------------------------------------------------
ushort_t
CxDateTime::usGetDayOfWeek() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), 0); //??? - 0
    /*DEBUG*/

    ushort_t usRv      = 0;
    tm       tmTimeInfo = {0};

    tmTimeInfo.tm_year = _m_usYear  - 1900;
    tmTimeInfo.tm_mon  = _m_usMonth - 1;
    tmTimeInfo.tm_mday = _m_usDay;

    time_t tmTime = std::mktime(&tmTimeInfo);
    /*DEBUG*/xASSERT_RET(- 1 != tmTime, 0);

    usRv = tmTimeInfo.tm_wday;
    //xTRACEV(xT("That day is a %s"), sGetWeekDayStr(usRv, false).c_str());

    return usRv;
}
//---------------------------------------------------------------------------
//TODO: ullToMilliseconds
ulonglong_t
CxDateTime::ullToMilliseconds() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), 0); //??? - 0

    return _m_ullDateTimeInMSec;
}
//--------------------------------------------------------------------------
bool
CxDateTime::bSet(
    const ulonglong_t a_cullMilliseconds
)
{
    /*DEBUG*/// n/a
    /*DEBUG*/// ullMSec - n/a

    //--------------------------------------------------
    //datetime msec member
    _m_ullDateTimeInMSec = a_cullMilliseconds;

    //--------------------------------------------------
    //datetime members
    ulonglong_t ullMilliseconds = a_cullMilliseconds;

    //converts milliseconds to datetime members
    _m_usYear         = static_cast<ushort_t>( ullMilliseconds / ((1000ULL * 60 * 60 * 24 * 30) * 12) );

    ullMilliseconds  %= ((1000ULL * 60 * 60 * 24 * 30) * 12);
    _m_usMonth        = static_cast<ushort_t>( ullMilliseconds / ((1000ULL * 60 * 60 * 24) * 30) );

    ullMilliseconds  %= ((1000ULL * 60 * 60 * 24) * 30);
    _m_usDay          = static_cast<ushort_t>( ullMilliseconds / ((1000ULL * 60 * 60) * 24) );

    ullMilliseconds  %= ((1000ULL * 60 * 60) * 24);
    _m_usHour         = static_cast<ushort_t>( ullMilliseconds / ((1000ULL * 60) * 60) );

    ullMilliseconds  %= ((1000ULL * 60) * 60);
    _m_usMinute       = static_cast<ushort_t>( ullMilliseconds / ((1000ULL * 60)) );

    ullMilliseconds  %= ((1000ULL * 60));
    _m_usSecond       = static_cast<ushort_t>( ullMilliseconds / 1000ULL );

    ullMilliseconds  %= 1000ULL;
    _m_usMillisecond  = static_cast<ushort_t>( ullMilliseconds );

    return true;
}
//--------------------------------------------------------------------------
bool
CxDateTime::bSet(
    const ushort_t a_cusYear,
    const ushort_t a_cusMonth,
    const ushort_t a_cusDay,
    const ushort_t a_cusHour,
    const ushort_t a_cusMinute,
    const ushort_t a_cusSecond,
    const ushort_t a_cusMillisecond
)
{
    /*DEBUG*/// n/a
    /*DEBUG*/// n/a

    /*DEBUG*/xASSERT_RET(true == bIsValid(a_cusYear, a_cusMonth, a_cusDay, a_cusHour, a_cusMinute, a_cusSecond, a_cusMillisecond), false);

    //datetime members
    _m_usYear            = a_cusYear;
    _m_usMonth           = a_cusMonth;
    _m_usDay             = a_cusDay;
    _m_usHour            = a_cusHour;
    _m_usMinute          = a_cusMinute;
    _m_usSecond          = a_cusSecond;
    _m_usMillisecond     = a_cusMillisecond;

    //datetime msec member (convert to milliseconds)
    _m_ullDateTimeInMSec = _ullToMilliseconds();

    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    return true;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    converting
*
*****************************************************************************/

//--------------------------------------------------------------------------
ulonglong_t
CxDateTime::_ullToMilliseconds() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), 0ULL);
    /*DEBUG*/

    ulonglong_t ullRv = 0ULL;

    ullRv += _m_usYear        * 1000ULL * 60 * 60 * 24 * 30 * 12;      //TODO: days in month 30 or 31 ???
    ullRv += _m_usMonth       * 1000ULL * 60 * 60 * 24 * 30;
    ullRv += _m_usDay         * 1000ULL * 60 * 60 * 24;
    ullRv += _m_usHour        * 1000ULL * 60 * 60;
    ullRv += _m_usMinute      * 1000ULL * 60;
    ullRv += _m_usSecond      * 1000ULL * 1;
    ullRv += _m_usMillisecond;

    return ullRv;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    public: formating
*
*****************************************************************************/

//--------------------------------------------------------------------------
std::tstring_t
CxDateTime::sFormat(
    const ExFormatType a_cftFormat
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), std::tstring_t());
    /*DEBUG*/// n/a

    std::tstring_t sRv;

    switch (a_cftFormat) {
        case ftTime: {
                sRv = CxString::sFormat(
                        xT("%d:%.2d:%.2d:%.3d"),
                        _m_usHour, _m_usMinute, _m_usSecond, _m_usMillisecond);
            }
            break;

        case ftDate: {
                sRv = CxString::sFormat(
                        xT("%.2d.%.2d.%.4d"),
                        _m_usDay, _m_usMonth, _m_usYear);
            }
            break;

        case ftDateTime: {
                sRv = CxString::sFormat(
                        xT("%.2d.%.2d.%.4d %d:%.2d:%.2d:%.3d"),
                        _m_usDay, _m_usMonth, _m_usYear, _m_usHour, _m_usMinute, _m_usSecond, _m_usMillisecond);
            }
            break;

        case ftRFC1123: {
                sRv = CxString::sFormat(
                        xT("%s, %.2d %s %.4d %.2d:%.2d:%.2d GMT"),
                        sGetWeekDayStr(usGetDayOfWeek(), true).c_str(), _m_usDay, CxDateTime::sGetMonthStr(_m_usMonth, true).c_str(), _m_usYear, _m_usHour, _m_usMinute, _m_usSecond);
            }
            break;

        default: {
                /*DEBUG*/xASSERT_RET(false, std::tstring_t());
            }
            break;
    }

    return sRv;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    public: static
*
*****************************************************************************/

//--------------------------------------------------------------------------
/* static */
bool
CxDateTime::bIsValid(
    const ushort_t a_cusYear,
    const ushort_t a_cusMonth,
    const ushort_t a_cusDay,
    const ushort_t a_cusHour,
    const ushort_t a_cusMinute,
    const ushort_t a_cusSecond,
    const ushort_t a_cusMillisecond
)
{
    /*DEBUG*/

    bool bYear        = (/*cusYear   >= 0U && */a_cusYear   <= 9999U);
    /*DEBUG*/xASSERT_MSG(true == bYear,        xT("usYear:   ")        + CxString::string_cast(a_cusYear));

    bool bMonth       = (/*cusMonth  >= 0 /1/ &&*/ a_cusMonth  <= 12U);
    /*DEBUG*/xASSERT_MSG(true == bMonth,       xT("usMonth:  ")        + CxString::string_cast(a_cusMonth));

    bool bDay         = true;   ////(usDay    >= 0/*1*/ && usDay    <= usDaysInMonth(a_usYear, a_usMonth));
    /*DEBUG*/xASSERT_MSG(true == bDay,         xT("usDay:    ")        + CxString::string_cast(a_cusDay));

    bool bHour        = (/*cusHour   >= 0 &&*/ a_cusHour   <= 23U);
    /*DEBUG*/xASSERT_MSG(true == bHour,        xT("usHour:   ")        + CxString::string_cast(a_cusHour));

    bool bMinute      = (/*cusMinute >= 0 &&*/ a_cusMinute <= 59U);
    /*DEBUG*/xASSERT_MSG(true == bMinute,      xT("usMinute: ")        + CxString::string_cast(a_cusMinute));

    bool bSecond      = (/*cusSecond >= 0 &&*/ a_cusSecond <= 59U);
    /*DEBUG*/xASSERT_MSG(true == bSecond,      xT("usSecond: ")        + CxString::string_cast(a_cusSecond));

    bool bMillisecond = (/*cusMillisecond >= 0 &&*/ a_cusMillisecond   <= 999U);
    /*DEBUG*/xASSERT_MSG(true == bMillisecond, xT("usMillisecond:   ") + CxString::string_cast(a_cusMillisecond));

    xCHECK_RET(false == (bYear && bMonth && bDay && bHour && bMinute && bSecond && bMillisecond), false);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDateTime::bIsValid(
    const CxDateTime &a_cdtDT
)
{
    /*DEBUG*/

    return bIsValid(a_cdtDT._m_usYear, a_cdtDT._m_usMonth, a_cdtDT._m_usDay, a_cdtDT._m_usHour, a_cdtDT._m_usMinute, a_cdtDT._m_usSecond, a_cdtDT._m_usMillisecond);
}
//---------------------------------------------------------------------------
bool
CxDateTime::bIsValid() const {
    /*DEBUG*/

    return bIsValid(*this);
}
//---------------------------------------------------------------------------
/* static */
CxDateTime
CxDateTime::dtGetCurrent() {
    /*DEBUG*/

#if   xOS_ENV_WIN
    SYSTEMTIME stDateTime = {0};

    (void)::GetLocalTime(&stDateTime);
    /*DEBUG*/xASSERT_RET(false != bIsValid(stDateTime.wYear, stDateTime.wMonth, stDateTime.wDay, stDateTime.wHour, stDateTime.wMinute, stDateTime.wSecond, stDateTime.wMilliseconds), CxDateTime());

    return CxDateTime(stDateTime.wYear, stDateTime.wMonth, stDateTime.wDay, stDateTime.wHour, stDateTime.wMinute, stDateTime.wSecond, stDateTime.wMilliseconds);
#elif xOS_ENV_UNIX
    //get milliseconds
    timeval tvTime = {0};

    int iRv = ::gettimeofday(&tvTime, NULL);
    /*DEBUG*/xASSERT_RET(- 1 != iRv, CxDateTime());

    //get datetime
    std::tm *ptmDateTime = {0};

    ptmDateTime = std::localtime( reinterpret_cast<const time_t *>( &tvTime.tv_sec ));
    /*DEBUG*/xASSERT_RET(NULL != ptmDateTime, CxDateTime());

    //set datetime
    ushort_t usYear        = ptmDateTime->tm_year + 1900U;
    ushort_t usMonth       = ptmDateTime->tm_mon  + 1U;   //TODO: +1U ???
    ushort_t usDay         = ptmDateTime->tm_mday;
    ushort_t usHour        = ptmDateTime->tm_hour;
    ushort_t usMinute      = ptmDateTime->tm_min;
    ushort_t usSecond      = ptmDateTime->tm_sec;
    ushort_t usMillisecond = static_cast<ushort_t>( tvTime.tv_usec * 0.001 );

    /*DEBUG*/xASSERT_RET(false != bIsValid(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond), CxDateTime());

    return CxDateTime(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond);
#endif
}
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

/* static */
longlong_t
CxDateTime::i64FiletimeToInt64(
    const FILETIME &cftTime
)
{
    return Int64ShllMod32(cftTime.dwHighDateTime, 32) | cftTime.dwLowDateTime;
}

#endif
//--------------------------------------------------------------------------
#if   xOS_ENV_WIN

/* static */
bool
CxDateTime::bUnixTimeToFileTime(
    const time_t  a_ctmUnixTime,
    FILETIME     *a_pftFileTime
)
{
    /*DEBUG*/// ctmTime - n/a
    /*DEBUG*/xASSERT_RET(NULL != a_pftFileTime, false);

    longlong_t llRv = 0LL;

    llRv = Int32x32To64(a_ctmUnixTime, 10000000) + 116444736000000000;
    a_pftFileTime->dwLowDateTime  = static_cast<ulong_t>( llRv );
    a_pftFileTime->dwHighDateTime = llRv >> 32;

    return true;
}

#endif

//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

//TODO: make tests tmFileTimeToUnixTime
/* static */
time_t
CxDateTime::tmFileTimeToUnixTime(
    const FILETIME &a_ftFileTime
)
{
    const __int64 NANOSECS_BETWEEN_EPOCHS = 116444736000000000LL;

    __int64 llRv = 0LL;

    llRv = (static_cast<__int64>( a_ftFileTime.dwHighDateTime ) << 32) + a_ftFileTime.dwLowDateTime;
    llRv -= NANOSECS_BETWEEN_EPOCHS;
    llRv /= 10000000;

    return static_cast<time_t>( llRv );
}

#endif
//--------------------------------------------------------------------------
/* static */
ushort_t
CxDateTime::usDaysInMonth(
    const ushort_t a_cusYear,
    const ushort_t a_cusMonth
)
{
    /*DEBUG*/

    xCHECK_RET(2 == a_cusMonth && bIsLeapYear(a_cusYear), 29);

    const CxArray<ushort_t, 13> causMonthsDays = {{/*31*/0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

    ushort_t usRv = 0;

    usRv = causMonthsDays[a_cusMonth];

    return usRv;
}
//--------------------------------------------------------------------------
/* static */
bool
CxDateTime::bIsLeapYear(
    const ushort_t a_cusYear
)
{
    /*DEBUG*/

    return ( 0 == (a_cusYear % 4) && ( 0 != (a_cusYear % 100) || 0 == (a_cusYear % 400)) );
}
//--------------------------------------------------------------------------


/****************************************************************************
*    public: other
*
*****************************************************************************/

//---------------------------------------------------------------------------
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
std::tstring_t
CxDateTime::sGetZodiacSign(
    const ushort_t a_cusMonth,
    const ushort_t a_cusDay
)
{
    /*DEBUG*/// usDay
    /*DEBUG*/// usMonth

    //Овен     |  U+2648  |  21 марта    — 20 апреля
    xCHECK_RET(a_cusMonth == 3  && a_cusDay >= 21, xT("Овен"));
    xCHECK_RET(a_cusMonth == 4  && a_cusDay <= 20, xT("Овен"));

    //Телец    |  U+2649  |  21 апреля   — 21 мая
    xCHECK_RET(a_cusMonth == 4  && a_cusDay >= 21, xT("Телец"));
    xCHECK_RET(a_cusMonth == 5  && a_cusDay <= 21, xT("Телец"));

    //Близнецы |  U+264A  |  22 мая      — 21 июня
    xCHECK_RET(a_cusMonth == 5  && a_cusDay >= 22, xT("Близнецы"));
    xCHECK_RET(a_cusMonth == 6  && a_cusDay <= 21, xT("Близнецы"));

    //Рак      |  U+264B  |  22 июня     — 23 июля
    xCHECK_RET(a_cusMonth == 6  && a_cusDay >= 22, xT("Рак"));
    xCHECK_RET(a_cusMonth == 7  && a_cusDay <= 23, xT("Рак"));

    //Лев      |  U+264С  |  24 июля     — 23 августа
    xCHECK_RET(a_cusMonth == 7  && a_cusDay >= 24, xT("Лев"));
    xCHECK_RET(a_cusMonth == 8  && a_cusDay <= 23, xT("Лев"));

    //Дева     |  U+264D  |  24 августа  — 23 сентября
    xCHECK_RET(a_cusMonth == 8  && a_cusDay >= 24, xT("Дева"));
    xCHECK_RET(a_cusMonth == 9  && a_cusDay <= 23, xT("Дева"));

    //Весы     |  U+264E  |  24 сентября — 23 октября
    xCHECK_RET(a_cusMonth == 9  && a_cusDay >= 24, xT("Весы"));
    xCHECK_RET(a_cusMonth == 10 && a_cusDay <= 23, xT("Весы"));

    //Скорпион |  U+264F  |  24 октября  — 22 ноября
    xCHECK_RET(a_cusMonth == 10 && a_cusDay >= 24, xT("Скорпион"));
    xCHECK_RET(a_cusMonth == 11 && a_cusDay <= 22, xT("Скорпион"));

    //Стрелец  |  U+2650  |  23 ноября   — 21 декабря
    xCHECK_RET(a_cusMonth == 11 && a_cusDay >= 23, xT("Стрелец"));
    xCHECK_RET(a_cusMonth == 12 && a_cusDay <= 21, xT("Стрелец"));

    //Козерог  |  U+2651  |  22 декабря  — 20 января
    xCHECK_RET(a_cusMonth == 12 && a_cusDay >= 22, xT("Козерог"));
    xCHECK_RET(a_cusMonth == 1  && a_cusDay <= 20, xT("Козерог"));

    //Водолей  |  U+2652  |  21 января   — 19 февраля
    xCHECK_RET(a_cusMonth == 1  && a_cusDay >= 21, xT("Водолей"));
    xCHECK_RET(a_cusMonth == 2  && a_cusDay <= 19, xT("Водолей"));

    //Рыбы     |  U+2653  |  20 февраля  — 20 марта
    xCHECK_RET(a_cusMonth == 2  && a_cusDay >= 20, xT("Рыбы"));
    xCHECK_RET(a_cusMonth == 3  && a_cusDay <= 20, xT("Рыбы"));

    /*DEBUG*/xTEST_FAIL;

    return std::tstring_t();
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxDateTime::sGetMonthStr(
    ushort_t   a_usMonth,
    const bool a_cbIsShortName
)
{
    /*DEBUG*/// usMonth      - n/a
    /*DEBUG*/// bIsShortName - n/a

    xCHECK_DO(12 < a_usMonth, a_usMonth = 12);
    xCHECK_DO(1  > a_usMonth, a_usMonth = 1);

    std::tstring_t sRv;

    if (false == a_cbIsShortName) {
        //monthes numbering: 1-12
        const CxArray<std::tstring_t, 12> casLongMonths = {{
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

        sRv = casLongMonths[a_usMonth - 1];
    }
    else {
        //monthes numbering: 1-12
        const CxArray<std::tstring_t, 12> casShortMonths = {{
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

        sRv = casShortMonths[a_usMonth - 1];
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
ushort_t
CxDateTime::usGetMonthNum(
    const std::tstring_t &a_csMonth,
    const bool            a_cbIsShortName
)
{
    /*DEBUG*/

    //monthes numbering: 1-12
    const CxArray<std::tstring_t, 12> casLongMonths = {{
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

    //monthes numbering: 1-12
    const CxArray<std::tstring_t, 12> casShortMonths = {{
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

    for (size_t i = 0; i < casLongMonths.size(); ++ i) {
        xCHECK_RET(false == a_cbIsShortName && true == CxString::bCompareNoCase(a_csMonth, casLongMonths[i]), i + 1);
        xCHECK_RET(true  == a_cbIsShortName && true == CxString::bCompareNoCase(a_csMonth, casShortMonths[i]), i + 1);
    }

    return static_cast<ushort_t>( - 1 );  //TODO: static_cast<ushort_t>( - 1 )
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxDateTime::sGetWeekDayStr(
    ushort_t   a_usDay,
    const bool a_cbIsShortName
)
{
    /*DEBUG*/// cusDay       - n/a
    /*DEBUG*/// cbIsShortName - n/a

    xCHECK_DO(6 < a_usDay, a_usDay = 6);

    std::tstring_t sRv;

    if (false == a_cbIsShortName) {
        //days numbering: 0-6
        const CxArray<std::tstring_t, 7> casLongDays = {{
            xT("Sunday"),
            xT("Monday"),
            xT("Tuesday"),
            xT("Wednesday"),
            xT("Thursday"),
            xT("Friday"),
            xT("Saturday"),
        }};

        sRv = casLongDays[a_usDay];
    } else {
        //days numbering: 0-6
        const CxArray<std::tstring_t, 8> casShortDays = {{
            xT("Sun"),
            xT("Mon"),
            xT("Tue"),
            xT("Wed"),
            xT("Thu"),
            xT("Fri"),
            xT("Sat")
        }};

        sRv = casShortDays[a_usDay];
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
ushort_t
CxDateTime::usGetWeekDayNum(
    const std::tstring_t &a_csDay,
    const bool            a_cbIsShortName
)
{
    /*DEBUG*/

    //days numbering: 0-6
    const CxArray<std::tstring_t, 7> casLongDays = {{
        xT("Sunday"),
        xT("Monday"),
        xT("Tuesday"),
        xT("Wednesday"),
        xT("Thursday"),
        xT("Friday"),
        xT("Saturday")
    }};

    //days numbering: 0-6
    const CxArray<std::tstring_t, 7> casShortDays = {{
        xT("Sun"),
        xT("Mon"),
        xT("Tue"),
        xT("Wed"),
        xT("Thu"),
        xT("Fri"),
        xT("Sat")
    }};

    for (size_t i = 0; i < casLongDays.size(); ++ i) {
        xCHECK_RET(false == a_cbIsShortName && true == CxString::bCompareNoCase(a_csDay, casLongDays[i]), i);
        xCHECK_RET(true  == a_cbIsShortName && true == CxString::bCompareNoCase(a_csDay, casShortDays[i]), i);
    }

    return static_cast<ushort_t>( - 1 );  //TODO: static_cast<ushort_t>( - 1 )
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bParse ()
/* static */
bool
CxDateTime::_bParse(
    const std::tstring_t &a_csDT,
    const ExFormatType    a_cftFormat,
    CxDateTime           *a_pdtDT) {
    /*DEBUG*/

    bool bRv = false;

    switch (a_cftFormat) {
        case ftTime: {
                //TODO: ftTime
            }
            break;

        case ftDate: {
                //TODO: ftDate
            }
            break;

        case ftDateTime: {
                //TODO: ftDateTime
            }
            break;

        case ftRFC1123: {
                //Wdy, DD Mon YYYY HH:MM:SS GMT (Wed, 23 Mar 2011 15:05:49 GMT)

                //replace ":" to " ", "-" to " "
                std::tstring_t sDT;

                sDT = a_csDT;
                sDT = CxString::sReplaceAll(sDT, CxConst::xCOLON,  CxConst::xSPACE);
                sDT = CxString::sReplaceAll(sDT, CxConst::xHYPHEN, CxConst::xSPACE);

                //split by separator " "
                std::vec_tstring_t vsDates;

                bRv = CxString::bSplit(sDT, CxConst::xSPACE, &vsDates);
                /*DEBUG*/xASSERT_RET(true == bRv, false);

                //CxString::vStdVectorPrintT(vsDates);

                //                   = CxString::string_cast<ushort_t>( vsDates.at(0) );   //Wed(0),
                (*a_pdtDT)._m_usDay    = CxString::string_cast<ushort_t>( vsDates.at(1) );   //23(1)
                (*a_pdtDT)._m_usMonth  = usGetMonthNum(vsDates.at(2), true);                //Mar(2)
                (*a_pdtDT)._m_usYear   = CxString::string_cast<ushort_t>( vsDates.at(3) );   //2011(3)
                (*a_pdtDT)._m_usHour   = CxString::string_cast<ushort_t>( vsDates.at(4) );   //15(4)
                (*a_pdtDT)._m_usMinute = CxString::string_cast<ushort_t>( vsDates.at(5) );   //05(5)
                (*a_pdtDT)._m_usSecond = CxString::string_cast<ushort_t>( vsDates.at(6) );   //49(6)

                #if xTEMP_DISABLED
                    xTRACE(xT("-----------------------------------"));
                    xTRACE(xFUNCTION);
                    xTRACEV(xT("_m_usDay:    %i"), (*a_pdtDT)._m_usDay);
                    xTRACEV(xT("_m_usMonth:  %i"), (*a_pdtDT)._m_usMonth);
                    xTRACEV(xT("_m_usYear:   %i"), (*a_pdtDT)._m_usYear);
                    xTRACEV(xT("_m_usHour:   %i"), (*a_pdtDT)._m_usHour);
                    xTRACEV(xT("_m_usMinute: %i"), (*a_pdtDT)._m_usMinute);
                    xTRACEV(xT("_m_usSecond: %i"), (*a_pdtDT)._m_usSecond);
                    xTRACE(xT("-----------------------------------"));
                #endif
            }
            break;

        default: {
                /*DEBUG*/xASSERT_RET(false, false);
            }
            break;
    }

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
