/****************************************************************************
* Class name:  CXDateTime
* Description: работа с датами
* File name:   CXDateTime.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     12.06.2009 15:37:34
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <XLib/CXDateTime.h>

#include <ctime>
#include <XLib/CXString.h>
#include <XLib/xassert.h>
//---------------------------------------------------------------------------
CXDateTime::CXDateTime() : //++
	m_ullDateTime(0)
{
	::ZeroMemory(&m_stDateTime, sizeof(SYSTEMTIME));
}
//---------------------------------------------------------------------------
CXDateTime::CXDateTime(ULONGLONG ullDateTime) : //++
	m_ullDateTime(ullDateTime)
{
	bMSecToDateTime(m_ullDateTime, /*ref*/m_stDateTime);
}
//---------------------------------------------------------------------------
////////CXDateTime::CXDateTime(USHORT usYear, USHORT usMonth, USHORT usDay, USHORT usHour, USHORT usMinute, USHORT usSecond, USHORT usMilliseconds) : //++
////////	m_ullDateTime(0)
////////{
////////	::ZeroMemory(&m_stDateTime, sizeof(SYSTEMTIME));
////////	
////////	/*DEBUG*/XASSERT(usYear         >= 0);
////////	/*DEBUG*/XASSERT(usMonth        >= 1 && usMonth        <= 31);
////////	/*DEBUG*/XASSERT(usDay          >= 1 && usDay          <= 365);
////////	/*DEBUG*/XASSERT(usHour         >= 0 && usHour         <= 23);
////////	/*DEBUG*/XASSERT(usMinute       >= 0 && usMinute       <= 59);
////////	/*DEBUG*/XASSERT(usSecond       >= 0 && usSecond       <= 59);
////////	/*DEBUG*/XASSERT(usMilliseconds >= 0 && usMilliseconds <= 999);
////////
////////	m_stDateTime.wYear         = usYear;
////////	m_stDateTime.wMonth        = usMonth;
////////	m_stDateTime.wDayOfWeek    = 0; 
////////	m_stDateTime.wDay          = usDay;
////////	m_stDateTime.wHour         = usHour;
////////	m_stDateTime.wMinute       = usMinute;
////////	m_stDateTime.wSecond       = usSecond;
////////	m_stDateTime.wMilliseconds = usMilliseconds;	
////////
////////	//-------------------------------------
////////	//ULL
////////	m_ullDateTime = ullDateTimeToMSec(m_stDateTime);
////////}
//---------------------------------------------------------------------------
CXDateTime::~CXDateTime() { //++
	//code
}
//---------------------------------------------------------------------------
CXDateTime CXDateTime::dtNow() { //++
	::GetLocalTime(&m_stDateTime);
	/*DEBUG*///not need

	m_ullDateTime = ullDateTimeToMSec(m_stDateTime);

///*	return CXDateTime(m_stDateTime.wYear, m_stDateTime.wMonth,  m_stDateTime.wDay,
//		m_stDateTime.wHour, m_stDateTime.wMinute, m_stDateTime.wSecond, m_stDateTime.wMilliseconds);*/	 
	return CXDateTime(m_ullDateTime);
}
//---------------------------------------------------------------------------
std::string CXDateTime::sFormatToStr() {
	return sFormatStr("%d-%.2d-%.2d %d:%.2d:%.2d:%.3d", 
						m_stDateTime.wYear, m_stDateTime.wMonth,  m_stDateTime.wDay,
						m_stDateTime.wHour, m_stDateTime.wMinute, m_stDateTime.wSecond, m_stDateTime.wMilliseconds);
}
//--------------------------------------------------------------------------


/****************************************************************************
*	Private	
*
*****************************************************************************/

//--------------------------------------------------------------------------
/*static*/BOOL CXDateTime::bMSecToDateTime(ULONGLONG ullMilliSec, SYSTEMTIME &stST) { 
	BOOL bRes = FALSE;

	stST.wYear = (USHORT)(ullMilliSec / ((1000ULL*60*60*24*30) * 12));
	ullMilliSec %= ((1000ULL*60*60*24*30) * 12);

	stST.wMonth = (USHORT)(ullMilliSec / ((1000ULL*60*60*24) * 30));
	ullMilliSec %= ((1000ULL*60*60*24) * 30);

	stST.wDay = (USHORT)(ullMilliSec / ((1000*60*60) * 24));
	ullMilliSec %= ((1000ULL*60*60) * 24);

	stST.wHour = (USHORT)(ullMilliSec / ((1000*60) * 60));
	ullMilliSec %= ((1000*60) * 60);

	stST.wMinute = (USHORT)(ullMilliSec / ((1000*60)));
	ullMilliSec %= ((1000*60));

	stST.wSecond = (USHORT)(ullMilliSec / 1000);
	ullMilliSec %= 1000;

	stST.wMilliseconds = (USHORT)(ullMilliSec);

	return TRUE;
}
//--------------------------------------------------------------------------
/*static*/ULONGLONG CXDateTime::ullDateTimeToMSec(const SYSTEMTIME &stST) { 
	ULONGLONG ullRes = 0ULL;

	ullRes += stST.wYear         * 1000ULL * 60 * 60 * 24 * 30 * 12;
	ullRes += stST.wMonth        * 1000ULL * 60 * 60 * 24 * 30;
	ullRes += stST.wDay          * 1000ULL * 60 * 60 * 24;
	ullRes += stST.wHour         * 1000 * 60 * 60; 
	ullRes += stST.wMinute       * 1000 * 60;
	ullRes += stST.wSecond       * 1000 * 1;
	ullRes += stST.wMilliseconds * 1;

	return ullRes;
}
//--------------------------------------------------------------------------


/****************************************************************************
*	Operators	
*
*****************************************************************************/

//--------------------------------------------------------------------------
CXDateTime &CXDateTime::operator = (CXDateTime dtDT) { //++
	bMSecToDateTime(dtDT.m_ullDateTime, m_stDateTime);
	m_ullDateTime = dtDT.m_ullDateTime;

	return (*this);
}
//--------------------------------------------------------------------------
CXDateTime CXDateTime::operator + (CXDateTime dtDT) {  //++
	bMSecToDateTime(m_ullDateTime + dtDT.m_ullDateTime, m_stDateTime);

	return (CXDateTime(m_ullDateTime + dtDT.m_ullDateTime));
}
//--------------------------------------------------------------------------
CXDateTime CXDateTime::operator - (CXDateTime dtDT) {  //++
	bMSecToDateTime(m_ullDateTime - dtDT.m_ullDateTime, m_stDateTime);

	return (CXDateTime(m_ullDateTime - dtDT.m_ullDateTime));
}
//--------------------------------------------------------------------------