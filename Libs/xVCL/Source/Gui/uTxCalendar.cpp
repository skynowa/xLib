#include <vcl.h>
#include <tchar.h>
#include <assert.h>
#pragma hdrstop

#include "uTxCalendar.h"

#define Tab_101 101
#define Exceed_RC 102
#define StartAngle_RC 103
#define EndAngle_RC 104
#define EditAngle_RC 105

#pragma package(smart_init)
//---------------------------------------------------------------------------
//TODO: ValidCtrCheck is used to assure that the components created do not have  any pure virtual functions.
static inline void ValidCtrCheck(TxCalendar *) {
	new TxCalendar(NULL);
}
//---------------------------------------------------------------------------
//TODO:
namespace Utxcalendar {
	void __fastcall PACKAGE Register()  {
		TComponentClass classes[1] = {__classid(TxCalendar)};
		RegisterComponents(L"Samples", classes, 0);
	}
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: TxCalendar
/*virtual*/
__fastcall TxCalendar::TxCalendar(TComponent *AOwner) :
	TCustomGrid   (AOwner),
	_m_pslCellData(NULL)
{
	_m_pslCellData = new TStringList();
	/*DEBUG*/
	for (int i = 0; i < 32; ++ i) {
		_m_pslCellData->Add(IntToStr(clWhite));
	}

	FUseCurrentDate = true;
	FixedCols       = 0;
	FixedRows       = 1;
	ColCount        = 7;
	RowCount        = 7;
	StartOfWeek     = 1;
	ScrollBars      = ssNone;
	FDate           = Date();
	(Options >> goRangeSelect) << goDrawFocusSelected;
	UpdateCalendar();
}
//---------------------------------------------------------------------------
//TODO: TxCalendar
/*virtual*/
 __fastcall TxCalendar::~TxCalendar() {
	delete _m_pslCellData;
}
//---------------------------------------------------------------------------
//TODO: NextMonth
void __fastcall TxCalendar::NextMonth() {
    ChangeMonth(1);
}
//---------------------------------------------------------------------------
//TODO: PrevMonth
void __fastcall TxCalendar::PrevMonth() {
    ChangeMonth(-1);
}
//---------------------------------------------------------------------------
//TODO: NextYear
void __fastcall TxCalendar::NextYear() {
	if (IsLeapYear(Year) && (Month == 2) && (Day == 29)) {
		Day = 28;
	}

	++ Year;
}
//---------------------------------------------------------------------------
//TODO: PrevYear
void __fastcall TxCalendar::PrevYear() {
	if (IsLeapYear(Year) && (Month == 2) && (Day == 29)) {
		Day = 28;
	}

	-- Year;
}
//---------------------------------------------------------------------------
//TODO: DaysPerMonth
int __fastcall TxCalendar::DaysPerMonth(int AYear, int AMonth) {
    int       iRes;
    const int DaysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    iRes = DaysInMonth[AMonth - 1];
	if ((AMonth == 2) && IsLeapYear(AYear)) {
		++ iRes; // leap-year Feb is special
	}

    return iRes;
}
//---------------------------------------------------------------------------
//TODO: DaysPerCurrMonth
int __fastcall TxCalendar::DaysPerCurrMonth() {
    int    iRes    = 0;
	USHORT usYear  = 0;
	USHORT usMonth = 0;
	USHORT usDay   = 0;

	CalendarDate.DecodeDate(&usYear, &usMonth, &usDay);

	iRes = DaysPerMonth(usYear, usMonth);

	//ShowMessage(iRes);

    return iRes;
}
//---------------------------------------------------------------------------
//TODO: UpdateCalendar
void __fastcall TxCalendar::UpdateCalendar() {
	USHORT    AYear   = 0;
	USHORT    AMonth  = 0;
	USHORT    ADay    = 0;
	TDateTime FirstDate;

	FUpdating = true;
	DecodeDate(FDate, AYear, AMonth, ADay);
	FirstDate = EncodeDate(AYear, AMonth, 1);

	// Day of week for 1st of month.
	FMonthOffset = 2 - ((DayOfWeek(FirstDate) - StartOfWeek + 7) % 7);
	if (FMonthOffset == 2) {
		FMonthOffset = - 5;
	}

    MoveColRow((ADay - FMonthOffset) % 7, (ADay - FMonthOffset) / 7 + 1, false, false);
    Invalidate();

    FUpdating = false;
}
//---------------------------------------------------------------------------
//TODO:	bIsCurrCalendarDate
bool __fastcall TxCalendar::bIsCurrCalendarDate(TDate dtBegin) {
    //число текущего года, месяца
	USHORT usCalendarYear  = 0;
	USHORT usCalendarMonth = 0;
	USHORT usCalendarDay   = 0;
	CalendarDate.DecodeDate(&usCalendarYear, &usCalendarMonth, &usCalendarDay);

	//число года, месяца начала выделения
	USHORT usBeginYear  = 0;
	USHORT usBeginMonth = 0;
	USHORT usBeginDay   = 0;
	dtBegin.DecodeDate(&usBeginYear, &usBeginMonth, &usBeginDay);

	//если не текущий год, месяц - выход
	if (usCalendarYear != usBeginYear || usCalendarMonth != usBeginMonth) {
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
//TODO: bSelectRange
bool __fastcall TxCalendar::bSelectRange(TDate dtBegin, int iSize, TColor clColor, int *piRemainDays) {
	/*DEBUG*/

	////_m_dtBegin = dtBegin;

	//число года, месяца начала выделения
	USHORT usBeginYear  = 0;
	USHORT usBeginMonth = 0;
	USHORT usBeginDay   = 0;
	dtBegin.DecodeDate(&usBeginYear, &usBeginMonth, &usBeginDay);

	//-------------------------------------
	//пометка выделения диапазона дней
	if (NULL != piRemainDays) { (* piRemainDays) = 0;}
	for (int i = usBeginDay; i < usBeginDay + iSize; ++ i) {
		if (i > DaysPerMonth(usBeginYear, usBeginMonth)) {
			if (NULL != piRemainDays) {++ (* piRemainDays);}
			continue;
		}

		/*DEBUG*/assert(i > 0 && i < 32);
		_m_pslCellData->Strings[i] = IntToStr(clColor);
    }
	UpdateCalendar();

	return true;
}
//---------------------------------------------------------------------------
//TODO: bClearSelection
bool __fastcall TxCalendar::bClearSelection() {
	for (int i = 0; i < _m_pslCellData->Count; ++ i) {
		/*DEBUG*/assert(i >= 0 && i < 32);
		_m_pslCellData->Strings[i] = IntToStr(clWhite);
	}
	UpdateCalendar();

	return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	protected
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: Change
void __fastcall TxCalendar::Change() {
	if (FOnChange) {
		FOnChange(this);
	}
}
//---------------------------------------------------------------------------
//TODO: ChangeMonth (Given a value of 1 or -1, moves to Next or Prev month accordingly)
void __fastcall TxCalendar::ChangeMonth(int Delta) {
	USHORT    AYear   = 0;
	USHORT    AMonth  = 0;
	USHORT    ADay    = 0;
	TDateTime NewDate;
	int       iCurDay = 0;

	DecodeDate(FDate, AYear, AMonth, ADay);
	iCurDay = ADay;

	if (Delta > 0) {
		ADay = DaysPerMonth(AYear, AMonth);
	} else {
		ADay = 1;
	}

	NewDate = EncodeDate(AYear, AMonth, ADay);
	NewDate = NewDate + Delta;
	DecodeDate(NewDate, AYear, AMonth, ADay);

	if (DaysPerMonth(AYear, AMonth) > iCurDay) {
		ADay = iCurDay;
	} else {
		ADay = DaysPerMonth(AYear, AMonth);
	}

	CalendarDate = EncodeDate(AYear, AMonth, ADay);
}
//---------------------------------------------------------------------------
//TODO: Click
void __fastcall TxCalendar::Click() {
	System::String sCellText;

	sCellText = CellText[Col][Row];
	if (false == sCellText.IsEmpty()) {
		Day = sCellText.ToInt();
	}
}
//---------------------------------------------------------------------------
//TODO: DaysThisMonth
int __fastcall TxCalendar::DaysThisMonth() {
    return DaysPerMonth(Year, Month);
}
//---------------------------------------------------------------------------
//TODO: DrawCell
void __fastcall TxCalendar::DrawCell(int ACol, int ARow, const TRect &ARect, TGridDrawState /*AState*/) {
	const System::String sCellText = CellText[ACol][ARow];

	if (0 != ARow && false == sCellText.IsEmpty()) {
		//непустые ячейки
		USHORT iCalendarYear  = 0;
		USHORT iCalendarMonth = 0;
		USHORT iCalendarDay   = 0;
		DecodeDate(CalendarDate, iCalendarYear, iCalendarMonth, iCalendarDay);

		USHORT iNowYear   = 0;
		USHORT iNowMonth  = 0;
		USHORT iNowDay    = 0;
		DecodeDate(Now(), iNowYear, iNowMonth, iNowDay);

		if (iCalendarYear == iNowYear && iCalendarMonth == iNowMonth && sCellText == IntToStr(iNowDay)) {
			//выделение текущего дня
			Canvas->Brush->Color = clBlue;
			Canvas->Font->Color  = clYellow;
			Canvas->Font->Style  = TFontStyles() << fsBold;
		} else {
		    //непустые ячейки
			Canvas->Brush->Color = StrToInt(_m_pslCellData->Strings[ StrToInt(sCellText) ]);
			Canvas->Font->Color  = clBlack;
			Canvas->Font->Style  = TFontStyles() << fsBold;
		}
	} else {
		//пустые ячейки
		Canvas->Brush->Color = clBtnFace;
		Canvas->Font->Color  = clBlack;
		Canvas->Font->Style  = TFontStyles() >> fsBold;
	}

	//отрисовка ячейки
	Canvas->TextRect(
		ARect,
		ARect.Left + (ARect.Right  - ARect.Left - Canvas->TextWidth(sCellText))  / 2,
		ARect.Top  + (ARect.Bottom - ARect.Top  - Canvas->TextHeight(sCellText)) / 2,
		sCellText
	);
}
//---------------------------------------------------------------------------
//TODO: IsLeapYear (Don't have any leap year code available.  Seemed like a straigthforward translation, but should be checked)
bool __fastcall TxCalendar::IsLeapYear(int AYear) {
	return ((AYear %   4)  == 0) && (((AYear % 100) != 0) || ((AYear % 400)  == 0));
}
//---------------------------------------------------------------------------
//TODO: SelectCell
bool __fastcall TxCalendar::SelectCell(int ACol, int ARow) {
	bool bRes = false;

	if ((!FUpdating && FReadOnly) || !CellText[ACol][ARow].c_str()) {
		bRes = false;
	} else {
		bRes = TCustomGrid::SelectCell(ACol, ARow);
	}

	return bRes;
}
//---------------------------------------------------------------------------
//TODO: WMSize
void __fastcall TxCalendar::WMSize(TWMSize &Message) {
	int GridLines = 0;

	GridLines        = 6 * GridLineWidth;
	DefaultColWidth  = (Message.Width  - GridLines) / 7;
	DefaultRowHeight = (Message.Height - GridLines) / 7;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	private
*
*****************************************************************************/


//---------------------------------------------------------------------------
//TODO: GetCellText
System::String __fastcall TxCalendar::GetCellText(int ACol, int ARow) {
	int            DayNum = 0;
	System::String sRes;

	if (!ARow) {
		//day names at tops of columns
		sRes = ShortDayNames[(StartOfWeek + ACol) % 7];
	} else {
		DayNum = FMonthOffset + ACol + (ARow - 1) * 7;
		if ((DayNum < 1) || (DayNum > DaysThisMonth())) {
			sRes = _T("");
		} else {
			sRes = IntToStr(DayNum);
		}
	}

	return sRes;
}
//---------------------------------------------------------------------------
//TODO: GetDateElement
int __fastcall TxCalendar::GetDateElement(int iIndex) {
	USHORT AYear  = 0;
	USHORT AMonth = 0;
	USHORT ADay   = 0;
	int    iRes   = - 1;

	DecodeDate(FDate, AYear, AMonth, ADay);

	switch(iIndex) {
		case 1:      iRes = AYear;		break;
		case 2:      iRes = AMonth;		break;
		case 3:      iRes = ADay;		break;

		default:     iRes = -1;			break;
	}

	return iRes;
}
//---------------------------------------------------------------------------
//TODO: SetCalendarDate
void __fastcall TxCalendar::SetCalendarDate(TDateTime Value) {
	FDate = Value;
	UpdateCalendar();
	Change();
}
//---------------------------------------------------------------------------
//TODO: SetDateElement
void __fastcall TxCalendar::SetDateElement(int Index, int Value) {
	USHORT AYear   = 0;
	USHORT AMonth  = 0;
	USHORT ADay    = 0;
	bool   bUpdate = false;

	if (Value > 0) {
		DecodeDate(FDate, AYear, AMonth, ADay);

		switch(Index) {
			case 1:
				if (AYear != Value) {
				    AYear   = Value;
				    bUpdate = true;
				}
				break;

			case 2:
				if ((Value <= 12) && (Value != AMonth)) {
				    AMonth  = Value;
				    bUpdate = true;
				}
				break;

			case 3:
				if ((Value <= DaysThisMonth()) && (Value != ADay)) {
				    ADay    = Value;
				    bUpdate = true;
				}
				break;
		}
		if (true == bUpdate) {
			FDate = EncodeDate(AYear, AMonth, ADay);
			FUseCurrentDate = false;
			UpdateCalendar();
			Change();
		}
	}
}
//---------------------------------------------------------------------------
//TODO: SetStartOfWeek
void __fastcall TxCalendar::SetStartOfWeek(TDayOfWeek Value) {
	if( (Value > 7) || (Value < 1) ) {
		FStartOfWeek = 1; // bad value sets to 1 (Sunday)
	} else {
		if (Value != FStartOfWeek) {
			FStartOfWeek = Value;
			UpdateCalendar();
		}
	}
}
//---------------------------------------------------------------------------
//TODO: SetUseCurrentDate
void __fastcall TxCalendar::SetUseCurrentDate(bool bValue) {
	if (bValue != FUseCurrentDate) {
		FUseCurrentDate = bValue;
		if (bValue) {
		    FDate = Date(); // use the current date, then
		    UpdateCalendar();
		}
	}
}
//---------------------------------------------------------------------------
//TODO: StoreCalendarDate
bool __fastcall TxCalendar::StoreCalendarDate() {
    return !FUseCurrentDate;
}
//---------------------------------------------------------------------------













//if (true == ComponentState.Contains(csDesigning)) {
