/***********************************************************************
*   Откл/вкл привод  
*
************************************************************************/


#include <winioctl.h>

HANDLE hDevice;

void __fastcall TfrmMainServer::LockCDRom(bool bLockFlag)  {
    for (int x = 0; x < 26; x ++) {     //проходимся циклом по битам
       if (((GetLogicalDrives() >> x) & 1)) {      //узнаём значение текущего бита, если единица - диск с номером x есть
          tString asDriveLetter = tString((char)(65 + x)); // получаем литеру диска
          tString asPath        = tString((char)(65 + x)) + ":\\";

          //здесь узнаём готово ли устройство
          WORD OldErrorMode;
          OldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS); // убираем показ ошибок
          bool bReady  = DirectoryExists(asPath);              //пытаемcя открыть корневую директорию
          SetErrorMode(OldErrorMode);                          //восстанавливаем старый режим показа ошибок

          if (bReady) {
             UINT iDriveType = GetDriveType((asDriveLetter + ":\\").c_str()); // узнаём тип диска

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
