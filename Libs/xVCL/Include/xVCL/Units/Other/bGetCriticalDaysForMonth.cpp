/****************************************************************************
*	bGetCriticalDaysForMonth.cpp - вывод критических дней по месяцам
*
*****************************************************************************/


#include <xVCL\Gui\uTxCalendar.h>

//---------------------------------------------------------------------------
//TODO: bGetCriticalDaysForMonth
BOOL bGetCriticalDaysForMonth(TxCalendar *pxcalCal, TDate dtCriticalDaysBegin, INT iLength, INT iCycleLength) {
	/*DEBUG*/xASSERT_RET(NULL   != pxcalCal,     FALSE);
	/*DEBUG*/// dtCriticalDaysBegin - n/a
	/*DEBUG*/xASSERT_RET(0       < iLength,      FALSE);
	/*DEBUG*/xASSERT_RET(0       < iCycleLength, FALSE);
	/*DEBUG*/// iLength < iCycleLength - n/a

	//-------------------------------------
	//
	pxcalCal->bClearSelection();

	xCHECK_RET(iLength >= iCycleLength, TRUE);	//обработка ошибок ввода

	USHORT iForYear  = 0;
	USHORT iForMonth = 0;
	USHORT usForDay  = 0;
	pxcalCal->CalendarDate.DecodeDate(&iForYear, &iForMonth, &usForDay);

	std::auto_ptr<TStringList> apSL(new TStringList());
    /*DEBUG*/xASSERT_RET(NULL != apSL.get(), FALSE);

	//-------------------------------------
	//расчет критич. дней
	{
		//дата последнего числа искомого месяца
		TDate dtFor   = EncodeDate(iForYear, iForMonth, pxcalCal->DaysPerMonth(iForYear, iForMonth));
		TDate dtBegin = dtCriticalDaysBegin;

		apSL->Clear();
		
		//-------------------------------------
		//вариант 1 - вычисление всех критич. периодов до даты iForYear/iForMonth включительно (низкая скорость)
		//for (;;) {
		//	if (dtBegin > dtFor) {
		//		apSL->Add(dtBegin.DateString());
		//		break;
		//	}
		//
		//	apSL->Add(dtBegin.DateString());
		//	dtBegin += iCycleLength;
		//}
		////ShowMessage(apSL->Text);
		//
		////фильтр нужного месяца
		//xCalendar1->bClearSelection();
		//for (int i = 0; i < apSL->Count; ++ i) {
		//	USHORT usYear;
		//	USHORT usMonth;
		//	USHORT usDay;
		//	TDate(apSL->Strings[i]).DecodeDate(&usYear, &usMonth, &usDay);
		//
		//	if (usYear != iForYear || usMonth != iForMonth) {
		//		apSL->Delete(i); -- i;
		//	}
		//}

		//-------------------------------------
		//вариант 2 (улучшено быстродействие)
		for (;;) {
			USHORT usYear;
			USHORT usMonth;
			USHORT usDay;
			dtBegin.DecodeDate(&usYear, &usMonth, &usDay);

			if (dtBegin > dtFor) {
				if (usYear == iForYear && usMonth == iForMonth) {
					apSL->Add(dtBegin.DateString());
				}
				break;
			}

			if (usYear == iForYear && usMonth == iForMonth) {
				apSL->Add(dtBegin.DateString());
			}
			
			dtBegin += iCycleLength;
		}

		//-------------------------------------
		//дополнение с прошлого месяца
		if (0 != apSL->Count) {
			USHORT iYear  = 0;
			USHORT iMonth = 0;
			USHORT usDay  = 0;
			TDate(apSL->Strings[0]).DecodeDate(&iYear, &iMonth, &usDay);

			INT iDelta = usDay - 1 - iCycleLength + iLength;		//ShowMessage(iDelta);

			pxcalCal->bSelectRange(TDate(iYear, iMonth, 1), iDelta, clRed, NULL);
			
		}
	}	//ShowMessage(apSL->Text);

	//-------------------------------------
	//выделение критич. дней
	for (INT i = 0; i < apSL->Count; ++ i) {
		pxcalCal->bSelectRange(TDate(apSL->Strings[i]), iLength, clRed, NULL);
		
		//ShowMessage(g_iRemainDays);
	}

	return TRUE;
}
//---------------------------------------------------------------------------