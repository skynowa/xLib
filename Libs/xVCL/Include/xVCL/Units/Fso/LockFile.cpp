/***********************************************************************
*   
*
************************************************************************/


HANDLE hFile;

void __fastcall TfrmMainServer::LockFile(tString const & asFilePath, bool bLockFlag)  {
    if (bLockFlag == true) {
        hFile = CreateFile(
              ("\\\\.\\" + asFilePath).c_str(),
              GENERIC_WRITE,
              0,
              NULL,
              OPEN_EXISTING,
              FILE_ATTRIBUTE_NORMAL,
              NULL
        );
    } else {
        CloseHandle (hFile);
    }
}
