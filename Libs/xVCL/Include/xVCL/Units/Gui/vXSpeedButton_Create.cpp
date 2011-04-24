/***********************************************************************
*   vXSpeedButton_Create
*
************************************************************************/


#include <xVCL/Gui/TXSpeedButton.h>

typedef void __fastcall  (__closure* EventHandler)(TObject *Sender);
//---------------------------------------------------------------------------
void vXSpeedButton_Create(TTabSheet     *pTBS,
						  TXSpeedButton *pSpeedBtn[],
						  int 		     iHeight,
						  int 			 iWidth/*78*/,
						  int 			 iStartCapacity,
						  int 			 iStopCapacity,
						  int 			 iItemsInRow,
						  TPopupMenu    *pmBtnProperties,
						  EventHandler   ehXSpeedButton_OnClick)
{

	/*DEBUG*/xASSERT(NULL != pTBS);
	/*DEBUG*/xASSERT(NULL != pSpeedBtn);
	/*DEBUG*/xASSERT(0    <  iHeight);
	/*DEBUG*/xASSERT(0    <  iWidth);
	/*DEBUG*/xASSERT(0    <= iStartCapacity);
	/*DEBUG*/xASSERT(0    <  iStopCapacity);
	/*DEBUG*/xASSERT(0    <  iItemsInRow);

	/*
    vXSpeedButton_Create(tsSoft,   22, 22,   0,   200,  14);  //0    - 299
    vXSpeedButton_Create(tsBrowse, 22, 77,   300, 500,  4);   //300  - 599     <------
	*/

	//-------------------------------------
	//создаем кнопки
	std::auto_ptr<TIniFile> apIni(new TIniFile(ChangeFileExt(Application->ExeName, _T(".ini"))));
	/*DEBUG*/xASSERT(NULL != apIni.get());

	int iCapacity       = iStartCapacity;
	int x               = 0;       //колонки
	int y               = 0;       //ряды
	int iCountBtnsInRow = 0;       //счётчик кнопок в ряде

	for (y = 0, iCountBtnsInRow = 0; iCapacity < iStopCapacity; ++ iCapacity, ++ iCountBtnsInRow) { //144 - объём таба
		//-------------------------------------
		//перенос ряда
		if (iCountBtnsInRow >= iItemsInRow) {
			y              += iHeight;
			x               = 0;
			iCountBtnsInRow = 0;
		}

		//-------------------------------------
		//свойства кнопки
		pSpeedBtn[iCapacity]             = new TXSpeedButton(NULL);
		/*DEBUG*/xASSERT(NULL != pSpeedBtn[iCapacity]);
		pSpeedBtn[iCapacity]->Tag        = iCapacity;       //Name
		pSpeedBtn[iCapacity]->Parent     = pTBS;
		pSpeedBtn[iCapacity]->Left       = (x += iWidth) - iWidth;
		pSpeedBtn[iCapacity]->Top        = y;
		pSpeedBtn[iCapacity]->Width      = iWidth;  //22;
		pSpeedBtn[iCapacity]->Height     = iHeight; //22;
		pSpeedBtn[iCapacity]->Margin     = 2;
		pSpeedBtn[iCapacity]->Spacing    = 5;
		pSpeedBtn[iCapacity]->Flat       = true;
		//Hint
		String usHint = apIni.get()->ReadString(IntToStr(iCapacity), _T("Caption"), _T(""));
		if (true == usHint.IsEmpty()) {
			pSpeedBtn[iCapacity]->Hint   = apIni->ReadString(IntToStr(iCapacity), _T("FilePath"), _T(""));
		} else {
			pSpeedBtn[iCapacity]->Hint   = usHint;
		}
		pSpeedBtn[iCapacity]->ShowHint   = true;
		//
		pSpeedBtn[iCapacity]->Caption     = apIni->ReadString(IntToStr(iCapacity), _T("Caption"),  _T(""));
		pSpeedBtn[iCapacity]->m_sFilePath = apIni->ReadString(IntToStr(iCapacity), _T("FilePath"), _T(""));
		pSpeedBtn[iCapacity]->m_sParam    = apIni->ReadString(IntToStr(iCapacity), _T("Param"),    _T(""));
		pSpeedBtn[iCapacity]->m_sIconPath = apIni->ReadString(IntToStr(iCapacity), _T("IconPath"), _T(""));
		//Glyph
		vXSpeedButton_LoadAssocIcon(pSpeedBtn[iCapacity], apIni->ReadString(IntToStr(iCapacity), _T("IconPath"), _T("")));

		pSpeedBtn[iCapacity]->PopupMenu  = pmBtnProperties;
		pSpeedBtn[iCapacity]->OnClick    = ehXSpeedButton_OnClick;
	}
}
//---------------------------------------------------------------------------