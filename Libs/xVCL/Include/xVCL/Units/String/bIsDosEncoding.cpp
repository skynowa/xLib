/**********************************************************************
*   DOS ли кодировка?
*
***********************************************************************/

bool bIsDosEncoding(const tString &csFilePath) {
    //Читаем файл
    TStringList* pList = new TStringList;
    pList->LoadFromFile(csFilePath);
    tString asFile = pList->Text;    //храним весь файл
    delete pList;

    tString asDosChars = "‰–“Љ…Ќѓ™‡•љ”›‚ЂЏђЋ‹„†ќџ—‘Њ€’њЃћ©ЄҐ­Ј§ў Ї®«¤Ў";    //ДОС-овские символы
    int iCountSovpadeniya = 0;   //кол-во совпадений
    int iMaxSovpadeniy    = asFile.Length() / (1000 * 6); //макс. число совпадений (если больше, то текст - ДОС)
    int iZoom             = 1;   //во сколько раз уменьшаем объём поиска

    for (int i = 1; i <= asDosChars.Length(); i ++) {    Application->ProcessMessages();
        for (int j = 1; j < asFile.Length() / iZoom; j ++) {    Application->ProcessMessages();
            if (asFile[j] == asDosChars[i]) {
                iCountSovpadeniya ++;
                if (iCountSovpadeniya > iMaxSovpadeniy) {
                    return true;
                }
            }
        }
    }
    return false;
}
