/*********************************************************************************************************
*	Находим следующею свободную букву диска
*
**********************************************************************************************************/


tString __fastcall GetNextFreeDriveLetter() {
	DWORD dwNextFreeDriveLetter = GetLogicalDrives();    //функция возвращает битовую маску
	for (int i = 0; i < 26; i ++) {                   	 //проходимся циклом по битам
		int n = (dwNextFreeDriveLetter >> i) & 1;    	 //узнаём значение текущего бита
		tString asDriveLetter = (char)(65 + i);   	 //получаем литеру диска
		if (n) {
			//если единица - диск с номером i есть
			//tString path = tString((char)(65+i)) + ":\\";
			//tString out = "Диск " + DriveLetter + "\n";
			//ShowMessage(out);
		} else {
			if (asDriveLetter > 'B') {
				return asDriveLetter;
			}
		}
	}
    return 0;
}

