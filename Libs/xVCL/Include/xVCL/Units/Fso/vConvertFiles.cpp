/**********************************************************************
*   конвертим файл (принимаем файл)   
*
***********************************************************************/


//---------------------------------------------------------------------------
void __fastcall vConvertFiles(const tString &casFilePath) {
    Application->ProcessMessages();

    //для останова
    if (iFlagStop == 1) {
        btnStop->Visible = false;
        return;
    }

    gauProgress->Progress ++;
    staInfo->SimpleText = "Файл:  " + MinimizeName(casFilePath, staInfo->Canvas, 180);

    bool bRes = bConvertHtmlToText(CppWebBrowser1, casFilePath, ChangeFileExt(casFilePath, ".txt"), true); //конвертим
    if (bRes == false) {
        MessageBox(0, ("Не могу конвертировать файл:\n" + casFilePath).c_str(), Application->Title.c_str(), MB_OK + MB_ICONSTOP);
    }

////    bool bRes = bExtractHtmlCode(CppWebBrowser1, casFilePath, ChangeFileExt(casFilePath, ".txt"), true); //конвертим
////    if (bRes == false) {
////        MessageBox(0, ("Не могу конвертировать файл:\n" + casFilePath).c_str(), Application->Title.c_str(), MB_OK + MB_ICONSTOP);
////    }
}
//---------------------------------------------------------------------------
