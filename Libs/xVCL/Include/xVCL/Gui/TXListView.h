/****************************************************************************
* Class name:  TXListView
* Description: 
* File name:   TXListView.h
* Compilers:   C++Builder 2010
* String type: Unicode
* Libraries:   VCL
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     21.10.2009 11:11:48
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef TXListViewH
#define TXListViewH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <tchar.h>
#include <vector>
#include <Clipbrd.hpp>
#include <FileCtrl.hpp>
#include <cgauges.h>
#include <jpeg.hpp>

#include <XVCL/Common.h>

#ifdef DEF_TXLISTVIEW
	//инструкции
#endif

//---------------------------------------------------------------------------
class TXListView : public TListView {
	public:
					__fastcall  TXListView(TComponent* Owner);
					__fastcall ~TXListView();

		int                     iProgressBars_Count;
		void __fastcall         vProgressBar_Add   (const int ciItemIndex);
		void __fastcall         vProgressBar_Remove(const int ciItemIndex);

		//-------------------------------------
		//__property ProgressBar_Progress
		long int __fastcall _liProgressBar_GetProgress(const int ciItemIndex);
		void     __fastcall _vProgressBar_SetProgress (const int ciItemIndex, long int liProgress);

		//-------------------------------------
		//__property ProgressBar_MinValue
		long int __fastcall _liProgressBar_GetMinValue(const int ciItemIndex);
		void     __fastcall _vProgressBar_SetMinValue (const int ciItemIndex, long int liMinValue);

		//-------------------------------------
		//__property ProgressBar_MaxValue
		long int __fastcall _liProgressBar_GetMaxValue(const int ciItemIndex);
		void     __fastcall _vProgressBar_SetMaxValue (const int ciItemIndex, long int liMaxValue);

		//-------------------------------------
		//__property ProgressBar_Visible
		bool     __fastcall _bProgressBar_GetVisible  (const int ciItemIndex);
		void     __fastcall _vProgressBar_SetVisible  (const int ciItemIndex, bool bVisible);

	private:
		std::vector<TCGauge *> _m_vecpProgressBars;
		
	public:
		void        __fastcall _vProgressBar_Adjust(TListItem *pItem, TRect r);
		void        __fastcall _vProgressBar_AdjustAll();

		TWndMethod             _m_procOldWnd;
		void        __fastcall _procNewWnd(Messages::TMessage &Message);


};
//---------------------------------------------------------------------------
#endif
