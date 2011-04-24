/**********************************************************************
*   для перетаскивания
*
***********************************************************************/

extern TStringList* pList;

void __fastcall WmDropFiles(TWMDropFiles &Message) {
    //--- Предварительно ---
    staInfo->SimpleText = "";
    //--- Предварительно ---

	char cPath[256];
	HDROP hDrop = (HDROP)Message.Drop;
	int iFiles = DragQueryFile(hDrop, -1, NULL, NULL);	//количество файлов,

	//ведь можно перетаскивать один файл, а можно сразу несколько.
	for (int i = 0; i < iFiles; i ++) {
		DragQueryFile(hDrop, i, cPath, sizeof(cPath));
        pList->Add(cPath);  //полное имя перетсакиваемого на форму файла (включая путь)
	}
	DragFinish(hDrop);

    btnStart->Click();
    ////btnTest->Click();
}
