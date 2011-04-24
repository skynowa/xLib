/***********************************************************************
*	Найти общее кол-во строк в файле
*
************************************************************************/


#include  <stdio.h>

//---------------------------------------------------------------------------
u_long __fastcall ulGetDicFileAllLines(const std::string &sFilePath) {
    FILE *pFile;
    if ((pFile = fopen(sFilePath.c_str(), "r+t")) == NULL){
        MessageBox(0, ("File: " + sFilePath + " can't open.").c_str(), APP_NAME, MB_OK + MB_ICONSTOP);
        return false;
    }

    u_long ulLines = 0;   //счётчик строк
    char cBuff[80];
    do {
        Application->ProcessMessages();
        ulLines ++;
        fgets(cBuff, 80, pFile);        //ShowMessage(cBuff);
        if (feof(pFile)) {
            break;
        }
    } while(true);
    fclose(pFile);
    return ulLines;
}
//---------------------------------------------------------------------------
