/**********************************************************************
*   для перетаскивания
*
***********************************************************************/


//---------------------------------------------------------------------------
void __fastcall vWmDropFiles(TWMDropFiles &Message) {
    //--- Предварительно ---
    staInfo->SimpleText = "";
    //--- Предварительно ---

	char szPath[256];   memset(szPath, 0, sizeof(szPath));
	HDROP hDrop = (HDROP)Message.Drop;
	int  iFiles = DragQueryFile(hDrop, -1, NULL, NULL);	//количество файлов,

	//ведь можно перетаскивать один файл, а можно сразу несколько.
	for (int i = 0; i < iFiles; i ++) {
		DragQueryFile(hDrop, i, szPath, sizeof(szPath));
        pList->Add(szPath);  //полное имя перетсакиваемого на форму файла (включая путь)
	}
	DragFinish(hDrop);

    btnStart->Click();
}
//---------------------------------------------------------------------------
