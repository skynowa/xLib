/****************************************************************************
* Unit name:   sGetHoroscopeName
* Description: ����� �������
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
//TODO: - sGetHoroscopeName (����� �������)
/*
FAQ: ����� �������

-----------------------------------------------------
|  ����	    |  ������  |  �������� ����������	    |
-----------------------------------------------------
|  ����	    |  U+2648  |  21 �����    � 20 ������   |
|  �����	|  U+2649  |  21 ������   � 21 ���      |
|  �������� |  U+264A  |  22 ���      � 21 ����     |
|  ���	    |  U+264B  |  22 ����     � 23 ����     |
|  ���	    |  U+264�  |  24 ����     � 23 �������  |
|  ����	    |  U+264D  |  24 �������  � 23 �������� |
|  ����	    |  U+264E  |  24 �������� � 23 �������  |
|  �������� |  U+264F  |  24 �������  � 22 ������   |
|  �������  |  U+2650  |  23 ������   � 21 �������  |
|  �������  |  U+2651  |  22 �������  � 20 ������   |
|  �������  |  U+2652  |  21 ������   � 19 �������  |
|  ����	    |  U+2653  |  20 �������  � 20 �����    |
-----------------------------------------------------
*/
tString 
sGetHoroscopeName(INT iDay, INT iMonth) {
	/*DEBUG*/// cdDate
	
	tString sRes;
	INT     iCount = 0;

	xCHECK_DO(iDay >= 21 && iMonth >= 3  &&  iDay <= 20 && iMonth <= 4,  sRes = xT("����")    ; ++ iCount);
	xCHECK_DO(iDay >= 21 && iMonth >= 4  &&  iDay <= 21 && iMonth <= 5,  sRes = xT("�����")   ; ++ iCount);
	xCHECK_DO(iDay >= 22 && iMonth >= 5  &&  iDay <= 21 && iMonth <= 6,  sRes = xT("��������"); ++ iCount);
	xCHECK_DO(iDay >= 22 && iMonth >= 6  &&  iDay <= 23 && iMonth <= 7,  sRes = xT("���")     ; ++ iCount);
	xCHECK_DO(iDay >= 24 && iMonth >= 7  &&  iDay <= 23 && iMonth <= 8,  sRes = xT("���")     ; ++ iCount);
	xCHECK_DO(iDay >= 24 && iMonth >= 8  &&  iDay <= 23 && iMonth <= 9,  sRes = xT("����")    ; ++ iCount);
	xCHECK_DO(iDay >= 24 && iMonth >= 9  &&  iDay <= 23 && iMonth <= 10, sRes = xT("����")    ; ++ iCount);
	xCHECK_DO(iDay >= 24 && iMonth >= 10 &&  iDay <= 22 && iMonth <= 11, sRes = xT("��������"); ++ iCount);
	xCHECK_DO(iDay >= 23 && iMonth >= 11 &&  iDay <= 21 && iMonth <= 12, sRes = xT("�������") ; ++ iCount);
	xCHECK_DO(iDay >= 22 && iMonth >= 12 &&  iDay <= 20 && iMonth <= 1,  sRes = xT("�������") ; ++ iCount);
	xCHECK_DO(iDay >= 21 && iMonth >= 1  &&  iDay <= 19 && iMonth <= 2,  sRes = xT("�������") ; ++ iCount);
	xCHECK_DO(iDay >= 20 && iMonth >= 2  &&  iDay <= 20 && iMonth <= 3,  sRes = xT("����")    ; ++ iCount);

	/*DEBUG*/xASSERT(1 == iCount);

	return sRes;
}
//---------------------------------------------------------------------------