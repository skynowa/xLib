/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::ChangeKeyboardLang(const tString &asLangName) {
	tString asLangID = ""; 	///LANG_UKRANIAN
	
    if (asLangName == "Английская")  {asLangID = IntToHex(MAKELANGID(LANG_ENGLISH,    SUBLANG_DEFAULT), 8);}
    if (asLangName == "Русская")     {asLangID = IntToHex(MAKELANGID(LANG_RUSSIAN,    SUBLANG_DEFAULT), 8);}
    if (asLangName == "Вьетнамская") {asLangID = IntToHex(MAKELANGID(LANG_VIETNAMESE, SUBLANG_DEFAULT), 8);}
    if (asLangName == "Немецкая")    {asLangID = IntToHex(MAKELANGID(LANG_GERMAN,     SUBLANG_DEFAULT), 8);}
    ////if (asLangName == "Украинская")  {asLangID = IntToHex(MAKELANGID(LANG_UKRANIAN,   SUBLANG_DEFAULT), 8);}
    if (asLangName == "Африканская") {asLangID = IntToHex(MAKELANGID(LANG_AFRIKAANS,  SUBLANG_DEFAULT), 8);}
    if (asLangName == "Китайская")   {asLangID = IntToHex(MAKELANGID(LANG_CHINESE,    SUBLANG_DEFAULT), 8);}
    if (asLangName == "Чешская")     {asLangID = IntToHex(MAKELANGID(LANG_CZECH,      SUBLANG_DEFAULT), 8);}
    if (asLangName == "Эстонская")   {asLangID = IntToHex(MAKELANGID(LANG_ESTONIAN,   SUBLANG_DEFAULT), 8);}
    if (asLangName == "Грецкая")     {asLangID = IntToHex(MAKELANGID(LANG_FRENCH,     SUBLANG_DEFAULT), 8);}
    if (asLangName == "Итальянская") {asLangID = IntToHex(MAKELANGID(LANG_ITALIAN,    SUBLANG_DEFAULT), 8);}
    if (asLangName == "Японская")    {asLangID = IntToHex(MAKELANGID(LANG_JAPANESE,   SUBLANG_DEFAULT), 8);}
    if (asLangName == "Корейская")   {asLangID = IntToHex(MAKELANGID(LANG_KOREAN,     SUBLANG_DEFAULT), 8);}
    if (asLangName == "Латвийская")  {asLangID = IntToHex(MAKELANGID(LANG_LATVIAN,    SUBLANG_DEFAULT), 8);}
    if (asLangName == "Польская")    {asLangID = IntToHex(MAKELANGID(LANG_POLISH,     SUBLANG_DEFAULT), 8);}
    if (asLangName == "Турецкая")    {asLangID = IntToHex(MAKELANGID(LANG_TURKISH,    SUBLANG_DEFAULT), 8);}
    if (asLangName == "Вьетнамская") {asLangID = IntToHex(MAKELANGID(LANG_VIETNAMESE, SUBLANG_DEFAULT), 8);}

    ActivateKeyboardLayout(LoadKeyboardLayout(asLangID.c_str(), 0), 0);
}
