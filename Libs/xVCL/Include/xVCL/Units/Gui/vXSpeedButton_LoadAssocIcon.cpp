/***********************************************************************
*	vXSpeedButton_LoadAssocIcon
*
************************************************************************/


#include <xVCL/Gui/TXSpeedButton.h>
//---------------------------------------------------------------------------
//TODO: vXSpeedButton_LoadAssocIcon 
void vXSpeedButton_LoadAssocIcon(TXSpeedButton *pSBTN, const String &csFlePath) {
	/*DEBUG*/xASSERT(NULL  != pSBTN);
	/*DEBUG*/// csFlePath - n/a

	//-------------------------------------
	//если путь пустой
	xCHECK_DO(true == csFlePath.IsEmpty(), pSBTN->Glyph->Assign(NULL); return )

	//-------------------------------------
	//дефолтная иконка
	if ( (FALSE == CxDir::bIsExists/*DirectoryExists*/(csFlePath.c_str())) && (FALSE == CxFile::bIsExists(csFlePath.c_str())) ) {
	    //--csFlePath = "F:\\MyCD\\!!!!!!!!\\_MyProjects\\MyBC++\\Projects\\Start2\\Project\\Icon_16.ico";
        return;
    }

    //-------------------------------------
    //загружаем иконку файла exe-файла в pImageList
	const std::auto_ptr<TImageList> apImageList(new TImageList(NULL));
	/*DEBUG*/xASSERT(NULL != apImageList.get());

	TSHFileInfoW sfInfo = {0};             //TODO: SHGetFileInfo
	ULONG ulImageHandle = ::SHGetFileInfo(csFlePath.c_str(),
											0,
											&sfInfo,
											sizeof(sfInfo),
											SHGFI_SYSICONINDEX | SHGFI_ICON | SHGFI_SMALLICON);
	if (0 != ulImageHandle) {
		apImageList.get()->Handle      = ulImageHandle;
        apImageList.get()->ShareImages = true;
    }
	////::CloseHandle((VOID *)ulImageHandle);

	const std::auto_ptr<TIcon> apIcon(new TIcon());
	/*DEBUG*/xASSERT(NULL != apIcon.get());
	apIcon->Handle      = sfInfo.hIcon;      //<<<<<<<<<<
	apIcon->Transparent = true;

	int iIconIndex = apImageList->AddIcon(apIcon.get());

    //-------------------------------------
    //иконка в exe
	const std::auto_ptr<Graphics::TBitmap> apBitmap(new Graphics::TBitmap());
	/*DEBUG*/xASSERT(NULL != apBitmap.get());

	apImageList->GetBitmap(iIconIndex, apBitmap.get());
	apBitmap->Transparent      = true;
	apBitmap->TransparentColor = clGradientActiveCaption;     ////????????????

	pSBTN->Glyph = apBitmap.get();
}
//--------------------------------------------------------------------------- 
