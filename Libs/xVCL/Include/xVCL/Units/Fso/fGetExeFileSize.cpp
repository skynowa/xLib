/***********************************************************************
*   vIcoToSpeedBtn   
*
************************************************************************/


#include "uLaunchProject.h"

#include <stdio.h>
#include <Math.hpp>

//---------------------------------------------------------------------------
float __fastcall fGetExeFileSize(const tString &casFolderPath) {  //".exe"
    tString asFilePath(asSearchFileEx(EXE_EXT, casFolderPath));
    if (true == asFilePath.IsEmpty()) {
        return 0.0;
    }

    unsigned long  ulFileSize = 0;
    FILE          *pFile      = fopen(asFilePath.c_str(), "r+t");
    /*DEBUG*/xASSERT(NULL != pFile);
    if (NULL == pFile) {
        return 0.0;
    }

    __try {
        fseek(pFile, 0, SEEK_END);
        ulFileSize = ftell(pFile);
        fseek(pFile, 0, SEEK_SET);
    } __finally {
        /*DEBUG*/xASSERT(NULL != pFile);
        if (NULL != pFile) {
            fclose(pFile);  pFile = NULL;
        }
    }      

    return RoundTo((ulFileSize / 1000), 0);
}
//---------------------------------------------------------------------------


