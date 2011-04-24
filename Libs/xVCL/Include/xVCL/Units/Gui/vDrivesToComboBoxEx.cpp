/***********************************************************************
*	Заполняем ComboBoxEx именами, метками дисков
*
************************************************************************/
       

//---------------------------------------------------------------------------
void __fastcall vDrivesToComboBoxEx() {  //DONE: doDrivesToComboBoxEx()
    cboeLocalDrives->Items->Clear();

	DWORD dwBufLen = ::GetLogicalDriveStrings(0, NULL);
    if (!dwBufLen) {
        return;
	}

	wchar_t *pwzBuff = new wchar_t[sizeof(wchar_t) * dwBufLen], *pBuff = pwzBuff;
	/*DEBUG*/xASSERT(NULL != pwzBuff);
	/*DEBUG*/xASSERT(NULL != pBuff);
    __try {
		if (!::GetLogicalDriveStrings(dwBufLen, pwzBuff)) {
			return;
		}

		//-------------------------------------
		//
		TSHFileInfo sfi;    ZeroMemory(&sfi, sizeof(sfi));

		while (*pBuff) {
			/*DEBUG*/xASSERT(NULL != pBuff);

			//-------------------------------------
			//определяем соответствующую иконку
			int iIconIndex = -1;
			HIMAGELIST hImage = (HIMAGELIST)::SHGetFileInfo(pBuff, 0, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
			if (NULL != hImage) {
				iIconIndex = sfi.iIcon;
			} //else - по дефолту

			//-------------------------------------
			//получаем данные о размерах
			tString    usDriveLetter              = L"";
			unsigned __int64 ui64FreeBytesAvailable     = 0;
			unsigned __int64 ui64TotalNumberOfBytes     = 0;
			unsigned __int64 ui64TotalNumberOfFreeBytes = 0;
			wchar_t          wzDriveLabel[30]           = L"[Empty]";
			wchar_t          wzDriveFat[30]             = L"[Empty]";
			DWORD            dwDriveSN                  = 0;

			usDriveLetter = tString(pBuff, 2);  //удаляем слэш из имени, т.е. "C:"

			if (false == bIsDriveReady(std::wstring(usDriveLetter.t_str()))) {
				//MessageBox(0, (L"vDrivesToComboBoxEx()    Диск " + usDriveLetter + L" не готов.").t_str(), APP_NAME, MB_OK);
			}

			if (false == ::GetDiskFreeSpaceEx(usDriveLetter.t_str(), (PULARGE_INTEGER)&ui64FreeBytesAvailable, (PULARGE_INTEGER)&ui64TotalNumberOfBytes, (PULARGE_INTEGER)&ui64TotalNumberOfFreeBytes)) {

			}

			if (false == ::GetVolumeInformation((usDriveLetter + L"\\").t_str(), wzDriveLabel, 255, &dwDriveSN, NULL, NULL, NULL, NULL)) {

			}

			//-------------------------------------
			//заполняем cboeLocalDrives
			cboeLocalDrives->ItemsEx->AddItem(
				usDriveLetter + L" " + wzDriveLabel + L"  " + L"   [Free: " + ui64TotalNumberOfFreeBytes / 1000000 + L" Mb]",
				iIconIndex,
				iIconIndex,
				0,
				0,
				0
			);

			//-------------------------------------
			//смещаем указатель имя следующего диска на 4 байта      "C:\\0D:\\0E:\\0..."
			pBuff += 4;
		}
	} __finally {
		/*DEBUG*/xASSERT(NULL != pwzBuff);
		delete [] pwzBuff;  pwzBuff = NULL;
	}



    //-------------------------------------
    //устанавливаем в cboeLocalDrives текущий диск
    for (int i = 0; i < cboeLocalDrives->Items->Count; i ++) {
        if (ExtractFileDrive(Application->ExeName) == cboeLocalDrives->Items->Strings[i].SetLength(2)) {     
            cboeLocalDrives->ItemIndex = i;
        }
    }
}
//---------------------------------------------------------------------------
