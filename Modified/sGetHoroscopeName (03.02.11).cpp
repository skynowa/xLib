/****************************************************************************
* Unit name:   sGetHoroscopeName
* Description: знаки зодиака
* File name:   sGetHoroscopeName.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     06.11.2009 11:50:17
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <XLib/Common.h>


//--------------------------------------------------------------------------- 
//TODO: - sGetHoroscopeName (знаки зодиака)
/*
FAQ: знаки зодиака

-----------------------------------------------------
|  Знак	    |  Символ  |  Западная астрология	    |
-----------------------------------------------------
|  Овен	    |  U+2648  |  21 марта    — 20 апреля   |
|  Телец	|  U+2649  |  21 апреля   — 21 мая      |
|  Близнецы |  U+264A  |  22 мая      — 21 июня     |
|  Рак	    |  U+264B  |  22 июня     — 23 июля     |
|  Лев	    |  U+264С  |  24 июля     — 23 августа  |
|  Дева	    |  U+264D  |  24 августа  — 23 сентября |
|  Весы	    |  U+264E  |  24 сентября — 23 октября  |
|  Скорпион |  U+264F  |  24 октября  — 22 ноября   |
|  Стрелец  |  U+2650  |  23 ноября   — 21 декабря  |
|  Козерог  |  U+2651  |  22 декабря  — 20 января   |
|  Водолей  |  U+2652  |  21 января   — 19 февраля  |
|  Рыбы	    |  U+2653  |  20 февраля  — 20 марта    |
-----------------------------------------------------
*/
tString 
sGetHoroscopeName(INT iDay, INT iMonth) {
	/*DEBUG*/// cdDate
	
	tString sRes;
	INT     iCount = 0;

	xCHECK_DO(iDay >= 21 && iMonth >= 3  &&  iDay <= 20 && iMonth <= 4,  sRes = xT("Овен")    ; ++ iCount);
	xCHECK_DO(iDay >= 21 && iMonth >= 4  &&  iDay <= 21 && iMonth <= 5,  sRes = xT("Телец")   ; ++ iCount);
	xCHECK_DO(iDay >= 22 && iMonth >= 5  &&  iDay <= 21 && iMonth <= 6,  sRes = xT("Близнецы"); ++ iCount);
	xCHECK_DO(iDay >= 22 && iMonth >= 6  &&  iDay <= 23 && iMonth <= 7,  sRes = xT("Рак")     ; ++ iCount);
	xCHECK_DO(iDay >= 24 && iMonth >= 7  &&  iDay <= 23 && iMonth <= 8,  sRes = xT("Лев")     ; ++ iCount);
	xCHECK_DO(iDay >= 24 && iMonth >= 8  &&  iDay <= 23 && iMonth <= 9,  sRes = xT("Дева")    ; ++ iCount);
	xCHECK_DO(iDay >= 24 && iMonth >= 9  &&  iDay <= 23 && iMonth <= 10, sRes = xT("Весы")    ; ++ iCount);
	xCHECK_DO(iDay >= 24 && iMonth >= 10 &&  iDay <= 22 && iMonth <= 11, sRes = xT("Скорпион"); ++ iCount);
	xCHECK_DO(iDay >= 23 && iMonth >= 11 &&  iDay <= 21 && iMonth <= 12, sRes = xT("Стрелец") ; ++ iCount);
	xCHECK_DO(iDay >= 22 && iMonth >= 12 &&  iDay <= 20 && iMonth <= 1,  sRes = xT("Козерог") ; ++ iCount);
	xCHECK_DO(iDay >= 21 && iMonth >= 1  &&  iDay <= 19 && iMonth <= 2,  sRes = xT("Водолей") ; ++ iCount);
	xCHECK_DO(iDay >= 20 && iMonth >= 2  &&  iDay <= 20 && iMonth <= 3,  sRes = xT("Рыбы")    ; ++ iCount);

	/*DEBUG*/xASSERT(1 == iCount);

	return sRes;
}
//---------------------------------------------------------------------------