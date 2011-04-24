/****************************************************************************
* Class name:  TXListView
* Description: 
* File name:   TXListView.cpp
* Compilers:   C++Builder 2010
* String type: Unicode
* Libraries:   VCL
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     21.10.2009 11:11:48
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include "TXListView.h"
//---------------------------------------------------------------------------
__fastcall TXListView::TXListView(TComponent* Owner) :
	TListView          (Owner),
	iProgressBars_Count(0)
 {
	//-------------------------------------
	//субклассинг
	_m_procOldWnd    = this->WindowProc;
	this->WindowProc = _procNewWnd;
	
	
	/*
	//-------------------------------------
	//xlvQueue
	xlvQueue = new TListView(tsQueue);
	xASSERT(NULL != xlvQueue);

	xlvQueue->Name                    = _T("xlvQueue");
	xlvQueue->Parent                  = tsQueue;
	xlvQueue->Left                    = 0;
	xlvQueue->Top                     = 0;
	xlvQueue->Width                   = 795;
	xlvQueue->Height                  = 474;
	xlvQueue->Align                   = alClient;
	xlvQueue->Color                   = clWindow;
	xlvQueue->GridLines               = true;
	xlvQueue->HideSelection           = false;
	//xlvQueue->DoubleBuffered          = true;
	xlvQueue->MultiSelect             = true;
	xlvQueue->ReadOnly                = true;
	xlvQueue->RowSelect               = true;
	xlvQueue->PopupMenu               = pmLvQueue;
	xlvQueue->SmallImages             = ilAssocFileIcons;
	xlvQueue->Visible                 = true;
	xlvQueue->ViewStyle               = vsReport;

	xlvQueue->Columns->Add()->Caption = _T(" Имя файла");
	xlvQueue->Columns->Add()->Caption = _T(" Размер");
	xlvQueue->Columns->Add()->Caption = _T(" Прогресс");
	xlvQueue->Columns->Add()->Caption = _T(" Скорость");
	xlvQueue->Columns->Add()->Caption = _T(" Статус");
	xlvQueue->Columns->Add()->Caption = _T(" Сохранить в");
	xlvQueue->Columns->Add()->Caption = _T(" Ссылка");
	
	////xlvQueue->OnCustomDrawItem        =	xlvQueueCustomDrawItem;
	////xlvQueue->OnCustomDrawSubItem     =	xlvQueueCustomDrawSubItem;
	xlvQueue->OnDblClick	          = pmLvQueue_LinkPropertyClick;
	
	*/
}
//---------------------------------------------------------------------------
__fastcall TXListView::~TXListView() {
	size_t 	ttt = _m_vecpProgressBars.size();

	for (size_t i = 0; i < _m_vecpProgressBars.size(); i ++) {
		/*DEBUG*///xASSERT(NULL != m_vecpProgressBars.at(i)); - not need
		if (NULL != _m_vecpProgressBars.at(i)) {
			delete _m_vecpProgressBars.at(i);	_m_vecpProgressBars.at(i) = NULL;
		}
	}

	//-------------------------------------
	//субклассинг
	this->WindowProc = _m_procOldWnd;
	_m_procOldWnd    = NULL;
}
//---------------------------------------------------------------------------






/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: добавть TProgressBar в ячейку
void __fastcall TXListView::vProgressBar_Add(const int ciItemIndex) {
	/*DEBUG*/xASSERT(NULL != this);

	static int iCount = 0;

	//-------------------------------------
	//создаем TProgressBar невидимым
	TCGauge *ppbPB = new TCGauge(this);
	/*DEBUG*/xASSERT(NULL != ppbPB);
	ppbPB->Visible          = false;
	ppbPB->Parent           = this;
	ppbPB->Progress         = iCount ++ ;
	ppbPB->BackColor        = clWhite;
	ppbPB->ForeColor        = clBlack;
	ppbPB->AlignWithMargins = true;
	ppbPB->MinValue         = 0;
	ppbPB->MaxValue         = 100;

	//-------------------------------------
	//размещение TProgressBar и делаем видимым
	Items->Item[ciItemIndex]->Data = ppbPB;

	TRect rcRect;
	rcRect = Items->Item[ciItemIndex]->DisplayRect(drBounds);
	_vProgressBar_Adjust(Items->Item[ciItemIndex], rcRect);

	ppbPB->Visible = true;

	/*DEBUG*/xASSERT(NULL != ppbPB);
	_m_vecpProgressBars.push_back(ppbPB);

	ppbPB = NULL;

	iProgressBars_Count ++;
}
//---------------------------------------------------------------------------
//DONE: удалить TProgressBar с ячейки
void __fastcall TXListView::vProgressBar_Remove(const int ciItemIndex) {
	/*DEBUG*/xASSERT(NULL != this);
	/*DEBUG*///xASSERT(NULL != _m_vecpProgressBars.at(ciItemIndex));

	if (NULL == _m_vecpProgressBars.at(ciItemIndex)) {
		/*DEBUG*/xASSERT(NULL == Items->Item[ciItemIndex]->Data);
		/*DEBUG*/xASSERT(NULL == _m_vecpProgressBars.at(ciItemIndex));
		
		return;
	}

	//-------------------------------------
	//удаление TProgressBar
	Items->Item[ciItemIndex]->Data = NULL;
	delete _m_vecpProgressBars.at(ciItemIndex);    _m_vecpProgressBars.at(ciItemIndex) = NULL;

	//-------------------------------------
	//удаление из std::vector
	//_m_vecpProgressBars.erase(&_m_vecpProgressBars.at(ciItemIndex));
	_m_vecpProgressBars.erase(_m_vecpProgressBars.begin() + ciItemIndex);
	////ShowMessage("Размер: " + IntToStr((int)_m_vecpProgressBars.size()) + _T("\r\nИндкс: ") + IntToStr((int)ciItemIndex));


	//-------------------------------------
	//
	_vProgressBar_AdjustAll();




	//::InvalidateRect(this->Handle, NULL, FALSE);
	//::UpdateWindow(this->Handle);
	//::SendMessage(this->Handle, WM_SETREDRAW, (WPARAM)FALSE, (LPARAM)0);
	//::SendMessage(this->Handle, WM_SETREDRAW, (WPARAM)TRUE, (LPARAM)0);

	iProgressBars_Count --;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: субклассинг
void __fastcall TXListView::_procNewWnd(Messages::TMessage &Message) {
	/*DEBUG*/xASSERT(NULL != this);

	if (WM_NOTIFY == Message.Msg) {
		LPNMLISTVIEW pnmv = reinterpret_cast<LPNMLISTVIEW>(Message.LParam);
		switch (pnmv->hdr.code) {
            case LVN_DELETEITEM: 
			{
				//::OutputDebugString(_T("LVN_DELETEITEM"));
                break;
            }
		}





		LPNMHDR lpNMHDR = reinterpret_cast<LPNMHDR>(Message.LParam);
		switch (lpNMHDR->code) {
			case HDN_ITEMCHANGED:
				{
					//::OutputDebugString(_T("HDN_ITEMCHANGED"));
					_vProgressBar_AdjustAll();
				}
				break;
			case HDN_ITEMCHANGING :
				{
					//::OutputDebugString(_T("HDN_ITEMCHANGING"));
				}
				break;
			case HDN_BEGINTRACK:
				{
					//::OutputDebugString(_T("HDN_BEGINTRACK"));
				}
				break;
			case HDN_ENDTRACK:
				{
					//::OutputDebugString(_T("HDN_ENDTRACK"));
				}
				break;
			case HDN_TRACK:
				{
					//::OutputDebugString(_T("HDN_TRACK"));
				}
				break; 
			case LVN_DELETEITEM:
				{
					//::OutputDebugString(_T("LVN_DELETEITEM"));
				}
				break; 
			
			default:
				{
				}
				break;
		}
	}
	
	_m_procOldWnd(Message); 
}
//---------------------------------------------------------------------------
//DONE: выравнивание TProgressBar в ячейке
void __fastcall TXListView::_vProgressBar_Adjust(TListItem *pItem, TRect r) {
	/*DEBUG*/xASSERT(NULL != this);
	/*DEBUG*/xASSERT(NULL != pItem);

	const int ciWidthMargin  = 2;
	const int ciHeigthMargin = 2;

	r.Left   = r.Left   + Columns->Items[0]->Width + Columns->Items[1]->Width + ciWidthMargin;
	r.Right  = r.Left   + Columns->Items[2]->Width - ciWidthMargin * 2;
	r.Top    = r.Top    + ciHeigthMargin;
	r.Bottom = r.Bottom - ciHeigthMargin * 2;

	if (r.Left > r.Right) {
		r.Right = r.Left;
	}
 
	TCGauge *ppbPB = static_cast<TCGauge *>(pItem->Data);         
	/*DEBUG*/xASSERT(NULL != ppbPB);

	ppbPB->BoundsRect = r;
	ppbPB->Refresh();
}
//---------------------------------------------------------------------------
//DONE: выравнивание всех TProgressBar-ов в ячейках
void __fastcall TXListView::_vProgressBar_AdjustAll() {
	/*DEBUG*/xASSERT(NULL != this);

	TRect rcRect;
	for (int i = 0; i < Items->Count; ++ i) {
		TCGauge *ppbPB = static_cast<TCGauge *>(Items->Item[i]->Data);
		if (NULL == ppbPB) {
			continue;
		}

		rcRect = Items->Item[i]->DisplayRect(drBounds);
		_vProgressBar_Adjust(Items->Item[i], rcRect);
	}

	Repaint();
}
//---------------------------------------------------------------------------

/****************************************************************************
* __property
*
*****************************************************************************/

//---------------------------------------------------------------------------
//__property ProgressBar_Progress
long int __fastcall TXListView::_liProgressBar_GetProgress(const int ciItemIndex) {
	/*DEBUG*/xASSERT(NULL != this);

	return _m_vecpProgressBars.at(ciItemIndex)->Progress;
}
void __fastcall TXListView::_vProgressBar_SetProgress(const int ciItemIndex, long int liProgress) {
	/*DEBUG*/xASSERT(NULL != this);

	_m_vecpProgressBars.at(ciItemIndex)->Progress = liProgress;
}
//---------------------------------------------------------------------------
//__property ProgressBar_MinValue
long int __fastcall TXListView::_liProgressBar_GetMinValue(const int ciItemIndex) {
	/*DEBUG*/xASSERT(NULL != this);

	return _m_vecpProgressBars.at(ciItemIndex)->MinValue;
}
void __fastcall TXListView::_vProgressBar_SetMinValue(const int ciItemIndex, long int liMinValue) {
	/*DEBUG*/xASSERT(NULL != this);

	_m_vecpProgressBars.at(ciItemIndex)->MinValue = liMinValue;
}
//---------------------------------------------------------------------------
//__property ProgressBar_MaxValue
long int __fastcall TXListView::_liProgressBar_GetMaxValue(const int ciItemIndex) {
	/*DEBUG*/xASSERT(NULL != this);

	return _m_vecpProgressBars.at(ciItemIndex)->MaxValue;
}
void __fastcall TXListView::_vProgressBar_SetMaxValue(const int ciItemIndex, long int liMaxValue) {
	/*DEBUG*/xASSERT(NULL != this);

	_m_vecpProgressBars.at(ciItemIndex)->MaxValue = liMaxValue;
}
//---------------------------------------------------------------------------
//__property ProgressBar_Visible
bool __fastcall TXListView::_bProgressBar_GetVisible(const int ciItemIndex) {
	/*DEBUG*/xASSERT(NULL != this);

	return _m_vecpProgressBars.at(ciItemIndex)->Visible;
}
void __fastcall TXListView::_vProgressBar_SetVisible(const int ciItemIndex, bool bVisible) {
	/*DEBUG*/xASSERT(NULL != this);

	_m_vecpProgressBars.at(ciItemIndex)->Visible = bVisible;
}
//---------------------------------------------------------------------------

