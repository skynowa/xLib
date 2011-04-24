/***********************************************************************
*   ����/��� ������  
*
************************************************************************/


#include <winioctl.h>

HANDLE hDevice;

void __fastcall TfrmMainServer::LockCDRom(bool bLockFlag)  {
    for (int x = 0; x < 26; x ++) {     //���������� ������ �� �����
       if (((GetLogicalDrives() >> x) & 1)) {      //����� �������� �������� ����, ���� ������� - ���� � ������� x ����
          tString asDriveLetter = tString((char)(65 + x)); // �������� ������ �����
          tString asPath        = tString((char)(65 + x)) + ":\\";

          //����� ����� ������ �� ����������
          WORD OldErrorMode;
          OldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS); // ������� ����� ������
          bool bReady  = DirectoryExists(asPath);              //������c� ������� �������� ����������
          SetErrorMode(OldErrorMode);                          //��������������� ������ ����� ������ ������

          if (bReady) {
             UINT iDriveType = GetDriveType((asDriveLetter + ":\\").c_str()); // ����� ��� �����

              switch (iDriveType) {
                  case DRIVE_REMOVABLE:
                  break;

                  case DRIVE_FIXED:
                  break;

                  case DRIVE_REMOTE:
                  break;

                  case DRIVE_CDROM:
                        if (bLockFlag == true) {
                            hDevice = CreateFile(
                                  ("\\\\.\\" + asDriveLetter + ":").c_str(),
                                  GENERIC_WRITE,
                                  0,
                                  NULL,
                                  OPEN_EXISTING,
                                  FILE_ATTRIBUTE_NORMAL,
                                  NULL
                            );
                        } else {
                            CloseHandle (hDevice);
                        }
                  break;

                  case DRIVE_RAMDISK:
                  break;

                  default:
                  break;
              }
          }
       }
    }
} 
