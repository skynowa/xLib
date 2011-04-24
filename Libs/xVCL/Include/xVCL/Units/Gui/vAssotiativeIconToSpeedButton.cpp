/***********************************************************************
*	Заполняем ComboBoxEx именами, метками дисков
*
************************************************************************/

//not use
//---------------------------------------------------------------------------
void __fastcall vAssotiativeIconToSpeedButton(TSpeedButton *sbtnSB, const tString &cusFlePath) {
	/*DEBUG*/xASSERT(NULL != sbtnSB);
	/*DEBUG*/xASSERT(false == FileExists(cusFlePath));

	ShowMessage("xxxxx");

//  TIcon *ico = new TIcon();
//  ico->Handle = ExtractIcon(HInstance, asFlePath.c_str(), 0);
//
//
//    sbtnSB->Glyph->Width  = sbtnSB->ClientWidth;
//    sbtnSB->Glyph->Height = sbtnSB->ClientHeight;
////    Canvas->StretchDraw(Rect(0,0,Width ,Height ), ico);
//
//  ico->Free();

    //определяем соответствующую иконку
	//////////////////////////int         iIconIndex = - 1;
	TSHFileInfo sfi        = {0};
    
	if (::SHGetFileInfo(cusFlePath.t_str(), 0, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX | SHGFI_SMALLICON)) {
		std::auto_ptr<TIcon> apIcon(new TIcon());
		/*DEBUG*/xASSERT(NULL != apIcon.get());
		apIcon.get()->Handle = sfi.hIcon;
		////////////////////////////iIconIndex    = sfi.iIcon;
		//////ImageList1->Clear();
		//////ImageList1->AddIcon(pIcon);   //ShowMessage(SysErrorMessage(GetLastError()));
	}

	//заполняем иконкой кнопку
	std::auto_ptr<Graphics::TBitmap> apBitmap(new Graphics::TBitmap());
	/*DEBUG*/xASSERT(NULL != apBitmap.get());
	apBitmap.get()->Transparent      = false;
	apBitmap.get()->TransparentColor = clGradientActiveCaption;

	////////////////////cboeLocalDrives->Images->GetBitmap(iIconIndex, pBitmap);
	////////////ImageList1->GetBitmap(/*iIconIndex*/0, pBitmap);

	sbtnSB->Glyph   = apBitmap.get();
	sbtnSB->Caption = _T("");
	sbtnSB->Hint    = _T("");
	sbtnSB->Visible = true;
}
//---------------------------------------------------------------------------
