/***********************************************************************
*	vCleanProj.cpp (удалить файлы)
*
************************************************************************/


#include "uLaunchProject.h"

//---------------------------------------------------------------------------
void __fastcall vCleanProj(const tString &asFoderPath) {    //ShowMessage(asFoderPath);
    //del *.obj;*.ilk;*.tlb;*.tli;*.tlh;*.tmp;*.rsp;*.pgc;*.pgd; *.plg;*.ncb;*.suo;*.opt;*.user; /f /s /q
    //rd /s /q Debug
    //rd /s /q Release

	//-------------------------------------
	//файлы для удаления
    const int ciExtSize = 16;
    const tString casExt[ciExtSize] = {
        ".obj", ".ilk", ".tlb", ".tli", ".tlh", ".tmp", ".rsp", ".pgc", ".pgd",
        ".plg", ".ncb", ".suo", ".opt", ".user", ".log", ".ini"
    };

	//-------------------------------------
	//роемся в папке asFoderPath
    Application->ProcessMessages();

	TSearchRec SR;  ::ZeroMemory(&SR, sizeof(SR));
	if (FindFirst(asFoderPath + "*.*", faAnyFile, SR) == 0) {
        Application->ProcessMessages();
        
        do {
            if (SR.Attr & faDirectory) {
                //-------------------------------------
                //папки
                if (SR.Name != ".")
                    if (SR.Name != "..") {             //ShowMessage(asFoderPath + SR.Name + "\\");
                        //-------------------------------------
                        //исключаем папки
                        if (LowerCase(SR.Name) == LowerCase("!Backup")) {
                            //ShowMessage(asFoderPath + SR.Name + "\\");
                            continue;
                        }
                        if (LowerCase(SR.Name) == LowerCase("Resource")) {
                            //ShowMessage(asFoderPath + SR.Name + "\\");
                            continue;
                        }
                        
                        //-------------------------------------
                        //идем к следующей папке
                        vCleanProj(asFoderPath + SR.Name + "\\");  // Рекурсивный вызов
                    }
            } else {       ///ShowMessage(SR.Name);
                //-------------------------------------
                //файлы папки


                //-------------------------------------
                //удаляем содержимое папок Debug и Release
                tString asW1("");
                tString asW2("");

                //Debug
                asW1 = LowerCase(asFoderPath);
                asW2 = LowerCase(BASE_PATH + "Project" + "\\" + "Debug" + "\\");
                if (asW1 == asW2) {         //ShowMessage(asFoderPath + SR.Name + "\\");
                    FileSetAttr(asFoderPath + SR.Name, 0);
                    DeleteFile(asFoderPath + SR.Name);
                }

                //Release
                asW1 = LowerCase(asFoderPath);
                asW2 = LowerCase(BASE_PATH + "Project" + "\\" + "Release" + "\\");
                if (asW1 == asW2) {        //ShowMessage(asFoderPath + SR.Name + "\\");
                    FileSetAttr(asFoderPath + SR.Name, 0);
                    DeleteFile(asFoderPath + SR.Name);
                }

                //-------------------------------------
                //удаляем файлы по расширению
                tString asFileExt = LowerCase(ExtractFileExt(SR.Name));
                for (int i = 0; i < ciExtSize; i ++) {
                    if (asFileExt == casExt[i] ) {
                        ///ShowMessage(asFoderPath + SR.Name);
                        FileSetAttr(asFoderPath + SR.Name, 0);
                        //try {
                            DeleteFile(asFoderPath + SR.Name);
                        //}catch (...){}
                    }
                }
            }
        }
        while (FindNext(SR) == 0);

        FindClose(SR);
	}
}
//---------------------------------------------------------------------------
