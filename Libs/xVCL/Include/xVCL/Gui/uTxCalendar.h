#ifndef uTxCalendarH
#define uTxCalendarH
//---------------------------------------------------------------------------
#include <Menus.hpp>
#include <SysUtils.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include <Graphics.hpp>
#include <Forms.hpp>
#include <Windows.hpp>
#include <Messages.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <System.hpp>
//---------------------------------------------------------------------------
class PACKAGE TxCalendar : public TCustomGrid {
	public:
		typedef short TDayOfWeek;

		__fastcall virtual        TxCalendar       (TComponent *AOwner);
	    __fastcall virtual       ~TxCalendar       ();
		
		void           __fastcall NextMonth        ();
		void           __fastcall PrevMonth        ();
		void           __fastcall NextYear         ();
		void           __fastcall PrevYear         ();
		virtual int    __fastcall DaysPerMonth     (int AYear, int AMonth);
        int            __fastcall DaysPerCurrMonth ();
		virtual void   __fastcall UpdateCalendar   ();

		bool          __fastcall  bSelectRange     (TDate dtBegin, int iSize, TColor clColor, int *piRemainDays);
	    bool          __fastcall  bClearSelection  ();

		__property TDateTime      CalendarDate                 = {read = FDate, write = SetCalendarDate, stored = StoreCalendarDate};
		__property System::String CellText[int ACol][int ARow] = {read = GetCellText};
 

		////TDate                     _m_dtBegin;
	protected:
		virtual void   __fastcall Change           ();
		void           __fastcall ChangeMonth      (int Delta);
		DYNAMIC void   __fastcall Click            ();
		virtual int    __fastcall DaysThisMonth    ();
		virtual void   __fastcall DrawCell         (int ACol, int ARow, const TRect &ARect, TGridDrawState AState);
		virtual bool   __fastcall IsLeapYear       (int AYear);
		virtual bool   __fastcall SelectCell       (int ACol, int ARow);
		void           __fastcall WMSize           (TWMSize& Message);

	private:
		TDateTime                 FDate;
		int                   	  FMonthOffset;
		TNotifyEvent              FOnChange;
		Boolean                   FReadOnly;
		TDayOfWeek                FStartOfWeek;
		Boolean                   FUpdating;
		Boolean                   FUseCurrentDate;

		System::String __fastcall GetCellText      (int ACol, int ARow);
		int            __fastcall GetDateElement   (int Index);
		void           __fastcall SetCalendarDate  (TDateTime Value);
		void           __fastcall SetDateElement   (int Index, int Value);
		void           __fastcall SetStartOfWeek   (TDayOfWeek Value);
		void           __fastcall SetUseCurrentDate(bool Value);
		bool           __fastcall StoreCalendarDate();
	
		TStringList              *_m_pslCellData;
		bool __fastcall           bIsCurrCalendarDate(TDate dtBegin);

	__published:
		__property Align;
		__property Anchors;
		__property BorderStyle;
		__property Color;
		__property Constraints;
		__property Ctl3D;
		__property int Day                = {read = GetDateElement, write = SetDateElement, stored = false, index = 3, nodefault};
		__property DragCursor;
		__property DragKind;
		__property DragMode;
		__property Enabled;
		__property Font;
		__property GridLineWidth;
		__property int Month              = {read = GetDateElement, write = SetDateElement, stored = false, index = 2, nodefault};
		__property ParentColor;
		__property ParentFont;
		__property ParentShowHint;
		__property PopupMenu;
		__property Boolean ReadOnly       = {read = FReadOnly, write = FReadOnly, default = 0};
		__property ShowHint;
		__property TDayOfWeek StartOfWeek = {read = FStartOfWeek, write = SetStartOfWeek, default = 1};
		__property TabOrder;
		__property TabStop;
		__property Boolean UseCurrentDate = {read = FUseCurrentDate, write = SetUseCurrentDate, default = 1};
		__property Visible;
		__property int Year               = {read = GetDateElement, write = SetDateElement, stored = false, index = 1, nodefault};
		__property OnClick;
		__property TNotifyEvent OnChange  = {read = FOnChange, write = FOnChange};
		__property OnDblClick;
		__property OnDragDrop;
		__property OnDragOver;
		__property OnEndDock;
		__property OnEndDrag;
		__property OnEnter;
		__property OnExit;
		__property OnKeyDown;
		__property OnKeyPress;
		__property OnKeyUp;
		__property OnStartDock;
		__property OnStartDrag;

		BEGIN_MESSAGE_MAP
			VCL_MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize);
		END_MESSAGE_MAP(TCustomGrid);
};
//---------------------------------------------------------------------------
#endif
