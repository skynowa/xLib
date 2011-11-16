/**
 * \file  CxDateTime.cpp
 * \brief date, time
 */


#include <xLib/Common/CxDateTime.h>

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
    const std::string_t &csDT,
    const EFormatType   cftFormat
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

    BOOL bRes = _bParse(csDT, cftFormat, &dtDT);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);

    bRes = bSet(dtDT._m_usYear, dtDT._m_usMonth,  dtDT._m_usDay,
                   dtDT._m_usHour, dtDT._m_usMinute, dtDT._m_usSecond, dtDT._m_usMillisecond);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
CxDateTime::CxDateTime(
    const CxDateTime &cdtDT
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

    BOOL bRes = bSet(cdtDT._m_usYear, cdtDT._m_usMonth,  cdtDT._m_usDay,
                   cdtDT._m_usHour, cdtDT._m_usMinute, cdtDT._m_usSecond, cdtDT._m_usMillisecond);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
CxDateTime::CxDateTime(
    const ULONGLONG cullMilliseconds
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

    BOOL bRes = bSet(cullMilliseconds);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
CxDateTime::CxDateTime(
    const USHORT cusHour,
    const USHORT cusMinute,
    const USHORT cusSecond,
    const USHORT cusMillisecond
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

    BOOL bRes = bSet(0, 0, 0, cusHour, cusMinute, cusSecond, cusMillisecond);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
CxDateTime::CxDateTime(
    const USHORT cusYear,
    const USHORT cusMonth,
    const USHORT cusDay
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

    BOOL bRes = bSet(cusYear, cusMonth, cusDay, 0, 0, 0, 0);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
CxDateTime::CxDateTime(
    const USHORT usYear,
    const USHORT usMonth,
    const USHORT usDay,
    const USHORT usHour,
    const USHORT usMinute,
    const USHORT usSecond,
    const USHORT usMillisecond
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

    BOOL bRes = bSet(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
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
BOOL
CxDateTime::operator == (
    const CxDateTime &cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),      FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(cdtDT), FALSE);

    return static_cast<BOOL>(_m_ullDateTimeInMSec == cdtDT._m_ullDateTimeInMSec);
}
//---------------------------------------------------------------------------
BOOL
CxDateTime::operator != (
    const CxDateTime &cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),      FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(cdtDT), FALSE);

    return static_cast<BOOL>( _m_ullDateTimeInMSec != cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
BOOL
CxDateTime::operator <  (
    const CxDateTime &cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),      FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(cdtDT), FALSE);

    return static_cast<BOOL>( _m_ullDateTimeInMSec < cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
BOOL
CxDateTime::operator <= (
    const CxDateTime &cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),      FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(cdtDT), FALSE);

    return static_cast<BOOL>( _m_ullDateTimeInMSec <= cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
BOOL
CxDateTime::operator > (
    const CxDateTime &cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),      FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(cdtDT), FALSE);

    return static_cast<BOOL>( _m_ullDateTimeInMSec > cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
BOOL
CxDateTime::operator >= (
    const CxDateTime &cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),     FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(cdtDT), FALSE);

    return static_cast<BOOL>( _m_ullDateTimeInMSec >= cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: assignment operators
*
*****************************************************************************/

//--------------------------------------------------------------------------
const CxDateTime &
CxDateTime::operator = (
    const CxDateTime &cdtDT
)
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), *this);
    /*DEBUG*/

    xCHECK_RET(this == &cdtDT, *this);

    BOOL bRes = bSet(cdtDT._m_ullDateTimeInMSec);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return *this);

    return *this;
}
//--------------------------------------------------------------------------
#if defined(xOS_ENV_WIN) && defined(xCOMPILER_CODEGEAR)

const CxDateTime &
CxDateTime::operator = (
    const TDateTime &cdtDT
)
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), *this);
    /*DEBUG*/

    USHORT usYear        = 0;
    USHORT usMonth       = 0;
    USHORT usDay         = 0;
    USHORT usHour        = 0;
    USHORT usMinute      = 0;
    USHORT usSecond      = 0;
    USHORT usMillisecond = 0;

    cdtDT.DecodeDate(&usYear, &usMonth, &usDay);
    /*DEBUG*/// n/a

    cdtDT.DecodeTime(&usHour, &usMinute, &usSecond, &usMillisecond);
    /*DEBUG*/// n/a

    bRes = bSet(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, *this);

    return *this;
}

#endif
//---------------------------------------------------------------------------
const CxDateTime &
CxDateTime::operator = (
    const ULONGLONG cullMillisecond
)
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), *this);
    /*DEBUG*/

    BOOL bRes = bSet(cullMillisecond);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return *this);

    return *this;
}
//--------------------------------------------------------------------------
CxDateTime
CxDateTime::operator + (
    const CxDateTime &cdtDT
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), CxDateTime());
    /*DEBUG*/

    return CxDateTime(_m_ullDateTimeInMSec + cdtDT._m_ullDateTimeInMSec);
}
//--------------------------------------------------------------------------
CxDateTime
CxDateTime::operator - (
    const CxDateTime &dtDT
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), CxDateTime());
    /*DEBUG*/

    return CxDateTime(_m_ullDateTimeInMSec - dtDT._m_ullDateTimeInMSec);
}
//--------------------------------------------------------------------------
const CxDateTime &
CxDateTime::operator += (
    const CxDateTime &cdtDT
)
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), *this);
    /*DEBUG*/

    _m_ullDateTimeInMSec += cdtDT._m_ullDateTimeInMSec;

    BOOL bRes = bSet(_m_ullDateTimeInMSec);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return *this);

    return *this;
}
//--------------------------------------------------------------------------
const CxDateTime &
CxDateTime::operator -= (
    const CxDateTime &cdtDT
)
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), *this);
    /*DEBUG*/

    _m_ullDateTimeInMSec -= cdtDT._m_ullDateTimeInMSec;

    BOOL bRes = bSet(_m_ullDateTimeInMSec);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return *this);

    return *this;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    public:
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxDateTime::bGet(
    USHORT *pusYear,
    USHORT *pusMonth,
    USHORT *pusDay,
    USHORT *pusHour,
    USHORT *pusMinute,
    USHORT *pusSecond,
    USHORT *pusMillisecond
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/// n/a

    xCHECK_DO(NULL != pusYear,        *pusYear        = _m_usYear);
    xCHECK_DO(NULL != pusMonth,       *pusMonth       = _m_usMonth);
    xCHECK_DO(NULL != pusDay,         *pusDay         = _m_usDay);
    xCHECK_DO(NULL != pusHour,        *pusHour        = _m_usHour);
    xCHECK_DO(NULL != pusMinute,      *pusMinute      = _m_usMinute);
    xCHECK_DO(NULL != pusSecond,      *pusSecond      = _m_usSecond);
    xCHECK_DO(NULL != pusMillisecond, *pusMillisecond = _m_usMillisecond);

    return TRUE;
}
//---------------------------------------------------------------------------
USHORT
CxDateTime::usGetDayOfWeek() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0); //??? - 0
    /*DEBUG*/

    USHORT usRes      = 0;
    tm     tmTimeInfo = {0};

    tmTimeInfo.tm_year = _m_usYear  - 1900;
    tmTimeInfo.tm_mon  = _m_usMonth - 1;
    tmTimeInfo.tm_mday = _m_usDay;

    time_t tmTime = std::mktime(&tmTimeInfo);
    /*DEBUG*/xASSERT_RET(- 1 != tmTime, 0);

    usRes = tmTimeInfo.tm_wday;
    //xTRACEV(xT("That day is a %s"), sGetWeekDayStr(usRes, FALSE).c_str());

    return usRes;
}
//---------------------------------------------------------------------------
//TODO: ullToMilliseconds
ULONGLONG
CxDateTime::ullToMilliseconds() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0); //??? - 0

    return _m_ullDateTimeInMSec;
}
//--------------------------------------------------------------------------
BOOL
CxDateTime::bSet(
    const ULONGLONG cullMilliseconds
)
{
    /*DEBUG*/// n/a
    /*DEBUG*/// ullMSec - n/a

    //--------------------------------------------------
    //datetime msec member
    _m_ullDateTimeInMSec = cullMilliseconds;

    //--------------------------------------------------
    //datetime members
    ULONGLONG ullMilliseconds = cullMilliseconds;

    //converts milliseconds to datetime members
    _m_usYear         = static_cast<USHORT>( ullMilliseconds / ((1000ULL * 60 * 60 * 24 * 30) * 12) );

    ullMilliseconds  %= ((1000ULL * 60 * 60 * 24 * 30) * 12);
    _m_usMonth        = static_cast<USHORT>( ullMilliseconds / ((1000ULL * 60 * 60 * 24) * 30) );

    ullMilliseconds  %= ((1000ULL * 60 * 60 * 24) * 30);
    _m_usDay          = static_cast<USHORT>( ullMilliseconds / ((1000ULL * 60 * 60) * 24) );

    ullMilliseconds  %= ((1000ULL * 60 * 60) * 24);
    _m_usHour         = static_cast<USHORT>( ullMilliseconds / ((1000ULL * 60) * 60) );

    ullMilliseconds  %= ((1000ULL * 60) * 60);
    _m_usMinute       = static_cast<USHORT>( ullMilliseconds / ((1000ULL * 60)) );

    ullMilliseconds  %= ((1000ULL * 60));
    _m_usSecond       = static_cast<USHORT>( ullMilliseconds / 1000ULL );

    ullMilliseconds  %= 1000ULL;
    _m_usMillisecond  = static_cast<USHORT>( ullMilliseconds );

    return TRUE;
}
//--------------------------------------------------------------------------
BOOL
CxDateTime::bSet(
    const USHORT cusYear,
    const USHORT cusMonth,
    const USHORT cusDay,
    const USHORT cusHour,
    const USHORT cusMinute,
    const USHORT cusSecond,
    const USHORT cusMillisecond
)
{
    /*DEBUG*/// n/a
    /*DEBUG*/// n/a

    /*DEBUG*/xASSERT_RET(TRUE == bIsValid(cusYear, cusMonth, cusDay, cusHour, cusMinute, cusSecond, cusMillisecond), FALSE);

    //datetime members
    _m_usYear            = cusYear;
    _m_usMonth           = cusMonth;
    _m_usDay             = cusDay;
    _m_usHour            = cusHour;
    _m_usMinute          = cusMinute;
    _m_usSecond          = cusSecond;
    _m_usMillisecond     = cusMillisecond;

    //datetime msec member (convert to milliseconds)
    _m_ullDateTimeInMSec = _ullToMilliseconds();

    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    converting
*
*****************************************************************************/

//--------------------------------------------------------------------------
ULONGLONG
CxDateTime::_ullToMilliseconds() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0ULL);
    /*DEBUG*/

    ULONGLONG ullRes = 0ULL;

    ullRes += _m_usYear        * 1000ULL * 60 * 60 * 24 * 30 * 12;      //TODO: days in month 30 or 31 ???
    ullRes += _m_usMonth       * 1000ULL * 60 * 60 * 24 * 30;
    ullRes += _m_usDay         * 1000ULL * 60 * 60 * 24;
    ullRes += _m_usHour        * 1000ULL * 60 * 60;
    ullRes += _m_usMinute      * 1000ULL * 60;
    ullRes += _m_usSecond      * 1000ULL * 1;
    ullRes += _m_usMillisecond;

    return ullRes;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    public: formating
*
*****************************************************************************/

//--------------------------------------------------------------------------
std::string_t
CxDateTime::sFormat(
    const EFormatType cftFormat
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), std::string_t());
    /*DEBUG*/// n/a

    std::string_t sRes;

    switch (cftFormat) {
        case ftTime: {
                sRes = CxString::sFormat(
                        xT("%d:%.2d:%.2d:%.3d"),
                        _m_usHour, _m_usMinute, _m_usSecond, _m_usMillisecond);
            }
            break;

        case ftDate: {
                sRes = CxString::sFormat(
                        xT("%.2d.%.2d.%.4d"),
                        _m_usDay, _m_usMonth, _m_usYear);
            }
            break;

        case ftDateTime: {
                sRes = CxString::sFormat(
                        xT("%.2d.%.2d.%.4d %d:%.2d:%.2d:%.3d"),
                        _m_usDay, _m_usMonth, _m_usYear, _m_usHour, _m_usMinute, _m_usSecond, _m_usMillisecond);
            }
            break;

        case ftRFC1123: {
                sRes = CxString::sFormat(
                        xT("%s, %.2d %s %.4d %.2d:%.2d:%.2d GMT"),
                        sGetWeekDayStr(usGetDayOfWeek(), TRUE).c_str(), _m_usDay, CxDateTime::sGetMonthStr(_m_usMonth, TRUE).c_str(), _m_usYear, _m_usHour, _m_usMinute, _m_usSecond);
            }
            break;

        default: {
                /*DEBUG*/xASSERT_RET(FALSE, std::string_t());
            }
            break;
    }

    return sRes;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    public: static
*
*****************************************************************************/

//--------------------------------------------------------------------------
/*static*/
BOOL
CxDateTime::bIsValid(
    const USHORT cusYear,
    const USHORT cusMonth,
    const USHORT cusDay,
    const USHORT cusHour,
    const USHORT cusMinute,
    const USHORT cusSecond,
    const USHORT cusMillisecond
)
{
    /*DEBUG*/

    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(cusYear),        CxString::lexical_cast(cusYear));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(cusMonth),       CxString::lexical_cast(cusMonth));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(cusDay),         CxString::lexical_cast(cusDay));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(cusHour),        CxString::lexical_cast(cusHour));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(cusMinute),      CxString::lexical_cast(cusMinute));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(cusSecond),      CxString::lexical_cast(cusSecond));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(cusMillisecond), CxString::lexical_cast(cusMillisecond));

    bool bYear        = (/*cusYear   >= 0U && */cusYear   <= 9999U);
    /*DEBUG*/xASSERT_MSG(true == bYear,        xT("usYear:   ")        + CxString::lexical_cast(cusYear));

    bool bMonth       = (/*cusMonth  >= 0 /1/ &&*/ cusMonth  <= 12U);
    /*DEBUG*/xASSERT_MSG(true == bMonth,       xT("usMonth:  ")        + CxString::lexical_cast(cusMonth));

    bool bDay         = true;   ////(usDay    >= 0/*1*/ && usDay    <= usDaysInMonth(usYear, usMonth));
    /*DEBUG*/xASSERT_MSG(true == bDay,         xT("usDay:    ")        + CxString::lexical_cast(cusDay));

    bool bHour        = (/*cusHour   >= 0 &&*/ cusHour   <= 23U);
    /*DEBUG*/xASSERT_MSG(true == bHour,        xT("usHour:   ")        + CxString::lexical_cast(cusHour));

    bool bMinute      = (/*cusMinute >= 0 &&*/ cusMinute <= 59U);
    /*DEBUG*/xASSERT_MSG(true == bMinute,      xT("usMinute: ")        + CxString::lexical_cast(cusMinute));

    bool bSecond      = (/*cusSecond >= 0 &&*/ cusSecond <= 59U);
    /*DEBUG*/xASSERT_MSG(true == bSecond,      xT("usSecond: ")        + CxString::lexical_cast(cusSecond));

    bool bMillisecond = (/*cusMillisecond >= 0 &&*/ cusMillisecond   <= 999U);
    /*DEBUG*/xASSERT_MSG(true == bMillisecond, xT("usMillisecond:   ") + CxString::lexical_cast(cusMillisecond));

    xCHECK_RET(false == (bYear && bMonth && bDay && bHour && bMinute && bSecond && bMillisecond), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDateTime::bIsValid(
    const CxDateTime &cdtDT
)
{
    /*DEBUG*/

    return bIsValid(cdtDT._m_usYear, cdtDT._m_usMonth, cdtDT._m_usDay, cdtDT._m_usHour, cdtDT._m_usMinute, cdtDT._m_usSecond, cdtDT._m_usMillisecond);
}
//---------------------------------------------------------------------------
BOOL
CxDateTime::bIsValid() const {
    /*DEBUG*/

    /*DEBUG*/xASSERT_MSG(CxMacros::numeric_limits_check<ULONGLONG>(_m_ullDateTimeInMSec), CxString::lexical_cast(_m_ullDateTimeInMSec));

    return bIsValid(*this);
}
//---------------------------------------------------------------------------
/*static*/
CxDateTime
CxDateTime::dtGetCurrent() {
    /*DEBUG*/

#if defined(xOS_ENV_WIN)
    SYSTEMTIME stDateTime = {0};

    ::GetLocalTime(&stDateTime);
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(stDateTime.wYear, stDateTime.wMonth, stDateTime.wDay, stDateTime.wHour, stDateTime.wMinute, stDateTime.wSecond, stDateTime.wMilliseconds), CxDateTime());

    return CxDateTime(stDateTime.wYear, stDateTime.wMonth, stDateTime.wDay, stDateTime.wHour, stDateTime.wMinute, stDateTime.wSecond, stDateTime.wMilliseconds);
#elif defined(xOS_ENV_UNIX)
    //get milliseconds
    timeval tvTime = {0};

    int iRes = ::gettimeofday(&tvTime, NULL);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, CxDateTime());

    //get datetime
    std::tm *ptmDateTime = {0};

    ptmDateTime = std::localtime( reinterpret_cast<const time_t *>( &tvTime.tv_sec ));
    /*DEBUG*/xASSERT_RET(NULL != ptmDateTime, CxDateTime());

    //set datetime
    USHORT usYear        = ptmDateTime->tm_year + 1900U;
    USHORT usMonth       = ptmDateTime->tm_mon  + 1U;   //TODO: +1U ???
    USHORT usDay         = ptmDateTime->tm_mday;
    USHORT usHour        = ptmDateTime->tm_hour;
    USHORT usMinute      = ptmDateTime->tm_min;
    USHORT usSecond      = ptmDateTime->tm_sec;
    USHORT usMillisecond = static_cast<USHORT>( tvTime.tv_usec * 0.001 );

    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond), CxDateTime());

    return CxDateTime(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond);
#endif
}
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

/*static*/
LONGLONG
CxDateTime::i64FiletimeToInt64(
    const FILETIME &cftTime
)
{
    return Int64ShllMod32(cftTime.dwHighDateTime, 32) | cftTime.dwLowDateTime;
}

#endif
//--------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

/*static*/
BOOL
CxDateTime::bUnixTimeToFileTime(
    const time_t  ctmUnixTime,
    FILETIME     *pftFileTime
)
{
    /*DEBUG*/// ctmTime - n/a
    /*DEBUG*/xASSERT_RET(NULL != pftFileTime, FALSE);

    LONGLONG llRes = 0LL;

    llRes = Int32x32To64(ctmUnixTime, 10000000) + 116444736000000000;
    pftFileTime->dwLowDateTime  = static_cast<ULONG>( llRes );
    pftFileTime->dwHighDateTime = llRes >> 32;

    return TRUE;
}

#endif

//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

//TODO: make tests tmFileTimeToUnixTime
/*static*/
time_t
CxDateTime::tmFileTimeToUnixTime(
    const FILETIME &ftFileTime
)
{
    const __int64 NANOSECS_BETWEEN_EPOCHS = 116444736000000000LL;

    __int64 llRes = 0LL;

    llRes = (static_cast<__int64>( ftFileTime.dwHighDateTime ) << 32) + ftFileTime.dwLowDateTime;
    llRes -= NANOSECS_BETWEEN_EPOCHS;
    llRes /= 10000000;

    return static_cast<time_t>( llRes );
}

#endif
//--------------------------------------------------------------------------
/*static*/
USHORT
CxDateTime::usDaysInMonth(
    const USHORT cusYear,
    const USHORT cusMonth
)
{
    /*DEBUG*/

    xCHECK_RET(2 == cusMonth && bIsLeapYear(cusYear), 29);

    const CxArray<USHORT, 13> causMonthsDays = {{/*31*/0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

    USHORT usRes = 0;

    usRes = causMonthsDays[cusMonth];

    return usRes;
}
//--------------------------------------------------------------------------
/*static*/
BOOL
CxDateTime::bIsLeapYear(
    const USHORT cusYear
)
{
    /*DEBUG*/

    return static_cast<BOOL>( 0 == (cusYear % 4) && ( 0 != (cusYear % 100) || 0 == (cusYear % 400)) );
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

/*static*/
std::string_t
CxDateTime::sGetZodiacSign(
    const USHORT cusMonth,
    const USHORT cusDay
)
{
    /*DEBUG*/// usDay
    /*DEBUG*/// usMonth

    //Овен     |  U+2648  |  21 марта    — 20 апреля
    xCHECK_RET(cusMonth == 3  && cusDay >= 21, xT("Овен"));
    xCHECK_RET(cusMonth == 4  && cusDay <= 20, xT("Овен"));

    //Телец    |  U+2649  |  21 апреля   — 21 мая
    xCHECK_RET(cusMonth == 4  && cusDay >= 21, xT("Телец"));
    xCHECK_RET(cusMonth == 5  && cusDay <= 21, xT("Телец"));

    //Близнецы |  U+264A  |  22 мая      — 21 июня
    xCHECK_RET(cusMonth == 5  && cusDay >= 22, xT("Близнецы"));
    xCHECK_RET(cusMonth == 6  && cusDay <= 21, xT("Близнецы"));

    //Рак      |  U+264B  |  22 июня     — 23 июля
    xCHECK_RET(cusMonth == 6  && cusDay >= 22, xT("Рак"));
    xCHECK_RET(cusMonth == 7  && cusDay <= 23, xT("Рак"));

    //Лев      |  U+264С  |  24 июля     — 23 августа
    xCHECK_RET(cusMonth == 7  && cusDay >= 24, xT("Лев"));
    xCHECK_RET(cusMonth == 8  && cusDay <= 23, xT("Лев"));

    //Дева     |  U+264D  |  24 августа  — 23 сентября
    xCHECK_RET(cusMonth == 8  && cusDay >= 24, xT("Дева"));
    xCHECK_RET(cusMonth == 9  && cusDay <= 23, xT("Дева"));

    //Весы     |  U+264E  |  24 сентября — 23 октября
    xCHECK_RET(cusMonth == 9  && cusDay >= 24, xT("Весы"));
    xCHECK_RET(cusMonth == 10 && cusDay <= 23, xT("Весы"));

    //Скорпион |  U+264F  |  24 октября  — 22 ноября
    xCHECK_RET(cusMonth == 10 && cusDay >= 24, xT("Скорпион"));
    xCHECK_RET(cusMonth == 11 && cusDay <= 22, xT("Скорпион"));

    //Стрелец  |  U+2650  |  23 ноября   — 21 декабря
    xCHECK_RET(cusMonth == 11 && cusDay >= 23, xT("Стрелец"));
    xCHECK_RET(cusMonth == 12 && cusDay <= 21, xT("Стрелец"));

    //Козерог  |  U+2651  |  22 декабря  — 20 января
    xCHECK_RET(cusMonth == 12 && cusDay >= 22, xT("Козерог"));
    xCHECK_RET(cusMonth == 1  && cusDay <= 20, xT("Козерог"));

    //Водолей  |  U+2652  |  21 января   — 19 февраля
    xCHECK_RET(cusMonth == 1  && cusDay >= 21, xT("Водолей"));
    xCHECK_RET(cusMonth == 2  && cusDay <= 19, xT("Водолей"));

    //Рыбы     |  U+2653  |  20 февраля  — 20 марта
    xCHECK_RET(cusMonth == 2  && cusDay >= 20, xT("Рыбы"));
    xCHECK_RET(cusMonth == 3  && cusDay <= 20, xT("Рыбы"));

    /*DEBUG*/xASSERT(FALSE);

    return std::string_t();
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxDateTime::sGetMonthStr(
    USHORT     usMonth,
    const BOOL cbIsShortName
)
{
    /*DEBUG*/// usMonth      - n/a
    /*DEBUG*/// bIsShortName - n/a

    xCHECK_DO(12 < usMonth, usMonth = 12);
    xCHECK_DO(1  > usMonth, usMonth = 1);

    std::string_t sRes;

    if (FALSE == cbIsShortName) {
        //monthes numbering: 1-12
        const CxArray<std::string_t, 12> casLongMonths = {{
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

        sRes = casLongMonths[usMonth - 1];
    }
    else {
        //monthes numbering: 1-12
        const CxArray<std::string_t, 12> casShortMonths = {{
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

        sRes = casShortMonths[usMonth - 1];
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
USHORT
CxDateTime::usGetMonthNum(
    const std::string_t &csMonth,
    const BOOL          cbIsShortName
)
{
    /*DEBUG*/

    //monthes numbering: 1-12
    const CxArray<std::string_t, 12> casLongMonths = {{
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
    const CxArray<std::string_t, 12> casShortMonths = {{
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
        xCHECK_RET(FALSE == cbIsShortName && TRUE == CxString::bCompareNoCase(csMonth, casLongMonths[i]), i + 1);
        xCHECK_RET(TRUE  == cbIsShortName && TRUE == CxString::bCompareNoCase(csMonth, casShortMonths[i]), i + 1);
    }

    return static_cast<USHORT>( - 1 );  //TODO: static_cast<USHORT>( - 1 )
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxDateTime::sGetWeekDayStr(
    USHORT     usDay,
    const BOOL cbIsShortName
)
{
    /*DEBUG*/// cusDay       - n/a
    /*DEBUG*/// cbIsShortName - n/a

    xCHECK_DO(6 < usDay, usDay = 6);

    std::string_t sRes;

    if (FALSE == cbIsShortName) {
        //days numbering: 0-6
        const CxArray<std::string_t, 7> casLongDays = {{
            xT("Sunday"),
            xT("Monday"),
            xT("Tuesday"),
            xT("Wednesday"),
            xT("Thursday"),
            xT("Friday"),
            xT("Saturday"),
        }};

        sRes = casLongDays[usDay];
    } else {
        //days numbering: 0-6
        const CxArray<std::string_t, 8> casShortDays = {{
            xT("Sun"),
            xT("Mon"),
            xT("Tue"),
            xT("Wed"),
            xT("Thu"),
            xT("Fri"),
            xT("Sat")
        }};

        sRes = casShortDays[usDay];
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
USHORT
CxDateTime::usGetWeekDayNum(
    const std::string_t &csDay,
    const BOOL          cbIsShortName
)
{
    /*DEBUG*/

    //days numbering: 0-6
    const CxArray<std::string_t, 7> casLongDays = {{
        xT("Sunday"),
        xT("Monday"),
        xT("Tuesday"),
        xT("Wednesday"),
        xT("Thursday"),
        xT("Friday"),
        xT("Saturday")
    }};

    //days numbering: 0-6
    const CxArray<std::string_t, 7> casShortDays = {{
        xT("Sun"),
        xT("Mon"),
        xT("Tue"),
        xT("Wed"),
        xT("Thu"),
        xT("Fri"),
        xT("Sat")
    }};

    for (size_t i = 0; i < casLongDays.size(); ++ i) {
        xCHECK_RET(FALSE == cbIsShortName && TRUE == CxString::bCompareNoCase(csDay, casLongDays[i]), i);
        xCHECK_RET(TRUE  == cbIsShortName && TRUE == CxString::bCompareNoCase(csDay, casShortDays[i]), i);
    }

    return static_cast<USHORT>( - 1 );  //TODO: static_cast<USHORT>( - 1 )
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bParse ()
/*static*/
BOOL
CxDateTime::_bParse(
    const std::string_t &csDT,
    const EFormatType   cftFormat,
    CxDateTime         *pdtDT) {
    /*DEBUG*/

    BOOL bRes = FALSE;

    switch (cftFormat) {
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
                std::string_t sDT;

                sDT.assign(csDT);
                sDT.assign( CxString::sReplaceAll(sDT, CxConst::xCOLON,  CxConst::xSPACE) );
                sDT.assign( CxString::sReplaceAll(sDT, CxConst::xHYPHEN, CxConst::xSPACE) );

                //split by separator " "
                std::vector<std::string_t> vsDates;

                bRes = CxString::bSplit(sDT, CxConst::xSPACE, &vsDates);
                /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

                //CxString::vStdVectorPrintT(vsDates);

                //                   = CxString::lexical_cast<USHORT>( vsDates.at(0) );   //Wed(0),
                (*pdtDT)._m_usDay    = CxString::lexical_cast<USHORT>( vsDates.at(1) );   //23(1)
                (*pdtDT)._m_usMonth  = usGetMonthNum(vsDates.at(2), TRUE);                //Mar(2)
                (*pdtDT)._m_usYear   = CxString::lexical_cast<USHORT>( vsDates.at(3) );   //2011(3)
                (*pdtDT)._m_usHour   = CxString::lexical_cast<USHORT>( vsDates.at(4) );   //15(4)
                (*pdtDT)._m_usMinute = CxString::lexical_cast<USHORT>( vsDates.at(5) );   //05(5)
                (*pdtDT)._m_usSecond = CxString::lexical_cast<USHORT>( vsDates.at(6) );   //49(6)

                #if xTEMP_DISABLED
                    xTRACE(xT("-----------------------------------"));
                    xTRACE(xFUNCTION);
                    xTRACEV(xT("_m_usDay:    %i"), (*pdtDT)._m_usDay);
                    xTRACEV(xT("_m_usMonth:  %i"), (*pdtDT)._m_usMonth);
                    xTRACEV(xT("_m_usYear:   %i"), (*pdtDT)._m_usYear);
                    xTRACEV(xT("_m_usHour:   %i"), (*pdtDT)._m_usHour);
                    xTRACEV(xT("_m_usMinute: %i"), (*pdtDT)._m_usMinute);
                    xTRACEV(xT("_m_usSecond: %i"), (*pdtDT)._m_usSecond);
                    xTRACE(xT("-----------------------------------"));
                #endif
            }
            break;

        default: {
                /*DEBUG*/xASSERT_RET(FALSE, FALSE);
            }
            break;
    }

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
