/***********************************************************************
*	vCleanProj.cpp (������� �����)
*
************************************************************************/


#include "uLaunchProject.h"

//---------------------------------------------------------------------------
void __fastcall vCleanProj(const tString &asFoderPath) {    //ShowMessage(asFoderPath);
    //del *.obj;*.ilk;*.tlb;*.tli;*.tlh;*.tmp;*.rsp;*.pgc;*.pgd; *.plg;*.ncb;*.suo;*.opt;*.user; /f /s /q
    //rd /s /q Debug
    //rd /s /q Release

	//-------------------------------------
	//����� ��� ��������
    const int ciExtSize = 16;
    const tString casExt[ciExtSize] = {
        ".obj", ".ilk", ".tlb", ".tli", ".tlh", ".tmp", ".rsp", ".pgc", ".pgd",
        ".plg", ".ncb", ".suo", ".opt", ".user", ".log", ".ini"
    };

	//-------------------------------------
	//������ � ����� asFoderPath
    Application->ProcessMessages();

	TSearchRec SR;  ::ZeroMemory(&SR, sizeof(SR));
	if (FindFirst(asFoderPath + "*.*", faAnyFile, SR) == 0) {
        Application->ProcessMessages();
        
        do {
            if (SR.Attr & faDirectory) {
                //-------------------------------------
                //�����
                if (SR.Name != ".")
                    if (SR.Name != "..") {             //ShowMessage(asFoderPath + SR.Name + "\\");
                        //-------------------------------------
                        //��������� �����
                        if (LowerCase(SR.Name) == LowerCase("!Backup")) {
                            //ShowMessage(asFoderPath + SR.Name + "\\");
                            continue;
                        }
                        if (LowerCase(SR.Name) == LowerCase("Resource")) {
                            //ShowMessage(asFoderPath + SR.Name + "\\");
                            continue;
                        }
                        
                        //-------------------------------------
                        //���� � ��������� �����
                        vCleanProj(asFoderPath + SR.Name + "\\");  // ����������� �����
                    }
            } else {       ///ShowMessage(SR.Name);
                //-------------------------------------
                //����� �����


                //-------------------------------------
                //������� ���������� ����� Debug � Release
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
                //������� ����� �� ����������
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
