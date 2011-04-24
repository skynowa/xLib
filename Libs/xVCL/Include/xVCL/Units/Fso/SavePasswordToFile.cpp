/***********************************************************************
*	Сохраняем результаты в файл
*
************************************************************************/

void __fastcall SavePasswordToFile(const tString &asHost, const tString &asShare, const tString &asUser, const tString &asPassword) {
    FILE *pFileSavePassword;
    if ((pFileSavePassword = fopen((asHost + ".txt").c_str(), "wt")) == NULL) {
        MessageBox(NULL, ("File: " + asHost + ".txt" + " - can't create.").c_str(), "LAN Hack++", 0 | 16 | 0 | 0 | 262144);
    } else {
        fprintf(pFileSavePassword, ("Path:\t\\\\" + asHost + "\\" + asShare + '\n').c_str());
        fprintf(pFileSavePassword, ("User:\t"     + asUser + '\n').c_str());
        fprintf(pFileSavePassword, ("Pass:\t"     + asPassword + '\n').c_str());
        //fprintf(pFileSavePassword, ("Date:\t" + DateToStr(Date() + '\n').c_str()));
        fclose(pFileSavePassword);
    }
}