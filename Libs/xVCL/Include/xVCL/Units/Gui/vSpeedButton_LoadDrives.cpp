/***********************************************************************
*	vSpeedButton_LoadDrives.cpp
*
************************************************************************/


#include <vcl.h>
#pragma hdrstop
#include <Math.hpp>
//--------------------------------------------------------------------------- 
//TODO: vSpeedButton_LoadDrives        
void vSpeedButton_LoadDrives(TImageList *pilDrives, const std::vector<TSpeedButton *> &vecsbtnBtns) {
	/*DEBUG*/xASSERT(NULL != pilDrives);
	/*DEBUG*/xASSERT(0    < vecsbtnBtns.size());

	BOOL bRes = FALSE;
	
	//-------------------------------------
	//прячем TSpeedButton-ы
	for (std::size_t i = 0; i < vecsbtnBtns.size(); ++ i) {
		vecsbtnBtns.at(i)->Visible = false;  
	}

	//-------------------------------------
	//цикл по дискам
	std::vector<tString> vecsDrives;

	bRes = CxDrive::bGetLogicalDrives(&vecsDrives);
	/*DEBUG*/xASSERT(FALSE != bRes);
	
	for (std::size_t i = 0, uiSbtnDriveIndex = 0; i < vecsDrives.size(); ++ i, ++ uiSbtnDriveIndex) {
		//-------------------------------------
		//путь к диску со слешем
		String sDrivePath((vecsDrives.at(i) + CxConst::xSLASH).c_str());  	//vMsgBox(sDrivePath.c_str());

		tString   sDriveLabel                = _T("[Empty]");
		ULONGLONG ui64FreeBytesAvailable     = 0;
		ULONGLONG ui64TotalNumberOfBytes     = 0;
		ULONGLONG ui64TotalNumberOfFreeBytes = 0;
		
		//-------------------------------------
		//иконка диска
		const std::auto_ptr<Graphics::TBitmap> apBitmap(new Graphics::TBitmap());
		/*DEBUG*/xASSERT(NULL != apBitmap.get());
		apBitmap->Transparent      = true;
		apBitmap->TransparentColor = clBtnFace;	// clGradientActiveCaption;     ////????????????

		SHFILEINFO info = {0};
		ULONG ulImageHandle = ::SHGetFileInfo(sDrivePath.c_str(), 0, &info, sizeof(info), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
		if (0 != ulImageHandle) {
			pilDrives->Handle      = ulImageHandle;
			pilDrives->ShareImages = true;
		}
		////::CloseHandle((VOID *)ulImageHandle);

		if (pilDrives->Count > 0) {
			pilDrives->GetBitmap(info.iIcon, apBitmap.get());
		}

		//-------------------------------------
		//проверка готовности диска
		bRes = CxDrive::bIsReady(sDrivePath.c_str());
		if (FALSE == bRes) {
			//...
		} else {
			//лейбл диска
			bRes = CxDrive::bGetInfo(sDrivePath.c_str(), &sDriveLabel, NULL, NULL, NULL, NULL);
			/*DEBUG*/xASSERT(FALSE != bRes);

			//свободное / занятое место
			bRes = CxDrive::bGetFreeSpace(sDrivePath.c_str(), &ui64FreeBytesAvailable, &ui64TotalNumberOfBytes, &ui64TotalNumberOfFreeBytes);
			/*DEBUG*/xASSERT(FALSE != bRes);
		}

		//-------------------------------------
		//загоняем все данные на кнопку
		/*DEBUG*/xASSERT(vecsbtnBtns.size() > uiSbtnDriveIndex);
		/*DEBUG*/xASSERT(NULL  != vecsbtnBtns.at(uiSbtnDriveIndex));
		/*DEBUG*/xASSERT(NULL  != apBitmap.get());
		/*DEBUG*/xASSERT(false == sDrivePath.IsEmpty());
		/*DEBUG*/xASSERT(false == sDriveLabel.empty());

		vecsbtnBtns.at(uiSbtnDriveIndex)->Glyph   = apBitmap.get();
		vecsbtnBtns.at(uiSbtnDriveIndex)->Caption = sDrivePath[1];    //строка "C"
		vecsbtnBtns.at(uiSbtnDriveIndex)->Hint    = _T("Label: ") + String( sDriveLabel.c_str()                                        ) + _T("\r\n")
													_T("Total: ") + String( CxString::sFormatBytes(ui64TotalNumberOfBytes).c_str()     ) + _T("\r\n")
													_T("Free:  ") + String( CxString::sFormatBytes(ui64TotalNumberOfFreeBytes).c_str() );
		vecsbtnBtns.at(uiSbtnDriveIndex)->Visible = true;
	}
}
//---------------------------------------------------------------------------