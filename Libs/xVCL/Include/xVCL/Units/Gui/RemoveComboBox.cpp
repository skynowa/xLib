/***********************************************************************
*	Удалить текстовое поле, если оно есть
*
************************************************************************/

void __fastcall RemoveComboBox() {
    if (edtFromTo_lvwDicFiles) {
		delete edtFromTo_lvwDicFiles;
    }
    edtFromTo_lvwDicFiles = NULL;
}
