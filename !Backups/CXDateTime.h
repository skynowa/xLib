/****************************************************************************
* Class name:  CXDateTime
* Description: работа с датами
* File name:   CXDateTime.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     12.06.2009 15:37:34
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CXDateTimeH
#define CXDateTimeH
//---------------------------------------------------------------------------
#include <XLib/CXCommon.h>
//---------------------------------------------------------------------------
class CXDateTime {
	public:
				           CXDateTime       (); /*+*/
				           CXDateTime       (ULONGLONG ullDateTime); /*+*/
				           ////CXDateTime       (USHORT usYear, USHORT usMonth, USHORT usDay, USHORT usHour, USHORT usMinute, USHORT usSecond, USHORT usMilliseconds); /*+*/
				          ~CXDateTime       (); /*+*/
				          
	    CXDateTime         dtNow            (); /*+*/
    	std::string        sFormatToStr     (); /*+*/


		//-------------------------------------
		//операторы
		CXDateTime         &operator =      (CXDateTime dtDT);
		CXDateTime         operator  +      (CXDateTime dtDT);
		CXDateTime         operator  -      (CXDateTime dtDT);

   	private:
   		SYSTEMTIME         m_stDateTime;
		ULONGLONG          m_ullDateTime;

		static BOOL        bMSecToDateTime  (ULONGLONG ullMilliSec, SYSTEMTIME &stST); /*+*/
		static ULONGLONG   ullDateTimeToMSec(const SYSTEMTIME &stST); /*+*/
};
//---------------------------------------------------------------------------
#endif







//GetTimeFormatEx
//GetDateFormat