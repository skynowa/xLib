/***********************************************************************
*	Регистрируем горячую клавишу (скрыть/показать форму)
*
************************************************************************/


bool __fastcall RegHotKey(THotKey *pHK, TShortCut HotKey) {
    WORD        wKey;
    TShiftState ShiftState;
    Cardinal    Modifiers = 0;

    //снимаем регистрацию прежнего сочетания
    //UnregisterHotKey(Handle, 0);

    //раскладываем сочетание, полученное в hkyHideShow на составляющие
    //саму клавишу, и статус клавиш Shift и Ctrl:
    ShortCutToKey(pHK->HotKey, wKey, ShiftState);


    //если нет hkyHideShow буквы
    if (wKey == 0) {
        return false;
    }

    //если Alt нажат, добавляем в модификаторы значение MOD_ALT
    if (ShiftState.Contains(ssAlt)) {
        Modifiers = Modifiers | MOD_ALT;
    }

    //если Shift нажат, добавляем в модификаторы значение MOD_SHIFT
    if (ShiftState.Contains(ssShift)) {
        Modifiers = Modifiers | MOD_SHIFT;
    }

    //если Ctrl нажат, добавляем в модификаторы значение MOD_CONTROL
    if (ShiftState.Contains(ssCtrl)) {
        Modifiers = Modifiers | MOD_CONTROL;
    }

    //регистрируем новое сочетание клавиш:
    return RegisterHotKey(Handle, wKey, Modifiers, wKey);
}
