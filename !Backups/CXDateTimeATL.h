/****************************************************************************
* Class name:  CXDateTimeATL
* Description: работа с датами (ATL)
* File name:   CXDateTimeATL.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     16.06.2009 16:51:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CXDateTimeH_
#define CXDateTimeH_
//---------------------------------------------------------------------------
#include <windows.h> 
#include <time.h> 
//---------------------------------------------------------------------------
class CTimeSpan {
	public:
				   CTimeSpan      () throw();
				   CTimeSpan      (__time64_t time) throw();
				   CTimeSpan      (LONG lDays, INT nHours, INT nMins, INT nSecs) throw();

		LONGLONG   GetDays        ()const throw();
		LONGLONG   GetTotalHours  ()const throw();
		LONG       GetHours       ()const throw();
		LONGLONG   GetTotalMinutes()const throw();
		LONG       GetMinutes     ()const throw();
		LONGLONG   GetTotalSeconds()const throw();
		LONG       GetSeconds     ()const throw();
		__time64_t GetTimeSpan    ()const throw();

		CTimeSpan  operator +     (CTimeSpan span) const throw();
		CTimeSpan  operator -     (CTimeSpan span) const throw();
		CTimeSpan &operator +=    (CTimeSpan span) throw();
		CTimeSpan &operator -=    (CTimeSpan span) throw();
		BOOL       operator ==    (CTimeSpan span) const throw();
		BOOL       operator !=    (CTimeSpan span) const throw();
		BOOL       operator <     (CTimeSpan span) const throw();
		BOOL       operator >     (CTimeSpan span) const throw();
		BOOL       operator <=    (CTimeSpan span) const throw();
		BOOL       operator >=    (CTimeSpan span) const throw();

	public:
		////CString Format(LPCTSTR pszFormat) const;
		////CString Format(UINT nID) const;
	private:
		__time64_t m_timeSpan;
};
//---------------------------------------------------------------------------
class CTime {
	public:
				   CTime          () throw();
				   CTime          (__time64_t time) throw();
				   CTime          (INT nYear, INT nMonth, INT nDay, INT nHour, INT nMin, INT nSec, INT nDST = - 1);
				   CTime          (WORD wDosDate, WORD wDosTime, INT nDST =  - 1);
				   CTime          (const SYSTEMTIME &st, INT nDST =  - 1);
				   CTime          (const FILETIME &ft, INT nDST =  - 1);
		
	    struct tm *GetGmtTm       (struct tm *ptm) const;
		struct tm *GetLocalTm     (struct tm *ptm) const;
		BOOL       GetAsSystemTime(SYSTEMTIME &st) const throw();
		__time64_t GetTime        () const throw();
		INT        GetYear        () const throw();
		INT        GetMonth       () const throw();
		INT        GetDay         () const throw();
		INT        GetHour        () const throw();
		INT        GetMinute      () const throw();
		INT        GetSecond      () const throw();
		INT        GetDayOfWeek   () const throw();

		CTime     &operator =     (__time64_t time) throw();
		CTime     &operator +=    (CTimeSpan span) throw();
		CTime     &operator -=    (CTimeSpan span) throw();
		CTimeSpan  operator -     (CTime time) const throw();
		CTime      operator -     (CTimeSpan span) const throw();
		CTime      operator +     (CTimeSpan span) const throw();
		BOOL       operator ==    (CTime time) const throw();
		BOOL       operator !=    (CTime time) const throw();
		BOOL       operator <     (CTime time) const throw();
		BOOL       operator >     (CTime time) const throw();
		BOOL       operator <=    (CTime time) const throw();
		BOOL       operator >=    (CTime time) const throw();

		static CTime WINAPI GetCurrentTime()throw();
		static BOOL  WINAPI IsValidFILETIME(const FILETIME &ft)throw();
		// formatting using "C" strftime
		//////CString Format(LPCTSTR pszFormat) const;
		//////CString FormatGmt(LPCTSTR pszFormat) const;
		//////CString Format(UINT nFormatID) const;
		//////CString FormatGmt(UINT nFormatID) const;
	private:
		__time64_t m_time;
};
//---------------------------------------------------------------------------
class CFileTimeSpan {
	public:
					   CFileTimeSpan() throw();
					   CFileTimeSpan(const CFileTimeSpan &span) throw();
					   CFileTimeSpan(LONGLONG nSpan) throw();
		LONGLONG       GetTimeSpan  () const throw();
		VOID           SetTimeSpan  (LONGLONG nSpan) throw();

		CFileTimeSpan &operator =   (const CFileTimeSpan &span) throw();
		CFileTimeSpan &operator +=  (CFileTimeSpan span) throw();
		CFileTimeSpan &operator -=  (CFileTimeSpan span) throw();
		CFileTimeSpan  operator +   (CFileTimeSpan span) const throw();
		CFileTimeSpan  operator -   (CFileTimeSpan span) const throw();
		BOOL           operator ==  (CFileTimeSpan span) const throw();
		BOOL           operator !=  (CFileTimeSpan span) const throw();
		BOOL           operator <   (CFileTimeSpan span) const throw();
		BOOL           operator >   (CFileTimeSpan span) const throw();
		BOOL           operator <=  (CFileTimeSpan span) const throw();
		BOOL           operator >=  (CFileTimeSpan span) const throw();

	protected:
		LONGLONG       m_nSpan;
};
//---------------------------------------------------------------------------
class CFileTime: public FILETIME {
	public:
		static const ULONGLONG  Millisecond = 10000;
		static const ULONGLONG  Second      = Millisecond * static_cast<ULONGLONG> (1000);
		static const ULONGLONG  Minute      = Second      * static_cast<ULONGLONG> (60);
		static const ULONGLONG  Hour        = Minute      * static_cast<ULONGLONG> (60);
		static const ULONGLONG  Day         = Hour        * static_cast<ULONGLONG> (24);
		static const ULONGLONG  Week        = Day         * static_cast<ULONGLONG> (7);

								CFileTime     () throw();
								CFileTime     (const FILETIME &ft) throw();
								CFileTime     (ULONGLONG nTime) throw();

		ULONGLONG               GetTime       () const throw();
		VOID                    SetTime       (ULONGLONG nTime) throw();
		CFileTime               UTCToLocal    () const throw();
		CFileTime               LocalToUTC    () const throw();
		static CFileTime WINAPI GetCurrentTime() throw();

		CFileTime              &operator =    (const FILETIME &ft) throw();
		CFileTime              &operator +=   (CFileTimeSpan span) throw();
		CFileTime              &operator -=   (CFileTimeSpan span) throw();
		CFileTime               operator +    (CFileTimeSpan span) const throw();
		CFileTime               operator -    (CFileTimeSpan span) const throw();
		CFileTimeSpan           operator -    (CFileTime ft) const throw();
		BOOL                    operator ==   (CFileTime ft) const throw();
		BOOL                    operator !=   (CFileTime ft) const throw();
		BOOL                    operator <    (CFileTime ft) const throw();
		BOOL                    operator >    (CFileTime ft) const throw();
		BOOL                    operator <=   (CFileTime ft) const throw();
		BOOL                    operator >=   (CFileTime ft) const throw();
};
//---------------------------------------------------------------------------
// Used only if these strings could not be found in resources.
//////extern __declspec(selectany) const TCHAR * const szInvalidDateTime = _T("Invalid DateTime");
//////extern __declspec(selectany) const TCHAR * const szInvalidDateTimeSpan = _T("Invalid DateTimeSpan");
//---------------------------------------------------------------------------
#endif


/*
	CTime t1=CTime::GetCurrentTime(),t2;

	// задаем t2 - конечное время

	CTimeSpan sp=t2-t1;
	// теперь в sp хранится разница во времени, 
	// которую можно получить с помощью GetDays(), 
	// GetHours(), GetMinutes() и т.д. или записать в строку 
	// с пом. Format(...); ( см. MSDN )
*/