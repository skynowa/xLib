/****************************************************************************
* Class name:  CxDateTime
* Description: date, time
* File name:   CxDateTime.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     12.06.2009 15:37:34
*
*****************************************************************************/


#include <xLib/Common/CxDateTime.h>

#include <xLib/Common/CxArray.h>


/****************************************************************************
*    public: constructors, destructor    
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxDateTime (constructor)
CxDateTime::CxDateTime() :
    _m_bRes             (FALSE),
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
//TODO: CxDateTime (constructor)
CxDateTime::CxDateTime(const tString &csDT, EFormatType ftFormat) :
    _m_bRes             (FALSE),
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

    _m_bRes = _bParse(csDT, ftFormat, &dtDT);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);

    _m_bRes = bSet(dtDT._m_usYear, dtDT._m_usMonth,  dtDT._m_usDay,
                   dtDT._m_usHour, dtDT._m_usMinute, dtDT._m_usSecond, dtDT._m_usMillisecond);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: CxDateTime (constructor)
CxDateTime::CxDateTime(const CxDateTime &cdtDT) :
    _m_bRes             (FALSE),
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

    _m_bRes = bSet(cdtDT._m_usYear, cdtDT._m_usMonth,  cdtDT._m_usDay, 
                   cdtDT._m_usHour, cdtDT._m_usMinute, cdtDT._m_usSecond, cdtDT._m_usMillisecond);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: CxDateTime (constructor)
CxDateTime::CxDateTime(ULONGLONG ullMilliseconds) :
    _m_bRes             (FALSE),
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

    _m_bRes = bSet(ullMilliseconds);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: CxDateTime (constructor)
CxDateTime::CxDateTime(USHORT usHour, USHORT usMinute, USHORT usSecond, USHORT usMillisecond) :
    _m_bRes             (FALSE),
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

    _m_bRes = bSet(0, 0, 0, usHour, usMinute, usSecond, usMillisecond);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: CxDateTime (constructor)
CxDateTime::CxDateTime(USHORT usYear, USHORT usMonth, USHORT usDay) :
    _m_bRes             (FALSE),
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

    _m_bRes = bSet(usYear, usMonth, usDay, 0, 0, 0, 0);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
} 
//---------------------------------------------------------------------------
//DONE: CxDateTime (constructor)
CxDateTime::CxDateTime(USHORT usYear, USHORT usMonth, USHORT usDay, USHORT usHour, USHORT usMinute, USHORT usSecond, USHORT usMillisecond) :
    _m_bRes             (FALSE),
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

    _m_bRes = bSet(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxDateTime (destructor)
CxDateTime::~CxDateTime() { 
    /*DEBUG*/
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: comparison operators    
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: operator ==
BOOL
CxDateTime::operator == (const CxDateTime &cdtDT) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),      FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(cdtDT), FALSE);

    return static_cast<BOOL>(_m_ullDateTimeInMSec == cdtDT._m_ullDateTimeInMSec);
}
//---------------------------------------------------------------------------
//DONE: operator !=
BOOL
CxDateTime::operator != (const CxDateTime &cdtDT) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),      FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(cdtDT), FALSE);

    return static_cast<BOOL>( _m_ullDateTimeInMSec != cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
//DONE: operator <
BOOL
CxDateTime::operator <  (const CxDateTime &cdtDT) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),      FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(cdtDT), FALSE);

    return static_cast<BOOL>( _m_ullDateTimeInMSec < cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
//DONE: operator <=
BOOL
CxDateTime::operator <= (const CxDateTime &cdtDT) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),      FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(cdtDT), FALSE);

    return static_cast<BOOL>( _m_ullDateTimeInMSec <= cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
//DONE: operator >
BOOL
CxDateTime::operator > (const CxDateTime &cdtDT) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),      FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(cdtDT), FALSE);

    return static_cast<BOOL>( _m_ullDateTimeInMSec > cdtDT._m_ullDateTimeInMSec );
}
//---------------------------------------------------------------------------
//DONE: operator >=
BOOL
CxDateTime::operator >= (const CxDateTime &cdtDT) const {
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
//DONE: operator = ()
const CxDateTime &
CxDateTime::operator = (const CxDateTime &cdtDT) {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), *this);
    /*DEBUG*/

    xCHECK_RET(this == &cdtDT, *this);

    _m_bRes = bSet(cdtDT._m_ullDateTimeInMSec);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return *this);

    return *this;
}
//--------------------------------------------------------------------------
//DONE: operator = ()
#ifdef __BORLANDC__
const CxDateTime &
CxDateTime::operator = (const TDateTime &cdtDT) {
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

    _m_bRes = bSet(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, *this);

    return *this;
}
#endif
//---------------------------------------------------------------------------
//TODO: - operator = ()
const CxDateTime &
CxDateTime::operator = (ULONGLONG ullMillisecond) {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), *this);
    /*DEBUG*/

    _m_bRes = bSet(ullMillisecond);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return *this);

    return *this;
}
//--------------------------------------------------------------------------
//DONE: operator + ()
CxDateTime
CxDateTime::operator + (const CxDateTime &cdtDT) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), CxDateTime());
    /*DEBUG*/

    return CxDateTime(_m_ullDateTimeInMSec + cdtDT._m_ullDateTimeInMSec);
}
//--------------------------------------------------------------------------
//DONE: operator - ()
CxDateTime
CxDateTime::operator - (const CxDateTime &dtDT) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), CxDateTime());
    /*DEBUG*/

    return CxDateTime(_m_ullDateTimeInMSec - dtDT._m_ullDateTimeInMSec);
}
//--------------------------------------------------------------------------
//DONE: operator += ()
const CxDateTime &
CxDateTime::operator += (const CxDateTime &cdtDT) {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), *this);
    /*DEBUG*/

    _m_ullDateTimeInMSec += cdtDT._m_ullDateTimeInMSec;
    
    _m_bRes = bSet(_m_ullDateTimeInMSec);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return *this);

    return *this;
}
//--------------------------------------------------------------------------
//DONE: operator -= ()
const CxDateTime &
CxDateTime::operator -= (const CxDateTime &cdtDT) {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), *this);
    /*DEBUG*/

    _m_ullDateTimeInMSec -= cdtDT._m_ullDateTimeInMSec;

    _m_bRes = bSet(_m_ullDateTimeInMSec);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return *this);

    return *this;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    public: 
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bGet ()
BOOL
CxDateTime::bGet(USHORT *pusYear, USHORT *pusMonth, USHORT *pusDay, USHORT *pusHour, USHORT *pusMinute, USHORT *pusSecond, USHORT *pusMillisecond) const {
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
//DONE: usGetDayOfWeek (get day of week, days since Sunday 0-6)
USHORT
CxDateTime::usGetDayOfWeek() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0); //??? - 0
    /*DEBUG*/

    USHORT usRes      = 0;
    tm     tmTimeInfo = {0};
    
    tmTimeInfo.tm_year = _m_usYear  - 1900;
    tmTimeInfo.tm_mon  = _m_usMonth - 1;
    tmTimeInfo.tm_mday = _m_usDay;

    time_t tmTime = mktime(&tmTimeInfo);
    /*DEBUG*/xASSERT_RET(- 1 != tmTime, 0);

    usRes = tmTimeInfo.tm_wday;
    //xTRACEV(xT("That day is a %s"), sGetWeekDayStr(usRes, FALSE).c_str());

    return usRes;
}
//---------------------------------------------------------------------------
//TODO: ullToMilliseconds6 ()
ULONGLONG
CxDateTime::ullToMilliseconds() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0); //??? - 0

    return _m_ullDateTimeInMSec;
}
//--------------------------------------------------------------------------
//DONE: bGet (milliseconds to CxDateTime)
BOOL
CxDateTime::bSet(ULONGLONG ullMilliseconds) {
    /*DEBUG*/// n/a
    /*DEBUG*/// ullMSec - n/a

    //--------------------------------------------------
    //datetime msec member
    _m_ullDateTimeInMSec = ullMilliseconds;

    //--------------------------------------------------
    //datetime members

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
//DONE: bSet (datetime data to CxDateTime)
BOOL
CxDateTime::bSet(USHORT usYear, USHORT usMonth, USHORT usDay, USHORT usHour, USHORT usMinute, USHORT usSecond, USHORT usMillisecond) {
    /*DEBUG*/// n/a
    /*DEBUG*/// n/a

    /*DEBUG*/xASSERT_RET(TRUE == bIsValid(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond), FALSE);

    //datetime members
    _m_usYear            = usYear;
    _m_usMonth           = usMonth;
    _m_usDay             = usDay;
    _m_usHour            = usHour;
    _m_usMinute          = usMinute;
    _m_usSecond          = usSecond;
    _m_usMillisecond     = usMillisecond;

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
//DONE: _ullToMilliseconds (convert to milliseconds)
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
//DONE: sGetTimeStr (formating)
tString
CxDateTime::sFormat(EFormatType ftFormat) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), tString());
    /*DEBUG*/// n/a

    tString sRes;

    switch (ftFormat) {
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
                /*DEBUG*/xASSERT_RET(FALSE, tString());
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
//DONE: bIsValid (checking for a valid datetime)
/*static*/
BOOL
CxDateTime::bIsValid(USHORT usYear, USHORT usMonth, USHORT usDay, USHORT usHour, USHORT usMinute, USHORT usSecond, USHORT usMillisecond) {
    /*DEBUG*/

    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(usYear),        CxString::lexical_cast(usYear));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(usMonth),       CxString::lexical_cast(usMonth));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(usDay),         CxString::lexical_cast(usDay));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(usHour),        CxString::lexical_cast(usHour));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(usMinute),      CxString::lexical_cast(usMinute));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(usSecond),      CxString::lexical_cast(usSecond));
    /*DEBUG*/xASSERT_MSG(false != CxMacros::numeric_limits_check<USHORT>(usMillisecond), CxString::lexical_cast(usMillisecond));

    bool bYear        = (usYear   >= 0 && usYear   <= 9999);
    /*DEBUG*/xASSERT_MSG(true == bYear,        xT("usYear:   ")        + CxString::lexical_cast(usYear));

    bool bMonth       = (usMonth  >= 0/*1*/ && usMonth  <= 12);
    /*DEBUG*/xASSERT_MSG(true == bMonth,       xT("usMonth:  ")        + CxString::lexical_cast(usMonth));

    bool bDay         = true;   ////(usDay    >= 0/*1*/ && usDay    <= usDaysInMonth(usYear, usMonth));
    /*DEBUG*/xASSERT_MSG(true == bDay,         xT("usDay:    ")        + CxString::lexical_cast(usDay));

    bool bHour        = (usHour   >= 0 && usHour   <= 23);
    /*DEBUG*/xASSERT_MSG(true == bHour,        xT("usHour:   ")        + CxString::lexical_cast(usHour));

    bool bMinute      = (usMinute >= 0 && usMinute <= 59);
    /*DEBUG*/xASSERT_MSG(true == bMinute,      xT("usMinute: ")        + CxString::lexical_cast(usMinute));

    bool bSecond      = (usSecond >= 0 && usSecond <= 59);
    /*DEBUG*/xASSERT_MSG(true == bSecond,      xT("usSecond: ")        + CxString::lexical_cast(usSecond));

    bool bMillisecond = (usMillisecond >= 0 && usMillisecond   <= 999);
    /*DEBUG*/xASSERT_MSG(true == bMillisecond, xT("usMillisecond:   ") + CxString::lexical_cast(usMillisecond));

    xCHECK_RET(false == (bYear && bMonth && bDay && bHour && bMinute && bSecond && bMillisecond), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsValid ()
/*static*/
BOOL
CxDateTime::bIsValid(const CxDateTime &cdtDT) {
    /*DEBUG*/

    return bIsValid(cdtDT._m_usYear, cdtDT._m_usMonth, cdtDT._m_usDay, cdtDT._m_usHour, cdtDT._m_usMinute, cdtDT._m_usSecond, cdtDT._m_usMillisecond);;
}
//---------------------------------------------------------------------------
//DONE: bIsValid ()
BOOL
CxDateTime::bIsValid() const {
    /*DEBUG*/

    /*DEBUG*/xASSERT_MSG(CxMacros::numeric_limits_check<ULONGLONG>(_m_ullDateTimeInMSec), CxString::lexical_cast(_m_ullDateTimeInMSec));

    return bIsValid(*this);
}
//---------------------------------------------------------------------------
//DONE: dtGetCurrent (get current datetime)
/*static*/
CxDateTime
CxDateTime::dtGetCurrent() {
    /*DEBUG*/

#if defined(xOS_WIN)
    SYSTEMTIME stDateTime = {0};

    ::GetLocalTime(&stDateTime);
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(stDateTime.wYear, stDateTime.wMonth, stDateTime.wDay, stDateTime.wHour, stDateTime.wMinute, stDateTime.wSecond, stDateTime.wMilliseconds), CxDateTime());

    return CxDateTime(stDateTime.wYear, stDateTime.wMonth, stDateTime.wDay, stDateTime.wHour, stDateTime.wMinute, stDateTime.wSecond, stDateTime.wMilliseconds);
#elif defined(xOS_LINUX)
    //get milliseconds
    timeval tvTime = {0};

    INT iRes = gettimeofday(&tvTime, NULL);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, CxDateTime());

    //get datetime
    std::tm *ptmDateTime = {0};

    ptmDateTime = localtime( static_cast<const time_t *>( &tvTime.tv_sec ));
    /*DEBUG*/xASSERT_RET(NULL != ptmDateTime, CxDateTime());

    //set datetime
    USHORT usYear        = ptmDateTime->tm_year + 1900;
    USHORT usMonth       = ptmDateTime->tm_mon  + 1;
    USHORT usDay         = ptmDateTime->tm_mday;
    USHORT usHour        = ptmDateTime->tm_hour;
    USHORT usMinute      = ptmDateTime->tm_min;
    USHORT usSecond      = ptmDateTime->tm_sec;
    USHORT usMillisecond = static_cast<USHORT>( tvTime.tv_usec / 1000 );

    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond), CxDateTime());

    return CxDateTime(usYear, usMonth, usDay, usHour, usMinute, usSecond, usMillisecond);
#endif
}
//---------------------------------------------------------------------------
//DONE: i64FiletimeToInt64 ()
#if defined(xOS_WIN)
/*static*/
LONGLONG
CxDateTime::i64FiletimeToInt64(const FILETIME &cftTime) {
    return Int64ShllMod32(cftTime.dwHighDateTime, 32) | cftTime.dwLowDateTime;
}
#endif
//--------------------------------------------------------------------------
//DONE: usDaysInMonth
/*static*/
USHORT 
CxDateTime::usDaysInMonth(USHORT usYear, USHORT usMonth) {
    /*DEBUG*/

    xCHECK_RET(2 == usMonth && bIsLeapYear(usYear), 29);
        
    const CxArray<USHORT, 13> causMonthsDays = {{/*31*/0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

    USHORT usRes = 0;

    usRes = causMonthsDays[usMonth];

    return usRes;
}
//--------------------------------------------------------------------------
//DONE: bIsLeapYear
/*static*/
BOOL
CxDateTime::bIsLeapYear(USHORT usYear) {
    /*DEBUG*/

    return static_cast<BOOL>( 0 == (usYear % 4) && ( 0 != (usYear % 100) || 0 == (usYear % 400)) );
}
//--------------------------------------------------------------------------


/****************************************************************************
*    public: other
*
*****************************************************************************/

//--------------------------------------------------------------------------- 
//DONE: sGetZodiacSign (sign of the zodiac by date)
/*
NOTE: signs of the zodiac

        -----------------------------------------------------
        |  Знак        |  Символ  |  Западная астрология        |
        -----------------------------------------------------
        |  Овеен    |  U+2648  |  21 марта    — 20 апреля   |
        |  Телец    |  U+2649  |  21 апреля   — 21 мая      |
        |  Близнецы |  U+264A  |  22 мая      — 21 июня     |
        |  Рак        |  U+264B  |  22 июня     — 23 июля     |
        |  Лев        |  U+264С  |  24 июля     — 23 августа  |
        |  Дева        |  U+264D  |  24 августа  — 23 сентября |
        |  Весы        |  U+264E  |  24 сентября — 23 октября  |
        |  Скорпион |  U+264F  |  24 октября  — 22 ноября   |
        |  Стрелец  |  U+2650  |  23 ноября   — 21 декабря  |
        |  Козерог  |  U+2651  |  22 декабря  — 20 января   |
        |  Водолей  |  U+2652  |  21 января   — 19 февраля  |
        |  Рыбы        |  U+2653  |  20 февраля  — 20 марта    |
        -----------------------------------------------------
*/

/*static*/
tString
CxDateTime::sGetZodiacSign(USHORT usMonth, USHORT usDay) {
    /*DEBUG*/// usDay
    /*DEBUG*/// usMonth

    //Овен        |  U+2648  |  21 марта    — 20 апреля
    xCHECK_RET(usMonth == 3 && usDay >= 21,  xT("Овен"));
    xCHECK_RET(usMonth == 4 && usDay <= 20,  xT("Овен"));

    //Телец    |  U+2649  |  21 апреля   — 21 мая     
    xCHECK_RET(usMonth == 4 && usDay >= 21,  xT("Телец"));
    xCHECK_RET(usMonth == 5 && usDay <= 21,  xT("Телец"));

    //Близнецы |  U+264A  |  22 мая      — 21 июня     
    xCHECK_RET(usMonth == 5 && usDay >= 22,  xT("Близнецы"));
    xCHECK_RET(usMonth == 6 && usDay <= 21,  xT("Близнецы"));

    //Рак        |  U+264B  |  22 июня     — 23 июля     
    xCHECK_RET(usMonth == 6 && usDay >= 22,  xT("Рак"));
    xCHECK_RET(usMonth == 7 && usDay <= 23,  xT("Рак"));

    //Лев        |  U+264С  |  24 июля     — 23 августа  
    xCHECK_RET(usMonth == 7 && usDay >= 24,  xT("Лев"));
    xCHECK_RET(usMonth == 8 && usDay <= 23,  xT("Лев"));

    //Дева        |  U+264D  |  24 августа  — 23 сентября 
    xCHECK_RET(usMonth == 8 && usDay >= 24,  xT("Дева"));
    xCHECK_RET(usMonth == 9 && usDay <= 23,  xT("Дева"));

    //Весы        |  U+264E  |  24 сентября — 23 октября  
    xCHECK_RET(usMonth == 9 && usDay >= 24,  xT("Весы"));
    xCHECK_RET(usMonth == 10 && usDay <= 23, xT("Весы"));

    //Скорпион |  U+264F  |  24 октября  — 22 ноября   
    xCHECK_RET(usMonth == 10 && usDay >= 24, xT("Скорпион"));
    xCHECK_RET(usMonth == 11 && usDay <= 22, xT("Скорпион"));

    //Стрелец  |  U+2650  |  23 ноября   — 21 декабря  
    xCHECK_RET(usMonth == 11 && usDay >= 23, xT("Стрелец"));
    xCHECK_RET(usMonth == 12 && usDay <= 21, xT("Стрелец"));
    //Козерог  |  U+2651  |  22 декабря  — 20 января   
    xCHECK_RET(usMonth == 12 && usDay >= 22, xT("Козерог"));
    xCHECK_RET(usMonth == 1 && usDay <= 20,  xT("Козерог"));

    //Водолей  |  U+2652  |  21 января   — 19 февраля  
    xCHECK_RET(usMonth == 1 && usDay >= 21,  xT("Водолей"));
    xCHECK_RET(usMonth == 2 && usDay <= 19,  xT("Водолей"));

    //Рыбы        |  U+2653  |  20 февраля  — 20 марта    
    xCHECK_RET(usMonth == 2 && usDay >= 20,  xT("Рыбы"));
    xCHECK_RET(usMonth == 3 && usDay <= 20,  xT("Рыбы"));

    /*DEBUG*/xASSERT(FALSE);

    return tString();
}
//---------------------------------------------------------------------------
//DONE: sGetMonthStr ()
/*static*/ 
tString
CxDateTime::sGetMonthStr(USHORT usMonth, BOOL bIsShortName) {
    /*DEBUG*/// usMonth      - n/a
    /*DEBUG*/// bIsShortName - n/a

    xCHECK_DO(12 < usMonth, usMonth = 12);
    xCHECK_DO(1 > usMonth,  usMonth = 1);
    
    tString sRes;

    if (FALSE == bIsShortName) {
        //monthes numbering: 1-12
        const CxArray<tString, 12> casLongMonths = {{
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
        const CxArray<tString, 12> casShortMonths = {{
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
//DONE: usGetMonthNum (get month number by string)
/*static*/
USHORT
CxDateTime::usGetMonthNum(const tString &csMonth, BOOL bIsShortName) {
    /*DEBUG*/

    //monthes numbering: 1-12
    const CxArray<tString, 12> casLongMonths = {{
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
    const CxArray<tString, 12> casShortMonths = {{
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
        xCHECK_RET(FALSE == bIsShortName && TRUE == CxString::bCompareNoCase(csMonth, casLongMonths[i]), i + 1);
        xCHECK_RET(TRUE  == bIsShortName && TRUE == CxString::bCompareNoCase(csMonth, casShortMonths[i]), i + 1);
    }

    return static_cast<USHORT>( - 1 );  //TODO: static_cast<USHORT>( - 1 )
}
//---------------------------------------------------------------------------
//DONE: sGetWeekDayStr ()
/*static*/ 
tString
CxDateTime::sGetWeekDayStr(USHORT usDay, BOOL bIsShortName) {
    /*DEBUG*/// usDay       - n/a
    /*DEBUG*/// bIsShortName - n/a

    xCHECK_DO(6 < usDay, usDay = 6);
    xCHECK_DO(0 > usDay, usDay = 0);

    tString sRes;
    
    if (FALSE == bIsShortName) {
        //days numbering: 0-6
        const CxArray<tString, 7> casLongDays = {{
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
        const CxArray<tString, 8> casShortDays = {{
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
//DONE: usGetWeekDayNum (get week day number by string)
/*static*/
USHORT
CxDateTime::usGetWeekDayNum(const tString &csDay, BOOL bIsShortName) {
    /*DEBUG*/

    //days numbering: 0-6
    const CxArray<tString, 7> casLongDays = {{
        xT("Sunday"),    
        xT("Monday"),   
        xT("Tuesday"),  
        xT("Wednesday"), 
        xT("Thursday"),  
        xT("Friday"),    
        xT("Saturday")
    }};
    
    //days numbering: 0-6
    const CxArray<tString, 7> casShortDays = {{
        xT("Sun"),
        xT("Mon"),
        xT("Tue"),
        xT("Wed"),
        xT("Thu"),
        xT("Fri"),
        xT("Sat") 
    }};

    for (size_t i = 0; i < casLongDays.size(); ++ i) {
        xCHECK_RET(FALSE == bIsShortName && TRUE == CxString::bCompareNoCase(csDay, casLongDays[i]), i);
        xCHECK_RET(TRUE  == bIsShortName && TRUE == CxString::bCompareNoCase(csDay, casShortDays[i]), i);
    }

    return static_cast<USHORT>( - 1 );  //TODO: static_cast<USHORT>( - 1 )
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private    
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: _bParse (parsing datetime string)
/*static*/
BOOL
CxDateTime::_bParse(const tString &csDT, EFormatType ftFormat, CxDateTime *pdtDT) {
    /*DEBUG*/

    BOOL bRes = FALSE;

    switch (ftFormat) {
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
                tString sDT;

                sDT.assign(csDT);
                sDT.assign( CxString::sReplaceAll(sDT, CxConst::xCOLON,  CxConst::xSPACE) );
                sDT.assign( CxString::sReplaceAll(sDT, CxConst::xHYPHEN, CxConst::xSPACE) );

                //split by separator " "
                std::vector<tString> vecsDates;

                bRes = CxString::bSplit(sDT, CxConst::xSPACE, &vecsDates);
                /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

                //CxString::vStdVectorPrintT(vecsDates);

                //                   = CxString::lexical_cast<USHORT>( vecsDates.at(0) );   //Wed(0),
                (*pdtDT)._m_usDay    = CxString::lexical_cast<USHORT>( vecsDates.at(1) );   //23(1)
                (*pdtDT)._m_usMonth  = usGetMonthNum(vecsDates.at(2), TRUE);                //Mar(2)
                (*pdtDT)._m_usYear   = CxString::lexical_cast<USHORT>( vecsDates.at(3) );   //2011(3)
                (*pdtDT)._m_usHour   = CxString::lexical_cast<USHORT>( vecsDates.at(4) );   //15(4)
                (*pdtDT)._m_usMinute = CxString::lexical_cast<USHORT>( vecsDates.at(5) );   //05(5)
                (*pdtDT)._m_usSecond = CxString::lexical_cast<USHORT>( vecsDates.at(6) );   //49(6)

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

/*
How to convert local system time to UTC or GMT.

May 28th

Posted by Jijo Raj in Codeproject 

2 comments


In Messengers did you notice that the time stamp will be expressed in UTC or GMT. UTC stands for Universal Coordinated Time and GMT stands for Greenwich Mean Time and both are same. Since the users engaged in chat can be from across world, this one is really helpful to understand the real time. If they are expressed in local time, it can result in confusion.

For instance, User1 says – “Login to chat by 13:00″. It can be his local time and 13:00 for user2 might be a different time according to his timezone. And think what will happen?  UTC or GMT is very much useful if you communicate about time across world. But how can you convert your local system time to UTC or GMT?


First you’ve to get your timezone information by calling – GetTimeZoneInformation(). Then get the local time by calling – GetSystemTime() and translate it to UMT or GMT by calling – TzSpecificLocalTimeToSystemTime(). See the sample code snippet below.
// Get the local system time.
SYSTEMTIME LocalTime = { 0 };
GetSystemTime( &LocalTime );

// Get the timezone info.
TIME_ZONE_INFORMATION TimeZoneInfo;
GetTimeZoneInformation( &TimeZoneInfo );

// Convert local time to UTC.
SYSTEMTIME GmtTime = { 0 };
TzSpecificLocalTimeToSystemTime( &TimeZoneInfo,
&LocalTime,
&GmtTime );

// GMT = LocalTime + TimeZoneInfo.Bias
// TimeZoneInfo.Bias is the difference between local time
// and GMT in minutes.

// Local time expressed in terms of GMT bias.
float TimeZoneDifference = -( float(TimeZoneInfo.Bias) / 60 );
CString csLocalTimeInGmt;
csLocalTimeInGmt.Format( xT("%ld:%ld:%ld + %2.1f Hrs"),
GmtTime.wHour,
GmtTime.wMinute,
GmtTime.wSecond,
TimeZoneDifference );


Use SystemTimeToTzSpecificLocalTime() to convert UTC or GMT time back to your local timezone. You can also use UTC or GMT while logging messages. Anyway it all depends upto your needs.
*/


