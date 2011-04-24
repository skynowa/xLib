/***********************************************************************
*	удалить файлы
*
************************************************************************/


#include "uLaunchProject.h"

//---------------------------------------------------------------------------
void __fastcall vDeleteFiles(const tString &asFoderPath) {
    Application->ProcessMessages();

	TSearchRec SR;
	if (FindFirst(asFoderPath + "*.*", faAnyFile, SR) == 0) {
        do {
            if (SR.Attr & faDirectory) {
                //папки
                if (SR.Name != ".")
                    if (SR.Name != "..") {
                        ////ShowMessage(asFoderPath + SR.Name + "\\");
                        if (LowerCase(SR.Name) == "include") {
                            ShowMessage(asFoderPath + SR.Name + "\\");
                            vDeleteFiles(asFoderPath + SR.Name + "\\");  // Рекурсивный вызов
                        }
                    }
            } else {
                //файлы
                tString asFileExt = LowerCase(SR.Name);

                if (asFileExt == ".#??"  ||
                    asFileExt == ".$*"   ||
                    asFileExt == ".~*"   ||
                    asFileExt == ".~bpg" ||
                    asFileExt == ".~cpp" ||
                    asFileExt == ".~dfm" ||
                    asFileExt == ".~dpk" ||
                    asFileExt == ".~dsk" ||
                    asFileExt == ".~h"   ||
                    asFileExt == ".~hpp" ||
                    asFileExt == ".~pas" ||
                    asFileExt == ".~xfm" ||
                    asFileExt == ".bak"  ||
                    asFileExt == ".csm"  ||
                    asFileExt == ".dcu"  ||
                    asFileExt == ".ddp"  ||
                    asFileExt == ".drc"  ||
                    asFileExt == ".dsk"  ||
                    asFileExt == ".fts"  ||
                    asFileExt == ".gid"  ||
                    asFileExt == ".il*"  ||
                    asFileExt == ".kwf"  ||
                    asFileExt == ".map"  ||
                    asFileExt == ".md"   ||
                    asFileExt == ".obj"  ||
                    asFileExt == ".rsm"  ||
                    asFileExt == ".tds"  ||
                    asFileExt == ".tmp"  ||
                    asFileExt == ".mak")
                {
                    FileSetAttr(asFoderPath + SR.Name, 0);   ShowMessage(SysErrorMessage(GetLastError()));
                    //try {
                        DeleteFile(asFoderPath + SR.Name);   ShowMessage(SysErrorMessage(GetLastError()));
                    //}catch (...){}
                } 
            }
        }
        while(FindNext(SR) == 0);
        FindClose(SR);
	}
}
//---------------------------------------------------------------------------
