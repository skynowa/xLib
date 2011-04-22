/****************************************************************************
* Class name:  CXDateTimeATL
* Description: работа с датами (ATL)
* File name:   CXDateTimeATL.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     16.06.2009 16:51:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <XLib/CXDateTimeATL.h>

//---------------------------------------------------------------------------
const INT  maxTimeBufferSize = 128;
const LONG maxDaysInSpan     = 3615897L;
//---------------------------------------------------------------------------


/****************************************************************************
*	CTimeSpan
*
*****************************************************************************/


//---------------------------------------------------------------------------
CTimeSpan::CTimeSpan() throw() :
	m_timeSpan(0)
{
}
//---------------------------------------------------------------------------
CTimeSpan::CTimeSpan(__time64_t time) throw() : 
	m_timeSpan(time) 
{
}
//---------------------------------------------------------------------------
CTimeSpan::CTimeSpan(LONG lDays, INT nHours, INT nMins, INT nSecs) throw() {
	m_timeSpan = nSecs + 60 * (nMins + 60 * (nHours + __int64(24) * lDays));
}
//---------------------------------------------------------------------------
LONGLONG CTimeSpan::GetDays() const throw() {
	return (m_timeSpan / (24 * 3600));
}
//---------------------------------------------------------------------------
LONGLONG CTimeSpan::GetTotalHours() const throw() {
	return (m_timeSpan / 3600);
}
//---------------------------------------------------------------------------
LONG CTimeSpan::GetHours() const throw() {
	return (LONG(GetTotalHours() - (GetDays() * 24)));
}
//---------------------------------------------------------------------------
LONGLONG CTimeSpan::GetTotalMinutes() const throw() {
	return (m_timeSpan / 60);
}
//---------------------------------------------------------------------------
LONG CTimeSpan::GetMinutes() const throw() {
	return (LONG(GetTotalMinutes() - (GetTotalHours() * 60)));
}
//---------------------------------------------------------------------------
LONGLONG CTimeSpan::GetTotalSeconds() const throw() {
	return (m_timeSpan);
}
//---------------------------------------------------------------------------
LONG CTimeSpan::GetSeconds() const throw() {
	return (LONG(GetTotalSeconds() - (GetTotalMinutes() * 60)));
}
//---------------------------------------------------------------------------
__time64_t CTimeSpan::GetTimeSpan() const throw() {
	return (m_timeSpan);
}
//---------------------------------------------------------------------------
CTimeSpan CTimeSpan::operator + (CTimeSpan span) const throw() {
	return (CTimeSpan(m_timeSpan + span.m_timeSpan));
}
//---------------------------------------------------------------------------
CTimeSpan CTimeSpan::operator - (CTimeSpan span) const throw() {
	return (CTimeSpan(m_timeSpan - span.m_timeSpan));
}
//---------------------------------------------------------------------------
CTimeSpan &CTimeSpan::operator += (CTimeSpan span) throw() {
	m_timeSpan += span.m_timeSpan;

	return (*this);
}
//---------------------------------------------------------------------------
CTimeSpan &CTimeSpan::operator -= (CTimeSpan span) throw() {
	m_timeSpan -= span.m_timeSpan;

	return (*this);
}
//---------------------------------------------------------------------------
BOOL CTimeSpan::operator == (CTimeSpan span) const throw() {
	return (m_timeSpan == span.m_timeSpan);
}
//---------------------------------------------------------------------------
BOOL CTimeSpan::operator != (CTimeSpan span) const throw() {
	return (m_timeSpan != span.m_timeSpan);
}
//---------------------------------------------------------------------------
BOOL CTimeSpan::operator < (CTimeSpan span) const throw() {
	return (m_timeSpan < span.m_timeSpan);
}
//---------------------------------------------------------------------------
BOOL CTimeSpan::operator > (CTimeSpan span) const throw() {
	return (m_timeSpan > span.m_timeSpan);
}
//---------------------------------------------------------------------------
BOOL CTimeSpan::operator <= (CTimeSpan span) const throw() {
	return (m_timeSpan <= span.m_timeSpan);
}
//---------------------------------------------------------------------------
BOOL CTimeSpan::operator >= (CTimeSpan span) const throw() {
	return (m_timeSpan >= span.m_timeSpan);
}
//---------------------------------------------------------------------------


/****************************************************************************
*	CTime
*
*****************************************************************************/


//---------------------------------------------------------------------------
CTime WINAPI CTime::GetCurrentTime() throw() {
	return (CTime(::_time64(NULL)));
}
//---------------------------------------------------------------------------
BOOL WINAPI CTime::IsValidFILETIME(const FILETIME &fileTime) throw() {
	FILETIME localTime = {0};
	if ( ! ::FileTimeToLocalFileTime(&fileTime, &localTime)) {
		return FALSE;
	}
	// then convert that time to system time
	SYSTEMTIME sysTime = {0};
	if ( ! ::FileTimeToSystemTime(&localTime, &sysTime)) {
		return FALSE;
	}

	return TRUE;
}
//---------------------------------------------------------------------------
CTime::CTime() throw() : 
	m_time(0) 
{
}
//---------------------------------------------------------------------------
CTime::CTime(__time64_t time) throw() : 
	m_time(time) 
{
}
//---------------------------------------------------------------------------
CTime::CTime(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMin, INT nSec, INT nDST) {
#pragma warning (push)
#pragma warning (disable: 4127)  // conditional expression constant
	//////ATLENSURE(nYear >= 1900);
	//////ATLENSURE(nMonth >= 1 && nMonth <= 12);
	//////ATLENSURE(nDay >= 1 && nDay <= 31);
	//////ATLENSURE(nHour >= 0 && nHour <= 23);
	//////ATLENSURE(nMin >= 0 && nMin <= 59);
	//////ATLENSURE(nSec >= 0 && nSec <= 59);
#pragma warning (pop)
	struct tm atm = {0};

	atm.tm_sec   = nSec;
	atm.tm_min   = nMin;
	atm.tm_hour  = nHour;
	atm.tm_mday  = nDay;
	atm.tm_mon   = nMonth - 1; // tm_mon is 0 based
	atm.tm_year  = nYear - 1900; // tm_year is 1900 based
	atm.tm_isdst = nDST;
	
	m_time = _mktime64(&atm);
	////ATLASSUME(m_time != -1);       // indicates an illegal input time
	if (m_time == - 1) {
		////AtlThrow(E_INVALIDARG);
	} 
}
//---------------------------------------------------------------------------
CTime::CTime(WORD wDosDate, WORD wDosTime, INT nDST) {
	struct tm atm = {0};

	atm.tm_sec   = (wDosTime & ~ 0xFFE0) << 1;
	atm.tm_min   = (wDosTime & ~ 0xF800) >> 5;
	atm.tm_hour  = wDosTime >> 11;
	atm.tm_mday  = wDosDate & ~ 0xFFE0;
	atm.tm_mon   = ((wDosDate & ~ 0xFE00) >> 5) - 1;
	atm.tm_year  = (wDosDate >> 9) + 80;
	atm.tm_isdst = nDST;

	m_time = _mktime64(&atm);
	////ATLASSUME(m_time != -1);       // indicates an illegal input time
	//////if(m_time == -1)
	//////	AtlThrow(E_INVALIDARG);
}
//---------------------------------------------------------------------------
CTime::CTime(const SYSTEMTIME &sysTime, INT nDST) {
	if (sysTime.wYear < 1900) {
		__time64_t time0 = 0L;
		CTime timeT(time0);
		*this = timeT;
	}  else {
		CTime timeT((INT)sysTime.wYear, (INT)sysTime.wMonth, (INT)sysTime.wDay, (INT)sysTime.wHour, (INT)sysTime.wMinute, (INT)sysTime.wSecond, nDST);
		*this = timeT;
	}
}
//---------------------------------------------------------------------------
CTime::CTime(const FILETIME &fileTime, INT nDST) {
	// first convert file time (UTC time) to local time
	FILETIME localTime = {0};
	if ( ! ::FileTimeToLocalFileTime(&fileTime, &localTime)) {
		m_time = 0;
		////AtlThrow(E_INVALIDARG);
		return ;
	}
	// then convert that time to system time
	SYSTEMTIME sysTime = {0};
	if ( ! ::FileTimeToSystemTime(&localTime, &sysTime)) {
		m_time = 0;
		////AtlThrow(E_INVALIDARG);		
		return ;
	}
	// then convert the system time to a time_t (C-runtime local time)
	CTime timeT(sysTime, nDST);
	*this = timeT;
}
//---------------------------------------------------------------------------
CTime &CTime::operator = (__time64_t time) throw() {
	m_time = time;

	return (*this);
}
//---------------------------------------------------------------------------
CTime &CTime::operator += (CTimeSpan span) throw() {
	m_time += span.GetTimeSpan();
	return (*this);
}
//---------------------------------------------------------------------------
CTime &CTime::operator -= (CTimeSpan span) throw() {
	m_time -= span.GetTimeSpan();

	return (*this);
}
//---------------------------------------------------------------------------
CTimeSpan CTime::operator - (CTime time) const throw() {
	return (CTimeSpan(m_time - time.m_time));
}
//---------------------------------------------------------------------------
CTime CTime::operator - (CTimeSpan span) const throw() {
	return (CTime(m_time - span.GetTimeSpan()));
}
//---------------------------------------------------------------------------
CTime CTime::operator + (CTimeSpan span) const throw() {
	return (CTime(m_time + span.GetTimeSpan()));
}
//---------------------------------------------------------------------------
BOOL CTime::operator == (CTime time) const throw() {
	return (m_time == time.m_time);
}
//---------------------------------------------------------------------------
BOOL CTime::operator != (CTime time) const throw() {
	return (m_time != time.m_time);
}
//---------------------------------------------------------------------------
BOOL CTime::operator < (CTime time) const throw() {
	return (m_time < time.m_time);
}
//---------------------------------------------------------------------------
BOOL CTime::operator > (CTime time) const throw() {
	return (m_time > time.m_time);
}
//---------------------------------------------------------------------------
BOOL CTime::operator <= (CTime time) const throw() {
	return (m_time <= time.m_time);
}
//---------------------------------------------------------------------------
BOOL CTime::operator >= (CTime time) const throw() {
	return (m_time >= time.m_time);
}
//---------------------------------------------------------------------------
struct tm *CTime::GetGmtTm(struct tm *ptm)const {
	// Ensure ptm is valid
	////ATLENSURE(ptm != NULL);
	if (ptm != NULL) {
		struct tm ptmTemp = {0};

		errno_t err = _gmtime64_s(&ptmTemp, &m_time);
		// Be sure the call succeeded
		if (err != 0) {
			return NULL;
		} 
		*ptm = ptmTemp;

		return ptm;
	}

	return NULL;
}
//---------------------------------------------------------------------------
struct tm *CTime::GetLocalTm(struct tm *ptm)const {
	// Ensure ptm is valid
	////ATLENSURE(ptm != NULL);
	if (ptm != NULL) {
		struct tm ptmTemp = {0};

		errno_t err = _localtime64_s(&ptmTemp, &m_time);
		if (err != 0) {
			return NULL; // indicates that m_time was not initialized!
		} 
		*ptm = ptmTemp;

		return ptm;
	}

	return NULL;
}
//---------------------------------------------------------------------------
BOOL CTime::GetAsSystemTime(SYSTEMTIME &timeDest) const throw() {
	struct tm ttm  = {0};
	struct tm *ptm = NULL;

	ptm = GetLocalTm(&ttm);

	if ( ! ptm) {
		return FALSE;
	} 

	timeDest.wYear         = (WORD)(1900+ptm->tm_year);
	timeDest.wMonth        = (WORD)(1+ptm->tm_mon);
	timeDest.wDayOfWeek    = (WORD)ptm->tm_wday;
	timeDest.wDay          = (WORD)ptm->tm_mday;
	timeDest.wHour         = (WORD)ptm->tm_hour;
	timeDest.wMinute       = (WORD)ptm->tm_min;
	timeDest.wSecond       = (WORD)ptm->tm_sec;
	timeDest.wMilliseconds = 0;

	return TRUE;
}
//---------------------------------------------------------------------------
__time64_t CTime::GetTime() const throw() {
	return (m_time);
}
//---------------------------------------------------------------------------
INT CTime::GetYear() const {
	struct tm ttm  = {0};
	struct tm *ptm = NULL;

	ptm = GetLocalTm(&ttm);

	return ptm ? (ptm->tm_year) + 1900: 0;
}
//---------------------------------------------------------------------------
INT CTime::GetMonth() const {
	struct tm ttm  = {0};
	struct tm *ptm = NULL;

	ptm = GetLocalTm(&ttm);

	return ptm ? ptm->tm_mon + 1: 0;
}
//---------------------------------------------------------------------------
INT CTime::GetDay() const {
	struct tm ttm  = {0};
	struct tm *ptm = NULL;

	ptm = GetLocalTm(&ttm);

	return ptm ? ptm->tm_mday: 0;
}
//---------------------------------------------------------------------------
INT CTime::GetHour() const {
	struct tm ttm  = {0};
	struct tm *ptm = NULL;

	ptm = GetLocalTm(&ttm);

	return ptm ? ptm->tm_hour:  - 1;
}
//---------------------------------------------------------------------------
INT CTime::GetMinute() const {
	struct tm ttm  = {0};
	struct tm *ptm = NULL;

	ptm = GetLocalTm(&ttm);

	return ptm ? ptm->tm_min:  - 1;
}
//---------------------------------------------------------------------------
INT CTime::GetSecond() const {
	struct tm ttm  = {0};
	struct tm *ptm = NULL;

	ptm = GetLocalTm(&ttm);

	return ptm ? ptm->tm_sec:  - 1;
}
//---------------------------------------------------------------------------
INT CTime::GetDayOfWeek() const {
	struct tm ttm  = {0};
	struct tm *ptm = NULL;

	ptm = GetLocalTm(&ttm);

	return ptm ? ptm->tm_wday + 1: 0;
}

//---------------------------------------------------------------------------

/****************************************************************************
*	CFileTimeSpan
*
*****************************************************************************/

//---------------------------------------------------------------------------
CFileTimeSpan::CFileTimeSpan() throw() : 
	m_nSpan(0) 
{
}
//---------------------------------------------------------------------------
CFileTimeSpan::CFileTimeSpan(const CFileTimeSpan &span) throw() : 
	m_nSpan(span.m_nSpan) 
{
}
//---------------------------------------------------------------------------
CFileTimeSpan::CFileTimeSpan(LONGLONG nSpan) throw() : 
	m_nSpan(nSpan) 
{
}
//---------------------------------------------------------------------------
CFileTimeSpan &CFileTimeSpan::operator = (const CFileTimeSpan &span) throw() {
	m_nSpan = span.m_nSpan;

	return (*this);
} 
//---------------------------------------------------------------------------
CFileTimeSpan &CFileTimeSpan::operator += (CFileTimeSpan span) throw() {
	m_nSpan += span.m_nSpan;

	return (*this);
}
//---------------------------------------------------------------------------
CFileTimeSpan &CFileTimeSpan::operator -= (CFileTimeSpan span) throw() {
	m_nSpan -= span.m_nSpan;

	return (*this);
}
//---------------------------------------------------------------------------
CFileTimeSpan CFileTimeSpan::operator + (CFileTimeSpan span) const throw() {
	return (CFileTimeSpan(m_nSpan + span.m_nSpan));
}
//---------------------------------------------------------------------------
CFileTimeSpan CFileTimeSpan::operator - (CFileTimeSpan span) const throw() {
	return (CFileTimeSpan(m_nSpan - span.m_nSpan));
}
//---------------------------------------------------------------------------
BOOL CFileTimeSpan::operator == (CFileTimeSpan span) const throw() {
	return (m_nSpan == span.m_nSpan);
}
//---------------------------------------------------------------------------
BOOL CFileTimeSpan::operator != (CFileTimeSpan span) const throw() {
	return (m_nSpan != span.m_nSpan);
}
//---------------------------------------------------------------------------
BOOL CFileTimeSpan::operator < (CFileTimeSpan span) const throw() {
	return (m_nSpan < span.m_nSpan);
}
//---------------------------------------------------------------------------
BOOL CFileTimeSpan::operator > (CFileTimeSpan span) const throw() {
	return (m_nSpan > span.m_nSpan);
}
//---------------------------------------------------------------------------
BOOL CFileTimeSpan::operator <= (CFileTimeSpan span) const throw() {
	return (m_nSpan <= span.m_nSpan);
}
//---------------------------------------------------------------------------
BOOL CFileTimeSpan::operator >= (CFileTimeSpan span) const throw() {
	return (m_nSpan >= span.m_nSpan);
}
//---------------------------------------------------------------------------
LONGLONG CFileTimeSpan::GetTimeSpan() const throw() {
	return (m_nSpan);
}
//---------------------------------------------------------------------------
VOID CFileTimeSpan::SetTimeSpan(LONGLONG nSpan) throw() {
	m_nSpan = nSpan;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	CFileTime
*
*****************************************************************************/


//---------------------------------------------------------------------------
CFileTime::CFileTime() throw() {
	dwLowDateTime = 0;
	dwHighDateTime = 0;
}
//---------------------------------------------------------------------------
CFileTime::CFileTime(const FILETIME &ft) throw() {
	dwLowDateTime = ft.dwLowDateTime;
	dwHighDateTime = ft.dwHighDateTime;
}
//---------------------------------------------------------------------------
CFileTime::CFileTime(ULONGLONG nTime) throw() {
	dwLowDateTime  = DWORD(nTime);
	dwHighDateTime = DWORD(nTime >> 32);
}
//---------------------------------------------------------------------------
CFileTime &CFileTime::operator = (const FILETIME &ft) throw() {
	dwLowDateTime  = ft.dwLowDateTime;
	dwHighDateTime = ft.dwHighDateTime;

	return (*this);
}
//---------------------------------------------------------------------------
CFileTime WINAPI CFileTime::GetCurrentTime() throw() {
	CFileTime ft;
	GetSystemTimeAsFileTime(&ft);

	return ft;
}
//---------------------------------------------------------------------------
CFileTime &CFileTime::operator += (CFileTimeSpan span) throw() {
	SetTime(GetTime() + span.GetTimeSpan());

	return (*this);
}
//---------------------------------------------------------------------------
CFileTime &CFileTime::operator -= (CFileTimeSpan span) throw() {
	SetTime(GetTime() - span.GetTimeSpan());

	return (*this);
}
//---------------------------------------------------------------------------
CFileTime CFileTime::operator + (CFileTimeSpan span) const throw() {
	return (CFileTime(GetTime() + span.GetTimeSpan()));
}
//---------------------------------------------------------------------------
CFileTime CFileTime::operator - (CFileTimeSpan span) const throw() {
	return (CFileTime(GetTime() - span.GetTimeSpan()));
}
//---------------------------------------------------------------------------
CFileTimeSpan CFileTime::operator - (CFileTime ft) const throw() {
	return (CFileTimeSpan(GetTime() - ft.GetTime()));
}
//---------------------------------------------------------------------------
BOOL CFileTime::operator == (CFileTime ft) const throw() {
	return (GetTime() == ft.GetTime());
}
//---------------------------------------------------------------------------
BOOL CFileTime::operator != (CFileTime ft) const throw() {
	return (GetTime() != ft.GetTime());
}
//---------------------------------------------------------------------------
BOOL CFileTime::operator < (CFileTime ft) const throw() {
	return (GetTime() < ft.GetTime());
}
//---------------------------------------------------------------------------
BOOL CFileTime::operator > (CFileTime ft) const throw() {
	return (GetTime() > ft.GetTime());
}
//---------------------------------------------------------------------------
BOOL CFileTime::operator <= (CFileTime ft) const throw() {
	return (GetTime() <= ft.GetTime());
}
//---------------------------------------------------------------------------
BOOL CFileTime::operator >= (CFileTime ft) const throw() {
	return (GetTime() >= ft.GetTime());
}
//---------------------------------------------------------------------------
ULONGLONG CFileTime::GetTime() const throw() {
	return ((ULONGLONG(dwHighDateTime) << 32) | dwLowDateTime);
}
//---------------------------------------------------------------------------
VOID CFileTime::SetTime(ULONGLONG nTime) throw() {
	dwLowDateTime  = DWORD(nTime);
	dwHighDateTime = DWORD(nTime >> 32);
}
//---------------------------------------------------------------------------
CFileTime CFileTime::UTCToLocal() const throw() {
	CFileTime ftLocal;
	::FileTimeToLocalFileTime(this, &ftLocal);

	return (ftLocal);
}
//---------------------------------------------------------------------------
CFileTime CFileTime::LocalToUTC() const throw() {
	CFileTime ftUTC;
	::LocalFileTimeToFileTime(this, &ftUTC);

	return (ftUTC);
}
//---------------------------------------------------------------------------
