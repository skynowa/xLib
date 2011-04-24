/***********************************************************************
*	Найти общее кол-во строк в файле
*
************************************************************************/


#include  <stdio.h>

long __fastcall GetDicFileAllLines(const tString &asFilePath) {
    FILE *pFile;
    if ((pFile = fopen(asFilePath.c_str(), "r+t")) == NULL){
        MessageBox(NULL, ("File: " + asFilePath + " can't open.").c_str(), "LAN Hack++", 0 | 16 | 0 | 0 | 262144);
        return false;
    }

    long lLines = 0;   //счётчик строк
    char cBuff[80];
    do {
        Application->ProcessMessages();
        lLines ++;
        fgets(cBuff, 80, pFile);        //ShowMessage(cBuff);
        if (feof(pFile)) {
            break;
        }
    } while(true);
    fclose(pFile);
    return lLines;
}
