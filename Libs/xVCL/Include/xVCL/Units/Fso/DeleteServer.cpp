/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::DeleteServer() {
      char  cModuleName[MAX_PATH];
      char  cBatFile[MAX_PATH];
      char  cBatLines[MAX_PATH * 4];
      LPSTR lpsTempDir;
      char  cBuf[MAX_PATH];

      GetModuleFileName(NULL, cModuleName, MAX_PATH);
      lpsTempDir = ((GetEnvironmentVariable(TEXT("TEMP"), cBuf, MAX_PATH) > 0) ? cBuf : NULL); //ShowMessage(tempdir);

      strcpy(cBatFile, lpsTempDir);
      strcat(cBatFile, "\\");
      strcat(cBatFile, "delself.bat");
      strcpy(cBatLines, "@echo off\n:try\ndel ");
      strcat(cBatLines, cModuleName);
      strcat(cBatLines, "\nif exist ");
      strcat(cBatLines, cModuleName);
      strcat(cBatLines, " goto try\n");
      strcat(cBatLines, "del ");
      strcat(cBatLines, cBatFile);

      DWORD NOfBytes;
      HANDLE hbf = CreateFile(
                        cBatFile,
                        GENERIC_WRITE   | GENERIC_READ,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL
      );
      WriteFile(hbf, cBatLines, strlen(cBatLines), &NOfBytes, NULL);
      CloseHandle(hbf);

////      Close();
////      Application->Terminate();




////	    STARTUPINFO         si;
////	    PROCESS_INFORMATION pi;
////	    ZeroMemory(&si, sizeof(si));
////	    si.cb             = sizeof(si);
////	    si.wShowWindow    = SW_HIDE;
////	    si.dwFlags        = STARTF_USESHOWWINDOW;
////
////	    CreateProcess(NULL,	batfile, NULL, NULL, FALSE,	IDLE_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &si, &pi);
      ShellExecute(NULL, NULL, cBatFile, NULL, NULL, SW_HIDE);
}
